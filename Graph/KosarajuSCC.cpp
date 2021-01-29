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


struct Graph{
	int n, m = 0; // n>=1   vertices are 1, 2, 3, ...
	vi component, tempnodes;
	vector<bool> visited, visitedone;
	vector<vi > adj, revadj;
	int compo = 0;

	Graph(int n): n(n){
		component.resize(n+1);
		visited.resize(n+1);
		visitedone.resize(n+1);
		adj.resize(n+1);
		revadj.resize(n+1);
	}

	void add_edge(int u, int v){
		adj[u].push_back(v);
		m++;
		revadj[v].push_back(u);
	}

	void dfsone(int node){
		for(int next: adj[node]){
			if(!visitedone[next]){
				visitedone[next] = true;
				dfsone(next);
			}
		}
		tempnodes.push_back(node);
	}

	void dfstwo(int node, int val){
		for(int next: revadj[node]){
			if(!visited[next]){
				visited[next] = true;
				component[next] = val;
				dfstwo(next, val);
			}
		}
	}

	void scc(){
		fill(visitedone.begin(), visitedone.end(), false);
		dfsone(1);
		visitedone[1] = true;

		fill(visited.begin(), visited.end(), false);

		for(int i=tempnodes.size() -1; i>= 0; i--){
			if(!visited[tempnodes[i]]){
				compo++;
				visited[tempnodes[i]] = true;
				component[tempnodes[i]] = compo;
				dfstwo(tempnodes[i], compo);
			}
		}
	}

};

int main(){
	int n, m;
	cin >> n >> m;
	Graph g(n);
	for(int i=0; i<m; i++){
		int u, v;
		cin >> u >> v;
		g.add_edge(u, v);
	}
	g.scc();
	// debugtwo(g.component);
	debugthree(g.component, 1, g.component.size()-1);
	cout << "#components: " << g.compo << endl;
}