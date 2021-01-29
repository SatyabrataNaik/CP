#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

ll expmod(ll x, ll n, ll mod){
	if(n == 0) return 1;
	else if(n % 2 == 0){
		ll temp = expmod(x, n / 2, mod);
		return (temp * temp) % mod;
	}
	else{
		return (expmod(x, n - 1, mod) * x) % mod;
	}
}

ll modinv(ll x, ll mod){
	return expmod(x, mod - 2, mod);
}

const int MAXN = 2e5 + 5;
const ll mod = 1e9 + 7;

ll fac[MAXN], invfac[MAXN];

void compute_fac_invfac() {
	fac[0] = 1; invfac[0] = 1;
	rep(i, 1, MAXN) {
		fac[i] = fac[i - 1] * i % mod;
		invfac[i] = invfac[i - 1] * modinv(i, mod) % mod;
	}
}

ll C(int n, int k) {
	assert(n >= 0);
	if (n < k) return 0;
	else {
		return fac[n] * invfac[k] % mod * invfac[n - k] % mod;
	}
}

int main(){
	int n; 
	cin >> n;
	cout << modinv(n, (int)(1e9 + 7)) << endl;
}
