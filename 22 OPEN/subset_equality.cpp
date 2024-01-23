//by Dhruv Kkothari
#include <bits/stdc++.h>
using namespace std;
string s, t;
int q;
int n;
unordered_map <string, bool> works;
unordered_map <char, int> freq_s, freq_t;
int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cin>>s>>t>>q;
	for(char c : s){
		freq_s[c]++;
	}
	for(char c : t){
		freq_t[c]++;
	}
	for(int i = 'a'; i <= 'r'; i++){
		for(int j = i + 1; j <= 'r'; j++){
			//simulate the proccess for each pair
			string ss = "";
			ss.push_back(i), ss.push_back(j);
			set <char> has;
			for(auto c : ss)has.insert(c);
			string ns, nt;
			for(char c : s){
				if(has.find(c) != has.end())ns += to_string(c);
			}
			for(char c : t){
				if(has.find(c) != has.end())nt += to_string(c);
			}
			if(ns == nt)works[ss]=1;
			else works[ss] = 0;

		}
	}
	
	while(q--){
		//if it works for "abc", it will work for "ab".
		//furthermore, we check if "ab", "bc", and "ac" (all pairs) works
		string ss;
		cin>>ss;
		n = ss.size();
		bool working = 1;
		int sz1 = 0, sz2 = 0;
		for(char c : ss){
			sz1 += freq_s[c];
			sz2 += freq_t[c];
		}
		for(int i = 0; i < n; i++){
			for(int j = i + 1; j < n; j++){
				string pair = "";
				pair.push_back(ss[i]);
				pair.push_back(ss[j]);
				// cout<<pair<<endl;
				if(!works[pair])working = 0;
			}
		}
		if(working && sz1 == sz2)cout<<"Y";
		else cout<<"N";

		//bruteforce sol (TC 2)
		// set <char> has;
		// for(auto c : ss)has.insert(c);
		// string ns, nt;
		// for(char c : s){
		// 	if(has.find(c) != has.end())ns += to_string(c);
		// }
		// for(char c : t){
		// 	if(has.find(c) != has.end())nt += to_string(c);
		// }
		// if(ns == nt)cout<<"Y";
		// else cout<<"N";


	}
}
