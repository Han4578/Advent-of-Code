#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;
using namespace chrono;

ifstream input("input.txt");
//int lx = 20, ux = 30, ly = -10, uy = -5;
int lx = 277, ux = 318, ly = -92, uy = -53;

int get_height(int dy, int t) {
	t -= 2 * dy + 1;
	++dy;
	return -t * (dy + dy + t - 1) / 2;
}

void P1() {
	cout << (ly + 1) * ly / 2;
}

void P2() {
	int count = 0;
	for (int dx = ceil((sqrt(1 + 8 * lx) - 1) / 2); dx <= ux; ++dx) {
		int t = ceil(((2.0 * dx + 1) - sqrt(pow(2 * dx + 1, 2) - 8 * lx)) / 2);
		for (int dy = ceil((2.0 * ly / t + 1 - t) / 2); dy < -ly; ++dy) {
			int x = t * (dx + dx - t + 1) / 2, y = get_height(dy, t), ny = dy - t + 1, nx = dx - t + 1;
			while ( y >= ly && x <= ux) {
				if (y <= uy && x >= lx) {
					++count;
					break;
				}
				if (nx > 0) x += --nx;
				y += --ny;
			}
		}
	}

	cout << count;
}

int main() {
	auto start = high_resolution_clock::now();
	P2();
	auto end = high_resolution_clock::now();
	input.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
