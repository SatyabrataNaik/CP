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
		p.assign(N, 0);
		rank.assign(N, 0);
		for(int i=0; i<N; i++) p[i] = i;
	}

	int findSet(int i){
		if(p[i] == i) return i;
		else return (p[i] = findSet(p[i]));
	}

	void unionSet(int i, int j){
		int x = findSet(i), y = findSet(j);
		if(x != y){
			if(rank[x] > rank[y]){
				p[x] = y;
			}
			else {
				p[y] = x;
				if(rank[x] == rank[y]) rank[y]++;
			}
		}
	}
};

struct Edge
{
	int u, v, cost;
	Edge(int u, int v, int c): u(u), v(v), cost(c){}
};

struct Kruskal{
	int n, m = 0, spanningcost = 0;
	vi tree;
	vector<Edge> edges;
	vector<vi> adj;

	Kruskal(int n): n(n){
		adj.resize(n+1);
	}

	void add_edge(int u, int v, int cost){
		edges.push_back(Edge(u, v, cost));
		adj[u].push_back(m++);
		edges.push_back(Edge(v, u, cost));
		adj[v].push_back(m++);
	}

	void findMST(){
		vpi tempedges;
		for(int i=0; i<m; i++){
			tempedges.push_back(make_pair(edges[i].cost, i));
		}
		sort(tempedges.begin(), tempedges.end());
		UnionFind temp(m);
		for(int i=0; i<tempedges.size(); i++){
			int eid = tempedges[i].second;
			int u = edges[eid].u, v = edges[eid].v;
			if(temp.findSet(u) == temp.findSet(v)) continue;
			else{
				tree.push_back(eid);
				temp.unionSet(u, v);
				spanningcost+= edges[eid].cost;
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
	Kruskal g(n);
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