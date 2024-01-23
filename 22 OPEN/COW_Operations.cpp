//by Dhruv Kothari
#include <bits/stdc++.h>
using namespace std;
int main() {
  //use prefix sums to check parities
  //main idea, if s = "c....", and s doesn't work, then "cc" + s won't work, and "oo" or "ss" + s won't work
  //(as u can just delete those 2 c's)
  //then just bruteforce strings to find out certain parities that work
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin>>s;
	int n = s.size();
	int q;
	cin>>q;
	s = " " + s;
	int C[n + 1], O[n+ 1], W[n+ 1];
	C[0] = 0, O[0] = 0, W[0] = 0;
	for(int i = 1; i <= n; i++){
		C[i] = C[i-1];
		O[i] = O[i-1];
		W[i] = W[i-1];
		if(s[i] == 'C')C[i]++;
		else if(s[i] == 'O')O[i]++;
		else W[i]++;
	}
	while(q--){
		int start, end;
		cin>>start>>end;
		int c = C[end] - C[start-1], o = O[end] - O[start-1], w = W[end]-W[start-1];
		if(c % 2 == 1 && o % 2 == 0 && w % 2 == 0){ //this works
			cout<<"Y";
		}
		else if(c % 2 == 0 && o % 2 == 1 && w % 2 == 1){ //this also works
			cout<<"Y";
		}
		else cout<<"N";
	}
}
