#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

typedef pair<int, int> Coords;

struct hash_pair {
	size_t operator()(const Coords &p) const {
		return p.first * 1000 + p.second;
	}
};

unordered_set<Coords, hash_pair> cucumbers;
vector<const Coords *> east, south;
int width = 0, height = 0;

void get_cucumbers() {
	string line = "";
	int y = 0;
	while (getline(input, line)) {
		for (int x = 0; x < line.length(); ++x) {
			if (line[x] == '.') continue;
			const Coords *p = &(*cucumbers.insert(make_pair(x, y)).first);
			if (line[x] == '>') east.push_back(move(p));
			else south.push_back(move(p));
		}
		++y;
	}
	width = line.length();
	height = move(y);
}

void P1() {
	int steps = 0;

	while (true) {
		++steps;
		vector<int> east_to_move, south_to_move;

		for (int i = 0; i < east.size(); ++i) {
			auto &p = *east[i];
			if (cucumbers.find(make_pair((p.first + 1) % width, p.second)) == cucumbers.end()) east_to_move.push_back(i);
		}

		for (int i = east_to_move.size() - 1; i >= 0; --i) {
			Coords cucumber = *east[east_to_move[i]];
			cucumbers.erase(cucumber);
			east.erase(east.begin() + east_to_move[i]);
			cucumber.first = (cucumber.first + 1) % width;
			east.push_back(&*cucumbers.insert(cucumber).first);
		}

		for (int i = 0; i < south.size(); ++i) {
			auto &p = *south[i];
			if (cucumbers.find(make_pair(p.first, (p.second + 1) % height)) == cucumbers.end()) south_to_move.push_back(i);
		}

		for (int i = south_to_move.size() - 1; i >= 0; --i) {
			Coords cucumber = *south[south_to_move[i]];
			cucumbers.erase(cucumber);
			south.erase(south.begin() + south_to_move[i]);
			cucumber.second = (cucumber.second + 1) % height;
			south.push_back(&*cucumbers.insert(cucumber).first);
		}

		if (east_to_move.size() + south_to_move.size() == 0) break;
	}

	cout << steps;
}

void P2() {

}

int main() {
	auto start = high_resolution_clock::now();
	get_cucumbers();
	P1();
	auto end = high_resolution_clock::now();
	input.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
