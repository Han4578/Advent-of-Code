#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;
using namespace chrono;

ifstream input("input.txt");
unordered_map<string, char> polymers;
string original = "";

void set_up() {
	string line = "";
	getline(input, original);
	input.seekg(2, input.cur);

	while (getline(input, line)) polymers[line.substr(0, 2)] = line[line.length() - 1];
}

unsigned long long polymerization(int loop) {
	unordered_map<string, unsigned long long> pairs;
	unordered_map<char, unsigned long long> chars;

	for (int i = 0; i < original.length() - 1; ++i) ++pairs[original.substr(i, 2)];

	for (int i = 0; i < loop; ++i) {
		unordered_map<string, unsigned long long> new_pair;
		for (auto& [key, n] : pairs) {
			if (polymers.find(key) != polymers.end()) {
				new_pair[string() + key[0] + polymers[key]] += n;
				new_pair[string() + polymers[key] + key[1]] += n;
			} else {
				chars[key[0]] += n;
			}
		}
		pairs = move(new_pair);
	}

	for (auto& [k, n] : pairs) chars[k[0]] += n;

	unsigned long long biggest = 0, smallest = ULLONG_MAX;
	for (auto& [c, n] : chars) {
		if (biggest < n) biggest = n;
		else if (smallest > n) smallest = n;
	}

	return biggest - smallest;
}

void P1() {
	cout << polymerization(10);
	
}

void P2() {
	cout << polymerization(40);
}

int main() {
	auto start = high_resolution_clock::now();
	set_up();
	P1();
	cout << '\n';
	P2();
	input.close();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float)duration.count() / 1000 << " ms";
	return 0;
}