//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	n%=mod;
	ll ans = 1;
	while (k > 0){
		if ((k&1) ==1)ans=(ans*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return ans;
}



//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//ans[i]=Σa[j](jはiのsuperset)を求める。
//aの要素数は2の累乗でなくてはならない。
vl superset_sums(vl a){
	ll n=-inf;
	rep(i,30){
		ll asiz=a.size();
		if(asiz==(1LL<<i))n=i;
	}
	//下向きゼータ変換
	rep(i,n){
		rep(b,1LL<<n){
			if((b&(1LL<<i))==0)continue;
			a[b-(1LL<<i)]+=a[b];
		}
	}
	
	return a;
}

//ans[i]=Σa[j](jはiのsuperset)を求める。
//aの要素数は2の累乗でなくてはならない。
vl subset_sums(vl a){
	ll n=-inf;
	rep(i,30){
		ll asiz=a.size();
		if(asiz==(1LL<<i))n=i;
	}
	//上向きゼータ変換
	rep(i,n){
		rep(b,1LL<<n){
			if((b&(1LL<<i))!=0)continue;
			a[b+(1LL<<i)]+=a[b];
		}
	}

	return a;
}

ll my_popcount(ll a){
	ll ans=0;
	rep(i,inf){
		if(a&1LL)ans++;
		a=a/2;
		if(a==0)break;
	}
	return ans;
}

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vl b(n,0);
	rep(i,m){
		ll k;
		cin>>k;
		rep(j,k){
			ll s;
			cin>>s;
			s--;
			b[s]+=(1LL<<i);
		}
	}

	ll r=0;
	ll rpop=0;
	rep(i,m){
		ll rr;
		cin>>rr;
		r+=rr*(1LL<<i);
		if(rr==1)rpop++;
	}

	vl cnt(1LL<<m,0);
	rep(i,n){
		if((b[i]|r)!=r)continue;
		cnt[b[i]]++;
	}

	//総ORがrになる数え上げ。
	ll ans=0;

	//supersetの数え上げでは、1が立ってるbitは全て1なのが保証される奴の数え上げ。
	vl subcnt=subset_sums(cnt);

	//subset_sumが分かっていれば、それらを全部選ばない例で包除
	rep(bit,1LL<<m){
		if((bit|r)!=r)continue;
		ll zero=rpop-my_popcount(bit);
		ll sign;
		if(zero%2==0)sign=1;
		else sign=-1;
		ans+=mod+sign*power_mod(2,subcnt[bit]);
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
