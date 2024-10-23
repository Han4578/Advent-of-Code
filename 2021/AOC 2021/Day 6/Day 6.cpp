#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
	
using namespace std;
using namespace chrono;

ifstream input("input.txt");

class bint {
	string value = "";

public:

	bint(int n) {
		value = to_string(n);
		reverse(value.begin(), value.end());
	}

	bint() {
		value = "0";
	}

	void add(int index) {
		int i, n = value.length();

		for (i = index; i < n && value[i] == '9'; ++i) value[i] = '0';
		if (i == n) value += '1';
		else ++value[i];
	}

	void operator++ () {
		int i, n = value.length();

		for (i = 0; i < n && value[i] == '9'; ++i) value[i] = '0';
		if (i == n) value += '1';
		else ++value[i];
	}

	void operator+=(string b) {
		int l = value.length();
		for (int i = l; i < b.length(); ++i) value += b[i];

		for (int i = 0; i < min(l, (int) b.length()); ++i) {
			value[i] += b[i] - '0';
			if (value[i] > '9') {
				value[i] -= 10;
				if (i == value.length() - 1) value += '1';
				else add(i + 1);
			}
		}
	}

	void operator+=(bint b) {
		*this += b.getReversedValue();
	}

	string getValue() {
		string r = value;
		reverse(r.begin(), r.end());
		return r;
	}
	string getReversedValue() {
		return value;
	}

};

void P1() {
	string line = "";
	getline(input, line);
	deque<int> days(9, 0);
	int offset = '0', total = 0;

	for (int i = 0; i < line.length(); i += 2) ++days[line[i] - offset];
	
	for (int d = 0; d < 80; ++d) {
		int pregnant = days[0];
		days.pop_front();
		days.push_back(pregnant);
		days[6] += pregnant;
	}

	for (int n : days) total += n;
	
	cout << total;
}

void P2() {
	string line = "";
	getline(input, line);
	deque<bint> days(9, bint());
	int offset = '0';
	bint total = bint();

	for (int i = 0; i < line.length(); i += 2) ++days[line[i] - offset];

	for (int d = 0; d < 256; ++d) {
		bint pregnant = days[0];
		days.pop_front();
		days.push_back(pregnant);
		days[6] += pregnant;
	}

	for (bint n : days) total += n;

	cout << total.getValue();
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
