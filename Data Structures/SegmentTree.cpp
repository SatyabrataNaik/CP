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

struct SegmentTree
{	
	//Range Minimum Query
	vi a, t;
	int n;

	SegmentTree(int n): n(n){
		a.resize(n+1);
		t.resize(4*n+1);
	}

	void update(int pos, int val){
		updatehelper(pos, val, 1, 1, n); //pos, val, node, left, right 
		//node is the index in the tree
	}

	int get(int l, int r){
		return gethelper(l, r, 1, 1, n);
	}

	void updatehelper(int pos, int val, int node, int left, int right){
		if(pos < left || pos > right) return;
		else if(left == right){
			a[pos] = val;
			t[node] = val;
		}
		else{
			updatehelper(pos, val, 2*node, left, (left+right)/2);
			updatehelper(pos, val, 2*node + 1, (left+right)/2 + 1, right);
			t[node] = min(t[2*node], t[2*node+1]);
		}
	}

	int gethelper(int l, int r, int node, int left, int right){
		if(r < left || l > right) return inf;
		else if( l <= left && right <= r) return t[node];
		else{
			return min(gethelper(l, r, 2*node, left, (left + right)/2), gethelper(l, r, 2*node+1, (left+right)/2 + 1, right));
		}
	}
};

int main(int argc, char *argv[]){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	SegmentTree tree(n);	
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
			int l, r;
			cin >> l >> r;
			cout << tree.get(l, r) << endl;
			cout.flush();
		}
	}
}