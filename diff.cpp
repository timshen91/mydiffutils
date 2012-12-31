// Slow and dirty dynamic programming algorithm(O(n^2)), with limitation(4096) of lines of input.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int f[4096][4096];
pair<unsigned int, unsigned int> pre[4096][4096];

int main(int argc, char * argv[]) {
	if (argc != 3) {
		cout << "Usage : " << argv[0] << " old_file new_file\n";
		return 1;
	}
	string temp;
	ifstream f1(argv[1]);
	vector<string> s1;
	while (getline(f1, temp)) {
		s1.push_back(temp);
	}
	ifstream f2(argv[2]);
	vector<string> s2;
	while (getline(f2, temp)) {
		s2.push_back(temp);
	}

	for (unsigned int i = 0; i <= s1.size(); i++) {
		f[i][0] = 0;
	}
	for (unsigned int i = 0; i <= s2.size(); i++) {
		f[0][i] = 0;
	}
	for (unsigned int i = 1; i <= s1.size(); i++) {
		for (unsigned int j = 1; j <= s2.size(); j++) {
			if (f[i - 1][j] > f[i][j - 1]) {
				f[i][j] = f[i - 1][j];
				pre[i][j] = make_pair(i - 1, j);
			} else {
				f[i][j] = f[i][j - 1];
				pre[i][j] = make_pair(i, j - 1);
			}
			if (s1[i - 1] == s2[j - 1]) {
				if (f[i][j] < f[i - 1][j - 1] + 1) {
					f[i][j] = f[i - 1][j - 1] + 1;
					pre[i][j] = make_pair(i - 1, j - 1);
				}
			}
		}
	}
	pair<unsigned int, unsigned int> now = make_pair(s1.size(), s2.size()), last;
	vector<pair<unsigned int, unsigned int> > ans;
	while (now.first != 0 && now.second != 0) {
		last = now;
		now = pre[now.first][now.second];
		if (f[now.first][now.second] + 1 == f[last.first][last.second]) {
			ans.push_back(last);
		}
	}
	for (unsigned int i = 0, j = ans.size() - 1; i < j; i++, j--) {
		swap(ans[i], ans[j]);
	}
	ans.push_back(make_pair(s1.size() + 1, s2.size() + 1));
	unsigned int l = 1, r = 1;
	for (unsigned int i = 0; i < ans.size(); i++) {
		if (l < ans[i].first || r < ans[i].second) {
			cout << "line " << l << "\n";
			while (l < ans[i].first) {
				cout << "-" << s1[l - 1] << "\n";
				l++;
			}
			while (r < ans[i].second) {
				cout << "+" << s2[r - 1] << "\n";
				r++;
			}
		}
		l++;
		r++;
	}
	return 0;
}
