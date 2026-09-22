@echo off
REM STB Active Effects - build script.
REM Uses alandtse CommonLibSSE-NG (ng branch), which supports Skyrim 1.7.104.
REM VCPKG_ROOT should point at the vcpkg checkout (defaults to E:\vcpkg).

if not defined VCPKG_ROOT set "VCPKG_ROOT=E:\vcpkg"
if not defined COMMONLIBSSE_PATH set "COMMONLIBSSE_PATH=E:\CommonLibSSE-NG-alandtse"

cmake -B build -S . -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake ^
  -DVCPKG_TARGET_TRIPLET=x64-windows-static-md ^
  -DVCPKG_ROOT=%VCPKG_ROOT% ^
  -DCOMMONLIBSSE_PATH=%COMMONLIBSSE_PATH% ^
  -DCOPY_BUILD=OFF
cmake --build build --config Release --parallel
pause
