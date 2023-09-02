#include<iostream>
#include<vector>
#include<unordered_set>
#include<tuple>
#include<algorithm>

using namespace std;

bool intersect(vector<bool> &a, vector<bool> &b) {
	bool r = false;
	for (int i = 0; i < a.size() && !r; i++) r = a[i] && b[i];
	return r;
}

bool is_zero(vector<bool> &a) {
	for (bool t : a) if (t) return false;
	return true;
}

int main() {
	int n, m;
	cin >> n >> m; 

	vector<vector<bool>> v(n, vector<bool>(m));

	for (int i = 0; i < n; i++) {
		int k; 
		cin >> k;
		for (int j = 0; j < k; j++) {
			int b;
			cin >> b;
			v[i][b - 1] = true;
		}
	}

	int rank[n] = {0};
	int par[n];
	for (int i = 0; i < n; i++) par[i] = i;

	for (int i = 0; i < n - 1; i++) 
	for (int j = i + 1; j < n; j++) {
		if (intersect(v[i], v[j])) {
			int pi = par[i];
			while (pi != par[pi]) {
				pi = par[pi];
			}

			int pj = par[j];
			while (pj != par[pj]) {
				pj = par[pj];
			}

			if (pi == pj) continue;

			if (rank[pi] < rank[pj]) {
				par[pi] = pj;
			}
			else if (rank[pi] > rank[pj]) {
				par[pj] = pi;
			}
			else {
				par[pj] = pi;
				rank[pi]++;
			}
		}
	}

	vector<int> act_pars;
	unordered_set<int> all_p;
	for (int i = 0; i < n; i++) {
		int act_p = par[i];
		while (act_p != par[act_p]) {
			act_p = par[act_p];
		}
		act_pars.push_back(act_p);
		all_p.insert(act_p);
	}

	vector<pair<int, int>> group_lens;
	for (int i : all_p) {
		int s = 0;
		for (int j : act_pars) {
			s += (j == i);
		}
		group_lens.push_back(make_pair(i, s));
	}

	sort(group_lens.begin(), group_lens.end(), [](pair<int, int> a, pair<int, int> b) {
		return a.second < b.second;
	});

	int cost = group_lens.size() - 1;
	cost += is_zero(v[group_lens.back().first]);
	cout << cost;
}
