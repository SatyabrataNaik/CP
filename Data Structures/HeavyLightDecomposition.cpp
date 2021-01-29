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

const int mod = 1e9 + 7;
const int inf = 1e9 + 5;
const int MaxN = 1e6 + 5;


int lcaTable[MaxN][21];

void add(int &a, int b){
	a += b;
	if(a >= mod){
		a -= mod;
	}
}	

int mult(int a, int b){
	return ((ll)a * b) % mod;
}

struct SegmentTree
{	
	int baseArraySize;
	vector<int> baseArray;
	vector<int> tree;

	void resize(int n){
		baseArraySize = n;
		tree.resize(4 * n + 5);
	}

	void buildHelper(int node, int tl, int tr){
		cerr << "insideBuildhelper" << endl;
		debugone(tl);
		debugone(tr);

		if(tl == tr){
			tree[node] = baseArray[tl];
			return;
		}

		int mid = (tl + tr) / 2;
		buildHelper(2 * node, tl, mid);
		buildHelper(2 * node + 1, mid + 1, tr);
		tree[node] = max(tree[2 * node], tree[2 * node + 1]);
		debugone(tree[node]);

	}

	void build(){
		buildHelper(1, 0, baseArraySize - 1);
	}

	int rangeMaxQueryHelper(int node, int tl, int tr, int l, int r){
		if(tr < l || tl > r){
			return -1;
		}
		else if(tl == tr){
			return tree[node];
		}
		else{
			int mid = (tl + tr) / 2;
			return max(rangeMaxQueryHelper(2 * node, tl, mid, l, r), rangeMaxQueryHelper(2 * node + 1, mid + 1, tr, l, r));
		}	
	}

	int rangeMaxQuery(int l, int r){
		return rangeMaxQueryHelper(1, 0, baseArraySize - 1, l, r);
	}

	void updateHelper(int node, int tl, int tr, int pos, int val){
		if(tl == tr){
			assert(tl == pos);
			baseArray[pos] = val;
			tree[node] = val;
		}
		else{
			int mid = (tl + tr) / 2;
			if(pos <= mid){
				updateHelper(2 * node, tl, mid, pos, val);
			}
			else{
				updateHelper(2 * node + 1, mid + 1, tr, pos, val);
			}
			tree[node] = max(tree[2 * node], tree[2 * node + 1]);
		}
	}

	void update(int pos, int val){
		updateHelper(1, 0, baseArraySize - 1, pos, val);
	}
};

struct Node
{
	int parent, subTreeSize, cost, depth; //dfsUpdateNodes
	int positionInBaseArray, chainId; //dfsUpdateBaseArray
};

struct Chain
{
	int chainHead; //dfsUpdateBaseArray
};

struct Edge
{
	int u, v, cost;
	Edge(int u, int v, int cost): u(u), v(v), cost(cost){} 
};

//we are goind to give two queries
//maxWeight(u, v)
//update(u, v, c) /* guaranteed that uv is an edge */

struct HeavyLightDecomposition
{
	int cntNode, cntEdgeTwice, cntChain;
	vector<Node> nodes;
	vector<Chain> chains;
	vector<Edge> edges;
	vector<vector<int>> adj;

	SegmentTree segmentTree;


	HeavyLightDecomposition(int n){
		cntNode = n;
		cntEdgeTwice = 0;
		cntChain = 0;
		nodes.resize(n + 5);
		chains.resize(n + 5);
		adj.resize(n + 5);
		segmentTree.resize(n);

	}

	void addEdge(int u, int v, int c){
		edges.push_back(Edge(u, v, c));
		adj[u].push_back(cntEdgeTwice);
		cntEdgeTwice++;
		edges.push_back(Edge(v, u, c));
		adj[v].push_back(cntEdgeTwice);
		cntEdgeTwice++;
	}

	void dfsUpdateNodes(int curr, int prev, int depth){
		nodes[curr].parent = prev;
		nodes[curr].subTreeSize = 1;
		nodes[curr].depth = depth;

		for(auto &eid: adj[curr]){
			int child = edges[eid].v;
			if(child != prev){
				nodes[child].cost = edges[eid].cost;
				dfsUpdateNodes(child, curr, depth + 1);
				nodes[curr].subTreeSize += nodes[child].subTreeSize;
			}
		}
	}

