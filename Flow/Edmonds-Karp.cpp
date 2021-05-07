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
    FlowEdge(int u, int v, int cap): u(u), v(v), cap(cap), flow(0){}
  };



struct Network{

  vector<FlowEdge> edges;
  vector<vi> adj;
  int n, m = 0, s, t;
  queue<int> q;
  vi level, parent, preedge;

  Network(int n, int s, int t): n(n), s(s), t(t){
    adj.resize(n+1);
    level.resize(n+1);
    parent.resize(n+1);
    preedge.resize(n+1);
  }

  void add_edge(int u, int v, int cap){
    edges.push_back(FlowEdge(u, v, cap));
    edges.push_back(FlowEdge(v, u, 0));
    adj[u].push_back(m);
    adj[v].push_back(m+1);
    m+=2;
    debug(u, v, cap);
  }

  int bfs(){
    int toreturn = int(1e9);

    while(!q.empty()){
      // level is already set
      int node = q.front();
      q.pop();
      for(int i=0; i<adj[node].size(); i++){
        FlowEdge temp = edges[adj[node][i]];
        int next = temp.v;
        if(level[next] != -1 || temp.cap - temp.flow < 1){
          continue;
        }

        q.push(next);
        toreturn = min(toreturn, temp.cap - temp.flow);

        level[next] = level[node] + 1;
        parent[next] = node;
        preedge[next] = adj[node][i];
      }
    }

    if(level[t] == -1) return -1;
    else{
      return toreturn;
    }
  }


  int flow(){
    int res = 0;
    while(true){
      fill(level.begin(), level.end(), -1);
      fill(parent.begin(), parent.end(), -1);
      fill(preedge.begin(), preedge.end(), -1);
      level[s] = 0;
      q.push(s);
      int temp = bfs();
      if(temp != -1){
       res+= temp;
       int cur = t;
       while(cur != s){
        int edge =  preedge[cur];
        edges[edge].flow += temp;
        edges[edge ^ 1].flow -= temp;
        cur = edges[edge].u;
       }
      }
      else break;
    }

    return res;
  }

};

bool visited[1000+1];
void dfs(int node){
  for(auto &eid: adj[node]){
    if(eid%2 == 0 && edges[eid].cap - edges[eid].flow > 0 && !visited[edges[eid].v]){
      visited[edges[eid].v] = true;
      dfs(edges[eid].v);
    }
  }
}

int main(){
ios::sync_with_stdio(false);
cin.tie(0);
cout.tie(0);

//Here we take as input
//1. number of vertices n
//2. number of edges m
//3. number of 
//4. m lines giving vertices u, v and capacity

int n, m, s, t;
cin >> n >> m >> s >> t;
Network g(n, s, t);
for(int i=0; i<m; i++){
  int u, v, cap;
  cin >> u >> v >> cap;
  g.add_edge(u, v, cap);
}

cout << "Maximum Flow is: " << g.flow() << endl;
cout << "Now finding a cut" << endl;

visited[s] = true;
dfs(s);
vi cut;
for(int i=1; i<=n; i++){
  if(visited[i]) cut.push_back(i);
}
debugtwo(cut);
}
