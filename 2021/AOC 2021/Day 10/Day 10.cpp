#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <unordered_map>
#include <algorithm>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

long long calculate_total(int part) {
	string line = "";
	int total = 0;
	unordered_map<char, char> pairs = {{ '(', ')' }, { '{', '}' }, { '<', '>' }, { '[', ']' }};
	unordered_map<char, int> invalid = {{')', 3 }, {'}', 1197 }, {'>', 25137 }, {']', 57}};
	unordered_map<char, int> ends = {{')', 1 }, {'}', 3 }, {'>', 4 }, {']', 2}};
	deque<long long> incomplete_lines;

	while (getline(input, line)) {
		deque<char> queue;
		bool ended = true;

		for (char c : line) {
			if (pairs.find(c) == pairs.end() ) {
				if (queue[0] != c) {
					if (part == 1) total += invalid[c];
					ended = false;
					break;
				} else queue.pop_front();
			} else queue.push_front(pairs[c]);
		}

		if (part == 2 && ended && queue.size() > 0) {
			long long t = 0;

			for (char c : queue) {
				t *= 5;
				t += ends[c];
			}
			incomplete_lines.push_back(t);
		}
	}

	if (part == 2) {
		sort(incomplete_lines.begin(), incomplete_lines.end());
		return incomplete_lines[(incomplete_lines.size() - 1) / 2];
	} else return total;
}

void P1() {
	cout << calculate_total(1);
}

void P2() {
	cout << calculate_total(2);
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
