#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
using namespace chrono;

typedef tuple<int, int, int, int> MapKey;

ifstream input("input.txt");

struct Player {
	int position = 0, score = 0;
};

struct hash_player {
	size_t operator()(const MapKey &p) const {
		return get<0>(p) * 10000 + (get<1>(p) - 1) * 1000 + get<2>(p) * 10 + get<3>(p) - 1;
	}
};
struct equal_player {
	bool operator()(const MapKey &p1, const MapKey &p2) const {
		return p1._Equals(p2);
	}
};

unordered_map<int, int> weightage = {
	{3, 1},
	{4, 3},
	{5, 6},
	{6, 7},
	{7, 6},
	{8, 3},
	{9, 1}
};

void P1() {
	string line = "";
	Player players[2];
	int i = 0, n = 2, tens = 0;

	while (getline(input, line)) players[i++] = {line[line.length() - 1] - '0'};
	i = 0;

	while (true) {
		int total = 3 * n;

		if (n > 9) {
			n %= 10;
			++tens;
		}

		players[i].position = (players[i].position + total - 1) % 10 + 1;
		players[i].score += players[i].position;

		i = ++i % 2;
		if (players[(i + 1) % 2].score >= 1000) break;
		n += 3;
	}

	cout << (tens * 10 + n + 1) * players[i].score;
}

void P2() {
	string line = "";
	unordered_map <MapKey , unsigned long long, hash_player, equal_player> possibilities;
	unsigned long long wins[2] = {};
	int n = 0;
	int starting[2] = {};

	while (getline(input, line)) starting[n++] = line[line.length() - 1] - '0';
	possibilities.insert(make_pair(make_tuple(starting[0], 0, starting[1], 0), 1));

	while (possibilities.size() > 0) {
		const auto &[key, weight] = *possibilities.begin();

		for (const auto &[roll1, w1] : weightage) {
			const int new_pos1 = (get<0>(key) + roll1 - 1) % 10 + 1, new_score1 = get<1>(key) + new_pos1;
			if (new_score1 >= 21) {
				wins[0] += weight * w1;
				continue;
			}
			for (const auto &[roll2, w2] : weightage) {
				const int new_pos2 = (get<2>(key) + roll2 - 1) % 10 + 1, new_score2 = get<3>(key) + new_pos2;
				if (new_score2 >= 21) wins[1] += weight * w2;
				else possibilities[make_tuple(new_pos1, new_score1, new_pos2, new_score2)] += weight * w1 * w2;
			}
		}
		possibilities.erase(key);
	}

	cout << max(wins[0], wins[1]);
}

int main() {
	auto start = high_resolution_clock::now();
	P1();
	cout << '\n';
	input.clear();
	input.seekg(0, input.beg);
	P2();
	auto end = high_resolution_clock::now();
	input.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
