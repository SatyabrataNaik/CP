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

int main(){
	int n; 
	cin >> n;
	cout << modinv(n, (int)(1e9 + 7)) << endl;
}
