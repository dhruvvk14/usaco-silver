#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define pos first
#define tasty second
#define ll long long
int main(){
    int k, n, m;
    cin>>k>>m>>n;
    vector <pair <ll, ll> > patches(k);
    for(int i = 0; i < k;i ++)cin>>patches[i].pos>>patches[i].tasty;
    sort(patches.begin(), patches.end());
    vector <ll> nhoj(m);
    nhoj.push_back((ll)-2 * 1e10);
    nhoj.push_back((ll) 2 * 1e10);
    for(int i = 0; i < m; i++)cin>>nhoj[i];
    sort(nhoj.begin(), nhoj.end());
    //consider the following, between every 2 cows of nhoj.
    //There are x pastures between each of them (if x is 0, then skip)
    //notice how we can use 2 pointers for this...
    int patchInd = 0;
    vector <ll> tastiness;
    //O(K + M)
    //cout<<endl;
    for(int i = 0; i < nhoj.size() - 1 && patchInd < patches.size(); i++){
        ll startPoint = nhoj[i], endPoint = nhoj[i + 1];
        vector <pair <ll, ll> > allPatches;
        while(startPoint <= patches[patchInd].pos && patches[patchInd].pos <= endPoint && patchInd < patches.size()){
            if(patchInd >= patches.size())break;
            allPatches.push_back(patches[patchInd]);
            patchInd++;
        }
        if(allPatches.size() == 0)continue;
        //notice the following. the size of our window (intuitively), is the average of startPoint & endPoint
        double windowSize = (double)(endPoint - startPoint)/2;

        //make a sliding window
        int curPatchInd = 0, curPatchInd2 = 0; 
        ll finalAns = 0;
        ll cur = 0;
        ll total = 0;
        for(pair <ll, ll> p : allPatches)total += p.tasty;
        while(curPatchInd < allPatches.size() && curPatchInd2 < allPatches.size()){
            //essentially, there are 2 pointers
            //curPatchInd is the starting index, while the 2nd one is the current farthest it reaches
            //notice how curPatchInd -> allPatches.size(), the 2nd one never decreases...
            if(curPatchInd != 0){
                cur = cur - allPatches[curPatchInd - 1].tasty;
            }
            curPatchInd2 = max(curPatchInd2, curPatchInd);
            while(curPatchInd2 < allPatches.size() && abs(allPatches[curPatchInd2].pos - allPatches[curPatchInd].pos) < windowSize){
                cur = cur + allPatches[curPatchInd2].tasty;
                curPatchInd2++;
            }
            finalAns = max(cur, finalAns); 
            curPatchInd++;
        }
        tastiness.push_back(total - finalAns), tastiness.push_back(finalAns);
        //notice how finalAns >= total - finalAns
        //therefore, we can count them as 2 seperate answers.
    }
    sort(tastiness.begin(), tastiness.end());
    ll ans = 0;
    int amt = 0;
    while(!tastiness.empty() && amt < n){//get most "optimal" values
        ans += tastiness[tastiness.size() - 1];
        tastiness.pop_back();
        amt++;
    }
    cout<<ans<<endl; //output answer
}
