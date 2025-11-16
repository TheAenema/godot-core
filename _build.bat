cd %~dp0
set PYTHONDONTWRITEBYTECODE=1
scons platform=windows target=editor arch=x86_64 debug_symbols=true optimize=size deprecated=false -j24
pause
