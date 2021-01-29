#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

const int maxn = 2e6 + 5;
vi primes;
bool composite[maxn];

void generatePrimes(){
	for(int i = 2; i < maxn; i++){
		if(!composite[i]){
			primes.push_back(i);
		}
		for(int j = 0; j < primes.size() && i * primes[j] < maxn; j++){
			composite[i * primes[j]] = true;
			if(i % primes[j] == 0){
				break;
			}
		}	
	}
}

map<int, int> factorise(int n){
    map<int, int> prime_factorisation;
    int currn = n;
    for(int fac = 2; fac * fac <= currn; fac++){
        if(currn % fac == 0){
            int cnt = 0;
            while(currn % fac == 0){
                currn /= fac;
                cnt++;
            }
            prime_factorisation[fac] = cnt;
        }
    }
    if(currn != 1){
        prime_factorisation[currn] = 1;
    }
    return prime_factorisation;
}

int main(){
    generatePrimes();
    map<int, int> ans = factorise(100);
    for(auto x: ans){
        cout << x.first << " " << x.second << endl;
    }
}