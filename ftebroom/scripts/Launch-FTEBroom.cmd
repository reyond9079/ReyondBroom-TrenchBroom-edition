@echo off
cd /d "%~dp0"
start "FTEBroom" fteqw64.exe -nohome -basedir "%~dp0." -window -width 1280 -height 800 +exec ftebroom.cfg
