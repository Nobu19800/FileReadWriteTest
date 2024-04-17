#include "FileReadWriteTestUtil.h"

std::string eraseHeadBlank(std::string str) noexcept
{
	return str.erase(0, str.find_first_not_of(" \t"));
}

std::string eraseTailBlank(std::string str) noexcept
{
	return str.erase(str.find_last_not_of(" \t") + 1); // npos + 1 = 0
}

std::string eraseBothEndsBlank(std::string str) noexcept
{
	return eraseHeadBlank(eraseTailBlank(std::move(str)));
}

vstring split(const std::string& input,
	const std::string& delimiter,
	bool ignore_empty)
{
	if (input.empty()) { return {}; }
	if (delimiter.empty()) { return { eraseBothEndsBlank(input) }; }

	vstring results;
	std::string::size_type pos{ 0 };
	for (auto found_pos = input.find(delimiter, pos);
		found_pos != std::string::npos;
		found_pos = input.find(delimiter, pos))
	{
		std::string str{ eraseBothEndsBlank(input.substr(pos, found_pos - pos)) };
		if (!(ignore_empty && str.empty())) { results.emplace_back(std::move(str)); }
		pos = found_pos + delimiter.length();
	}

	std::string str{ eraseBothEndsBlank(input.substr(pos)) };
	if (!(ignore_empty && str.empty())) { results.emplace_back(std::move(str)); }
	return results;
}
