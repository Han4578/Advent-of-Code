#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace chrono;

typedef int (*Func)(int);

ifstream input("input.txt");
vector<int> cwabs;
int low = 0, high = 0;

int calculate_fuel(int point) {
	int fuel = 0;
	for (int c : cwabs) fuel += abs(c - point);
	return fuel;
}
int calculate_fuel2(int point) {
	int fuel = 0;
	for (int c : cwabs) {
		int diff = abs(c - point);
		fuel += (1 + diff) * diff / 2;
	}
	return fuel;
}

int binary_search(int p) {
	int lowest = low, highest = high;
	Func calc = (p == 1) ? calculate_fuel : calculate_fuel2;

	while (lowest <= highest) {
		int midpoint = round((float)(highest + lowest) / 2);
		int i = 1;
		int p = calc(midpoint);
		int p_right = calc(midpoint + 1);

		if (p >= p_right) lowest = midpoint + 1;
		else highest = midpoint - 1;
	}

	return calc(lowest);
}

void fill_cwabs() {
	int n = 0;
	while (input >> n) {
		cwabs.push_back(n);
		if (low > n) low = n;
		else if (high < n) high = n;
		input.seekg(1, input.cur);
	}
}

void P1() {
	cout << binary_search(1);
}

void P2() {
	cout << binary_search(2);
}

int main() {
	auto start = high_resolution_clock::now();
	fill_cwabs();
	P1();
	cout << '\n';
	P2();
	input.close();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
