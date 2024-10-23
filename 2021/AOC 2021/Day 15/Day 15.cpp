#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;
using namespace chrono;

typedef tuple<int, int, int> T;
typedef tuple<int, int, int, int> Q;

ifstream input("input.txt");
vector<vector<int>> grid;
int w = 0, h = 0, fx = 0, fy = 0;

struct comp {
	constexpr bool operator()(T const& a, T const& b) const noexcept {
		return get<2>(a) > get<2>(b);
	}
};
struct comp2 {
	constexpr bool operator()(Q const& a, Q const& b) const noexcept {
		return get<3>(a) > get<3>(b);
	}
};

void build_grid() {
	string line = "";

	while (getline(input, line)) {
		vector<int> row;
		for (int i : line) row.push_back(i - '0');
		grid.push_back(row);
	}
	w = grid[0].size();
	h = grid.size();
}

int get_risk(int x, int y) {
	if (x < w && y < h) return grid[y][x];

	return (grid[y % h][x % w] + (int)(x / w) + (int)(y / h) - 1) % 9 + 1;
}

int dijkstra(int scale) {
	fx = w * scale - 1;
	fy = h * scale - 1;

	priority_queue<T, vector<T>, comp> current;
	unordered_map<int, unordered_set<int>> history;

	current.push(make_tuple(0, 0, 0));

	while (true) {
		T to_move = current.top();
		current.pop();

		auto& [x, y, risk] = to_move;

		for (int dir = -1; dir < 2; dir += 2) {
			for (int dx = 0; dx < 2; ++dx) {
				for (int dy = 0; dy < 2; ++dy) {
					if (x + dx * dir < 0 || y + dy * dir < 0 || x + dx * dir > fx || y + dy * dir > fy || dx == dy) continue;
					int r = get_risk(x + dx * dir, y + dy * dir);

					if (x + dx * dir == fx && y + dy * dir == fy) return risk + r;
					if (history[y + dy * dir].contains(x + dx * dir)) continue;
					history[y + dy * dir].insert(x + dx * dir);
					current.push(make_tuple(x + dx * dir, y + dy * dir, risk + r));
				}
			}
		}
	}
}

int a_star(int scale) {
	fx = w * scale - 1;
	fy = h * scale - 1;

	priority_queue<Q, vector<Q>, comp2> current;
	unordered_map<int, unordered_set<int>> history;

	current.push(make_tuple(0, 0, 0, 0));

	while (true) {
		Q to_move = current.top();
		current.pop();

		if (history[get<1>(to_move)].contains(get<0>(to_move))) continue;
		auto& [x, y, risk, h] = to_move;
		history[y].insert(x);

		for (int dir = -1; dir < 2; dir += 2) {
			for (int dx = 0; dx < 2; ++dx) {
				for (int dy = 0; dy < 2; ++dy) {
					if (x + dx * dir < 0 || y + dy * dir < 0 || x + dx * dir > fx || y + dy * dir > fy || dx == dy) continue;
					int r = get_risk(x + dx * dir, y + dy * dir);

					if (x + dx * dir == fx && y + dy * dir == fy) return risk + r;
					current.push(make_tuple(x + dx * dir, y + dy * dir, risk + r, h + r - dx * dir - dy * dir));
				}
			}
		}
	}
}

void P1() {
	cout << dijkstra(1);

}

void P2() {
	cout << dijkstra(5);
}

int main() {
	auto start = high_resolution_clock::now();
	build_grid();
	P1();
	cout << '\n';
	P2();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	input.close();
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
