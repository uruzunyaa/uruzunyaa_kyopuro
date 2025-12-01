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


bool f=false;

bool check(string a,string b){
	string first=a+b;
	string second=b+a;
	if(first==second){
		f=true;
		return a.size()<b.size();
	}
	return first<second;
}

void solve(){
	f=false;
	ll n;
	cin>>n;
	vector<string> s(n);
	rep(i,n)cin>>s[i];

	shuffle(s.begin(),s.end(),mt);

	sort(s.begin(),s.end(),check);
	
	string ans;
	rep(i,n)ans+=s[i];
	if(!f){
		ans.clear();
		rep(i,n-2)ans+=s[i];
		ans+=s[n-1];
		ans+=s[n-2];
		if(n!=2){
			string tmp;
			rep(i,n-3)tmp+=s[i];
			tmp+=s[n-2];
			tmp+=s[n-3];
			tmp+=s[n-1];
			ans=min(ans,tmp);
		}
	}
	cout<<ans<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
