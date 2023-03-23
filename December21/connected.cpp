//by Dhruv Kothari
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
#define ll long long
#define pb push_back
vector <vector <ll> > adj;
const int mxn = 1e5 + 1;
bool visited[mxn];
int curComponent = 0;
int component[mxn];
vector <ll> current;
void dfs(int node){ // standard dfs func.
    if(visited[node])return;
    visited[node] = 1;
    component[node] = curComponent; // add to component
    current.pb(node);
    for(int i : adj[node])dfs(i);
}
ll solve(){
    curComponent = 0;
    int n, m;
    cin>>n>>m;
    adj.clear();
    adj.resize(mxn);
    for(int i = 0; i < m; i++){
        int a, b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    // cout<<endl;
    fill(visited, visited + n + 1, 0);
    fill(component, component + n + 1, 0);
    vector < vector<ll> > components;
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            current.clear();
            dfs(i);
            components.pb(current);
            curComponent++;
        }
    }
    for(int i = 0; i < components.size(); i++)sort(components[i].begin(), components[i].end());
    if(component[1] == component[n])return 0; //b(1) and b(n) are in same component
    int lastComp = component[n];
    ll firstTo[components.size()], lastTo[components.size()];
    fill(firstTo, firstTo + components.size(), (ll)1e18 + 1);
    firstTo[0] = 0;
    fill(lastTo, lastTo + components.size(), (ll)1e18 + 1);
    lastTo[component[n]] = 0;
    for(int c = 1; c < components.size(); c++){
        for(int b1 : components[c]){
            ll cost1 = 1e18 + 1;
            int ind = upper_bound(components[0].begin(), components[0].end(), b1) - components[0].begin(); //find ub...
            for(int i = 0; i <= 3 && ind >= 0; i++){
                if(0 <= ind && ind < components[0].size()){
                    cost1 = min((ll)abs(components[0].at(ind) - b1), (ll)cost1);
                }
                ind--;
            }
            cost1 = cost1 * cost1;
            firstTo[c] = min(firstTo[c], cost1);
        }
    }
    for(int c = 0; c <components.size(); c++){
        if(c == component[n])continue;
        for(int b1 : components[c]){
            ll cost1 = 1e18 + 1;
            int ind = upper_bound(components[lastComp].begin(), components[lastComp].end(), b1) - components[lastComp].begin(); //find ub
            for(int i = 0; i <= 3 && ind >= 0; i++){
                if(0 <= ind && ind < components[lastComp].size()){
                    cost1 = min((ll)abs(components[lastComp].at(ind) - b1), (ll)cost1);
                }
                ind--;
            }
            cost1 = cost1 * cost1;
            lastTo[c] = min(lastTo[c], cost1);
        }
    }
    ll ans = 1e18;
    for(int i = 0; i < components.size(); i++){
        ans = min(ans, (ll)lastTo[i] + firstTo[i]); // find min(lastTo[i] + firstTo[i]) for i in [0,components.size - 1]
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false); //fast io
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--)cout<<solve()<<endl;
}