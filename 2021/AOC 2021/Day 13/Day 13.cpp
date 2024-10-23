#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>

using namespace std;
using namespace chrono;

ifstream input("input.txt");
vector<pair<int, int>> instructions;
unordered_map<int, set<int>> coords;

void get_instructions() {
	string line;
	
	while (getline(input, line) && line != "");
	
	while (getline(input, line)) {
		int fold_line = stoi(line.substr(13, line.length()));
		instructions.push_back({(line[11] == 'x')? 0: 1, fold_line});
	}

	input.clear();
	input.seekg(0);
}

void fold(int n) {
	string line;
	coords.clear();

	while (getline(input, line) && line != "") {
		int i = line.find(','), t = n;
		int p[2] = {stoi(line.substr(0, i)), stoi(line.substr(i + 1, line.length()))};

		for (auto& [i, fold_line] : instructions) {
			if (--t < 0) break;
			if (p[i] < fold_line) continue;
			p[i] -= 2 * (p[i] - fold_line);
		}
		coords[p[1]].insert(p[0]);
	}	
}

void P1() {
	fold(1);
	int total = 0;
	for (pair<int, set<int>> p : coords) total += p.second.size();
	cout << total;
}

void P2() {
	fold(INT_MAX);
	int max_height = INT_MIN, max_width = INT_MIN, min_height = INT_MAX, min_width = INT_MAX;

	for (auto& [y, x] : coords) {
		if (*x.rbegin() > max_width) max_width = *x.rbegin();
		if (*x.begin() < min_width) min_width = *x.begin();
		if (y > max_height) max_height = y;
		else if (y < min_height) min_height = y;
	}

	for (int y = min_height; y <= max_height; ++y) {
		string line = string(max_width - min_width + 1, ' ');
		if (coords.find(y) != coords.end()) {
			for (int x : coords[y]) line[x] = '*';
		}
		cout << line << '\n';
	}
}

int main() {
	auto start = high_resolution_clock::now();
	get_instructions();
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