#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
  
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>


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
signed main(){
    // testBIT();
    vector<int> num = { 2,3,5,7,11,13,17,19 } , rem = { 1,2, 3,4,5,6,7,8 };
    cout << crt(num , rem) << endl;
    return 0;
}
