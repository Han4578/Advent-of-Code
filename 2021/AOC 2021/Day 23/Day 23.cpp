#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;
using namespace chrono;

ifstream part_1("Part 1.txt");
ifstream part_2("Part 2.txt");

struct Space {
	int id = 0;
	char type = 'O';
	vector<int> connected;
};

struct hash_pos {
	size_t operator()(const vector<int> &v) const {
		size_t total = 0;
		for (int n : v) total = total * 10 + n;
		return total;
	}
};

vector<Space> burrow;
vector<int> original;
unordered_map<vector<int>, int, hash_pos> cache;
int minimum = INT_MAX;

int V2();

void construct_burrow(int part) {
	string line = "";
	int id = 0, rooms = 0;

	ifstream &f = (part == 1) ? part_1 : part_2;

	getline(f, line);
	getline(f, line);

	for (char c : line) if (c == '.') {
		burrow.push_back(Space{ id });
		if (id > 0) {
			burrow[id - 1].connected.push_back(id);
			burrow[id].connected.push_back(id - 1);
		}
		++id;
	}
	original = vector<int>(burrow.size(), 0);
	while (getline(f, line)) {
		char c = 'A';
		
		for (int n = 1; n < line.length() - 1; ++n) {
			if (!isalpha(line[n])) continue;
			int connect = (rooms > 0) ? id - rooms : n - 1;
			burrow.push_back(Space{ id, c++ });
			burrow[id].connected.push_back(connect);
			burrow[connect].connected.push_back(id);
			original.push_back(line[n]);
			++id;
		}

		rooms = c - 'A';
	}
}

bool check_room(vector<int> &position, int room) {
	bool available = true;

	while (burrow[room].connected.size() > 1) {
		room = burrow[room].connected[1];
		if (position[room] == 0 || position[room] != burrow[room].type) {
			available = false;
			break;
		}
	}
	return available;
}

void move_pod(vector<int> position, tuple<int, int, int> &movement, int energy) {
	swap(position[get<1>(movement)], position[get<2>(movement)]);
	energy += pow(10, position[get<2>(movement)] - 'A') * get<0>(movement);
	if (energy > minimum) return;

	if (cache.find(position) != cache.end() && cache[position] <= energy) return;
	else cache[position] = energy;
	vector<tuple<int, int, int>> possibilities;
	bool in_place = true;

	for (int i = 0; i < position.size(); ++i) {
		if (position[i] == 0) continue;
		if (burrow[i].type == position[i] && check_room(position, i)) continue;
		in_place = false;
		vector<int> current = { i }, next;
		unordered_set<int> history;
		int	distance = 1;


		while (current.size() > 0) {
			for (int c : current) {
				if (history.find(c) != history.end()) continue;
				history.insert(c);
				for (int con : burrow[c].connected) {
					if (position[con] != 0) continue;
					next.push_back(con);
					if (burrow[con].connected.size() > 2) continue;
					if (burrow[i].type != 'O' && burrow[con].type == 'O') possibilities.push_back(make_tuple(distance, i, con));
					else if (burrow[i].type == 'O' && burrow[con].type == position[i]) {
						if (check_room(position, con)) possibilities.push_back(make_tuple(distance, i, con));
					}
				}
			}

			swap(current, next);
			next.clear();
			++distance;
		}
	}

	if (in_place) {
		minimum = min(minimum, energy);
		return;
	}

	sort(possibilities.begin(), possibilities.end(), [](tuple<int, int, int> &a, tuple<int, int, int> &b) {return get<0>(a) < get<0>(b);});

	for (auto &p : possibilities) {
		move_pod(position, p, energy);
	}
}

void P1() {
	construct_burrow(1);
	tuple<int, int, int> no_move = { 0, 0, 0 };
	move_pod(original, no_move, 0);
	cout << minimum;
}

void P2() {
	construct_burrow(2);
	cout << V2();

}

int main() {
	auto start = high_resolution_clock::now();
	P1();
	cout << '\n';
	cache.clear();
	burrow.clear();
	original.clear();
	P2();
	auto end = high_resolution_clock::now();
	part_1.close();
	part_2.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}

vector<int> new_pos(vector<int> pos, int old, int new_p) {
	swap(pos[old], pos[new_p]);
	return move(pos);
}

int V2() {
	priority_queue < pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater<pair<int, vector<int>>>> queue;
	unordered_set<vector<int>, hash_pos> history;
	queue.push(make_pair(0, original));
	while (queue.size() > 0) {
		auto p = queue.top();
		queue.pop();
		vector<int> &position = p.second;
		if (history.find(position) != history.end()) continue;

		int distance = 1;
		bool in_place = true;

		for (int i = 0; i < position.size(); ++i) {
			if (position[i] == 0) continue;
			if (burrow[i].type == position[i] && check_room(position, i)) continue;
			vector<int> current = { i }, next;
			unordered_set<int> history2;
			int	distance = 1;
			in_place = false;

			while (current.size() > 0) {
				for (int c : current) {
					if (history2.find(c) != history2.end()) continue;
					history2.insert(c);
					for (int con : burrow[c].connected) {
						if (position[con] != 0) continue;
						next.push_back(con);
						if (burrow[con].connected.size() > 2) continue;
						if ((burrow[i].type != 'O' && burrow[con].type == 'O') || (burrow[i].type == 'O' && burrow[con].type == position[i] && check_room(position, con))) {
							queue.push(make_pair(p.first + pow(10, position[i] - 'A') * distance, new_pos(position, i, con)));
						}
					}
				}

				swap(current, next);
				next.clear();
				++distance;
			}
		}
		if (in_place) return p.first;
		history.insert(position);
	}
}