#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;
using namespace chrono;

struct R {
	long long value = 0;
	int length = 0;
};

ifstream input("input.txt");
string binary = "";

long long to_dec(string binary) {
	long long total = 0;
	for (int i = binary.length() - 1; i >= 0; --i) if (binary[i] == '1') total += pow(2, binary.length() - i - 1);
	return total;
}

void operate(long long &total, long long value, int id) {
	if (total == -1) {
		total = value;
		return;
	}
	switch (id) {
		case 0:
			total += value;
			break;
		case 1:
			total *= value;
			break;
		case 2:
			if (value < total) total = value;
			break;
		case 3:
			if (value > total) total = value;
			break;
		case 5:
			total = total > value;
			break;
		case 6:
			total = total < value;
			break;
		case 7:
			total = total == value;
			break;
	}
}

R op(string packet) {
	int total = to_dec(packet.substr(0, 3));

	if (to_dec(packet.substr(3, 3)) == 4) { //literal
		for (int i = 6; i < packet.length(); i += 5) {
			if (packet[i] == '0') return {total, i + 5};
		}

	} else {
		if (packet[6] == '1') {
			int start = 18;
			for (int i = 0; i < to_dec(packet.substr(7, 11)); ++i) {
				R result = op(packet.substr(start));
				total += result.value;
				start += result.length;
			}
			return { total, start};
		} else {
			int limit = to_dec(packet.substr(7, 15));
			for (int i = 0; i < limit;) {
				R result = op(packet.substr(22 + i, limit - i));
				total += result.value;
				i += result.length;
			}
			return { total, 22 + limit };
		}
	}
}

R op2(string packet) {
	int id = to_dec(packet.substr(3, 3));

	if (id == 4) { //literal
		string total = "";
		for (int i = 6; i < packet.length(); i += 5) {
			total += packet.substr(i + 1, 4);
			if (packet[i] == '0') return { to_dec(total), i + 5 };
		}
			
	} else {
		int length = 0;
		long long total = -1;
		if (packet[6] == '1') {
			int start = 18;
			for (int i = 0; i < to_dec(packet.substr(7, 11)); ++i) {
				R result = op2(packet.substr(start));
				operate(total, result.value, id);
				start += result.length;
			}
			length = start;
		} else {
			int limit = to_dec(packet.substr(7, 15));
			for (int i = 0; i < limit;) {
				R result = op2(packet.substr(22 + i, limit - i));
				operate(total, result.value, id);
				i += result.length;
			}
			length = limit + 22;
		}

		return { total, length };
	}
}

void build_string() {
	char c = ' ';
	unordered_map<char, string> conversions = {
		{'0', "0000"},
		{'1', "0001"},
		{'2', "0010"},
		{'3', "0011"},
		{'4', "0100"},
		{'5', "0101"},
		{'6', "0110"},
		{'7', "0111"},
		{'8', "1000"},
		{'9', "1001"},
		{'A', "1010"},
		{'B', "1011"},
		{'C', "1100"},
		{'D', "1101"},
		{'E', "1110"},
		{'F', "1111"}
	};

	while (input >> c) binary += conversions[c];
}

void P1() {
	cout << op(binary).value;
}

void P2() {
	cout << op2(binary).value;

}

int main() {
	auto start = high_resolution_clock::now();
	build_string();
	P1();
	cout << '\n';
	P2();
	auto end = high_resolution_clock::now();
	input.close();
	auto duration = duration_cast<microseconds>(end - start);
	cout << '\n' << (float) duration.count() / 1000 << " ms";
	return 0;
}
