#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

const int maxn = 2e7 + 5;
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
int main(){
	// int n = 10;
	// cout << "Enter the number of primes to generate: ";
	generatePrimes();
	// cin >> n;
	for(int i = 0; i < primes.size() - 1; i++){
		if(primes[i] == 2011 && primes[i + 1] - primes[i] == 2){
			cout << primes[i] << " " << primes[i + 1] << endl;
			return 0; 
		}
	}
	cout << endl;
}
