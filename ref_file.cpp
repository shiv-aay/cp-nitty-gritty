#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
  
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

// Simple code of segment tree, evrything 0 indexed
class NumArray {
public:
    // Check the constructor for the initialization of these variables.
    vector<int> seg; // Segment Tree to be stored in a vector.
    int n; // Length of the segment tree vector. 
    

    // Function to build the Segment Tree
    // This function will fill up the child values first
    // (left == right) will satisfy for the leaf values and they will be updated in segment tree
    // seg[pos]=seg[2*pos+1]+ seg[2*pos+2]; -> This will help populate all other intermediate nodes
    // as well as the root node with the "sum" of their child nodes.
    // Finally we have a segment tree which has all 'nodes' with sum values of their child.
    void buildTree(vector<int>& nums, int pos, int left, int right){
        if (left == right){
            seg[pos] = nums[left]; 
            return;
        }
        int mid = (left+right)/2;
        buildTree(nums, 2*pos+1, left, mid);
        buildTree(nums, 2*pos+2, mid+1, right);
        seg[pos]=seg[2*pos+1]+ seg[2*pos+2];
    }

    // Function to update a node in the segment tree
    // When a node is updated, then the change in the node value has to be propagated to the root
    // left, right -> represents the range of the node of segment tree. (Ex: [0, n-1] -> root)
    // pos       -> represents "position" in the segment tree data structure (Ex: 0 -> root)
    // Using left, right and pos -> we have all the information on the segment tree
    // Node at 'pos' in segment tree will have children at 2pos+1(left) and 2pos+2(right)

    // If index is less than left or more than right, then it is out of bound 
    //      for this node's range so we ignore it and return (This makes the algo O(logn))
    // If left==right==index, then we found the index, 
    //      update the value of the segment tree node & return
    // Otherwise, we need to find the index and we do this by checking child nodes (2pos+1, 2pos+2)
    //      update the segment tree pos with the updated child values' sum.
    //      This would help propagate the updated value of the chid indexes to the parent (through recursion)
    void updateUtil(int pos, int left, int right, int index, int val) {
        // no overlap
        if(index <left || index >right) return;
        
        // total overlap
        if(left==right){
            if(left==index)
                seg[pos]=val;
            return;
        }

        // partial overlap
        int mid=(left+right)/2;
        updateUtil(2*pos+1,left,mid,index,val); // left child
        updateUtil(2*pos+2,mid+1,right,index,val); // right child
        seg[pos]=seg[2*pos+1]+seg[2*pos+2];
    }

    // Function to get the sum from the range [qlow, qhigh]
    // low, high -> represents the range of the node of segment tree. (Ex: [0, n-1] -> root)
    // pos       -> represents "position" in the segment tree data structure (Ex: 0 -> root)
    // Using low, high and pos -> we have all the information on the segment tree
    // Node at 'pos' in segment tree will have children at 2pos+1(left) and 2pos+2(right)
    
    // While searching for the range, there will be three cases: (Ex: arr: [-1, 4, 2, 0])
    //  - Total Overlap:    Return the value. (Ex: qlow, qhigh: 0,3 and low, high: 1,2)
    //  - No Overlap:       Return 0. (Ex: qlow, qhigh: 0,1 and low, high: 2,3)
    //  - Partial Overlap:  Search for it in both the child nodes and their ranges.
    //                      (Ex: Searching for 1,2 and node range is 0,1)
    int rangeUtil(int qlow, int qhigh, int low, int high, int pos){
        if (qlow <= low && qhigh>= high){ // total overlap
            return seg[pos];
        }
        if (qlow > high || qhigh < low) { // no overlap
            return 0;
        }
        // partial overlap
        int mid = low+(high-low)/2;
        return (rangeUtil(qlow, qhigh, low, mid, 2*pos+1) + rangeUtil(qlow, qhigh, mid+1, high, 2*pos+2));
    }
    
