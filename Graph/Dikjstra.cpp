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
struct Dikjstra{
	int n, m = 0;
	vi dist;
	vector<bool> taken;
	vector<Edge> edges;
	vector<vi> adj;
	int s, t;

	Dikjstra(int n, int s, int t): n(n), s(s), t(t){
		adj.resize(n+1);
		taken.assign(n, false);
		dist.resize(n + 1);
	}

	void add_edge(int u, int v, int cost){
		edges.push_back(Edge(u, v, cost));
		adj[u].push_back(m++);
		edges.push_back(Edge(v, u, cost));
		adj[v].push_back(m++);
	}

	void findShortestPath(){
		priority_queue<pi, vpi, cmp> q;
		taken[s] = true;
		dist[s] = 0;
		for(auto eid: adj[s]){
			q.push(make_pair(edges[eid].cost, eid));
		}

		while(!q.empty()){
			pi x = q.top();
			q.pop();
			int eid = x.second;
			int next = edges[eid].v;
			if(!taken[next]){
				taken[next] = true;
				dist[next] = x.first;
				for(int eid2: adj[next]){
					q.push(make_pair(edges[eid2].cost + x.first, eid2));
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
	Dikjstra g(n, 1, n);
	for(int i=0; i<m; i++){
		int u, v, c;
		cin >> u >> v >> c;
		g.add_edge(u, v, c);
	}
	g.findShortestPath();
	cout << "Dikjstra" << endl;
	cout << "Path cost is: " << g.dist[n] << endl;
	return 0;
}