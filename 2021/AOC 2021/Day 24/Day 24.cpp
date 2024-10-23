#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

vector<tuple<int, int, int>> instructions;

void read_instructions() {
	string line = "";
	int div = 0, x = 0, y = 0;
	while (getline(input, line)) {
		for (int i = 0; i < 4; ++i) getline(input, line);
		div = stoi(line.substr(6));
		getline(input, line);
		x = stoi(line.substr(6));
		for (int i = 0; i < 10; ++i) getline(input, line);
		y = stoi(line.substr(6));
		for (int i = 0; i < 2; ++i) getline(input, line);
		instructions.push_back(make_tuple(div, x, y));
	}
}

unsigned long long validate(bool biggest) {
	vector<pair<int, int>> digits = {make_pair((biggest)? 9: 1, 0)};
	int digit = 0;

	while (digit < 14) {
		auto &[div, x, y] = instructions[digit];
		int &inp = digits[digit].first, z = digits[digit].second;

		if (div == 1) {
			while (z % 26 + x == inp && inp > 0 && inp < 10) inp += (biggest) ? -1 : 1;
			z *= 26;
			z += inp + y;
		} else {
			while (z % 26 + x != inp && inp > 0 && inp < 10) inp += (biggest) ? -1 : 1;
			z = trunc((float)z / div);
		}
		if (inp < 1 || inp > 9) {
			do {
				--digit;
				digits.pop_back();
			} while (get<0>(instructions[digit]) != 1);
			digits[digit].first += (biggest)? -1: 1;
			continue;
		}
		digits.push_back(make_pair((biggest) ? 9 : 1, z));
		++digit;
	}
	unsigned long long total = 0;
	for (pair<int, int> &p : digits) total = total * 10 + p.first;
	return total / 10;
}

void P1() {
	cout << validate(true);
}

void P2() {
	cout << validate(false);
}

int main() {
	auto start = high_resolution_clock::now();
	read_instructions();
	P1();
	cout << '\n';
	P2();
	auto end = high_resolution_clock::now();
	input.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
