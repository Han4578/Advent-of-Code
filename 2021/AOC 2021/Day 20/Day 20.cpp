#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>

using namespace std;
using namespace chrono;

ifstream input("input.txt");
string algo = "";
deque<string> original;

char get_char(const string &binary) {
	int i = 0;
	for (char c : binary) i = i * 2 + (c == '#');
	
	return algo[i];
}

void build_image() {
	string line = "";

	getline(input, algo);
	input.ignore();

	while (getline(input, line)) {
		original.push_back("." + line + ".");
	}
}

int enhance(const int times) {
	char bg = '.';
	deque<string> image = original;
	image.push_back(string(image[0].length(), bg));
	image.push_front(string(image[0].length(), bg));

	for (int q = 0; q < times; ++q) {
		int width = image[0].length() + 2, height = image.size() + 2;

		for (string &line : image) line = bg + line + bg;

		image.push_front(string(width, bg));
		image.push_back(string(width, bg));

		deque<string> new_image = image;

		for (int y = 1; y < height - 1; ++y) {
			for (int x = 1; x < width - 1; ++x) {
				new_image[y][x] = get_char(image[y - 1].substr(x - 1, 3) + image[y].substr(x - 1, 3) + image[y + 1].substr(x - 1, 3));
			}
		}
		bg = algo[(bg == '.') ? 0: algo.length() - 1];

		for (string &line : new_image) {
			line[0] = bg;
			line[line.length() - 1] = bg;
		}
		new_image[0] = string(width, bg);
		new_image[height - 1] = string(width, bg);

		image = move(new_image);
	}

	int total = 0;
	for (string &line : image) for (char &c : line) if (c == '#') ++total;
	return total;
}

void P1() {
	cout << enhance(2);
}

void P2() {
	cout << enhance(50);
}

int main() {
	auto start = high_resolution_clock::now();
	build_image();
	P1();
	cout << '\n';
	P2();
	auto end = high_resolution_clock::now();
	input.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float)duration.count() / 1000 << " ms";
	return 0;
}