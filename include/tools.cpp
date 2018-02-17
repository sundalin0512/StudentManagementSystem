#include "tools.h"
std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
	size_t size = str.size();

	for (size_t i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s;
			s = str.substr(i, pos - i).c_str();
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	if (result.back() == "")
		result.erase(result.end() - 1);
	return result;
}

static std::vector<std::wstring> split(std::wstring str, std::wstring pattern)
{
	std::wstring::size_type pos;
	std::vector<std::wstring> result;
	str += pattern;//扩展字符串以方便操作
	size_t size = str.size();

	for (size_t i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::wstring s;
			s = str.substr(i, pos - i).c_str();
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	if (result.back() == L"")
		result.erase(result.end() - 1);
	return result;
}