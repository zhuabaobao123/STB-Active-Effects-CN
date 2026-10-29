# STB Active Effects Translations

**Localized fork** of [STB Active Effects](https://github.com/STB-Team/STB-Active-Effects) —
a customizable SKSE active-effects HUD widget for Skyrim Special Edition /
Anniversary Edition.

This fork adds an external JSON translation layer and rebuilds against the
**ng** branch of [CommonLibSSE-NG](https://github.com/alandtse/CommonLibSSE-NG)
so the plugin works on **Skyrim 1.7.104** (Address Library v13).

## What changed in this fork

- `src/Localization.h`, `src/Localization.cpp` — translations are read at runtime
  from `Data/SKSE/Plugins/STB_ActiveEffects.json` (flat `{"English": "..."}`
  map). The DLL keeps the English source strings; delete the JSON to revert to
  English, edit it to change any label — no rebuild needed.
- Every SKSE Menu Framework string is wrapped with `_T()`, including the section
  title.
- Eight translation files ship in the repo / release:
  `STB_ActiveEffects_{en,ru,ja,ko,fr,de,es,zh-Hans}.json`.
- Built with `add_commonlibsse_plugin()` (auto-generated `SKSEPlugin_Version` /
  `SKSEPlugin_Query`) instead of the hand-written exports.
- API adaptations for CommonLibSSE-NG 9.x: `PlayerCamera::IsCurrentState()`,
  local `ActorValueToString` renamed to `AVToString` (it collides with
  `RE::ActorValueToString`).

## Requirements

- **Visual Studio 2022** (or newer) with the *Desktop development with C++* workload.
- **CMake** >= 3.21.
- **vcpkg** — set `VCPKG_ROOT` (or pass it via CMake).
- **CommonLibSSE-NG (ng branch)** checkout; this fork does **not** vendor it.
  Point `COMMONLIBSSE_PATH` at your checkout.

vcpkg dependencies are installed automatically from `vcpkg.json`.

## Building

```sh
git clone https://github.com/zhuabaobao123/STB-Active-Effects-CN.git
cd STB-Active-Effects-CN

set COMMONLIBSSE_PATH=E:\CommonLibSSE-NG-alandtse
set VCPKG_ROOT=E:\vcpkg
gen.bat
```

or manually:

```sh
cmake -B build -S . -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake ^
  -DVCPKG_TARGET_TRIPLET=x64-windows-static-md ^
  -DCOMMONLIBSSE_PATH=%COMMONLIBSSE_PATH% ^
  -DCOPY_BUILD=OFF
cmake --build build --config Release --parallel
```

Output: `build/Release/STB_ActiveEffects.dll`.

## Installing

This fork is distributed as a FOMOD: pick **one** language, and load the
resulting mod **after** the original `STB Active Effects` mod.

Requirements: SKSE64, Address Library for SKSE Plugins **v13** (includes
1.7.104), SKSE Menu Framework.

## License

This work — including the compiled `STB_ActiveEffects.dll` — is licensed under
the **GNU General Public License v3.0 or later (GPL-3.0-or-later)**, because the
DLL links against CommonLibSSE-NG, which is GPL-3.0-or-later.

- Full, unmodified GPL-3.0 text: [`LICENSE.txt`](LICENSE.txt) (copy: `COPYING.txt`)
- Additional permissions (Modding Exception / Linking Exception): [`EXCEPTIONS.md`](EXCEPTIONS.md)
- Official license page: <https://www.gnu.org/licenses/gpl-3.0.html>

### Upstream credits

- **STB Active Effects** (c) STB Team — MIT License (see [`LICENSE`](LICENSE)) —
  <https://github.com/STB-Team/STB-Active-Effects>
- **CommonLibSSE-NG** (c) alandtse / CharmedBaryon — GPL-3.0-or-later —
  <https://github.com/alandtse/CommonLibSSE-NG>
- **SKSE Menu Framework** (c) Thiago099 / QTR-Modding — LGPL-2.1
- **SkyUI** icons (c) SkyUI Team

### Disclaimer

This program is distributed in the hope that it will be useful, but **WITHOUT
ANY WARRANTY**; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

This mod is not affiliated with or endorsed by Bethesda Softworks. The Elder
Scrolls and Skyrim are trademarks of ZeniMax Media Inc.
