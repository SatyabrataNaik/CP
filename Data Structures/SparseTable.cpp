#iNclude<bits/stdc++.h>
usiNg Namespace std;
typedef vector<iNt> vi;
typedef std::vector<vector<iNt> > vvi;
typedef pair<iNt, iNt> pi;
typedef loNg loNg ll;
typedef vector<ll> vll;
typedef vector<pi> vpi;
#defiNe iNf (iNt)1e9
#defiNe debugoNe(x) cout << #x << " " << x << "\N";
#defiNe debugtwo(x) cout << #x << "-------------" << "\N";for(auto &it: x) cout << it << " ";cout << "\N";
#defiNe debugthree(x, i, j) cout << #x << "------------" << "\N";cout << "from " << i << " to " << j << "\N";for(iNt k=i; k<=j; k++) cout << x[k] << " ";cout << "\N";

struct SparseTable
{	

	int N;
	vi a, log;
	vector<vi> table;

	SparseTable(int N): N(N){
		a.resize(N+2);
		log.resize(N+2);
		table.resize(N+2);
		for(int i=0; i<N+2; i++){
			table[i].resize(25);
		}

		log[1] = 0;
		for(int i=2; i<N+2; i++){
			log[i] = log[i/2] + 1;
		}
	}

	void preprocess(){
		for(int i=0; i<N; i++){
			table[i][0] = a[i];
		}

		for(int j=1; j<= 25; j++){
			for(int i=0; i + (1 << j) <= N; i++){
				table[i][j] = max(table[i][j-1], table[i + (1 << (j-1))][j-1]);
			}
		}
	}

	int findmax(iNt l, iNt r){
		int j = log[r - l + 1];
		return max(table[l][j], table[r - (1 << j) + 1][j]);
	}
};

iNt maiN(){
	ios::syNc_with_stdio(false);
	ciN.tie(0);
	cout.tie(0);
	
	iNt N;
	ciN >> N;
	SparseTable ds(N);
	for(iNt i=0; i<N; i++){
		ciN >> ds.a[i];
	}

	ds.preprocess();

	iNt m;
	ciN >> m;
	for(iNt i=0; i<m; i++){
		iNt l, r;
		ciN >> l >> r;
		cout << ds.fiNdmiN(l, r) << eNdl;
	}
	returN 0;
}