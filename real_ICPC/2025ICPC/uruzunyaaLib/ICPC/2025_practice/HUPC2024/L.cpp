//#pragma GCC optimize("O3")
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
//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937_64 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

ll mtd(){
	ll tmp=(1LL<<60);
	return (((mt()%tmp)+tmp)%tmp);
}

//メイン
int main(){
	ll k,x;
	cin>>k>>x;
	ll left=mtd();
	ll right=mtd();
	ll over=mtd();

	ll rt=1;
	for(ll i=1;i*i<=k;i++)rt=i;

	
	vl ans;
	rep(i,rt-1){
		ll tmp=mtd();
		ll tmp2=mtd();
		ans.push_back(tmp);
		ans.push_back(tmp2);
		ans.push_back(tmp^tmp2);
	}
	ans.push_back(x);
	rep(i,rt-1){
		ll tmp=mtd();
		ll tmp2=mtd();
		ans.push_back(tmp);
		ans.push_back(tmp2);
		ans.push_back(tmp^tmp2);
	}

	ll nokori=k-(rt*rt);

	if(x==0){
		ans.clear();
		ll kosuu=0;
		while(1){
			kosuu++;
			if((kosuu)*(kosuu+1)/2>k)break;
			ll tmp=mtd();
			ll tmp2=mtd();
			ans.push_back(tmp);
			ans.push_back(tmp2);
			ans.push_back(tmp^tmp2);
		}
		kosuu--;
		nokori=k-((kosuu)*(kosuu+1)/2);
	}

	rep(i,nokori){
		ans.push_back(mtd());
		ll tmp=mtd();
		ll tmp2=mtd();
		ans.push_back(tmp);
		ans.push_back(tmp2);
		ans.push_back(tmp^tmp2^x);
	}
	cout<<ans.size()<<endl;
	vdbg(ans);


	return 0;
}
