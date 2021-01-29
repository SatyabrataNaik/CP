#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<pi> vpi;
#define inf 2e9
#define debugone(x) cout << #x << " " << x << endl;
#define debugtwo(x) cout << #x << "-------------" << endl;for(auto &it: x) cout << it << " ";cout << endl;
#define debugthree(x, i, j) cout << #x << "------------" << endl;cout << "from " << i << " to " << j << endl;for(int k=i; k<=j; k++) cout << x[k] << " ";cout << endl;

struct Trie {
	vector<map<int, int>> nodes;

	Trie() {
		nodes.resize(1);
	}

	void insert(vi &to_insert) {
		insert_helper(0, to_insert, 0);
	}

	void insert_helper(int v, vi &to_insert, int pos) {
		if (pos >= sz(to_insert)) return;

		if (!nodes[v].count(to_insert[pos])) {
			map<int, int> to_push;
			nodes[v][to_insert[pos]] = sz(nodes);
			nodes.push_back(to_push);
		} 
			
		insert_helper(nodes[v][to_insert[pos]], to_insert, pos + 1);
	}

	bool if_exists(vi &to_search) {
		return if_exists_helper(0, to_search, 0);
	}

	bool if_exists_helper(int v, vi &to_search, int pos) {
		if (pos >= sz(to_search)) return 1;
		else {
			if (nodes[v].count(to_search[pos])) {
				return if_exists_helper(nodes[v][to_search[pos]], to_search, pos + 1);
			} else {
				return 0;
			}
		}
	}

};

int main(int argc, char *argv[]){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}