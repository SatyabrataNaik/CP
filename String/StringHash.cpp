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


struct StringHash {
	ll p, ll m, ll n; 
	vll p_pow, h;

	StringHash(string s, ll _p, ll _m) {
		n = s.size();
		p = _p; 
		m = _m;

		p_pow = vll(n);
		p_pow[0] = 1;
		for (int i = 1; i < n; i++)
			p_pow[i] = (p_pow[i-1] * p) % m;

		h = vll(n + 1);
		for (int i = 0; i < n; i++)	
			h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;
	}

	find_substring_hash(int l, int r) {
		assert(l >= 0 && r >= l && r < n);

		ll cur_h = (h[r + 1] + m - h[l]) % m;
		cur_h = (cur_h * p_pow[n-l-1]) % m; //note that multiplication is used. not div
		return cur_h;
	}
};

int count_unique_substrings(string const& s) {
	int n = s.size();

	const int p = 31;
	const int m = 1e9 + 9;
	vector<long long> p_pow(n);
	p_pow[0] = 1;
	for (int i = 1; i < n; i++)
			p_pow[i] = (p_pow[i-1] * p) % m;

	vector<long long> h(n + 1, 0);
	for (int i = 0; i < n; i++)
			h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;

	int cnt = 0;
	for (int l = 1; l <= n; l++) {
			set<long long> hs;
			for (int i = 0; i <= n - l; i++) {
					long long cur_h = (h[i + l] + m - h[i]) % m;
					cur_h = (cur_h * p_pow[n-i-1]) % m;
					hs.insert(cur_h);
			}
			cnt += hs.size();
	}
	return cnt;
}

int main(){
	string a;
	cin >> a;
	auto res = generateZArray(a);
	for(auto &it: res){
		cout << it << " ";
	}
	cout << endl;
}