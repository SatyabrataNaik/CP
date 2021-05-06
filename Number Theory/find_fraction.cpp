#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;

template<typename T> T mo(T x, T y) { x %= y; return x <= 0 ? x + y : x; }

/*
http://www.ktiwari.in/algo/t92.pdf - Optimal search for rationals, Lemma 5
Given an interval I = [α/β, γ/δ], there exists
a fraction a_mn/b_mn in I = [α/β, γ/δ] such that for all a/b ∈ I, a_mn <= a, b_mn <= b. Further, we can
determine this fraction in time O(log2(max(α, β, γ, δ))).
*/
pll find_fraction(ll alpha, ll beta, ll gamma, ll delta) {
	if (alpha / beta == gamma / delta && alpha % beta != 0) {
		pll it = find_fraction(delta, gamma % delta, beta, alpha % beta);
		ll a = (alpha / beta) * it.first + it.second;
		return make_pair(a, it.first);
	} else {
		return make_pair((alpha + beta - 1) / beta, 1);
	}
}

int main(){
	ll a, b, c, d; cin >> a >> b >> c >> d;
	pll x = find_fraction(a, b, c, d);
	cout << x.first << "/" << x.second << endl;
  return 0;
}