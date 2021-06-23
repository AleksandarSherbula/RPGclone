#include "JsonParser.h"
#include "Game.h"

#include <fstream>
#include <sstream>
#include <iomanip>

JsonParser::JsonParser()
{
}

JsonParser::JsonParser(const std::string& filepath)
{
    mFilePath = filepath;
	m_JsonString = ReadFromFile(mFilePath);
	m_json = nlohmann::json::parse(m_JsonString);
}

nlohmann::json& JsonParser::GetJSON()
{
	return m_json;
}

nlohmann::json& JsonParser::GetJSON(const std::string& key, int index)
{
    if (index < 0)
        return m_json[key];
    else
        return m_json[key][index];
}

int JsonParser::GetInt(const std::string& key, int index)
{
    if (index < 0)
	    return m_json[key].get<int>();
    else
        return m_json[key][index].get<int>();
}

bool JsonParser::GetBool(const std::string& key, int index)
{
    if (index < 0)
        return m_json[key].get<bool>();
    else
        return m_json[key][index].get<bool>();
}

std::string JsonParser::GetString(const std::string& key, int index)
{
    if (index < 0)
        return m_json[key].get<std::string>();
    else
        return m_json[key][index].get<std::string>();
}

bool JsonParser::GetKeyPressed(const std::string& key)
{
	for (int i = 0; i < m_json["Input"][key].size(); i++)
	{
		const std::string& strKeyCode = m_json["Input"][key][i].get<std::string>();

		if (game->GetKeyPressed(GetKeyCode(strKeyCode)))
		{
			return true;
		}
	}
	return false;
}

bool JsonParser::GetKeyUp(const std::string& key)
{
	for (int i = 0; i < m_json["Input"][key].size(); i++)
	{
		const std::string& strKeyCode = m_json["Input"][key][i].get<std::string>();

		if (game->GetKeyUp(GetKeyCode(strKeyCode)))
		{
			return true;
		}
	}
	return false;
}

bool JsonParser::GetKeyDown(const std::string& key)
{
	for (int i = 0; i < m_json["Input"][key].size(); i++)
	{
		const std::string& strKeyCode = m_json["Input"][key][i].get<std::string>();

		if (game->GetKeyDown(GetKeyCode(strKeyCode)))
		{
			return true;
		}
	}
	return false;
}

void JsonParser::SaveData()
{
	WriteToFile(mFilePath);
}

std::string JsonParser::ReadFromFile(const std::string& filepath)
{
	std::ifstream data(filepath, std::ios::in | std::ios::binary);

	std::stringstream ss;
	std::string line;

	while (getline(data, line))
	{
		if (line.find("//") == std::string::npos)
			ss << line;
	}

	return ss.str();
}

void JsonParser::WriteToFile(const std::string& filepath)
{
	std::ofstream data(filepath);

	data << std::setw(4) << m_json << std::endl;
	data.close();
}

