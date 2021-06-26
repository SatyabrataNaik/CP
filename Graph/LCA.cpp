struct LCA {
	int n, TIME, LOGN;
	vvi g, up;
	vi tin, tout;

	LCA (int _n) {
		n = _n;
		TIME = 0;
		LOGN = ceil(log2(n)) + 1;
		up = vvi(n + 1, vi(LOGN));
		tin = tout = vi(n + 1);
	}

	void dfs(int v, int pr) {
		//v = pr for v to be root
		//g must have been initialized
		assert(sz(g) > 0);
		up[v][0] = pr;
		rep(i, 1, LOGN) up[v][i] = up[up[v][i - 1]][i - 1];

		tin[v] = TIME++;
		for (int to : g[v]) if (to != pr) {
			dfs(to, v);
		}
		tout[v] = TIME++;
	}

	bool is_ancestor(int pr, int v) {
		return (tin[pr] <= tin[v] && tout[v] <= tout[pr]);
	}

	int lca(int u, int v) {
		if (is_ancestor(u, v)) return u;
		if (is_ancestor(v, u)) return v;
		repi(i, LOGN - 1, 0) if (not is_ancestor(up[u][i], v)) u = up[u][i];
		return up[u][0];
	}
};