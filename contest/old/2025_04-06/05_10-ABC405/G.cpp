#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define YES cout<<"Yes"<<endl;return 0;
#define NO cout<<"No"<<endl;return 0;
#define inf 4000000000000000000LL
#define mod 998244353LL

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

ll blocksize=0;
bool conpare(const vl& m1,const vl& m2){
	if(m1[1]/blocksize!=m2[1]/blocksize)return (m1[1]/blocksize) < (m2[1]/blocksize);
	else return m1<m2;
}

vl factmd(250001,1);
vl factinv(250001,1);
vl inv(250001,1);

//メイン
int main(){
	loop(i,1,250001){
		factmd[i]=factmd[i-1]*i;
		factmd[i]%=mod;
		factinv[i]=power_mod(factmd[i],mod-2);
		inv[i]=power_mod(i,mod-2);
	}
	ll n,q;
	cin>>n>>q;
	vl a(n);
	rep(i,n)cin>>a[i],a[i]--;

	
	loop(i,1,n){
		if(i*i>=n)break;
		blocksize=i;
	}
	blocksize++;
	//{通り、含まれてる数字の総数}
	vector<pair<ll,ll>> b(blocksize,{1,0});
	vl s(n,0);

	vvl query(q,vl(4));
	rep(i,q){
		cin>>query[i][0]>>query[i][1]>>query[i][2];
		query[i][0]--;
		query[i][2]--;
		query[i][3]=i;
	}
	sort(query.begin(),query.end(),conpare);

	vl ans(q);

	//[l,r)
	ll l=0,r=0;
	
	rep(j,q){
		//lを左に動かす
		while(query[j][0]<l){
			l--;
			ll tmp=a[l];
			ll tbk=tmp/blocksize;
			b[tbk].second++;
			s[tmp]++;
			b[tbk].first*=inv[s[tmp]];
			b[tbk].first%=mod;
		}
		//rを右に動かす
		while(query[j][1]>r){
			ll tmp=a[r];
			ll tbk=tmp/blocksize;
			b[tbk].second++;
			s[tmp]++;
			b[tbk].first*=inv[s[tmp]];
			b[tbk].first%=mod;
			r++;
		}
		//lを右に動かす
		while(query[j][0]>l){
			ll tmp=a[l];
			ll tbk=tmp/blocksize;
			b[tbk].first*=s[tmp];
			b[tbk].first%=mod;
			b[tbk].second--;
			s[tmp]--;
			l++;
		}
		//rを左に動かす
		while(query[j][1]<r){
			r--;
			ll tmp=a[r];
			ll tbk=tmp/blocksize;
			b[tbk].first*=s[tmp];
			b[tbk].first%=mod;
			b[tbk].second--;
			s[tmp]--;
		}
		
		//デバッグ用
		// cout<<query[j][3]<<endl;
		// rep(ii,blocksize)cout<<"{"<<b[ii].first<<","<<b[ii].second<<"}";
		// vdbg(s);

		//x以下の答えを計算する。
		ll tmp=query[j][2]/blocksize;
		ll sum=0;
		ll kotae=1;
		rep(k,tmp){
			kotae*=b[k].first;
			kotae%=mod;
			sum+=b[k].second;
		}
		tmp*=blocksize;
		loop(k,tmp,query[j][2]-1){
			sum+=s[k];
			kotae*=factinv[s[k]];
			kotae%=mod;
		}
		kotae*=factmd[sum];
		kotae%=mod;
		ans[query[j][3]]=kotae;
	}
	
	rep(i,q)cout<<ans[i]<<endl;
	return 0;
}
