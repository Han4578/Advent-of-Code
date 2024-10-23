#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <valarray>
#include <tuple>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

typedef pair<valarray<int>, valarray<int>> Cube;

void split(const Cube &c1, const Cube &c2, vector<Cube> &new_cubes) {
	if (c1.second[2] > c2.second[2]) new_cubes.push_back(Cube(make_pair(valarray<int>{c1.first[0], c1.first[1], c2.second[2] + 1}, c1.second)));
	if (c1.first[2] < c2.first[2]) new_cubes.push_back(Cube(make_pair(c1.first, valarray<int>{c1.second[0], c1.second[1], c2.first[2] - 1})));
	if (c1.second[1] > c2.second[1]) new_cubes.push_back(Cube(make_pair(valarray<int>{c1.first[0], c2.second[1] + 1, max(c1.first[2], c2.first[2])}, valarray<int>{c1.second[0], c1.second[1], min(c1.second[2], c2.second[2])})));
	if (c1.first[1] < c2.first[1]) new_cubes.push_back(Cube(make_pair(valarray<int>{c1.first[0], c1.first[1], max(c1.first[2], c2.first[2])}, valarray<int>{c1.second[0], c2.first[1] - 1, min(c1.second[2], c2.second[2])})));
	if (c1.second[0] > c2.second[0]) new_cubes.push_back(Cube(make_pair(valarray<int>{c2.second[0] + 1, max(c1.first[1], c2.first[1]), max(c1.first[2], c2.first[2])}, valarray<int>{c1.second[0], min(c1.second[1], c2.second[1]), min(c1.second[2], c2.second[2])})));
	if (c1.first[0] < c2.first[0]) new_cubes.push_back(Cube(make_pair(valarray<int>{c1.first[0], max(c1.first[1], c2.first[1]), max(c1.first[2], c2.first[2])}, valarray<int>{c2.first[0] - 1, min(c1.second[1], c2.second[1]), min(c1.second[2], c2.second[2])})));
}

unsigned long long reboot(bool limit) {
	vector<Cube> cubes, new_cubes;

	while (!input.eof()) {
		string state = "";
		valarray<int> start(0, 3), end(0, 3);
		input >> state;

		for (int i = 0; i < 3; ++i) {
			while (input.get() != '=');
			input >> start[i];
			input.seekg(2, input.cur);
			input >> end[i];
		}
		input.ignore();

		if (limit && (start[0] > 50 || start[0] < -50)) break;

		Cube cube = make_pair(start, end);

		for (int i = 0; i < cubes.size(); ++i) {
			Cube &c = cubes[i];
			if (!(c.first <= end).min() || !(c.second >= start).min()) continue;
			split(c, cube, new_cubes);
			cubes.erase(cubes.begin() + i);
			--i;
		}

		for (Cube &c : new_cubes) cubes.push_back(move(c));
		if (state == "on") cubes.push_back(move(cube));
		new_cubes.clear();
	}

	unsigned long long volume = 0;

	for (Cube &c : cubes) {
		valarray<int> sides = c.second - c.first;
		unsigned long long total = 1;
		for (int n : sides) total *= n + 1;
		if (total < 0) {
			cout << "oh";
		}
		volume += total;
	}

	return volume;
}

void P1() {
	cout << reboot(true);
}

void P2() {
	cout << reboot(false);
}

int main() {
	auto start = high_resolution_clock::now();
	P1();
	cout << '\n';
	input.clear();
	input.seekg(0, input.beg);
	P2();
	auto end = high_resolution_clock::now();
	input.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
