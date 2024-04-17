#ifndef RTCLOADTESTUTIL_H
#define RTCLOADTESTUTIL_H

#include <vector>
#include <string>
#include <sstream>

using vstring = std::vector<std::string>;


template <typename To>
bool stringTo(To& val, const char* str)
{
	if (str == nullptr) { return false; }

	std::stringstream s;
	if ((s << str).fail()) { return false; }
	if ((s >> val).fail()) { return false; }
	return true;
}

std::string eraseHeadBlank(std::string str) noexcept;
std::string eraseTailBlank(std::string str) noexcept;
std::string eraseBothEndsBlank(std::string str) noexcept;

vstring split(const std::string& input,
	const std::string& delimiter,
	bool ignore_empty = false);

#endif // RTCLOADTESTUTIL_H
