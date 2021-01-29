#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<pi> vpi;

#define debugone(x) cout << #x << " " << x << endl;
#define debugtwo(x) cout << #x << "-------------" << endl;for(auto &it: x) cout << it << " ";cout << endl;
#define debugthree(x, i, j) cout << #x << "------------" << endl;cout << "from " << i << " to " << j << endl;for(int k=i; k<=j; k++) cout << x[k] << " ";cout << endl;

struct UnionFind{
	vi p, rank;
	UnionFind(int N){
		p.resize(N+1);
		rank.resize(N+1);
		for(int i=0; i<N; i++) {
			p[i] = i;
			rank[i] = 0;
		}
	}

	int findSet(int i){
		if(p[i] == i) return i;
		else return (p[i] = findSet(p[i]));
	}

	void unionSet(int i, int j){
		int x = findSet(i), y = findSet(j);
		if(x != y){
			if(rank[x] > rank[y]){
				p[y] = x;
			}
			else {
				p[x] = y;
				if(rank[x] == rank[y]) rank[y]++;
			}
		}
	}
};

int main(int argc, char *argv[]){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	
	
}