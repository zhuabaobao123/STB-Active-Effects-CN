STB Active Effects Translations
===============================

SUMMARY
-------
A localized rebuild of STB Active Effects 2.x for Skyrim Special Edition /
Anniversary Edition. Menu strings are loaded from external JSON files; the
DLL itself keeps the English originals (delete the JSON to revert to English).

LICENSING
---------
This work is licensed under the GNU General Public License version 3 or later
(GPL-3.0-or-later), because the plugin DLL links against CommonLibSSE-NG,
which is GPL-3.0-or-later.

  * Full, unmodified GPL-3.0 license text: LICENSE.txt
    (identical copy: COPYING.txt)
  * Additional permissions (Modding Exception and Linking Exception):
    EXCEPTIONS.md
  * Official GPL-3.0 page: https://www.gnu.org/licenses/gpl-3.0.html

Upstream credits and their original licenses:
  * STB Active Effects (c) STB Team - MIT License (see file "LICENSE")
    https://github.com/STB-Team/STB-Active-Effects
  * CommonLibSSE-NG (c) alandtse / CharmedBaryon - GPL-3.0-or-later
    https://github.com/alandtse/CommonLibSSE-NG
  * SKSE Menu Framework (c) Thiago099 / QTR-Modding - LGPL-2.1
  * SkyUI icons (c) SkyUI Team

Localization fork modifications (c) 2026 zhuabaobao123:
  * src/Localization.h, src/Localization.cpp - external JSON translation layer
  * _T() wrapping of all SKSE Menu Framework strings (including section titles)
  * Eight translation files: STB_ActiveEffects_<lang>.json
    (en, ru, ja, ko, fr, de, es, zh-Hans)
  * Rebuilt against CommonLibSSE-NG (ng branch) for Skyrim 1.7.104 support

DISCLAIMER
----------
This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

This mod is not affiliated with or endorsed by Bethesda Softworks. The Elder
Scrolls and Skyrim are trademarks of ZeniMax Media Inc.

SOURCE CODE
-----------
The complete corresponding source code is included in the "source" folder of
this archive and is also publicly available at:

    https://github.com/zhuabaobao123/STB-Active-Effects-CN

BUILDING
--------
    cmake -B build -S . -A x64 ^
      -DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake ^
      -DVCPKG_TARGET_TRIPLET=x64-windows-static-md ^
      -DCOMMONLIBSSE_PATH=<path to alandtse/CommonLibSSE-NG (ng) checkout>
    cmake --build build --config Release

See gen.bat and CMakeLists.txt for details.

INSTALLATION
------------
Use a mod manager. This archive is a FOMOD: select exactly one language.
Load the resulting mod after the original "STB Active Effects" mod.

Requirements:
  * SKSE64
  * Address Library for SKSE Plugins v13 (includes 1.7.104)
  * SKSE Menu Framework
