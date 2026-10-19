// FTEBroom commands operate on the csaddon history and selection model.
float() ftebroom_command =
{
    if (argv(0) != "ftebroom_box") return FALSE;
    if (argv(6) == "") { print("Usage: ftebroom_box x y z width depth height\n"); return TRUE; }
    vector center = [stof(argv(1)), stof(argv(2)), stof(argv(3))];
    vector size = [stof(argv(4)), stof(argv(5)), stof(argv(6))];
    for (int i = 0; i < 3; i++)
        if (!(size[i] >= 1 && size[i] <= 8192 && fabs(center[i]) <= 16384))
        { print("FTEBroom: invalid box dimensions or position.\n"); return TRUE; }
    static brushface_t faces[6];
    static const vector normals[6] = {'-1 0 0','0 -1 0','0 0 -1','1 0 0','0 1 0','0 0 1'};
    for (int i = 0; i < 6; i++)
    {
        faces[i].planenormal = normals[i];
        faces[i].planedist = center * normals[i] + size[i % 3] * 0.5;
        faces[i].shadername = autocvar_ca_newbrushtexture;
        reset_texturecoords(&faces[i]);
    }
    brush_deselectall();
    int id = brush_history_create(selectedbrushmodel, faces, 6, CONTENTBIT_SOLID, TRUE);
    print(sprintf("FTEBroom: created brush %i.\n", id));
    return TRUE;
};
