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

void sub(vector<ll>& nokori,ll num){
    if(nokori.size()==0){
        if(isSqrt(num))ans.push_back(num);
        return;
    }
	num*=10;
	rep(i,nokori.size()){
        if(i!=0){
            if(nokori[i]==nokori[i-1])continue;
        }
        ll nowNum=nokori[i];
		num+=nowNum;
        nokori.erase(nokori.begin()+i);
        sub(nokori,num);
        nokori.insert(nokori.begin() + i, nowNum);
        num-=nowNum;
	}
	return;
}

int main(){
    ll n;
    string s;
    cin>>n>>s;
    vector <ll> a(n);
    rep(i,n){
        a[i]=s[i]-'0';
    }
    sort(a.begin(),a.end());
    sub(a,0);
    sort(ans.begin(),ans.end());

    vector <ll> unqAns;
    if(ans.size()>0)unqAns.push_back(ans[0]);
    loop(i,1,ans.size()-1){
        if(ans[i]!=ans[i-1])unqAns.push_back(ans[i]);
    }
    cout<<unqAns.size()<<endl;
    
    return 0;
}