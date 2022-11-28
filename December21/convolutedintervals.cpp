//by Dhruv Kothari
#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
//lets sort them, because why not?
//Observation 1: for any interval to fit between k, their start value ≤ k (as their start value can't be larger than k itself, as values can't be negative)
//this means that when this happens, we can automatically end our process
//Observation 2: for TC 3-5, we must pre process our information. We can find the upper and lower value of K which works for each pairing. 
//This still isn't enough, we must know more than the lower and upper bounds. We can use inverse prefix sums to find out the actual value...
//Observation 3: when K = 0, a part of K = 1's answer will use K = 0's answer. Specifically, it is when K = 0 is the upperbound...
//In mathematical terms: ans(k + 1) = ans(k) - ans(when k is upper bound) + ans(when k + 1 is upper bound)
//This is a recursive formula, which requries a base case, when K = 0...
#define start first
#define end second
int main(){
    cin>>n>>m;
    int startVal[5001] = {0}, endVal[5001] = {0};
    pair <int, int> intervals[n];
    for(int i = 0; i < n; i++){
        cin>>intervals[i].start>>intervals[i].end;
        startVal[intervals[i].start]++, endVal[intervals[i].end]++;
    }
    sort(intervals, intervals + n);
    long long a[2 * m + 1];
    long long b[2 * m + 1];
    for(int i = 0; i <= 2 * m; i++)a[i] = 0, b[i] = 0;
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= m; j++){
            a[i + j] += (long long)startVal[i] * startVal[j];   
            b[i + j] += (long long)endVal[i] * endVal[j];
        }
    }
    long long curAns = 0;
    for(int i = 0; i <= 2 * m; i++){
        curAns += (long long)a[i];
        cout<<curAns<<endl;
        curAns -= (long long)b[i];
    }
}
