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

/**
1. Go over the subsets in decreasing order
2. Example:   x = 10011000
		(x - 1) = 10010111, i.e, all the bits after right most bit are 1
3. This (x - 1) when taken and ('&') with n results in the next smallest subset
4. Be careful for the terminating condition (x == 0)
**/

void generateSubsets(int n){
	cout << bitset<8>(n) << endl;
	for(int x = n; x > 0; x = (x - 1) & n){
		cout << bitset<8>(x) << endl;
	}
	cout << bitset<8>(x) << endl;
}

int main(int argc, char *argv[]){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n;
	cin >> n;
	generateSubsets(n);
}