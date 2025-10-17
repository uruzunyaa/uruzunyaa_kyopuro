// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#ifdef DEBUG
#include "cpp-dump/dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#endif
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353
typedef string::const_iterator State;
class ParseError {};
// int number(State &begin);
// int term(State &begin);
char expression(State &begin, string &S);
// int factor(State &begin);
void consume(State &begin, char expected) {
    if (*begin == expected) {
        begin++;
    } else {
        cerr << "Expected '" << expected << "' but got '" << *begin << "'"
            << endl;
        cerr << "Rest string is '";
        while (*begin) {
            cerr << *begin++;
        }
        cerr << "'" << endl;
        throw ParseError();
    }
}

char expression(State &begin, string &S) {
    if (*begin == '(') {
        consume(begin, '(');
        char a = expression(begin, S);

        char op = *begin;
        ++begin;

        char b = expression(begin , S);
        consume(begin,')');
        
        if (S.find(a) > S.find(b)) swap(a,b);

        if (op == '<') {
            return a;
        } else {
            return b;
        }

    } else {
        char ret = *begin;
        ++begin;
        return ret;
    }
}

ll solve() {
    ll n;
    cin>>n;
    if (n == 0) return 1;
    string a,s,t;
    cin>>a>>s>>t;

    vl fact(16);
    fact[0]=1;
    loop(i,1,15)fact[i]=fact[i-1]*i;
    
    ll ans=0;
    rep(i,n){
        string tmp;
        rep(j,n)if(i!=j)tmp.push_back(a[j]);
        //a[i]答えになるか見る
        rep(b,1<<(n-1)){
            string target;
            rep(j,n-1){
                if((b&(1<<j))==0)target.push_back(tmp[j]);
            }
            target.push_back(a[i]);
            ll p=0;
            rep(j,n-1){
                if((b&(1<<j)))target.push_back(tmp[j]),p++;
            }
            //cout<<a[i]<<" "<<target<<endl;
            dump(a[i], ' ', target);
            State begin=s.begin();
            char sans=expression(begin,target);
            begin=t.begin();
            char tans=expression(begin,target);
            if(sans==tans&&sans==a[i]){
                ans+=fact[p]*fact[n-1-p];
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}

int main(){
    while(1){
        if(solve()==1)break;
    }
    return 0;
}
