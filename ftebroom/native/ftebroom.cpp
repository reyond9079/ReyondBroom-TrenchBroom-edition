// SPDX-License-Identifier: GPL-2.0-or-later
// FTEBroom: Dear ImGui frontend for FTE's native csaddon brush editor.
#include <cstdint>
#define VARGS __cdecl
typedef int uploadfmt_t;
typedef int clipboardtype_t;
typedef struct qdownload_s qdownload_t;
typedef struct downloadlist_s downloadlist_t;
enum dlfailreason_e : int;
enum com_tokentype_e : int;
enum fs_relative : int;
#include "imgui.h"
#include "plugin.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <vector>

static plugcorefuncs_t* core;
static plugcmdfuncs_t* commands;
static plugcvarfuncs_t* cvars;
static plug2dfuncs_t* draw;
static pluginputfuncs_t* input;
static qhandle_t atlas;
static quintptr_t lastTime;
static int mouseKeys[5], wheelUp, wheelDown;
static bool ready;
static void command(const char* text)
{
  commands->AddText(text, qfalse);
}

struct Vertex
{
  float x, y, u, v, r, g, b, a;
};
static Vertex lerp(const Vertex& a, const Vertex& b, float t)
{
  return {
    a.x + (b.x - a.x) * t,
    a.y + (b.y - a.y) * t,
    a.u + (b.u - a.u) * t,
    a.v + (b.v - a.v) * t,
    a.r + (b.r - a.r) * t,
    a.g + (b.g - a.g) * t,
    a.b + (b.b - a.b) * t,
    a.a + (b.a - a.a) * t};
}
// Clip triangles before submitting them as degenerate quads to FTE's batched 2D API.
static void triangle(std::vector<Vertex> polygon, const ImVec4& clip, qhandle_t image)
{
  for (int edge = 0; edge < 4 && !polygon.empty(); ++edge)
  {
    auto distance = [&](const Vertex& p) {
      return edge == 0   ? p.x - clip.x
             : edge == 1 ? clip.z - p.x
             : edge == 2 ? p.y - clip.y
                         : clip.w - p.y;
    };
    std::vector<Vertex> result;
    Vertex previous = polygon.back();
    float pd = distance(previous);
    for (auto current : polygon)
    {
      float cd = distance(current);
      if ((cd >= 0) != (pd >= 0))
        result.push_back(lerp(previous, current, pd / (pd - cd)));
      if (cd >= 0)
        result.push_back(current);
      previous = current;
      pd = cd;
    }
    polygon = std::move(result);
  }
  for (size_t i = 1; i + 1 < polygon.size(); ++i)
  {
    Vertex p[4] = {polygon[0], polygon[i], polygon[i + 1], polygon[i + 1]};
    vec2_t xy[4], uv[4];
    vec4_t color[4];
    for (int j = 0; j < 4; ++j)
    {
      xy[j][0] = p[j].x;
      xy[j][1] = p[j].y;
      uv[j][0] = p[j].u;
      uv[j][1] = p[j].v;
      color[j][0] = p[j].r;
      color[j][1] = p[j].g;
      color[j][2] = p[j].b;
      color[j][3] = p[j].a;
    }
    draw->Image2dQuad(xy, uv, color, image);
  }
}
static void render()
{
  ImGui::Render();
  auto data = ImGui::GetDrawData();
  draw->Colour4f(1, 1, 1, 1);
  for (int n = 0; n < data->CmdListsCount; ++n)
  {
    auto list = data->CmdLists[n];
    for (auto& cmd : list->CmdBuffer)
    {
      if (cmd.UserCallback)
      {
        if (cmd.UserCallback != ImDrawCallback_ResetRenderState)
          cmd.UserCallback(list, &cmd);
        continue;
      }
      for (unsigned int i = 0; i + 2 < cmd.ElemCount; i += 3)
      {
        std::vector<Vertex> p;
        for (int j = 0; j < 3; ++j)
        {
          auto& v =
            list->VtxBuffer[list->IdxBuffer[cmd.IdxOffset + i + j] + cmd.VtxOffset];
          auto c = ImGui::ColorConvertU32ToFloat4(v.col);
          p.push_back({v.pos.x, v.pos.y, v.uv.x, v.uv.y, c.x, c.y, c.z, c.w});
        }
        triangle(std::move(p), cmd.ClipRect, (qhandle_t)cmd.GetTexID());
      }
    }
  }
}
static void initialize()
{
  if (ready)
    return;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  auto& io = ImGui::GetIO();
  io.IniFilename = nullptr;
  io.LogFilename = nullptr;
  io.BackendRendererName = "FTE native 2D";
  io.BackendPlatformName = "FTE MenuEvent";
  io.Fonts->AddFontDefault();
  unsigned char* pixels;
  int w, h;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &w, &h);
  std::vector<unsigned char> tga(18 + w * h * 4, 0);
  tga[2] = 2;
  tga[12] = w & 255;
  tga[13] = w >> 8;
  tga[14] = h & 255;
  tga[15] = h >> 8;
  tga[16] = 32;
  tga[17] = 0x28;
  for (int i = 0; i < w * h; ++i)
  {
    tga[18 + i * 4] = pixels[i * 4 + 2];
    tga[19 + i * 4] = pixels[i * 4 + 1];
    tga[20 + i * 4] = pixels[i * 4];
    tga[21 + i * 4] = pixels[i * 4 + 3];
  }
  atlas = draw->LoadImageData("ftebroom/font.tga", "image/tga", tga.data(), tga.size());
  atlas = draw->LoadImage("ftebroom/font.tga");
  io.Fonts->SetTexID((ImTextureID)atlas);
  ready = true;
  char status[96];
  std::snprintf(
    status,
    sizeof status,
    "FTEBroom: Dear ImGui renderer initialized (atlas %i).\n",
    (int)atlas);
  core->Print(status);
}
static bool safeName(const char* name)
{
  if (!*name)
    return false;
  for (auto p = name; *p; ++p)
    if (!((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9')
          || *p == '_' || *p == '-'))
      return false;
  return true;
}
static void panel(float w, float h)
{
  auto& io = ImGui::GetIO();
  io.DisplaySize = {w, h};
  auto now = core->GetMilliseconds();
  io.DeltaTime = lastTime ? std::max(.001f, (now - lastTime) / 1000.f) : 1.f / 60;
  lastTime = now;
  ImGui::NewFrame();
  ImGui::SetNextWindowPos({12, 12}, ImGuiCond_Once);
  ImGui::SetNextWindowSize({390, 610}, ImGuiCond_Once);
  ImGui::Begin("FTEBroom | Prototype 0.1", nullptr, ImGuiWindowFlags_NoCollapse);
  ImGui::TextWrapped("Native FTE rendering + csaddon geometry + Dear ImGui");
  if (ImGui::Button("Edit scene (F1 returns here)"))
    input->SetMenuFocus(qfalse, nullptr, 0, 0, 0);
  ImGui::Separator();
  if (ImGui::Button("Undo"))
    command("brushedit_undo\n");
  ImGui::SameLine();
  if (ImGui::Button("Redo"))
    command("brushedit_redo\n");
  ImGui::SameLine();
  if (ImGui::Button("Delete selection"))
    command("brushedit_delete\n");
  static float origin[3] = {0, 0, 64}, size[3] = {128, 128, 128};
  ImGui::InputFloat3("Centre", origin);
  ImGui::InputFloat3("Size", size);
  if (ImGui::Button("Create box"))
  {
    char b[256];
    std::snprintf(
      b,
      sizeof b,
      "ftebroom_box %g %g %g %g %g %g\n",
      origin[0],
      origin[1],
      origin[2],
      size[0],
      size[1],
      size[2]);
    command(b);
  }
  int grid = (int)cvars->GetFloat("ca_grid");
  if (ImGui::SliderInt("Grid", &grid, 1, 128))
    cvars->SetFloat("ca_grid", grid);
  int view = (int)cvars->GetFloat("ca_brush_view");
  if (ImGui::Combo("View", &view, "Perspective\0X\0Y\0Z\0"))
    cvars->SetFloat("ca_brush_view", view);
  static char material[128] = "ftebroom/grid";
  ImGui::InputText("Material", material, sizeof material);
  if (ImGui::Button("Use for new brushes"))
    cvars->SetString("ca_newbrushtexture", material);
  if (ImGui::Button("Slice tool"))
  {
    command("brushedit_slice\n");
    input->SetMenuFocus(qfalse, nullptr, 0, 0, 0);
  }
  ImGui::SameLine();
  if (ImGui::Button("Subtract"))
    command("brushedit_subtract\n");
  ImGui::Separator();
  static char name[64] = "my_map";
  ImGui::InputText("Map name", name, sizeof name);
  ImGui::BeginDisabled(!safeName(name));
  if (ImGui::Button("Save as .map"))
    ImGui::OpenPopup("Confirm save");
  ImGui::SameLine();
  if (ImGui::Button("Open .map"))
    ImGui::OpenPopup("Confirm open");
  ImGui::EndDisabled();
  if (ImGui::BeginPopupModal("Confirm save", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
  {
    ImGui::Text("Write maps/%s.map? Existing file will be replaced.", name);
    if (ImGui::Button("Save"))
    {
      char b[160];
      std::snprintf(b, sizeof b, "mod_terrain_save \"\" %s\n", name);
      command(b);
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel"))
      ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
  }
  if (ImGui::BeginPopupModal("Confirm open", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
  {
    ImGui::Text("Open maps/%s.map and discard unsaved changes?", name);
    if (ImGui::Button("Open"))
    {
      char b[160];
      std::snprintf(b, sizeof b, "mapedit maps/%s.map\n", name);
      command(b);
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel"))
      ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
  }
  ImGui::TextWrapped(
    "Save writes maps/<name>.map in the writable game folder. Existing files are "
    "overwritten. Open discards unsaved changes. Use copies of your maps.");
  ImGui::Separator();
  ImGui::TextWrapped(
    "Scene: click to select; RMB to look; WASD to move. Ctrl+Z/Y: history. F1: this "
    "panel. Advanced ReyondBroom tools are not implemented yet.");
  ImGui::End();
  render();
}
static qboolean QDECL
event(int type, int key, int unicode, float x, float y, float w, float h)
{
  initialize();
  auto& io = ImGui::GetIO();
  io.AddMousePosEvent(x, y);
  if (type == 0)
    panel(w, h);
  if (type == 1 || type == 2)
  {
    bool down = type == 1;
    for (int i = 0; i < 5; ++i)
      if (key == mouseKeys[i])
        io.AddMouseButtonEvent(i, down);
    if (down && key == wheelUp)
      io.AddMouseWheelEvent(0, 1);
    if (down && key == wheelDown)
      io.AddMouseWheelEvent(0, -1);
    struct Key
    {
      const char* name;
      ImGuiKey code;
    };
    static const Key keys[] = {
      {"backspace", ImGuiKey_Backspace},
      {"enter", ImGuiKey_Enter},
      {"tab", ImGuiKey_Tab},
      {"del", ImGuiKey_Delete},
      {"leftarrow", ImGuiKey_LeftArrow},
      {"rightarrow", ImGuiKey_RightArrow},
      {"home", ImGuiKey_Home},
      {"end", ImGuiKey_End},
      {"ctrl", ImGuiMod_Ctrl},
      {"shift", ImGuiMod_Shift},
      {"a", ImGuiKey_A},
      {"c", ImGuiKey_C},
      {"v", ImGuiKey_V},
      {"x", ImGuiKey_X},
      {"z", ImGuiKey_Z},
      {"y", ImGuiKey_Y}};
    for (auto k : keys)
      if (key == input->GetKeyCode(k.name, nullptr))
        io.AddKeyEvent(k.code, down);
    if (down && unicode >= 32)
      io.AddInputCharacter((unsigned int)unicode);
    if (
      down
      && (key == input->GetKeyCode("escape", nullptr) || key == input->GetKeyCode("f1", nullptr)))
      input->SetMenuFocus(qfalse, nullptr, 0, 0, 0);
  }
  return qtrue;
}
static void openPanel()
{
  input->SetMenuFocus(qtrue, "", 0, 0, 1);
}
static void shutdown()
{
  if (ready)
  {
    ImGui::DestroyContext();
    draw->UnloadImage(atlas);
    ready = false;
  }
}
extern "C" qboolean NATIVEEXPORT FTEPlug_Init(plugcorefuncs_t* api)
{
  core = api;
  commands =
    (plugcmdfuncs_t*)core->GetEngineInterface(plugcmdfuncs_name, sizeof(*commands));
  cvars = (plugcvarfuncs_t*)core->GetEngineInterface(plugcvarfuncs_name, sizeof(*cvars));
  draw = (plug2dfuncs_t*)core->GetEngineInterface(plug2dfuncs_name, sizeof(*draw));
  input =
    (pluginputfuncs_t*)core->GetEngineInterface(pluginputfuncs_name, sizeof(*input));
  if (!commands || !cvars || !draw || !input)
  {
    core->Print("FTEBroom: incompatible FTE plugin API.\n");
    return qfalse;
  }
  for (int i = 0; i < 5; ++i)
  {
    char name[16];
    std::snprintf(name, sizeof name, "mouse%d", i + 1);
    mouseKeys[i] = input->GetKeyCode(name, nullptr);
  }
  wheelUp = input->GetKeyCode("mwheelup", nullptr);
  wheelDown = input->GetKeyCode("mwheeldown", nullptr);
  core->ExportFunction("MenuEvent", (funcptr_t)event);
  core->ExportFunction("Shutdown", (funcptr_t)shutdown);
  commands->AddCommand("ftebroom", openPanel, "Open the FTEBroom editor panel.");
  core->Print("FTEBroom: native module loaded. Type ftebroom.\n");
  return qtrue;
}
