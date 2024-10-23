#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <array>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

string get_remainder(string a, string b) {
	string r = "";
	for (char c : a) if (find(b.begin(), b.end(), c) == b.end()) r += c;
	return r;
}

string get_overlap(string a, string b) {
	string overlap;
	for (char c : a) if (find(b.begin(), b.end(), c) != b.end()) overlap += c;
	return overlap;
}

void P1() {
	string line = "";
	int total = 0;

	while (getline(input, line)) {
		line.erase(0, line.find('|') + 1);

		do {
			line.erase(line.begin());
			string sub = line.substr(0, line.find(' '));
			switch (sub.length()) {
				case 2:
				case 3:
				case 4:
				case 7:
					++total;
			}
			line.erase(0, sub.size());
		} while (line[0] == ' ');
	}

	cout << total;
}

void P2() {
	string line = "";
	int total = 0;

	while (getline(input, line)) {
		int i = 0;
		char top = 0, bottom = 0;
		array<string, 6> signals = {};
		string t = "";
		unordered_map<char, string> digits;

		while (line[0] != '|') {
			string sub = line.substr(0, line.find(' '));
			line.erase(0, sub.length() + 1);
			sort(sub.begin(), sub.end());
			switch (sub.length()) {
				case 2:
					digits['1'] = sub;
					break;
				case 3:
					digits['7'] = sub;
					break;
				case 4:
					digits['4'] = sub;
					break;
				case 7:
					digits['8'] = sub;
					break;
				default:
					signals[i++] = sub;
			}
		}
		int length = signals.end() - signals.begin();
		top = get_remainder(digits['7'], digits['1'])[0];

		for (int i = 0; i < length; ++i) {
			string signal = signals[i];
			if (signal.length() != 5) continue;

			string s = get_remainder(digits['4'] + top, signal);

			if (s.length() == 2) digits['2'] = signal;
			else {
				string o = get_overlap(signal, digits['1']);

				if (o.length() == 1) {
					bottom = get_remainder(signal, digits['4'] + top)[0];
					digits['5'] = signal;
				} else digits['3'] = signal;
			}
		}

		for (int i = 0; i < length; ++i) {
			string s = signals[i];
			if (s.length() != 6) continue;

			if (digits.find(9) == digits.end()) {
				string nine = digits['4'] + top + bottom;
				sort(nine.begin(), nine.end());
				if (s == nine) {
					digits['9'] = s;
					continue;
				}
			}

			string o = get_overlap(s, digits['1']);
			digits[(o.length() == 1) ? '6' : '0'] = s;
		}

		line.erase(line.begin());
		
		do {
			line.erase(line.begin());
			string sub = line.substr(0, line.find(' '));
			sort(sub.begin(), sub.end());
			
			for (auto p : digits) {
				if (p.second == sub) {
					t += p.first;
					break;
				}
			}

			line.erase(0, sub.size());
		} while (line[0] == ' ');
		total += stoi(t);
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