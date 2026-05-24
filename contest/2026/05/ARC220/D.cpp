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

void myassert(string s){
	cout<<s<<endl;
	assert(false);
}

bool judge(ll n,vl a){
	ll k=(n-2)*(n-2);
	k++;
	k/=2;

	if(a.size()<k){
		myassert("size");
	}
	
	set<pair<ll,ll>> st;
	rep(i,a.size()-1){
		pair<ll,ll> tmp={a[i],a[i+1]};
		if(tmp.first>tmp.second)swap(tmp.first,tmp.second);
		if(st.count(tmp)||tmp.first==tmp.second){
			myassert("twice_use");
		}
		st.insert(tmp);
	}

	rep(i,a.size()-2){
		if(abs(a[i]-a[i+2])>=2)myassert("abs_is_not_1");
	}

	rep(i,a.size()){
		if(a[i]>n)myassert("overflow");
	}
	return true;
}

void dfs(ll n,ll offsetx,ll offsety,vl & ans){
	ll x=((n-2)/6)*2+2,y=n;
	if(n<5)return;
	if(n==5){
		ans.push_back(y+offsety);
		ans.push_back(x+1+offsetx);
		ans.push_back(y-1+offsety);
		ans.push_back(x+offsetx);
		return;
	}
	while(x!=n-3){
		ans.push_back(y+offsety);
		ans.push_back(x+1+offsetx);
		ans.push_back(y-1+offsety);
		ans.push_back(x+2+offsetx);
		x+=2;
	}
	y-=2;
	while(x!=2){
		ans.push_back(y+offsety);
		ans.push_back(x-1+offsetx);
		ans.push_back(y-1+offsety);
		ans.push_back(x-2+offsetx);
		x-=2;
		y-=2;
	}
	y+=2;
	while(y!=n){
		ans.push_back(y+offsety);
		ans.push_back(x-1+offsetx);
		ans.push_back(y+1+offsety);
		ans.push_back(x+offsetx);
		y+=2;
	}
	while(x!=((n-2)/6)*2+2){
		ans.push_back(y+offsety);
		ans.push_back(x+1+offsetx);
		ans.push_back(y-1+offsety);
		ans.push_back(x+2+offsetx);
		x+=2;
	}
	dfs(n-6,offsetx+2,offsety+4,ans);
	return;
}

void solve(ll n){
	vl ans;
	if(n%2==0){
		ll k=(n-2)*(n-2);
		k++;
		k/=2;

		ll small=1;
		ll big=2;
		if(n%2==1)big++;
		ans.push_back(big);
		big++;

		while(ans.size()<k){
			if((small/2)%2==0){
				ans.push_back(small);
				ans.push_back(big);
				ans.push_back(small+1);
				ans.push_back(big+1);
				big+=2;
				if(n-big<1){
					small+=2;
					big-=2;
				}
			}else{
				ans.push_back(small);
				ans.push_back(big);
				ans.push_back(small+1);
				ans.push_back(big-1);
				big-=2;
				if(small+2==big||small+3==big){
					small+=2;
					big+=2;
				}
			}
		}
	}else{
		ans.push_back(((n-2)/6)*2+2);
		dfs(n,0,0,ans);
	}
	
	cout<<ans.size()<<endl;
	vdbg(ans);
	judge(n,ans);
	return;	
}

int main(){
	ll t;
	cin>>t;
	rep(i,t){
		ll n;
		cin>>n;
		//n=i+3;
		//cout<<"test of "<<n<<endl;
		solve(n);
	}
}
