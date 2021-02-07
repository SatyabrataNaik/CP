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

const int MAXN = 2e5 + 10;
const int INF = 2e9;

struct SegTree {
	//Range add and range minimum
	//1 based indexing

	// int t[4*MAXN], a[MAXN], lazy[4*MAXN];
	int n;
	vector<int> t, a, lazy;

	SegTree(int _n) {
		n = _n;
		t.resize(4*MAXN, INF); a.resize(MAXN, 0); lazy.resize(4*MAXN, 0);
		build(a, 1, 1, n);
	}

	int get_val(int l, int r) {
		return query(1, 1, n, l, r);
	}

	void update_val(int l, int r, int addend) {
		update(1, 1, n, l, r, addend);
	}

	void build(vector<int> a, int v, int tl, int tr) {
			if (tl == tr) {
					t[v] = a[tl];
			} else {
					int tm = (tl + tr) / 2;
					build(a, v*2, tl, tm);
					build(a, v*2+1, tm+1, tr);
					t[v] = min(t[v*2], t[v*2 + 1]);
			}
	}


	void push(int v) {
			t[v*2] += lazy[v];
			lazy[v*2] += lazy[v];
			t[v*2+1] += lazy[v];
			lazy[v*2+1] += lazy[v];
			lazy[v] = 0;
	}

	//range addition
	void update(int v, int tl, int tr, int l, int r, int addend) {
			if (r < tl || l > tr) 
					return;
			if (l <= tl && tr <= r) {
					t[v] += addend;
					lazy[v] += addend;
			} else {
					push(v);
					int tm = (tl + tr) / 2;
					update(v*2, tl, tm, l, r, addend);
					update(v*2+1, tm+1, tr, l, r, addend);
					t[v] = min(t[v*2], t[v*2+1]);
			}
	}

	int query(int v, int tl, int tr, int l, int r) {
			if (r < tl || l > tr)
					return INF;
			if (l <= tl && tr <= r)
					return t[v];
			push(v);
			int tm = (tl + tr) / 2;
			return min(query(v*2, tl, tm, l, r), 
								 query(v*2+1, tm+1, tr, l, r));
	}

};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	SegTree tree(n);
	int q;
	cin >> q;
	// 1 for update and 2 for minimum
	for(int i=0; i<q; i++){
		int x;
		cin >> x;
		if(x == 1){
			int l, r, addend; cin >> l >> r >> addend;
			tree.update_val(l, r, addend);
		}
		else{
			int l, r;
			cin >> l >> r;
			cout << tree.get_val(l, r) << endl;
		}
	}
}