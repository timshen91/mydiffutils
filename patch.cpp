#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char * argv[]) {
	if (argc != 3) {
		cout << "Usage : " << argv[0] << " old_file diff_file\n";
		return 1;
	}
	string temp;
	ifstream f1(argv[1]);
	vector<string> s;
	while (getline(f1, temp)) {
		s.push_back(temp);
	}
	ifstream f2(argv[2]);
	int line;
	int offset;
	vector<bool> deleted(s.size());
	vector<string> added(s.size());
	getline(f2, temp);
	while (temp.substr(0, 5) == "line ") {
		line = atoi(temp.substr(5).c_str()) - 1;
		offset = 0;
		getline(f2, temp);
		while (temp[0] == '-') {
			temp = temp.substr(1);
			if (temp != s[line + offset]) {
				return 1;
			}
			deleted[line + offset++] = true;
			getline(f2, temp);
		}
		while (temp[0] == '+') {
			temp = temp.substr(1);
			added[line] += temp;
			added[line] += "\n";
			getline(f2, temp);
		}
	}
	for (unsigned int i = 0; i < s.size(); i++) {
		cout << added[i];
		if (!deleted[i]) {
			cout << s[i] << "\n";
		}
	}
	return 0;
}
