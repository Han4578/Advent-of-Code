#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <unordered_set>
#include <set>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

bool check_visited(unordered_set<string> &unset, string value) {
	return unset.find(value) != unset.end();
}

void P1() {
	vector<string> rows;
	string line;
	int total = 1;

	while (getline(input, line)) rows.push_back(line);

	for (int y = 0; y < rows.size(); ++y) {
		for (int x = 0; x < rows[y].length(); ++x) {
			char c = rows[y][x];

			if ((x - 1 >= 0 && rows[y][x - 1] <= c) || (x + 1 < rows[y].length() && rows[y][x + 1] <= c) ||
				(y - 1 >= 0 && rows[y - 1][x] <= c) || (y + 1 < rows.size() && rows[y + 1][x] <= c)) continue;
			else total += c - '0' + 1;
		}
	}

	cout << total;
}

void P2() {
	vector<string> rows;
	string line;
	unordered_set<string> visited;
	deque<int> highest = {0, 0, 0};
	int total = 1;

	while (getline(input, line)) rows.push_back(line);

	for (int y = 0; y < rows.size(); ++y) {
		for (int x = 0; x < rows[y].length(); ++x) {
			char c = rows[y][x];
			if (c == '9' || check_visited(visited, (to_string(x) + ',' + to_string(y)))) continue;

			int size = 1;
			set<pair<int, int>> current = {make_pair(x, y)};
			set<pair<int, int>> next_step = {};

			while (current.size() > 0) {
				for (pair<int, int> pair : current) {
					int x = pair.first, y = pair.second;
					visited.insert(to_string(x) + ',' + to_string(y));
					if (x - 1 >= 0				 && rows[y][x - 1] != '9' && !check_visited(visited, (to_string(x - 1) + ',' + to_string(y)))) next_step.insert(make_pair(x - 1, y));
					if (x + 1 < rows[y].length() && rows[y][x + 1] != '9' && !check_visited(visited, (to_string(x + 1) + ',' + to_string(y)))) next_step.insert(make_pair(x + 1, y));
					if (y - 1 >= 0				 && rows[y - 1][x] != '9' && !check_visited(visited, (to_string(x) + ',' + to_string(y - 1)))) next_step.insert(make_pair(x, y - 1));
					if (y + 1 < rows.size()		 && rows[y + 1][x] != '9' && !check_visited(visited, (to_string(x) + ',' + to_string(y + 1)))) next_step.insert(make_pair(x, y + 1));
				}
				set<pair<int, int>> temp = current;
				size += next_step.size();
				current = next_step;
				next_step = temp;
				next_step.clear();
			}

			int i = 0;

			for (i = highest.size() - 1; i >= 0; --i) {
				if (highest[i] < size) continue;
				else break;
			}

			if (i < (int)highest.size() - 1) {
				if (i >= 0) highest.insert(highest.begin() + i + 1, size);
				else highest.push_front(size);
				highest.pop_back();
			}
		}
	}

	for (int n : highest) total *= n;
	cout << total;
}

int main() {
	auto start = high_resolution_clock::now();
	P1();
	cout << '\n';
	input.clear();
	input.seekg(0);
	P2();
	input.close();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
