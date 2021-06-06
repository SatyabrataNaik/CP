#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

const int maxn = 2e7 + 5;
vi primes;
int smallest_prime_fac[maxn];
bool composite[maxn];

void generatePrimes(){
    for(int i = 2; i < maxn; i++){
        if(!composite[i]) {
            primes.push_back(i);
            smallest_prime_fac[i] = i;
        }
        for(int j = 0; j < primes.size() && i * primes[j] < maxn; j++){
            composite[i * primes[j]] = true;
            smallest_prime_fac[i * primes[j]] = primes[j];
            if(i % primes[j] == 0){
                break;
            }
        }   
    }
}

map<int, int> sieveFactor(int n) {
    assert(n < maxn && n >= 2);
    map<int, int> ans;

    while (n != 1) {
        int cur_fac = smallest_prime_fac[n];
        debug(n, cur_fac);
        int cur_cnt = 0;
        while (n % cur_fac == 0) {
            cur_cnt += 1;
            n /= cur_fac;
        }
        ans[cur_fac] = cur_cnt;
    }

    return ans;
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