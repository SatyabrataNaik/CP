#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

void find_euclid_coeff(ll a, ll b, ll &x, ll &y){
	if(a % b == 0){
		x = 0;
		y = 1;
	}
	else{
		ll x1, y1;
		find_euclid_coeff(b, a % b, x1, y1);
		x = y1;
		y = x1 - (a / b) * y1;
	}
}

int main(){
	ll maxi = 0;
	for(int a = 2; a <= 10000; a++){
		for(int b = 1; b <= a; b++){
			// ll a, b;
			// cin >> a >> b;
			ll x, y;
			//ax + by = gcd
			ll g = __gcd(a, b);
			if (a < b)
				swap(a, b);
			//assert(a >= b);
			find_euclid_coeff(a, b, x, y);
			assert(a * x + b * y == g);
			ll lcm = a * b / g;
			assert(abs(a * x) <= lcm && abs(b * y) <= lcm);
			// cout << x << " " << y << endl;
			maxi = max(maxi, max(abs(x), abs(y)));
		}
	}
	cout << maxi << endl;
}
