#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <valarray>

#define PI 3.1415926

using namespace std;
using namespace chrono;

ifstream input("input.txt");

typedef valarray<int> Position;

struct hash_valarray {
	size_t operator()(const Position* a) const {
		return (*a)[0] * 73856093 ^ (*a)[1] * 19349663 ^ (*a)[2] * 83492791;
	}
};
struct equal_valarray {
	size_t operator()(const Position* a, const Position* b) const {
		return equal(begin(*a), end(*a), begin(*b), end(*b));
	}
};

typedef unordered_set<Position*, hash_valarray, equal_valarray> Scanner;
typedef tuple<Position* , Position* , int> Pair;
typedef vector<Pair> PairSet;

Scanner *combined_scanner = nullptr;
vector<Position> scanner_locations = { {0, 0, 0} };
const Position max_distance = { 2000, 2000, 2000 };

void rotate(int a, int b, valarray<int> &v) {
		swap(v[a], v[b]);
		v[a] *= -1;
}

void rotate3D(Position *s, valarray<valarray<int>> &matrix) {
	Position original = *s;
	for (int i = 0; i < 3; ++i) {
		(*s)[i] = (matrix[i] * original).sum();
	}
}

void combine_scanners() {
	string line = "";
	vector<Scanner*> scanners;
	vector<PairSet*> relatives;
	
	while (getline(input, line)) {
		PairSet *relative = new PairSet;
		Scanner *scanner = new Scanner;

		while (input.get() != '\n' && !input.eof()) {
			input.seekg(-1, input.cur);
			Position* pos = new Position(0, 3);
			for (int i = 0; i < 3; ++i) {
				input >> (*pos)[i];
				input.ignore();
			}

			for (Position *beacon : *scanner) relative->push_back(make_tuple(beacon, pos, ((*beacon - *pos) * (*beacon - *pos)).sum()));

			scanner->insert(pos);
		}
		relatives.push_back(relative);
		scanners.push_back(scanner);
	}

	combined_scanner = scanners[0];

	while (relatives.size() > 1) {
		for (int i = 1; i < relatives.size(); ++i) {
			PairSet *posset = relatives[i];
			int overlap = 0, pair_found = 0;
			Pair a1, a2;
			unordered_set<Position *, hash_valarray, equal_valarray> matches;

			for (auto &t2 : *posset) {
				int d = get<2>(t2);
				for (auto &t : *relatives[0]) {
					if (d == get<2>(t)) {
						if (pair_found == 0) {
							a1 = t;
							a2 = t2;
							++pair_found;

						} else if (pair_found == 1) {
							if (get<0>(a1) == get<0>(t) || get<0>(a1) == get<1>(t) || get<1>(a1) == get<1>(t) || get<1>(a1) == get<0>(t)) {
								if (get<0>(a1) != get<0>(t) && get<0>(a1) != get<1>(t)) swap(get<0>(a1), get<1>(a1));
								if (get<0>(a2) != get<0>(t2) && get<0>(a2) != get<1>(t2)) swap(get<0>(a2), get<1>(a2));
								++pair_found;
							};
						}
						matches.insert({ get<0>(t2), get<1>(t2) });
						break;
					}
				}
				if (matches.size() >= 12) break;
			}

			if (matches.size() < 12) continue;

			valarray<int> v1 = *get<0>(a1) - *get<1>(a1), v2 = *get<0>(a2) - *get<1>(a2);

			float dx = 0, dy = 0, dz = 0;

			while (!equal(begin(v1), end(v1), begin(v2), end(v2))) {
				if (dx < 3) {
					++dx;
					rotate(1, 2, v2);
				} else {
					dx = 0;
					rotate(1, 2, v2);
					if (dz < 3 && dy == 0) {
						++dz;
						rotate(0, 1, v2);
					} else {
						dz = 0;
						if (dy == 0) rotate(0, 1, v2);
						++dy;
						for (int i = 0; i < ((round(dy) == 1) ? 1 : 2); ++i) {
							rotate(2, 0, v2);
						}
						if (round(dy) == 2) ++dy;
					}
				}
			}

			dx /= 2;
			dy /= 2;
			dz /= 2;
			
			valarray<valarray<int>> matrix = {
				{(int)round(cos(PI * dy) * cos(PI * dz)), -(int)round(sin(PI * dz)), (int)round(sin(PI * dy) * cos(PI * dz))},
				{(int)round(cos(PI * dx) * cos(PI * dy) * sin(PI * dz) + sin(PI * dx) * sin(PI * dy)), (int)round(cos(PI * dx) * cos(PI * dz)), (int)round(cos(PI * dx) * sin(PI * dy) * sin(PI * dz) - sin(PI * dx) * cos(PI * dy))},
				{(int)round(sin(PI * dx) * cos(PI * dy) * sin(PI * dz) - cos(PI * dx) * sin(PI * dy)), (int)round(sin(PI * dx) * cos(PI * dz)), (int)round(sin(PI * dx) * sin(PI * dy) * sin(PI * dz) + cos(PI * dx) * cos(PI * dy))}
			};				

			rotate3D(get<0>(a2), matrix);
			Position center = *get<0>(a1) - *get<0>(a2);
			scanner_locations.push_back(center);
			delete get<0>(a2);

			for (Position *s : *scanners[i]) {
				if (s == get<0>(a2)) continue;

				rotate3D(s, matrix);

				*s += center;
				
				if (scanners[0]->find(s) == scanners[0]->end()) {
					for (Position *p : *scanners[0]) {
						Position d = *p - *s;
						if ((d > max_distance).sum() > 0) continue;
						relatives[0]->push_back(make_tuple(p, s, (d * d).sum()));
					}
					scanners[0]->insert(s);
				} else delete s;
			}
			delete scanners[i];
			delete relatives[i];
			scanners.erase(scanners.begin() + i);
			relatives.erase(relatives.begin() + i);
			break;
		}
	}
	delete relatives[0];
}

void P1() {
	cout << combined_scanner->size();
}

void P2() {
	int distance = 0;
	for (int i = 0; i < scanner_locations.size(); ++i) {
		for (int j = 0; j < scanner_locations.size(); ++j) {
			distance = max(distance, abs(scanner_locations[i] - scanner_locations[j]).sum());
		}
	}
	cout << distance;
}

int main() {
	auto start = high_resolution_clock::now();
	combine_scanners();
	P1();
	cout << '\n';
	P2();	
	auto end = high_resolution_clock::now();
	input.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}