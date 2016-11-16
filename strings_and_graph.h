#ifndef STRINGS_AND_GRAPH_H_
#define STRINGS_AND_GRAPH_H_

#include <string>
#include <unordered_map>

std::unordered_map<int, int> FindSymbolInString(const char& symbol, const std::string& string) {
	std::unordered_map<int, int> symbols_in_string;
	for (int i = 0; i < string.size(); ++i) {
		if (string[i] == symbol) {
			symbols_in_string.insert({i, symbols_in_string.size()});
		}
	}
	return symbols_in_string;
}

#endif // STRINGS_AND_GRAPH_H_