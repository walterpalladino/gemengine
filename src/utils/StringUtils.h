
#pragma once

#include <string>
#include <vector>

using namespace std;

#define MAX_STRING_SIZE 65536

std::string StringPrintf(const char *format, ...);
std::string UpperCase(const std::string &s);
std::string LowerCase(const std::string &s);

std::string RemoveAllString(const std::string &s, const std::string &substr);

long FindString(const std::string &s, const std::string &substr, size_t from, size_t to);

vector<string> StringTokenizer(const string &str, const string &delimiters = " ");
