param([Parameter(Mandatory=$true)][string]$Bundle)
$ErrorActionPreference = 'Stop'
$source = (Resolve-Path $Bundle).Path
$test = Join-Path ([IO.Path]::GetTempPath()) ('FTEBroom-smoke-' + [guid]::NewGuid())
Copy-Item -LiteralPath $source -Destination $test -Recurse
@'
exec ftebroom.cfg
in 7 ftebroom_box 0 0 64 128 128 128
in 8 mod_terrain_save "" smoke_created
in 9 brushedit_undo
in 10 mod_terrain_save "" smoke_undo
in 11 brushedit_redo
in 12 mod_terrain_save "" smoke_redo
in 13 ftebroom_box 0 0 0 -1 128 128
in 14 mod_terrain_save "" smoke_invalid
in 15 screenshot smoke-panel.png
in 16 mapedit maps/smoke_redo.map
in 21 mod_terrain_save "" smoke_reopened
in 22 quit
'@ | Set-Content "$test/ftebroom/smoke.cfg"
$process = Start-Process "$test/fteqw64.exe" -ArgumentList @('-nohome','-basedir',('"'+$test+'"'),'-window','-width','1280','-height','800','-condebug','+exec','smoke.cfg') -WorkingDirectory $test -WindowStyle Hidden -PassThru
if (!$process.WaitForExit(45000)) {
    Stop-Process -Id $process.Id
    throw "Smoke test timed out. Logs retained at $test"
}
if ($process.ExitCode -ne 0) { throw "Engine exited with code $($process.ExitCode); logs: $test" }
if (!(Test-Path "$test/ftebroom/smoke-panel.png")) { throw "Missing engine screenshot: $test" }
function Planes([string]$Name) {
    $file = "$test/ftebroom/maps/$Name.map"
    if (!(Test-Path $file)) { throw "Missing export: $file" }
    return @(Get-Content $file | Where-Object { $_ -match '^\( ' } | Sort-Object)
}
$created = Planes 'smoke_created'
$undo = Planes 'smoke_undo'
if ($created.Count -ne 12 -or $undo.Count -ne 6) { throw "Unexpected plane counts: created=$($created.Count), undo=$($undo.Count)" }
foreach ($other in @('smoke_redo','smoke_invalid','smoke_reopened')) {
    if (Compare-Object $created (Planes $other)) { throw "Geometry differs: $other" }
}
$log = Get-Content "$test/ftebroom/qconsole.log" -Raw
if ($log -notmatch 'Dear ImGui renderer initialized \(atlas [1-9]' -or $log -notmatch 'invalid box dimensions') { throw 'Missing expected native/QC diagnostics' }
Write-Host "PASS: create/undo/redo, invalid dimensions and MAP reload preserve expected planes. Screenshot and logs: $test"

