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

struct cmp
{
	bool operator()(pair<int, pi> a, pair<int, pi> b){
		return a > b;
	}
};

struct FlowEdge{
	int u, v, cap, flow, cost, constcost;
	FlowEdge(int u, int v, int cap, int cost): u(u), v(v), cap(cap), flow(0), cost(cost), constcost(cost){}
};

struct Network{
	vector<FlowEdge> edges;
	vector<vi > adj;
	vi level, preedge, bottleneckflow;
	vector<bool> visited;
	priority_queue<pair<int, pi>, vector<pair<int, pi> >, cmp> q;

	int n, m = 0, s, t;

	Network(int n, int s, int t): n(n), s(s), t(t){
		adj.resize(n+1);
		level.resize(n+1);
		preedge.resize(n+1);
		bottleneckflow.resize(n+1);
		visited.resize(n+1);
	}

	void add_edge(int u, int v, int cap, int cost){
		edges.push_back(FlowEdge(u, v, cap, cost));
		edges.push_back(FlowEdge(v, u, 0, (-1)* cost));
		adj[u].push_back(m);
		adj[v].push_back(m+1);
		m+= 2;
	}

	void reduce_cost(){
		for(int i=0; i<m; i++){
			edges[i].cost = level[edges[i].u] + edges[i].cost - level[edges[i].v];
		}
	}

	void bellman(){
		//find levels
		fill(level.begin(), level.end(), int(1e9));
		level[s] = 0;

		for(int i=0; i<n; i++){
			for(int eid = 0; eid < m; eid++){
				if(edges[eid].cap - edges[eid].flow < 1) continue;
				else {
					level[edges[eid].v] = min(level[edges[eid].v], level[edges[eid].u] + edges[eid].cost);
				}
			}
		}
	}

	void dijkstra(){
		fill(level.begin(), level.end(), int(1e9));
		level[s] = 0;

		fill(visited.begin(), visited.end(), false);
		visited[s] = true;

		//bottleneckflow and predegree are mainted
		bottleneckflow[s] = int(1e9);
		for(int i = 0; i<adj[s].size(); i++){
			int eid = adj[s][i];
			if(edges[eid].cap - edges[eid].flow >= 1){
				q.push({edges[eid].cost, {edges[eid].v, eid}});
			}
		}

		while(!q.empty()){
			pair<int, pi> temp = q.top();
			q.pop();
			int dist = temp.first, node = temp.second.first, eid = temp.second.second;
			if(!visited[node]){
				visited[node] = true;
				bottleneckflow[node] = min(bottleneckflow[edges[eid].u], edges[eid].cap - edges[eid].flow);
				level[node] = dist;
				preedge[node] = eid;

				for(int i=0; i<adj[node].size(); i++){
					int newid = adj[node][i];
					if(edges[newid].cap - edges[newid].flow >= 1){
						q.push({dist + edges[newid].cost, {edges[newid].v, newid}});
					}
				}
			}
		}

	} 

	void augment(){
		// this basically changes the residual graph
		int cur = t;
		while(cur != s){
			int u = edges[preedge[cur]].u;
			edges[preedge[cur]].flow += bottleneckflow[t];
			edges[preedge[cur] ^ 1].flow -= bottleneckflow[t];
			cur = u;
		}
	}


	int flow(){
		int res = 0;
		bellman();
		reduce_cost();

		while(true){
			dijkstra(); //this will level vertices.
			if(!visited[t]) break;
			else{
				res+= bottleneckflow[t];
				augment();
				reduce_cost();
			}
		}

		return res;
	}


	int cost(){
		//assume that flow() has already been called
		int res = 0;
		for(int i=0; i<m; i+=2){
			res+= (edges[i].flow) * (edges[i].constcost);
		}

		return res;
	}

};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, s, t;
	cin >> n >> m >> s >> t;
	Network g(n, s, t);
	for(int i=0; i<m; i++){
		int u, v, cap, cost;
		cin >> u >> v >> cap >> cost;
		g.add_edge(u, v, cap, cost);
	}

	cout << "Flow is " << g.flow() << endl;
	cout << "Cost is " << g.cost() << endl;
}