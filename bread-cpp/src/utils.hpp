#pragma once

#include <string>
#include <vector>

inline std::string escape_char(const std::string& s) {
	
	std::vector<char> temporal((size_t)(s.size() * 1.5));

	for (const auto c : s) {
		
		switch (c) {
		case '\n':
			temporal.push_back('\\');
			temporal.push_back('n');
		break;
		case '\t':
			temporal.push_back('\\');
			temporal.push_back('t');
			break;
		case '"':
			temporal.push_back('\\');
			temporal.push_back('"');
			break;
		default:
			temporal.push_back(c);
		}


	}

	return std::string{ &(temporal[0]), temporal.size() };


}

inline int count_escaped(const char* begin, const char* end) {
	int count = 0;
	for (; begin != end; begin++, count++) {
		if (*begin == '\n' || *begin == '\t' || *begin == '"') count++;
	};
	return count;
}

inline std::string make_pointee(int count) {
	std::string s( count + 1, ' ');
	s[count] = '^';
	return s;
}

inline std::string untilLineEnd(const char* begin) {
	int count = 0;
	auto it = begin;
	while (*it != '\0' && *it != '\n') it++;
	return std::string(begin, it - begin);

}

inline std::string indent(const char* text, const char* indentWith) {

}


inline std::string pointee_escaped(const char* begin, const char* end) {
	return make_pointee(count_escaped(begin, end));
}
