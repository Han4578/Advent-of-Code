#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

unordered_map<string, unordered_map<int, unordered_map<char, long long>>> elements;
string current = "";

void get_initial_string() {
	string line = "";

	getline(input, current);
	input.seekg(2, input.cur);

	while (getline(input, line)) elements[line.substr(0, 2)][1][line[line.length() - 1]] = 1;
}

bool find(auto map, auto key) {
	return map.find(key) != map.end();
}

unordered_map<char, long long>* get_count(string key, int loop) {
	if (!find(elements, key) || loop < 1) return {};
	if (find(elements[key], loop)) return &elements[key][loop];
	else {
		--loop;
		unordered_map<char, long long> count;
		string k = string() + key[0] + elements[key][1].begin()->first + key[1];
		++count[k[1]];
		for (int i = 0; i < k.length(); ++i) {
			if (i == k.length() - 1) break;
			unordered_map<char, long long>* rc = get_count(k.substr(i, 2), loop);
			for (auto& [c, n] : *rc) count[c] += n;
		}
		elements[key].insert(make_pair(loop + 1, move(count)));
		return &elements[key][loop + 1];
	}
}

long long polymerization(int loop) {
	unordered_map<char, long long> count;

	for (int i = 0; i < current.length(); ++i) {
		++count[current[i]];
		if (i == current.length() - 1) break;
		string key = current.substr(i, 2);
		unordered_map<char, long long >* rc = get_count(key, loop);
		for (auto& [c, n] : *rc) count[c] += n;
	}

	long long biggest = 0, smallest = LLONG_MAX;
	for (auto& [c, n] : count) {
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
	get_initial_string();
	P1();
	input.clear();
	input.seekg(0);
	cout << '\n';
	P2();
	input.close();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
