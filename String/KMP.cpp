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
*Implementation of Knuth-Morris-Pratt (KMP) algorithm
*we have string "mystring" and we will find the "prefixFunction"
*prefixFunction[i] = length of longest prefix Ending at position 'i'

*CLRS has a fantastic implementation
PROOF: ----------------------------------------------
	Notations:
	P_k = prefix of length k
	pi[q] = prefix function
	pi*[q] = {pi[q], pi[pi[q]], pi[pi[pi[q]]], ...}
	
	Whole algorithm is based on following Lemma:
	pi*[q] = set of all suffixes of P_q (which means we have to only traverse through it to find largest largest suffix of P_q-1)
	Formally,
	pi*[q] = {k: k < q, P_k suffix of P_q}

ANALYSIS: -------------------------------------------
	We have following observations for 'length' variable:
	1) length < n; length >= 0
	3) for loop can only increase 'length' by one;
	2) while loop can only decrease 'length'
	Time and Space complexity: O(n)
*/

vector<int> createPrefixFunction(string myString){
	int n = (int)myString.length();
	//we will be using 1 based indexing.
	myString.insert(myString.begin(), 1, '@');
	vector<int> prefixFunction(n + 1);

	prefixFunction[0] = -1;
	prefixFunction[1] = 0;
	int length = 0;

	for(int i = 2; i <= n; i++){
		while(length > 0 && myString[length + 1] != myString[i]){
			length = prefixFunction[length];
		}
		if(myString[length + 1] == myString[i]){
			length++;
		}
		prefixFunction[i] = length;
	}
	return prefixFunction;
}

vector<int> createPrefixFunctionNaiveMethod(string myString){
	int n = (int)myString.length();
	//we will be using 1 based indexing.
	myString.insert(myString.begin(), 1, '@');
	vector<int> prefixFunction(n + 1);

	prefixFunction[0] = -1;
	prefixFunction[1] = 0;
	int length = 0;

	for(int i = 2; i <= n; i++){
		int length = i - 1;
		while(length > 0){
			bool matches = true;
			int pos1 = length, pos2 = i;
			while(pos1 > 0){
				if(myString[pos1] != myString[pos2]){
					matches = false;
					break;
				}
				pos1--;
				pos2--;
			}
			if(matches){
				break;
			}
			else length--;
		}
		prefixFunction[i] = length;
	}
	return prefixFunction;
}

int main(){
	string s;
	cin >> s;
	vi a, b;
	debugtwo(a = createPrefixFunction(s));
	debugtwo(b = createPrefixFunctionNaiveMethod(s));
	assert(a == b);
	return 0;
}