    // Constructor for initializing the variables.
    NumArray(vector<int>& nums) {
        if(nums.size() > 0){
            n = nums.size();
            seg.resize(4*n,0);  // Maximum size of a segment tree for an array of size n is 4n
            buildTree(nums, 0, 0, n-1); // Build the segment tree
            // Print Segment Tree
            // for(int i=0;i<4*n;i++)
            //     cout<<seg[i]<<" ";
            // cout<<endl;
        }
    }
    
    // Update the segment Tree recurively using updateUtil
    void update(int index, int val) {
        if(n==0)return;
        updateUtil(0,0,n-1, index, val);
    }
    
    // Get the sum for a specific range for the segment Tree
    int sumRange(int left, int right) {
        if(n==0)return 0;
        return rangeUtil(left, right, 0, n-1, 0); 
        // query from left to right while segment tree is now at 'root' (pos=0) and range(0, n-1)
    }
};



// Euler Circuit (recursive code)
void EulerCycle(){
    vector<int> adj[4] = {
        {1,2} , {0,3} , {3} , {0,1}
    } , ans;
    function<void(int)> dfs = [&](int node){
        while(adj[node].size()){
            int child = adj[node].back();
            adj[node].pop_back();
            dfs(child);
        }
        ans.push_back(node);
    };
    dfs(0);
    for (int i=ans.size()-1; i>=0; i--)
    {
        cout << ans[i];
        if (i)
           cout<<" -> ";
    }
}

class DSU{
    vector<int> p;
public:
    DSU(vector<int> a){
        int n = a.size();
        p = vector<int>(n);
        for(int i = 0; i < n; i++){
            p[i] = i;
        }
    }
    int get_parent(int a){
        if(a == p[a]) return p[a];
        return p[a] = get_parent(p[a]);
    }
    void set_union(int child , int parent){
        child = get_parent(child);
        parent = get_parent(parent);
        p[child] = parent;
    }
};


// bth root of a
double powx(double a , int b){
    if(b < 2)
        return pow(a,b);
    if(b & 1)
        return a * powx(a,b-1);
    return powx(a*a,b/2);
}
int root(int a , int b){
    double prev_x = INT_MIN, x = ((double)a)/b;
    while(abs(x - prev_x) > 0.5){
        prev_x = x;
        x = prev_x - ((pow(prev_x,b) - a)/(b * pow(prev_x,b-1)));
    }
    return llround(x);
}



// ----------------------------------------------------------------
// Flexible Segment tree implementation
class SegmentTree{
    // 1 based indexing of Segment tree, 0 based indexing of input vector
    // start is inclusive, end is exclusive
    vector<int> t , v;
    int original_size;
    int DODGING_VALUE;
    function<int(int, int)> OPERATING_FUNCTION;
    void build(int start , int end , int node = 1) {
        if(start + 1 > end)
            return;
        if(start + 1 == end){
            t[node] = v[start];
            return;
        }
        int M = (start + end) >> 1;
        build(start, M, 2*node);
        build(M, end, 2*node+1);
        t[node] = OPERATING_FUNCTION(t[2*node] , t[2*node+1]);
    }
    
    public:
    SegmentTree(vector<int> a, function<int(int, int)> INPUT_FUNCTION , int INPUT_DODGING_VALUE){
        v = a;
        OPERATING_FUNCTION = INPUT_FUNCTION;
        DODGING_VALUE = INPUT_DODGING_VALUE;
        original_size = v.size();
        t = vector<int>(4*original_size);
        build(0 , original_size);
    }

    int get(int left , int right ,int start = 0, int end = -1 , int node = 1){
        if(end == -1)
            end = original_size , right++; // make right exclusive
        if(left >= end || right <= start)
            return DODGING_VALUE;
        if(start >= left && end <= right)
            return t[node];
        int M = (start + end) >> 1;
        return OPERATING_FUNCTION(
            get(left,right,start,M,2*node) ,
            get(left,right,M,end,2*node+1)
        );
    }

    void update(int newValue , int left , int right ,int start = 0, int end = -1 , int node = 1){
        if(end == -1)
            end = original_size , right++;
        if(left >= end || right <= start)
            return;
        if(start + 1 == end){
            t[node] = newValue;
            return;
        }
        int M = (start + end) >> 1;
        update(newValue , left , right , start, M, 2*node);
        update(newValue , left , right , M, end, 2*node+1);
        t[node] = OPERATING_FUNCTION(t[2*node] , t[2*node+1]);
    }

