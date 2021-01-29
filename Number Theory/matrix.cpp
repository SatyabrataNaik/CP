#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef vector<vector<double>> vvd;
typedef vector<double> vd;

vvd multiply(vvd &a, vvd &b){
	//p x q with q x r --> p x r
	int p = a.size(), q = a[0].size(), r = b[0].size();
	vvd ans(p, vd(r, 0.0));
	for(int i = 0; i < p; i++){
		for(int j = 0; j < r; j++){
			for(int k = 0; k < q; k++){
				ans[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return ans;
}

vvd power(vvd &a, int n){
	int p = a.size(), q = a[0].size();
	if(n == 0){
		//right identity matrix
		vvd ans(q, vd(q));
		for(int i = 0; i < q; i++){
			ans[i][i] = 1.0;
		}
		return ans;
	}
	else if(n % 2 == 0){
		vvd temp = power(a, n / 2);
		return multiply(temp, temp);
	}
	else{
		vvd temp = power(a, n - 1);
		return multiply(a, temp);
	}
}

int main(){
    
    return 0;
}