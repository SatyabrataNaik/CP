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

struct Fenwick
{
	int n;
	vi a, t;

	Fenwick(int n): n(n){
		a.resize(n+1);
		t.resize(n+1);
		a[0] = 0;
		t[0] = 0;
	}

	void update(int pos, int val){
		for(int x = pos; x <= n; x+= x & -x){
			t[x]+= val - a[pos];
		}
		a[pos] = val;
	}

	int get(int pos){
		int res = 0;
		for(int x = pos; x >= 1; x-= x & -x){
			res+= t[x];
		}
		return res;
	}

};

int main(int argc, char *argv[]){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	Fenwick tree(n);
	for(int i=1; i<=n; i++){
		int val;
		cin >> val;
		tree.update(i, val);
	}	
	int q;
	cin >> q;
	// 1 for update and 2 for sum
	for(int i=0; i<q; i++){
		int x;
		cin >> x;
		if(x == 1){
			int pos, val;
			cin >> pos >> val;
			tree.update(pos, val);

			debugthree(tree.a, 0, n);
			cout.flush();
		}
		else{
			int pos;
			cin >> pos;
			cout << tree.get(pos) << endl;
			cout.flush();
		}
	}

}