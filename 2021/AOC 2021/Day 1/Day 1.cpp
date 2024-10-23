#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

void P1() {
	int previous = 0, num = 0, total = 0;
	input >> previous;
	while (input >> num) {
		if (num > previous) total++;
		previous = num;
	}
	cout << total;
}

void P2() {
	int previous = 0, last_depth = 0, i = 0, current = 0, total = 0;
	const int size = 3;
	int window[size] = {};

	for (int j = 0; j < size; j++) {
		input >> window[j];
		last_depth += window[j];
	}

	while (input >> current) {
		previous = window[i];
		window[i] = current;
		if (current - previous > 0) total++;
		last_depth += current - previous;
		i = ++i % size;
	}

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
