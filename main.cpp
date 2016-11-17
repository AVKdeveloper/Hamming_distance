// This program finds Hamming distance for string and pattern
// We use algorithm by Dinitz
// O(V^2 * E)

#include <iostream>
#include <fstream> 
#include <string>
#include <cassert>
#include "flow_network.h"
#include "strings_and_graph.h"

int main() {
	std::fstream file_in;
	std::string string;
	std::string pattern;
	file_in.open("input.txt", std::fstream::in);
	file_in >> string >> pattern;
	std::unordered_map<int, int> questions_in_string = FindSymbolInString('?', string); 
	std::unordered_map<int, int> questions_in_pattern = FindSymbolInString('?', pattern);
	int vertices_quantity = 2 + questions_in_string.size() + questions_in_pattern.size();// quantity of vertices in graph
																						 // 2 - for fictitious source and target and other vertices are symbols '?' from string and pattern
	int hamming_distance = 0;
	FlowNetwork net(vertices_quantity, 0, 1); // init graph
	for (int i = 0; i + pattern.size() <= string.size(); ++i) { // we move pattern along string
		for (int j = 0; j < pattern.size(); ++j) {
			if (string[i + j] == '1') {
				switch (pattern[j]) {
				case '1': { // '1' -> '1'
					break;
				}
				case '0': { // '1' -> '0'
					hamming_distance++;
					break;
				}
				case '?': { // '1' -> '?' 
					net.AddEdge(0, 2 + questions_in_string.size() + questions_in_pattern[j], 1);
					// connected with source (vertex 0)
					break;
				}
				default: {
					assert(pattern[j] == '1' || pattern[j] == '0' || pattern[j] == '?');
					break;
				}
				}
			}
			else if (string[i + j] == '0') {
				switch (pattern[j]) {
				case '1': { // '0' -> '1'
					hamming_distance++;
					break;
				}
				case '0': { // '0' -> '0'
					break;
				}
				case '?': { // '0' -> '?'
					net.AddEdge(1, 2 + questions_in_string.size() + questions_in_pattern[j], 1);
					// connected with target (vertex 1)
					break;
				}
				default: {
					assert(pattern[j] == '1' || pattern[j] == '0' || pattern[j] == '?');
					break;
				}
				}
			}
			else if (string[i + j] == '?') {
				switch (pattern[j]) {
				case '1': { // '?' -> '1'
					net.AddEdge(0, 2 + questions_in_string[i + j], 1);
					// connected with source (vertex 0)
					break;
				}
				case '0': { // '?' -> '0'
					net.AddEdge(1, 2 + questions_in_string[i + j], 1);
					// connected with target (vertex 1)
					break;
				}
				case '?': { // '?' -> '?'
					net.AddEdge(2 + questions_in_string[i + j],
						2 + questions_in_string.size() + questions_in_pattern[j], 1);
					// connected two vertexes 
					break;
				}
				default: {
					assert(pattern[j] == '1' || pattern[j] == '0' || pattern[j] == '?');
					break;
				}
				}
			}
			else {
				assert(string[i + j] == '1' || string[i + j] == '0' || string[i + j] == '?');
			}
		}
	}
	file_in.close();
	hamming_distance += net.FindMaxFlowByDinitz();
	std::fstream file_out;
	file_out.open("output.txt", std::fstream::out);
	file_out << hamming_distance << std::endl;
	// Now we will restore the string and pattern
	net.TransformStringsUsingFlow(string, pattern, questions_in_string, questions_in_pattern);
	file_out << string << std::endl << pattern;
	file_out.close();
	return 0;
}