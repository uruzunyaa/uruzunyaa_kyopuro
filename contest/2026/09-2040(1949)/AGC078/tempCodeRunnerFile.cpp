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


//転倒数を求める,配列を破壊変更してる事に注意
ll inversion_number(vl &v) {
	int n = v.size();
	if (n == 1) return 0;
	vl v1(v.begin(), v.begin() + n / 2);
	vl v2(v.begin() + n / 2, v.end());
	ll res = inversion_number(v1) + inversion_number(v2);
	int p = 0, q = 0;
	for (int i = 0; i < n; i++) {
		if (q == v2.size() || (p < v1.size() && v1[p] <= v2[q])) {
			v[i] = v1[p++];
		}else {
			v[i] = v2[q++];
			res += v1.size() - p;
		}
    }
    return res;
}

void solve(){
	ll n;
	string s;
	cin>>n>>s;
	
	vl tmp;
	tmp.push_back(0);
	rep(i,n){
		if(s[i]=='A')tmp.push_back(0);
		else tmp.push_back(1);
	}
	tmp.push_back(1);

	rep(i,n+1){
		tmp[i]^=tmp[i+1];
	}
	tmp.pop_back();

	vl tmpa=tmp;
	ll abel=inversion_number(tmpa);
	vl tmpb=tmp;
	reverse(tmpb.begin(),tmpb.end());
	ll bart=inversion_number(tmpb);

	if(abel>bart){
		cout<<"Abel"<<endl;
		return;
	}
	if(abel<bart){
		cout<<"Bart"<<endl;
		return;
	}

	ll cnt=0;
	rep(i,n){
		if(s[i]=='A')cnt++;
		else cnt--;
	}
	cnt=abs(cnt);
	ll heru=(n-cnt)/2;
	if(heru%2==0)cout<<"Abel"<<endl;
	else cout<<"Bart"<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}