	/**
	*if a child is found which is not special, then create a new chain and make the child as head of chain
	*/
	void dfsUpdateBaseArray(int curr, int prev){
		segmentTree.baseArray.push_back(nodes[curr].cost);
		nodes[curr].positionInBaseArray = segmentTree.baseArray.size() - 1;
		nodes[curr].chainId = cntChain;

		int specialEdgeId = -1;
		int maxChildSize = -1;
		for(int i = 0; i < adj[curr].size(); i++){
			int child = edges[adj[curr][i]].v;
			if(child != prev){
				if(nodes[child].subTreeSize > maxChildSize){
					specialEdgeId = adj[curr][i];
					maxChildSize = nodes[child].subTreeSize;
				}
			}
		}

		if(specialEdgeId != -1){
			int child = edges[specialEdgeId].v;
			//extent chain
			dfsUpdateBaseArray(child, curr);
		}

		for(auto &eid: adj[curr]){
			int child = edges[eid].v;
			if(child != prev){
				if(eid != specialEdgeId){
					//start a new chain
					cntChain++;
					chains[cntChain].chainHead = child;
					dfsUpdateBaseArray(child, curr);
				}
			}
		}
	}

	void updateLca(){
		lcaTable[1][0] = 1;
		for(int i = 2; i <= cntNode; i++){
			lcaTable[i][0] = nodes[i].parent;
		}

		for(int up = 1; up <= 20; up++){
			for(int node = 1; node <= cntNode; node++){
				int x = lcaTable[node][up - 1];
				if(x != -1){
					x = lcaTable[x][up - 1];
				}
				lcaTable[node][up] = x;
			}
		}
	}

	int lca(int u, int v){
		int depthU = nodes[u].depth, depthV = nodes[v].depth;
		if(depthV < depthU){
			swap(u, v);
			swap(depthU, depthV);
		}

		int liftVHeight = depthV - depthU;
		debugone(liftVHeight);
		debugone(u);
		debugone(v);
		for(int i = 20; i >= 0; i--){
			if((1 << i) <= liftVHeight){
				debugone(v);
				v = lcaTable[v][i];
				liftVHeight -= (1 << i);
			}
		}

		//now u and v are at the same level
		//lift them simultaneously
		debugone(u);
		debugone(v);
		if(u == v) return u;

		for(int i = 20; i >= 0; i--){
			if(lcaTable[u][i] == lcaTable[v][i]){
				continue;
			}
			else{
				u = lcaTable[u][i];
				v = lcaTable[v][i];
			}
		}

		return lcaTable[u][0];
	}

	void build(){
		//assuming all nodes are from 1 to n
		//do dfs
		nodes[1].cost = -1;
		dfsUpdateNodes(1, -1, 0);
		chains[0].chainHead = 1;
		dfsUpdateBaseArray(1, -1);
		segmentTree.build();
		updateLca();
	}

	int crawlTree(int start, int end){
		debugone(start);
		debugone(end);
		int maxResult = -1;

		while(start != end){
			if(nodes[start].chainId == nodes[end].chainId){
				//just do rangeMaxQuery and break
				int pos1 = nodes[end].positionInBaseArray, pos2 = nodes[start].positionInBaseArray;
				cerr << "same chainId" << endl;
				debugone(pos1);
				debugone(pos2);
				maxResult = max(maxResult, segmentTree.rangeMaxQuery(pos1 + 1, pos2));
				break;
			}
			else{
				//find the headNode of chain
				int headNode = chains[nodes[start].chainId].chainHead;
				int pos1 = nodes[headNode].positionInBaseArray, pos2 = nodes[start].positionInBaseArray;
				cerr << "diff chainId" << endl;
				debugone(headNode);
				debugone(pos1);
				debugone(pos2);
				maxResult = max(maxResult, segmentTree.rangeMaxQuery(pos1, pos2));
				start = nodes[headNode].parent;
			}
		}

		return maxResult;
	}

	int maxWeight(int u, int v){
		int ancestor = lca(u, v);
		return max(crawlTree(u, ancestor), crawlTree(v, ancestor));
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, q;
	cin >> n >> q;
	HeavyLightDecomposition hld(n);	
	for(int i = 0; i < n - 1; i++){
		int u, v, c;
		cin >> u >> v >> c;
		hld.addEdge(u, v, c);
	}

	hld.build();

	debugtwo(hld.segmentTree.baseArray);
	debugtwo(hld.segmentTree.tree);
	cerr << "chainIds::::" << endl;
	for(int i = 1; i <= n; i++){
		cerr << hld.nodes[i].chainId << " ";
	}
	cerr << endl;

	for(int i = 0; i < q; i++){
		int x;
		cin >> x;
		if(x == 1){
			//maxWeight
			int u, v;
			cin >> u >> v;
			cout << hld.maxWeight(u, v) << endl;
		}
		else{
			//update
			int u, v, c;
			cin >> u >> v >> c;
			// hld.update(u, v, c);
		}
	}
	return 0;
}	
