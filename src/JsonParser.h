#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "nlohmann/json.hpp"
#include "olcResourcePack.h"

#include <string>

class JsonParser
{
private:
	std::string mFilePath;
	std::string m_JsonString;
	nlohmann::json m_json;
public:
	JsonParser();
	JsonParser(const std::string& filepath);

	nlohmann::json& GetJSON();
	nlohmann::json& GetJSON(const std::string& key, int index = -1);
	
	int GetInt(const std::string& key, int index = -1);
	bool GetBool(const std::string& key, int index = -1);
	std::string GetString(const std::string& key, int index = -1);

	bool GetKeyPressed(const std::string& key);
	bool GetKeyUp(const std::string& key);
	bool GetKeyDown(const std::string& key);

	void SaveData();
private:
	std::string ReadFromFile(const std::string& filepath);
	void WriteToFile(const std::string& filepath);
	int GetKeyCode(const std::string& j_key);
};

#endif // JSONPARSER_H