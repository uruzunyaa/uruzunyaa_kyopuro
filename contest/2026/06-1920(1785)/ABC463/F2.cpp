//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

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

ll inv(ll n){
	return power_mod(n,mod-2);
}


//nCr % mod を O(max(n)) で求める(power_mod前提条件)
//注意:先に階乗逆元等を求める関数を動かさないと
//O(Max(n log n))になる。
vl fact={1};
vl factinv={1};
void make_fact_and_factinv(ll n){
	fact=vl(n+1);
	factinv=vl(n+1);
	fact[0]=1;
	loop(i,1,n){
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
	}
	factinv[n]=power_mod(fact[n],mod-2);
	rrep(i,n){
		factinv[i]=factinv[i+1]*(i+1);
		factinv[i]%=mod;
	}
}
ll ncrmd(ll n,ll r){
	if(n<r)return 0;
	while(fact.size()<=n){
		ll i=fact.size();
		fact.push_back((fact[i-1]*i)%mod);
		factinv.push_back(power_mod(fact[i],mod-2));
	}
	ll ans=fact[n]*factinv[r];
	ans%=mod;
	ans*=factinv[n-r];
	ans%=mod;
	return ans;
}



//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};



map<vl,ll>mp2,mp3;
ll solve_two(ll cnt,ll twoone,ll twozero,ll oneone,ll onezero){
	vl input={cnt,twoone,twozero,oneone,onezero};
	if(mp2.count(input))return mp2[input];
	ll invof2=inv(2);
	ll kakuritu=invof2;
	ll maybe=0;
	
	//21
	cnt+=twoone*2;
	kakuritu*=power_mod(invof2,twoone);
	kakuritu%=mod;

	//20
	cnt+=twozero;
	kakuritu*=power_mod(invof2,twozero);
	kakuritu%=mod;

	//11
	cnt+=oneone;

	//10
	maybe+=onezero;
	//どっちか決め打った確立にしとく
	kakuritu*=power_mod(invof2,maybe);
	kakuritu%=mod;


	ll ans=0;
	loop(i,0,maybe){
		ll choice=i+cnt;
		ll tmp=ncrmd(maybe,i)*kakuritu;
		tmp%=mod;
		tmp*=inv(choice);
		tmp%=mod;
		ans+=tmp;
		ans%=mod;
	}
	mp2[input]=ans;
	return ans;
}

ll solve_three(ll twotwo,ll twoone,ll twozero){
	vl input={twotwo,twoone,twozero};
	if(mp3.count(input))return mp3[input];
	ll cnt=1;
	ll invof2=inv(2);
	ll kakuritu=invof2;
	ll maybe=0;
	
	//22
	cnt+=twotwo;

	//21
	maybe+=twoone;

	//20
	maybe+=twozero;

	//どっちか決め打った確立にしとく
	kakuritu*=power_mod(invof2,maybe);
	kakuritu%=mod;


	ll ans=0;
	loop(i,0,maybe){
		ll choice=i+cnt;
		ll tmp=ncrmd(maybe,i)*kakuritu;
		tmp%=mod;
		tmp*=inv(choice);
		tmp%=mod;
		ans+=tmp;
		ans%=mod;
	}
	mp3[input]=ans;
	return ans;
}
//メイン
int main(){
	ll n;
	cin>>n;
	make_fact_and_factinv(n);
	vl a(n*2);
	ll mx=0;
	rep(i,n*2){
		cin>>a[i];
		mx=max(a[i],mx);
	}
	rep(i,n*2){
		if(a[i]==mx)a[i]=2;
		else if(a[i]==mx-1)a[i]=1;
		else a[i]=0;
	}
	ll twotwo=0;
	ll twoone=0;
	ll twozero=0;
	ll oneone=0;
	ll onezero=0;
	ll zerozero=0;
	rep(i,n){
		vl tmp;
		tmp.push_back(a[i*2]);
		tmp.push_back(a[i*2+1]);
		sort(tmp.rbegin(),tmp.rend());
		if(tmp[0]==2&&tmp[1]==2)twotwo++;
		if(tmp[0]==2&&tmp[1]==1)twoone++;
		if(tmp[0]==2&&tmp[1]==0)twozero++;
		if(tmp[0]==1&&tmp[1]==1)oneone++;
		if(tmp[0]==1&&tmp[1]==0)onezero++;
		if(tmp[0]==0&&tmp[1]==0)zerozero++;
	}

	vl twoans(n*2,0);
	if(twotwo==0){
		rep(i,n){
			vl tmp;
			tmp.push_back(a[i*2]);
			tmp.push_back(a[i*2+1]);
			sort(tmp.rbegin(),tmp.rend());
			
			if(tmp[0]==2&&tmp[1]==2)twotwo--;
			if(tmp[0]==2&&tmp[1]==1)twoone--;
			if(tmp[0]==2&&tmp[1]==0)twozero--;
			if(tmp[0]==1&&tmp[1]==1)oneone--;
			if(tmp[0]==1&&tmp[1]==0)onezero--;
			if(tmp[0]==0&&tmp[1]==0)zerozero--;

			loop(j,i*2,i*2+1){
				if(a[j]==0)continue;
				
				ll cnt=1;
				if(tmp[0]==2&&tmp[1]==1)cnt++;

				ll kakuritu=solve_two(cnt,twoone,twozero,oneone,onezero);
				twoans[j]+=kakuritu;
			}

			if(tmp[0]==2&&tmp[1]==2)twotwo++;
			if(tmp[0]==2&&tmp[1]==1)twoone++;
			if(tmp[0]==2&&tmp[1]==0)twozero++;
			if(tmp[0]==1&&tmp[1]==1)oneone++;
			if(tmp[0]==1&&tmp[1]==0)onezero++;
			if(tmp[0]==0&&tmp[1]==0)zerozero++;
			
		}
	}
	//vdbg(twoans);
	
	vl ans(n*2,0);

	rep(i,n){
		vl tmp;
		tmp.push_back(a[i*2]);
		tmp.push_back(a[i*2+1]);
		sort(tmp.rbegin(),tmp.rend());
		
		if(tmp[0]==2&&tmp[1]==2)twotwo--;
		if(tmp[0]==2&&tmp[1]==1)twoone--;
		if(tmp[0]==2&&tmp[1]==0)twozero--;
		if(tmp[0]==1&&tmp[1]==1)oneone--;
		if(tmp[0]==1&&tmp[1]==0)onezero--;
		if(tmp[0]==0&&tmp[1]==0)zerozero--;

		loop(j,i*2,i*2+1){
			if(a[j]==0)continue;
			if(a[j]==1)continue;
			
			ll kakuritu=solve_three(twotwo,twoone,twozero);

			ans[j]+=kakuritu;
		}

		if(tmp[0]==2&&tmp[1]==2)twotwo++;
		if(tmp[0]==2&&tmp[1]==1)twoone++;
		if(tmp[0]==2&&tmp[1]==0)twozero++;
		if(tmp[0]==1&&tmp[1]==1)oneone++;
		if(tmp[0]==1&&tmp[1]==0)onezero++;
		if(tmp[0]==0&&tmp[1]==0)zerozero++;
	}


	rep(i,n*2){
		ans[i]+=twoans[i];
		ans[i]%=mod;
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	return 0;
}
