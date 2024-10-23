#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cctype>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

int run(bool diagonals = false) {
	unordered_map<int, unordered_map<int, int>> count_map;
	string line;
	int total = 0;

	while (getline(input, line)) {
		int nums[4] = {};
		string temp = "";
		int j = 0;

		for (char c : line) {
			if (isdigit(c)) temp += c;
			else if (temp != "") {
				nums[j++] = stoi(temp);
				temp = "";
			}
		}
		nums[3] = stoi(temp);
		if (!diagonals && nums[0] != nums[2] && nums[1] != nums[3]) continue;

		int cx = nums[2] - nums[0];
		int cy = nums[3] - nums[1];
		int dx = (cx == 0)? 0: (cx) / abs(cx);
		int dy = (cy == 0)? 0: (cy) / abs(cy);
		int x = nums[0], y = nums[1];

		for (int i = 0; i <= max(abs(cx), abs(cy)); ++i) {
			if (++count_map[y][x] == 2) ++total;
			x += dx;
			y += dy;
		}
	}

	return total;
}

void P1() {
	cout << run(false);
}

void P2() {
	cout << run(true);
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