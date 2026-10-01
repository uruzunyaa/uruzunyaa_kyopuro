#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>

//エラトステネスの篩方式で素因数分解機能を付けた

vl eprime;
//maxaまでの全ての数について、最小の素因数を求め,eprimeに入れる
void make_eratosthenes_prime(ll maxa){
	eprime=vl(maxa+1);
	loop(i,2,maxa){
		if(eprime[i]==0){
			eprime[i]=i;
			for(ll j=i*i;j<=maxa;j+=i){
				if(eprime[j]==0)eprime[j]=i;
			}
		}
	}
}
//make_eratosthenes_primeで作られている前提で、素因数分解をする。
vector<pair<ll,ll>> eratosthenes_prime_fact(ll n){
	vector<pair<ll,ll>> ans;
	while(n!=1){
		if(ans.size()==0||ans.back().first!=eprime[n]){
			ans.push_back({eprime[n],1});
		}else{
			ans.back().second++;
		}
		n/=eprime[n];
	}
	return ans;
}

//メイン
int main(){
	make_eratosthenes_prime(9999999);
	string s;
	cin>>s;
	
	loop(i,2,9999999){
		if(eprime[i]!=i)continue;
		string t=to_string(i);
		if(t.size()!=s.size())continue;
		bool f=true;
		rep(a,s.size())rep(b,a){
			if((s[a]==s[b])!=(t[a]==t[b])){
				f=false;
				break;
			}
		}
		if(f){
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
