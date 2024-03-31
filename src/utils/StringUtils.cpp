
#include "utils/StringUtils.h"

#include <algorithm> // for using transform
#include <cctype>	 // for using toupper / tolower

#include <stdarg.h>
#include <stdio.h>

const std::string delimiters = "?!;,*";

bool isPunctuation(char c)
{
	return delimiters.find(c) != std::string::npos;
}

std::string StringPrintf(const char *format, ...)
{
	char *buffer;

	buffer = new char[MAX_STRING_SIZE];

	va_list ap;
	va_start(ap, format);
	vsnprintf(buffer, MAX_STRING_SIZE, format, ap);
	va_end(ap);

	std::string dest(buffer);
	delete[] buffer;

	return dest;
}

// Make an uppercase copy of s
std::string UpperCase(const std::string &s)
{
	std::string upper(s);
	//	for (size_t i = 0; i < s.length(); ++i)
	//		upper[i] = toupper(upper[i]);
	transform(upper.begin(), upper.end(), upper.begin(),
			  ::toupper);
	return upper;
}

// Make a lowercase copy of s
std::string LowerCase(const std::string &s)
{
	string lower(s);
	//	for (size_t i = 0; i < s.length(); ++i)
	//		lower[i] = tolower(lower[i]);
	transform(lower.begin(), lower.end(), lower.begin(),
			  ::tolower);
	return lower;
}

std::string RemoveAllString(const std::string &s, const std::string &substr)
{
	std::string remove(s);
	size_t pos;

	while ((pos = remove.find(substr)) != std::string::npos)
	{
		remove.erase(pos, substr.length());
	}

	return remove;
}

long FindString(const std::string &s, const std::string &substr, size_t from, size_t to)
{
	long pos;

	pos = s.substr(from, to - from).find(substr);

	return pos;
}

vector<string> StringTokenizer(const string &str, const string &delimiters)
{
	vector<string> tokens;

	tokens.clear();
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}

	return tokens;
}
