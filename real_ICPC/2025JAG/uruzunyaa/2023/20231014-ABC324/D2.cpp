#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cmath>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
#define ll long long
#define inf 100000000000000000


bool isSqrt(ll n) {
    if (n < 0) return false;

    ll sqrtN = static_cast<ll>(sqrt(n));
    return sqrtN * sqrtN == n;
}

ll power(ll A, ll B) {
    ll result = 1;
    for (ll i = 0; i < B; i++) {
        result *= A;
    }
    return result;
}


vector<ll> ans;


int main(){
    ll n;
    string s;
    cin>>n>>s;
    vector <ll> a(n);
    rep(i,n){
        a[i]=s[i]-'0';
    }
    sort(a.rbegin(),a.rend());
    ll mx=0;
    rep(i,n){
        mx*=10;
        mx+=a[i];
    }
    ll ans=0;
    for(ll i=0;i*i<=mx;i++){
        string check=to_string(i*i);
        while (check.length() < n) {
            check = '0' + check;
        }
        sort(check.rbegin(),check.rend());
        if(stoll(check)==mx){
            //cout<<stoll(check)<<endl;
            ans++;
        }
    }
    cout<<ans;
}