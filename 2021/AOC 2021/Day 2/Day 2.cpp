#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

void P1() {
	int x = 0, y = 0;
	string line;
	int offset = '0';
	while (getline(input, line)) {
		char command = line[0];
		int n = line[line.size() - 1] - offset;
		switch (command) {
		case 'u':
			y -= n;
			break;
		case 'd':
			y += n;
			break;
		case 'f':
			x += n;
			break;
		}
	}

	cout << x * y;
}

void P2() {
	int x = 0, y = 0, aim = 0;
	string line;
	int offset = '0';
	while (getline(input, line)) {
		char command = line[0];
		int n = line[line.size() - 1] - offset;
		switch (command) {
		case 'u':
			aim -= n;
			break;
		case 'd':
			aim += n;
			break;
		case 'f':
			x += n;
			y += aim * n;
			break;
		}
	}

	cout << x * y;
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
