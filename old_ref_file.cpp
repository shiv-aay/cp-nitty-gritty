// Useful functions
#define vi vector<int>
bool sortbysec(const pair<int,int> &a,const pair<int,int> &b){return (a.second < b.second);}
#define gi greater<int>()
#define rsort(a,b) sort(a,b,gi)

    cout<<"DP (Print 2d dp for debugging)\n";
    rep(i, 0, n1){
        if(!i) {cout<<"___";rep(k,0,n2) cout<<s2[k]<<"_";cout<<endl;}
        rep(j, 0, n2){
            if(!j) cout<<s1[i]<<"| ";
            cout<<dp[i][j]<<" ";
        }    
        cout<<endl;
    } cout<<endl; cout<<endl; 

long long int lcmx(long long int a, long long int b){
    return a*b/__gcd(a,b);
} 
// calculate frequency of k in array, by binary search
int count(int x[], int n, int k) {
    int p = -1, q = -1;
    for (int a = n; a >= 1; a /= 2) {
        while (p+a < n && x[p+a] < k) p += a;
        while (q+a < n && x[q+a] <= k) q += a;
    }
    return q-p;
}
int printNcR(int n, int r)
{
    int p = 1, k = 1;
    if (n - r < r) r = n - r;
    if (r != 0) {
        while (r) {
            p *= n;
            k *= r;
            long long m = __gcd(p, k);
            p /= m;
            k /= m;
            n--;
            r--;
        }
    }
    else p = 1;
    return p;
}

const int N=1e5;
int primes[N]={0};
vector<int> pr;
void seive(){
    for(int i=2;i<N;i++){
        if(primes[i]==0)
            for(int j=i*i;j<N;j+=i)
                primes[j]=1;
        primes[i]^=1;
    }
    for(int i=2;i<N;i++)
        if(primes[i]) pr.push_back(i);      
    return;
}


int powr(int x, int n){
    int res = 1;
    while (n > 0){
        if (n & 1)
            res = (res % MOD * x % MOD) % MOD;
        x = (x % MOD * x % MOD) % MOD;
        n = n / 2;
    }
    return res;
}
int ncr(int n, int r)
{
    int n1 = fact[n];
    int n2 = (fact[r] % MOD * fact[n - r] % MOD) % MOD;
    n2 = powr(n2, MOD - 2);
    return (n1 % MOD * n2 % MOD) % MOD;
}
const int N = 3e5 + 5;
int fact[N];
fact[0] = 1;
for (int i = 1; i <= n; i++)
    fact[i] = (fact[i - 1] % MOD * i % MOD) % MOD; 

















It is my own DEBUG function(class) it works with GNU G++ 17 and higher. Here is code:

class LOG{
public:
    //check if type iterable function
    template<typename C>
    struct is_iterable{
      typedef long false_type;
      typedef char true_type;

      template<class T> static false_type check(...);
      template<class T> static true_type  check(int,
                        typename T::const_iterator = C().end());

      enum { value = sizeof(check<C>(0)) == sizeof(true_type) };
    };
    //string print
    static void print_value(string starting, string value, string ending = "\n"){
        cout << starting<< "\"" << value<< "\"" << ending;
    }
    //main print function
    template<class T>
    static void print_value(string starting, T value, string ending = "\n"){
        //if iterable than recursevly print ech value
        if constexpr (is_iterable<T>::value){
            typename T :: iterator it = value.begin();
            cout << starting << "{";
            while (it != value.end()){
               print_value ("", *it, (next(it, 1) == value.end() ? "" : ", "));
                it++;
            }
            cout << "}";
        }
        else{
            // else we probably have char, int, long long, and etc.
            cout << starting << value;
        }
        cout << ending;
    }
    //pair print
    template<class T, class M>
    static void print_value(string starting, pair<T, M> value, string ending = "\n"){
        cout << starting << "{";
        print_value("", value.ff, "");
        cout << ", ";
        print_value("", value.ss, "");
        cout << "}" << ending;
    }
    //map recursive print
    template<class T, class M>
    static void print_value(string starting, map<T, M> value, string ending = "\n"){
        cout << starting << "{" << endl;
        ll cur = 0;
        for (pair<T, M> v: value){
            print_value ("  {", v.ff, ": ");
            print_value ("", v.ss, (cur == value.size() - 1 ? "}" : "},"));
            cur++;
            cout << endl;
        }
        cout << "}" << ending;
    }
    //array print
    /*
    ARRAY PRINT DOES'T WORK CORRECTLY
      I HIGHLY RECOMMEND TO NOT USE IT
    */
    template<class T>
    static void print_value(string starting, vector<size_t> len, T* value, int dim){
        if (len.size() == 1){
            for (long long i = 0; i < len[0]; i++){
                cout << *(value + i) << " ";
            }
        }
        if (len.size() == 2){
            for (long long i = 0; i < len[0]; i++){
                for (long long j = 0; j < len[1]; j++){
                    cout << *(*(value + i) + j) << " ";
                }
                cout << endl;
            }
        }
        if (len.size() == 3){
            for (long long i = 0; i < len[0]; i++){
                for (long long j = 0; j < len[1]; j++){
                    for (long long z = 0; z < len[2]; z++){
                        cout << *(*(*(value + i)+ j) + z) << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
        if (len.size() == 4){
            for (long long i = 0; i < len[0]; i++){
                for (long long j = 0; j < len[1]; j++){
                    for (long long z = 0; z < len[2]; z++){
                        for (long long x = 0; x < len[3]; x++){
                            cout << (*(*(*(value + i) + j) + z) + x) << " ";
                        }
                        cout << endl;
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
    }
};
now the examples:

#include<bits/stdc++.h>
using namespace std;
//----LOG class code---
int main(){
    vector<long long> v(5);
    for (long long i = 0; i < 5; i++){
        cin >> v[i];
    }
    LOG::print_value ("starting string ", v, " ending string");
}
this is for all types exept arrays(like this: a[5]) now for arrays:

#include<bits/stdc++.h>
using namespace std;
//----LOG class code---
int main(){
    long long v[5][3];
    for (long long i = 0; i < 5; i++){
        for (long long j = 0; i < 3; j++){  
            cin >> v[i][j];
        }   
    }
    LOG::print_value ("starting string ", {5, 3}, a, 0);
// starting string, vector of lengths, variable name, starting dimension index
}
thath's it. Also check my friend account — ShirChoi. He helped me a lot with this. Wish you luck.
