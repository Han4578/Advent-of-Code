#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

ifstream input("input.txt");
bool can_split = false;
vector<string> lines;

struct Snail {
	Snail *branches[2] = {nullptr, nullptr}, *parent = nullptr;
	int value = -1;

	Snail(int val, Snail* par) {
		value = val;
		parent = par;
	}

	Snail(Snail *val) {
		parent = val;
	}

	Snail(Snail *a, Snail *b) {
		branches[0] = a;
		branches[1] = b;
		if (a != nullptr) a->parent = this;
		if (b != nullptr) b->parent = this;
	}
};

void explode(Snail* node, int const l);

Snail* build_pair(const string &s, Snail *parent) {
	Snail *pair = new Snail(parent);
	if (s[0] != '[') {
		pair->value = stoi(s);
		return pair;
	}

	for (int i = 1; i < s.length(); ++i) {
		if (s[i] == ',') continue;
		if (s[i] == '[') {
			int count = 1, j = i + 1;
			while (count > 0) {
				if (s[j] == '[') ++count;
				else if (s[j] == ']') --count;
				++j;
			}
			pair->branches[(pair->branches[0] == nullptr) ? 0 : 1] = build_pair(s.substr(i, j - i), pair);
			i = j;
		} else {
			string digit = "";
			while (isdigit(s[i])) digit += s[i++];
			pair->branches[(pair->branches[0] == nullptr) ? 0 : 1] = build_pair(digit, pair);
		}	
	}

	return pair;
}

void display(const Snail* node) {
	cout << '[';
	for (int i = 0; i < 2; ++i) {
		if (node->branches[i]->value > -1) cout << node->branches[i]->value;
		else display(node->branches[i]);
		if (i == 0) cout << ',';
	}
	cout << ']';
}

void split(Snail* node, int const layer) {
	node->branches[0] = new Snail{node->value / 2, node};
	node->branches[1] = new Snail{(int)ceil((float)node->value / 2), node};

	node->value = -1;
	if (layer >= 4) explode(node, layer);
	else {
		for (int i = 0; i < 2; ++i) {
			if (node->branches[i]->value > 9) split(node->branches[i], layer + 1);
		}
	}
}

void explode(Snail* node, int const l) {
	node->value = 0;
	pair<Snail*, int> snails[2] = {};
	for (int i = 0; i < 2; ++i) {
		if (node->branches[i]->value == 0) continue;
		Snail *current = node, *parent = node->parent;
		int layer = l;
		while (parent->parent != nullptr && parent->branches[i] == current) {
			current = parent, parent = parent->parent;
			--layer;
		}
		if (parent->parent == nullptr && parent->branches[i] == current) continue;
		current = parent->branches[i];
		int j = (i + 1) % 2;
		while (current->value == -1) {
			current = current->branches[j];
			++layer;
		}

		current->value += node->branches[i]->value;
		snails[i] = make_pair(current, layer);
	}
	for (auto &[snail, layer] : snails) {
		if (snail == nullptr) continue;
		if (can_split && snail->value >= 10) {
			split(snail, layer);
		}
	}
}

void reduce(Snail *node, int const layer) {
	if (node->value == -1) {
		if (layer >= 4) explode(node, layer);
		else {
			for (int i = 0; i < 2; ++i) {
				reduce(node->branches[i], layer + 1);
			}
		}
	}
	else if (can_split && node->value > 9) split(node, layer);
}

int calc(const Snail* node) {
	int total = 0;
	for (int i = 0; i < 2; ++i) total += (3 - i) * ((node->branches[i]->value == -1) ? calc(node->branches[i]) : node->branches[i]->value);
	return total;
}

void reduction(Snail *node) {
	can_split = false;
	reduce(node, 0);
	can_split = true;
	reduce(node, 0);
}

void read_lines() {
	string line = "";
	while (getline(input, line)) lines.push_back(line);
}

void P1() {
	Snail* root = build_pair(lines[0], nullptr);

	for (int i = 1; i < lines.size(); ++i) {
		root = new Snail(root, build_pair(lines[i], nullptr));
		reduction(root);
	}

	cout << calc(root);
}

void P2() {
	int highest = 0;

	for (int i = 0; i < lines.size() - 1; ++i) {
		for (int j = i + 1; j < lines.size(); ++j) {
			for (int k = 0; k < 2; ++k) {
				Snail* temp = new Snail(build_pair(lines[(k == 0)? i: j], nullptr), build_pair(lines[(k == 1)? i: j], nullptr));
				reduction(temp);
				highest = max(highest, calc(temp));
			}
		}
	}

	cout << highest;
}

int main() {
	auto start = high_resolution_clock::now();
	read_lines();
	P1();
	cout << '\n';
	P2();
	auto end = high_resolution_clock::now();
	input.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
