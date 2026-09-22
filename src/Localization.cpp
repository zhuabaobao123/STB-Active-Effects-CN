#include "Localization.h"

#include <fstream>
#include <map>
#include <mutex>

#include "nlohmann/json.hpp"

namespace
{
	std::map<std::string, std::string>& GetTable()
	{
		static std::map<std::string, std::string> table;
		return table;
	}

	std::mutex& GetMutex()
	{
		static std::mutex mutex;
		return mutex;
	}
}

void Localization::Load()
{
	const std::scoped_lock lock(GetMutex());
	auto& table = GetTable();
	table.clear();

	std::ifstream ifs(kFile);
	if (!ifs.is_open()) {
		logger::info("Localization file not found, using English: {}", kFile);
		return;
	}

	try {
		const auto data = nlohmann::json::parse(ifs);
		if (!data.is_object()) {
			logger::warn("Localization file is not an object, using English: {}", kFile);
			return;
		}
		for (const auto& [key, value] : data.items()) {
			if (value.is_string()) {
				table.emplace(key, value.get<std::string>());
			}
		}
		logger::info("Loaded {} translations from {}", table.size(), kFile);
	} catch (const std::exception& e) {
		table.clear();
		logger::warn("Failed to parse {}, using English ({})", kFile, e.what());
	}
}

const char* Localization::Translate(const char* a_english)
{
	if (!a_english) {
		return "";
	}
	const std::scoped_lock lock(GetMutex());
	const auto& table = GetTable();
	const auto it = table.find(a_english);
	return it != table.end() ? it->second.c_str() : a_english;
}
