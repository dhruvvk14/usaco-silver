//by Dhruv Kothari

#include <bits/stdc++.h>
using namespace std;
int n;
#define ll long long
struct Edge{
    int to, from;
    ll weight;
};
//DSU
class DisjointSets {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
	DisjointSets(int size) : parents(size), sizes(size, 1) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
	}

	/** @return the "representative" node in x's component */
	int find(int x) {
		return parents[x] == x ? x : (parents[x] = find(parents[x]));
	}

	/** @return whether the merge changed connectivity */
	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

		if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};


bool wsort(Edge e1, Edge e2){return e1.weight > e2.weight;}
int main() {
    //main idea: just make an Maximal Spanning Tree, which is the answer...
    cin>>n;
    vector <Edge> edges;
    for(int i = 1; i <= n; i++){
        Edge e;
        e.from = i;
        cin>>e.to>>e.weight;
		edges.push_back(e);
    }
    sort(edges.begin(), edges.end(), wsort);
    DisjointSets DSU(n + 1);
	ll ans = 0;
    for(auto e : edges){
        if(DSU.unite(e.from, e.to)){
            ans += e.weight;
        }
    }
    cout<<ans<<endl;
}
