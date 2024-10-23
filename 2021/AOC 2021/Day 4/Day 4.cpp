#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;
using namespace chrono;

ifstream input("input.txt");

tuple<string, vector<vector<string>>, vector<vector<int>>, int> create_vectors() {
	string commands = "", line = "";
	vector<vector<string>> boards;
	vector<vector<int>> chosen;
	vector<string> board;

	getline(input, commands);
	input.seekg(2, input.cur);

	while (getline(input, line)) {
		if (line == "") {
			boards.push_back(board);
			board = vector<string>{};
			continue;
		}
		string num = "";

		for (int i = 0; i < line.size(); ++i) {
			if (line[i] == ' ') {
				if (num == "") continue;
				board.push_back(num);
				num = "";
			}
			else num += line[i];
		}
		board.push_back(num);
	}
	boards.push_back(board);

	int width = sqrt(board.size());

	for (int i = 0; i < boards.size(); ++i) chosen.push_back(vector<int>(width * width, 0));

	return make_tuple(commands, boards, chosen, width);
}

void P1() {
	string command = "";
	bool found = false;
	int total = 0;
	string commands = "", line = "";
	vector<vector<string>> boards;
	vector<vector<int>> chosen;
	vector<string> board;
	int width = 0;
	tie(commands, boards, chosen, width) = create_vectors();

	for (int i = 0; i < commands.size(); ++i) {
		if (commands[i] != ',') command += commands[i];
		else {
			if (command == "") continue;
			for (int j = 0; j < boards.size(); ++j) {
				board = boards[j];
				vector<string>::iterator index = find(board.begin(), board.end(), command);

				if (index != board.end()) {

					chosen[j][index - board.begin()] = 1;

					bool exists = true;
					for (int x = 0; x < width; ++x) {
						exists = true;
						for (int y = 0; y < width; ++y) {
							if (chosen[j][x + y * width] == 0) {
								exists = false;
								break;
							}
						}
						if (!exists) continue;
						found = true;
						for (int l = 0; l < chosen[j].size(); ++l) if (chosen[j][l] == 0) total += stoi(board[l]);
						break;
					}
					if (found) break;

					for (int y = 0; y < width; ++y) {
						exists = true;
						for (int x = 0; x < width; ++x) {
							if (chosen[j][x + y * width] == 0) {
								exists = false;
								break;
							}
						}
						if (!exists) continue;
						found = true;
						for (int l = 0; l < chosen[j].size(); ++l) if (chosen[j][l] == 0) total += stoi(board[l]);
						break;
					}
					if (found) break;
				}
			}
			if (found) {
				total *= stoi(command);
				break;
			}
			command = "";
		}
	}
	cout << total;
}
void P2() {
	int total = 0, width = 0, last_i = 0;
	string commands = "", line = "", command = "", last_c = "";
	vector<vector<string>> boards;
	vector<vector<int>> chosen;
	vector<string> board, last_won;
	vector<int> to_delete;
	bool found = false;
	tie(commands, boards, chosen, width) = create_vectors();

	for (int i = 0; i < commands.size(); ++i) {
		if (commands[i] != ',') command += commands[i];
		else {
			if (command == "") continue;
			for (int j = 0; j < boards.size(); ++j) {
				bool c = true;
				for (int k : to_delete) if (k == j) {
					c = false;
					break;
				}
				if (!c) continue;

				board = boards[j];
				vector<string>::iterator index = find(board.begin(), board.end(), command);

				if (index != board.end()) {

					chosen[j][index - board.begin()] = 1;

					bool exists = true;
					for (int x = 0; x < width; ++x) {
						exists = true;
						for (int y = 0; y < width; ++y) {
							if (chosen[j][x + y * width] == 0) {
								exists = false;
								break;
							}
						}
						if (!exists) continue;
						found = true;
						break;
					}

					if (!found) {
						for (int y = 0; y < width; ++y) {
							exists = true;
							for (int x = 0; x < width; ++x) {
								if (chosen[j][x + y * width] == 0) {
									exists = false;
									break;
								}
							}
							if (!exists) continue;
							found = true;
							break;
						}
					}

					if (found) {
						last_won = board;
						last_i = j;
						last_c = command;
						to_delete.push_back(j);
						found = false;
					}
				}
			}
			if (i == commands.size() - 1) break;
			command = "";
		}

	}

	for (int l = 0; l < last_won.size(); ++l) if (chosen[last_i][l] == 0) total += stoi(last_won[l]);
	total *= stoi(last_c);

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