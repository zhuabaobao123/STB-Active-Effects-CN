#pragma once

#include <string>

// External-translation loader for the ImGui (SKSE Menu Framework) menu.
// The DLL keeps English source strings; translations live in an external
// flat JSON file: {"English source": "..."}. Deleting the JSON restores
// English. File name follows the DLL name: STB_ActiveEffects.json.
class Localization
{
public:
	Localization() = delete;

	// Load the translation table once at plugin load. A missing or broken
	// file silently falls back to English.
	static void Load();
	// Returns the translated text, or the English source when untranslated.
	static const char* Translate(const char* a_english);

	static constexpr const char* kFile = "Data/SKSE/Plugins/STB_ActiveEffects.json";
};

#define _T(s) Localization::Translate(s)
