#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef std::vector<vector<int> > vvi;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pi> vpi;
#define debugone(x) cerr << #x << " " << x << "\n"; cerr.flush();
#define debugtwo(x) cerr << #x << "-------------" << "\n";for(auto &it: x) cerr << it << " ";cerr << "\n"; cerr.flush();
#define debugthree(x, i, j) cerr << #x << "------------" << "\n";cerr << "from " << i << " to " << j << "\n";for(ll k=i; k<=j; k++) cerr << x[k] << " ";cerr << "\n"; cerr.flush();
#define trace1(x)                cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;
#define trace5(a, b, c, d, e)    cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl;
#define trace6(a, b, c, d, e, f) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl;
 
const int MOD = 1e9 + 7;
const int INF = 1e9 + 5;
const int MAX_N = 1e6 + 5;

vector<vi> tree(MAX_N);
bool block[MAX_N];
int size[MAX_N];
int centroidRoot;
vector<vi> centroidTree(MAX_N);

void dfsFindSize(int node, int parent){
	size[node] = 1;
	for(auto &child: tree[node]){
		if(child != parent && !block[child]){
			dfsFindSize(child, node);
			size[node] += size[child];	
		}
	}
}

//assume that the size of current tree has been calculated
int dfsFindCentroid(int node, int parent, int currSize){
	for(auto &child: tree[node]){
		if(child != parent && 2 * size[child] > currSize && !block[child]){
			return dfsFindCentroid(child, node, currSize);
		}
	}
	return node;
}

int createCentroidTree(int node, int parent){
	// block[parent] = true;
	dfsFindSize(node, parent);
	int x = dfsFindCentroid(node, parent, size[node]);
	if(node == 1 && parent == 1){
		centroidRoot = x;
	}
	block[x] = true;
	for(auto &child: tree[x]){
		if(!block[child]){
			int y = createCentroidTree(child, x);
			centroidTree[x].push_back(y);
		}
	}
	return x;
}

void dfsTest(int node, int parent){
	trace1(node);
	for(auto &child: centroidTree[node]){
		if(child != parent){
			trace1(child);
		}
	}
	for(auto &child: centroidTree[node]){
		if(child != parent){
			dfsTest(child, node);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	createCentroidTree(1, 1);
	dfsTest(centroidRoot, centroidRoot);
	return 0;
}	
