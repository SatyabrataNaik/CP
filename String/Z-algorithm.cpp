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
* Z-array is constructed. z[i] = maximum length of string STARTING from i, that is a
proper prefix of given string s
* example: s = a a b a c a b
           z = 0 1 0 1 0 1 0 
* [l, r] is maintained such that r is maximum possible with r < n
* s[l, r] is a proper prefix of s. i.e., s[l, r] = s[0, r - l]
* z[0] = 0
* Complexity is O(n) because the inner while loops are executed at most n. 
This is because r < n and every time program goes inside while loops, r is incremented by 1
**/

vector<int> generateZArray(const string &s){
	int n = (int)s.length();
	vi z(n);
	z[0] = 0; // we only calculate proper prefix
	int l = 0, r = 0;
	for(int i = 1; i < n; i++){
		if(i > r){
			//here, l = r = i, even though s[0] != s[i], because for next iteration, it is anyway i > r
			l = r = i;
			while(r < n && s[r - i] == s[r]){
				r++;
			}
			z[i] = r - l;
			r--;
		}
		else{
			if(z[i - l] < r - i + 1){
				z[i] = z[i - l];
			}
			else{
				l = i;
				while(r < n && s[r - l] == s[r]){
					r++;
				}
				z[i] = r - l;
				r--;
			}
		}
	}
	return z;
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