#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

vector<string> rows;
vector<pair<int, int>> glowing;
int row_length = 0, total_octo = 0, final_i = 1, current_i = 1;

void get_rows() {
	string line = "";
	while (getline(input, line)) {
		rows.push_back(line);
		total_octo += line.length();
	}
	row_length = rows[0].length();
}


static void explode(int x, int y) {
	for (int dx = -1; dx < 2; ++dx) {
		for (int dy = -1; dy < 2; ++dy) {
			if ((dx == 0 && dy == 0) || (x + dx < 0) || (x + dx >= row_length) || (y + dy < 0) || (y + dy >= rows.size()) || rows[y + dy][x + dx] > '9') continue;

			if (++rows[y + dy][x + dx] > '9') {
				glowing.push_back(make_pair(x + dx, y + dy));
				explode(x + dx, y + dy);
			}
		}
	}
}

int grow() {
	for (int y = 0; y < rows.size(); ++y) {
		for (int x = 0; x < row_length; ++x) {
			if (rows[y][x] > '9') continue;

			if (++rows[y][x] > '9') {
				glowing.push_back(make_pair(x, y));
				for (int dx = -1; dx < 2; ++dx) {
					for (int dy = -1; dy < 2; ++dy) {
						if ((dx == 0 && dy == 0) || (x + dx < 0) || (x + dx >= row_length) || (y + dy < 0) || (y + dy >= rows.size()) || (rows[y + dy][x + dx] > '9')) continue;

						if (++rows[y + dy][x + dx] > '9') {
							glowing.push_back(make_pair(x + dx, y + dy));
							explode(x + dx, y + dy);
						}
					}
				}
			}
		}
	}

	int total = glowing.size();
	if (total != total_octo) ++final_i;
	++current_i;
	for (pair<int, int> p : glowing) rows[p.second][p.first] = '0';
	glowing.clear();
	return total;
}

void P1() {
	int total = 0;
	for (int i = 0; i < 100; ++i) total += grow();
	cout << total;
}

void P2() {
	while (final_i == current_i) grow();
	cout << final_i;
}

int main() {
	auto start = high_resolution_clock::now();
	get_rows();
	P1();
	cout << '\n';
	P2();
	input.close();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}