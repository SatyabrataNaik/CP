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

struct Suffix
{
	int suffixId;
	pair<int, int> rank;
	Suffix(int x, int y, int z){
		suffixId = x;
		rank.first = y;
		rank.second = z;
	}
};


bool cmp(Suffix a, Suffix b){
	return a.rank < b.rank;
}

/**
*Kasai's Algorithm
*Refer geeksforgeeks for more details
*OBSERVATION ____________________________________________________________________________________
	Let lcp of suffix beginning at myString[i] be k. 
	If k is greater than 0, then lcp for suffix beginning at myString[i + 1] will be at-least k-1
*COMPLEXITY _____________________________________________________________________________________
	Similar to KMP. Observe variable 'k'.
	time ans space complexity: O(n)
*/

vector<int> buildLCP(string myString, vector<int> suffixArray){
	int n = (int) myString.length();
	vector<int> lcp(n), suffixRank(n);
	//computation of suffixRank
	for(int i = 0; i < n; i++){
		suffixRank[suffixArray[i]] = i;
	}
	int k = 0; //stores the value of lcp of myString[i - 1]
	for(int i = 0; i < n; i++){
		if(suffixRank[i] == n - 1){
			lcp[i] = 0;
			continue;
		}
		else{
			//j is the index in myString that comes after suffix_i in suffixArray
			//we directly match suffix_i and suffix_j and increment 'k'
			int j = suffixArray[suffixRank[i] + 1];
			while(i + k < n && j + k < n && myString[i + k] == myString[j + k]){
				k++;
			}
			lcp[suffixRank[i]] = k;
			if(k > 0){
				k--;
			}
		}
	}
	return lcp;
}

vector<int> buildSuffixArray(string myString){
	int n = (int)myString.length();
	vector<Suffix> suffixes;
	for(int i = 0; i < n; i++){
		suffixes.push_back(Suffix(i, (int)(myString[i] - 'a'), (i + 1 < n) ? (int)(myString[i + 1] - 'a') : -1));
	}
	vector<int> suffixRank(n);

	for(int len = 2; len <= n; len *= 2){
		//sort
		//Radix sort may be an option for improvement to O(nlogn) 
		sort(suffixes.begin(), suffixes.end(), cmp);
		for(int i = 0; i < n; i++){
			suffixRank[suffixes[i].suffixId] = i;
		}
		//update the ranks
		//update rank.first
		pair<int, int> prev = suffixes[0].rank;
		int tempRank = 0;
		suffixes[0].rank.first = tempRank;
		for(int i = 1; i < n; i++){
			if(suffixes[i].rank == prev){
				suffixes[i].rank.first = tempRank;
			}
			else{
				prev = suffixes[i].rank;
				suffixes[i].rank.first = ++tempRank;
			}
		}
		//update rank.second
		for(int i = 0; i < n; i++){
			int secondId = suffixes[i].suffixId + len;
			if(secondId >= n){
				suffixes[i].rank.second = -1;
			}
			else{
				suffixes[i].rank.second = suffixes[suffixRank[secondId]].rank.first;
			}
		}
	}

	vector<int> suffixArray;
	for(int i = 0; i < n; i++){
		suffixArray.push_back(suffixes[i].suffixId);
	}
	return suffixArray;
}

int main(){
	string s;
	cin >> s;
	vi a = buildSuffixArray(s);
	vi b = buildLCP(s, a);
	debugtwo(a);
	debugtwo(b);
	return 0;
}