int JsonParser::GetKeyCode(const std::string& j_key)
{
    if (j_key == "BACK")           return VK_BACK;
    if (j_key == "TAB")            return VK_TAB;
    if (j_key == "CLEAR")          return VK_CLEAR;
    if (j_key == "RETURN")         return VK_RETURN;
    if (j_key == "SHIFT")          return VK_SHIFT;
    if (j_key == "CONTROL")        return VK_CONTROL;
    if (j_key == "MENU")           return VK_MENU;
    if (j_key == "PAUSE")          return VK_PAUSE;
    if (j_key == "CAPITAL")        return VK_CAPITAL;
    if (j_key == "KANA")           return VK_KANA;
    if (j_key == "HANGEUL")        return VK_HANGEUL;
    if (j_key == "HANGUL")         return VK_HANGUL;
    if (j_key == "IME_ON")         return VK_IME_ON;
    if (j_key == "JUNJA")          return VK_JUNJA;
    if (j_key == "FINAL")          return VK_FINAL;
    if (j_key == "HANJA")          return VK_HANJA;
    if (j_key == "KANJI")          return VK_KANJI;
    if (j_key == "IME_OFF")        return VK_IME_OFF;
    if (j_key == "ESCAPE")         return VK_ESCAPE;
    if (j_key == "CONVERT")        return VK_CONVERT;
    if (j_key == "NONCONVERT")     return VK_NONCONVERT;
    if (j_key == "ACCEPT")         return VK_ACCEPT;
    if (j_key == "MODECHANGE")     return VK_MODECHANGE;
    if (j_key == "SPACE")          return VK_SPACE;
    if (j_key == "PRIOR")          return VK_PRIOR;
    if (j_key == "NECT")           return VK_NEXT;
    if (j_key == "END")            return VK_END;
    if (j_key == "HOME")           return VK_HOME;
    if (j_key == "LEFT")           return VK_LEFT;
    if (j_key == "UP")             return VK_UP;
    if (j_key == "RIGHT")          return VK_RIGHT;
    if (j_key == "DOWN")           return VK_DOWN;
    if (j_key == "SELECT")         return VK_SELECT;
    if (j_key == "PRINT")          return VK_PRINT;
    if (j_key == "EXECUTE")        return VK_EXECUTE;
    if (j_key == "SNAPSHOT")       return VK_SNAPSHOT;
    if (j_key == "INSERT")         return VK_INSERT;
    if (j_key == "DELETE")         return VK_DELETE;
    if (j_key == "HELP")           return VK_HELP;
    if (j_key == "NUM0")           return VK_NUMPAD0;
    if (j_key == "NUM1")           return VK_NUMPAD1;
    if (j_key == "NUM2")           return VK_NUMPAD2;
    if (j_key == "NUM3")           return VK_NUMPAD3;
    if (j_key == "NUM4")           return VK_NUMPAD4;
    if (j_key == "NUM5")           return VK_NUMPAD5;
    if (j_key == "NUM6")           return VK_NUMPAD6;
    if (j_key == "NUM7")           return VK_NUMPAD7;
    if (j_key == "NUM8")           return VK_NUMPAD8;
    if (j_key == "NUM9")           return VK_NUMPAD9;
    if (j_key == "MULTIPLY")       return VK_MULTIPLY;
    if (j_key == "ADD")            return VK_ADD;
    if (j_key == "SEPARATOR")      return VK_SEPARATOR;
    if (j_key == "SUBTRACT")       return VK_SUBTRACT;
    if (j_key == "DECIMAL")        return VK_DECIMAL;
    if (j_key == "DIVIDE")         return VK_DIVIDE;
    if (j_key == "F1")             return VK_F1;
    if (j_key == "F2")             return VK_F2;
    if (j_key == "F3")             return VK_F3;
    if (j_key == "F4")             return VK_F4;
    if (j_key == "F5")             return VK_F5;
    if (j_key == "F6")             return VK_F6;
    if (j_key == "F7")             return VK_F7;
    if (j_key == "F8")             return VK_F8;
    if (j_key == "F9")             return VK_F9;
    if (j_key == "F10")            return VK_F10;
    if (j_key == "F11")            return VK_F11;
    if (j_key == "F12")            return VK_F12;
    if (j_key == "F13")            return VK_F13;
    if (j_key == "F14")            return VK_F14;
    if (j_key == "F15")            return VK_F15;
    if (j_key == "F16")            return VK_F16;
    if (j_key == "F17")            return VK_F17;
    if (j_key == "F18")            return VK_F18;
    if (j_key == "F19")            return VK_F19;
    if (j_key == "F20")            return VK_F20;
    if (j_key == "F21")            return VK_F21;
    if (j_key == "F22")            return VK_F22;
    if (j_key == "F23")            return VK_F23;
    if (j_key == "F24")            return VK_F24;
    if (j_key == "A")              return 0x41;
    if (j_key == "B")              return 0x42;
    if (j_key == "C")              return 0x43;
    if (j_key == "D")              return 0x44;
    if (j_key == "E")              return 0x45;
    if (j_key == "F")              return 0x46;
    if (j_key == "G")              return 0x47;
    if (j_key == "H")              return 0x48;
    if (j_key == "I")              return 0x49;
    if (j_key == "J")              return 0x4A;
    if (j_key == "K")              return 0x4B;
    if (j_key == "L")              return 0x4C;
    if (j_key == "M")              return 0x4D;
    if (j_key == "N")              return 0x4E;
    if (j_key == "O")              return 0x4F;
    if (j_key == "P")              return 0x50;
    if (j_key == "Q")              return 0x51;
    if (j_key == "R")              return 0x52;
    if (j_key == "S")              return 0x53;
    if (j_key == "T")              return 0x54;
    if (j_key == "U")              return 0x55;
    if (j_key == "V")              return 0x56;
    if (j_key == "W")              return 0x57;
    if (j_key == "X")              return 0x58;
    if (j_key == "Y")              return 0x59;
    if (j_key == "Z")              return 0x5A;		

	game->ErrorInfo(L"No such key exists");

	return 0;
}