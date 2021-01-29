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

struct Edge
{
	int u, v, cost;
	Edge(int u, int v, int c): u(u), v(v), cost(c){}
};

struct cmp
{
	bool operator()(pi a, pi b){
		return a > b;
	}
};
struct Prim{
	int n, m = 0, spanningcost = 0;
	vi tree;
	vector<bool> taken;
	vector<Edge> edges;
	vector<vi> adj;

	Prim(int n): n(n){
		adj.resize(n+1);
		taken.assign(n, false);
	}

	void add_edge(int u, int v, int cost){
		edges.push_back(Edge(u, v, cost));
		adj[u].push_back(m++);
		edges.push_back(Edge(v, u, cost));
		adj[v].push_back(m++);
	}

	void findMST(){
		priority_queue<pi, vpi, cmp> q;
		taken[0] = true;
		for(auto eid: adj[0]){
			q.push(make_pair(edges[eid].cost, eid));
		}

		while(!q.empty()){
			pi x = q.top();
			q.pop();
			int eid = x.second;
			int next = edges[eid].v;
			if(!taken[next]){
				taken[next] = true;
				tree.push_back(eid);
				spanningcost+= edges[eid].cost;
				for(int eid2: adj[next]){
					q.push(make_pair(edges[eid2].cost, eid2));
				}
			}
		}
	}
};

int main(int argc, char *argv[]){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	//the nodes start from zero
	Prim g(n);
	for(int i=0; i<m; i++){
		int u, v, c;
		cin >> u >> v >> c;
		g.add_edge(u, v, c);
	}
	g.findMST();
	cout << "MST" << endl;
	for(int i=0; i<g.tree.size(); i++){
		int eid = g.tree[i];
		cout << g.edges[eid].u << " " << g.edges[eid].v << endl;
	}
	debugone(g.spanningcost);

	return 0;
}