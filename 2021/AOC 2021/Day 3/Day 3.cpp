#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

int filter(vector<string> r, int diff, int index) {
	vector<string> ratings;
	int common = 0;
	int total = 0;
	for (int i = 0; i < r.size(); ++i) common += (r[i][index] == '1') ? 1 : -1;

	char c = (common >= 0)? '1': '0';

	for (int i = 0; i < r.size(); ++i) if (abs(r[i][index] - c) == diff) ratings.push_back(r[i]);

	if (ratings.size() == 1) {
		for (int i = 0; i < ratings[0].size(); ++i) if (ratings[0][i] == '1') total += pow(2, ratings[0].size() - i - 1);
		return total;
	} else return filter(ratings, diff, index + 1);
}

void P1() {
	int gamma = 0;
	const int width = 12;
	int count[width] = {};
	string line = "";
	while (getline(input, line)) for (int i = 0; i < width; ++i) count[i] += (line[i] == '1') ? 1 : -1;
	for (int i = 0; i < width; ++i) if (count[i] > 0) gamma += pow(2, width - i - 1);

	cout << fixed << (int)(pow(2, width) - 1 - gamma) * gamma;
}

void P2() {
	int total = 1;
	vector<string> ratings;
	string line;
	while (getline(input, line)) ratings.push_back(line);

	for (int i = 0; i < 2; ++i) total *= filter(ratings, i, 0);

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