    void print(int start = 0, int end = -1, int node = 1){
        if(end == -1) end = original_size;
        cout << start << ", " << end << " : " << t[node] << endl;
        if(start + 1 >= end)
            return;
        int M = (start + end) >> 1;
        print(start, M, 2*node);
        print(M, end, 2*node+1);
    }
};



// BIT implementation
class BIT{
int n;
vector<int> v;
public:

    int getSum(int pos){
        pos++;
        int sum = 0;
        while(pos > 0){
            sum += v[pos];
            pos -= pos & (-pos);
        }
        return sum;
    }

    void update(int addVal , int pos){
        pos++;
        while(pos <= n){
            v[pos] += addVal;
            pos += pos & (-pos);
        }
    }

    BIT(vector<int> a){
        n = a.size();
        v = vector<int>(n+1);
        for(int i = 0; i < n; i++){
            update(a[i] , i);
        }
    }
};
void testBIT(){
    vector<int> a;
    for(int i = 1; i < 11; i++) a.push_back(i);
    BIT bt(a);
    cout << bt.getSum(2) << endl;
    bt.update(1,3);
    cout << bt.getSum(3) << endl;
    cout << bt.getSum(4) << endl;
}

// Extended Euclidean algorithm for gcd
int gcd_extended_euclidean(int a , int b , int& x , int& y){
    if(a == 0){
        x = 0;
        y = 1;
        return b;
    }
    int x1 , y1;
    int gcd = gcd_extended_euclidean(b%a , a , x1 , y1);
    x = y1 - (b/a) * x1;
    y = x1;
    return gcd;
}

// Modular Inverse
int modInverse(int a , int m){
    int x , y;
    int gcd = gcd_extended_euclidean(a , m , x , y);
    if(gcd != 1) return -1;
    return (x%m + m) % m;
}

// Chinese Remainder Theorem
int crt(vector<int> p , vector<int> k){
    int n = p.size() , ans , pp = 1;
    for(int i = 0; i < n; i++){
        pp *= p[i];
    }
    for(int i = 0; i < n; i++){
        ans = (ans + 
                (( (k[i] * modInverse(pp/p[i] , p[i])) % pp ) * (pp / p[i])) % pp
              ) % pp;
    }
    return ans;
}

// number of topological arrangements in a directed tree
  const int M = 1e9+7;
  int binpow(int a, int b){
    if(b == 0) return 1;
    if(b & 1)
        return (a * 1ll * binpow(a , b-1)) % M;
    return binpow((a*1ll*a)%M , b/2);
  }
  int div(int a, int b){
    return mul(a,binpow(b , M-2));
  }
  int mul(int a ,  int b){
    return (a*1ll*b)%M;
  }
  int waysToBuildRooms(vector<int>& p) {
    // p[i] is parent of i;
    int n = p.size();
    vector<int> adj[n] , sz(n) , fact(1e5+1);
    for(int i = 1; i < n; i++){
        adj[p[i]].push_back(i);
    }
    fact[0] = 1;
    for(int i = 1; i <= 1e5; i++){
        fact[i] = (i * 1ll * fact[i-1]) % M;
    }
    unordered_map<int , int> mp;
    function<int(int)> dp = [&](int node){
        if(mp.find(node) != mp.end())
            return mp[node];
        mp[node] = 1;
        for(int child : adj[node]){
            mp[node] = mul(mp[node] , dp(child));
            mp[node] = div(mp[node] , fact[sz[child]]);
            sz[node] += sz[child];
        }
        mp[node] = mul(mp[node] , fact[sz[node]]);
        sz[node]++; // add self
        return mp[node];
    };
    return dp(0);
  }

signed main(){
    // testBIT();
    vector<int> num = { 2,3,5,7,11,13,17,19 } , rem = { 1,2, 3,4,5,6,7,8 };
    cout << crt(num , rem) << endl;
    return 0;
}
