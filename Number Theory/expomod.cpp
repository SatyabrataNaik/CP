#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

ll expmod(ll x, ll n, ll mod){
	//x ^ n % mod
	if(n == 0) return 1;
	else if(n % 2 == 0){
		ll temp = expmod(x, n / 2, mod);
		return (temp * temp) % mod;
	}
	else{
		return (expmod(x, n - 1, mod) * x) % mod;
	}
}

int main(){
    
    return 0;
}