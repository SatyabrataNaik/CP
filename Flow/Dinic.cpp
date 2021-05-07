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


struct FlowEdge{
    int u, v, cap, flow;
    FlowEdge(int a, int b, int capa){
    	u = a;
    	v = b;
    	cap = capa;
    	flow = 0;
    }
  };

vector<vi> adj;
vector<FlowEdge> edges;


struct Network{
	int n, m = 0, s, t;
	queue<int> q;
	vi level, ptr;


	Network(int n, int s, int t): n(n), s(s), t(t){
		adj.resize(n+1);
		level.resize(n+1);
		ptr.resize(n+1);
	}

	void add_edge(int u, int v, int cap){
		edges.push_back(FlowEdge(u, v, cap));
		edges.push_back(FlowEdge(v, u, 0));
		adj[u].push_back(m);
		adj[v].push_back(m+1);
		m+= 2;		
	}

	bool bfs(){
		while(!q.empty()){
			int node = q.front();
			q.pop();
			for(int eid: adj[node]){
				int next = edges[eid].v;
				if(level[next] != -1 || edges[eid].cap - edges[eid].flow < 1) continue;
				else{
					q.push(next);
					level[next] = level[node] + 1;
				}
			}
		}
		return level[t] != -1;
	}

	int dfs(int node, int pushed){
		if(node == t) return pushed;
		else{
			for(int &cid = ptr[node]; cid< adj[node].size(); cid++){
				int eid = adj[node][cid];
				int next = edges[eid].v;
				if(level[next] != level[node] + 1 || edges[eid].cap - edges[eid].flow < 1) continue;
				else{
					int val = dfs(next, min(pushed, edges[eid].cap - edges[eid].flow));
					if(val == 0) continue;
					else{
						edges[eid].flow+= val;
						edges[eid ^ 1].flow-= val;
						return val;
					}
				}
			}
			return 0;
		}
	}

	int flow(){
		int res = 0;
		while(true){
			fill(level.begin(), level.end(), -1);
			fill(ptr.begin(), ptr.end(), 0);
			level[s] = 0;
			q.push(s);

			if(!bfs()){
				break;
			}
			else{
				while(true){
					int val = dfs(s, (int)1e9);
					if(val == 0) break;
					else res+= val;
				}
			}
		}
		return res;
	}
};

vi cut;
vector<bool> visited;

void dfs(int node){
	for(auto &eid: adj[node]){
		if(eid%2 == 0 && edges[eid].cap - edges[eid].flow > 0 ){
			int next = edges[eid].v;
			if(!visited[next]){
				cut.push_back(next);
				visited[next] = true;
				dfs(next);
			}
		}
	}
}

int main(){
	int n, m, s, t;

	cin >> n >> m >> s >> t;
	visited.resize(n+1);
	Network g(n, s, t);
	for(int i=0; i<m; i++){
		int u, v, cap;
		cin >> u >> v >> cap;
		g.add_edge(u, v, cap);
	}

	cout << "Flow is " << g.flow() << endl;
	visited[s] = true;
	cut.push_back(s);
	debugtwo(cut);

}