#include <chrono>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <tuple>

using namespace std;
using namespace chrono;

class Cave {
public:
	bool is_big = true;
	vector<string> connects;

	Cave(string s) {
		is_big = s[0] < 96;
	}

	Cave() {}

	void add_connection(string s) {
		connects.push_back(s);
	}

	void remove_connection(string s) {
		connects.erase(find(connects.begin(), connects.end(), s));
	}
};

ifstream input("input.txt");
map<string, Cave> caves;

Cave* get_cave(string id) {
	if (caves.find(id) == caves.end()) caves.insert(make_pair(id, Cave(id)));
	return &caves[id];
}

void build_cave() {
	string line;

	while (getline(input, line)) {
		int i = line.find('-');

		string s1 = line.substr(0, i), s2 = line.substr(i + 1, line.length());

		get_cave(s1)->add_connection(s2);
		get_cave(s2)->add_connection(s1);
	}

	for (auto& [name, cave] : caves) {
		if (!cave.is_big) continue;

		for (string s : cave.connects) {
			for (string ss : cave.connects) {
				caves[s].add_connection(ss);
			}
			caves[s].remove_connection(name);
		}
	}

}

bool has_double(map<string, int>& h) {
	for (pair<string, int> p : h) if (p.second > 1) return true;
	return false;
}

void P1() {
	int total = 0;
	vector<vector<string>> current = { vector<string>{"start"} }, next_step = {};

	while (current.size() > 0) {
		for (vector<string> path : current) {
			for (string p : caves[path[path.size() - 1]].connects) {
				if (p == "end") ++total;
				else if (find(path.begin(), path.end(), p) == path.end()) {
					vector<string> new_path = path;
					new_path.push_back(p);
					next_step.push_back(new_path);
				}
			}
		}
		current.clear();
		current.swap(next_step);
	}
	cout << total;
}

void P2() {
	int total = 0;
	vector<pair<vector<string>, bool>> current = { {vector<string>{"start"}, true } }, next_step = {};

	while (current.size() > 0) {
		for (auto &[path, revisit] : current) {
			for (string p : caves[path[path.size() - 1]].connects) {
				if (p == "start") continue;
				if (p == "end") {
					++total;
					continue;
				}

				bool visited = find(path.begin(), path.end(), p) != path.end();
				
				if (!visited || (revisit && visited)) {
					pair<vector<string>, bool> new_path = {path, revisit};
					if (visited) new_path.second = false;
					new_path.first.push_back(p);
					next_step.push_back(new_path);
				}
			}
		}
		current.clear();
		current.swap(next_step);
	}
	cout << total;

}

int main() {
	auto start = high_resolution_clock::now();
	build_cave();
	P1();
	cout << '\n';
	P2();
	input.close();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
