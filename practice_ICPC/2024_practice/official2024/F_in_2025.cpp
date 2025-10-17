#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL


//グリッド問題等用
vl fdx={1,1,-1,-1};
vl fdy={1,-1,1,-1};

//乱数、ファイル入出力
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

ll solve(){
	ll a,b,x,y,n;
	cin>>a>>b>>x>>y>>n;
	if(a==0)return 1;
	//rupはy切片、x座標に対してyがどれだけ大きいか。
	unordered_map<ll,set<pair<ll,ll>>> rup;
	//lupは、x+yが0,0よりどれだけ大きいか。
	unordered_map<ll,set<pair<ll,ll>>> lup;

	set<ll> ans;

	rep(i,n){
		ll c,d;
		cin>>c>>d;
		rup[d-c].insert({c,i+1});
		lup[c+d].insert({c,i+1});
	}

	rep(i,4){
		ll dx=fdx[i];
		ll dy=fdy[i];
		ll coinx=x,coiny=y;
		set<ll> tmp;
		rep(j,a+b+1){
			
			if(dx==dy){
				if(rup[coiny-coinx].size()!=0){
					if(dx==-1){
						auto it=rup[coiny-coinx].rbegin();
						while(it!=rup[coiny-coinx].rend()&&it->first>coinx)it++;
						if(it!=rup[coiny-coinx].rend()){
							tmp.insert(it->second);
							if(tmp.size()==1){
								ans.insert(it->second);
								break;
							}
						}
					}else{
						auto it=rup[coiny-coinx].begin();
						while(it!=rup[coiny-coinx].end()&&it->first<coinx)it++;
						if(it!=rup[coiny-coinx].end()){
							tmp.insert(it->second);
						}
					}
				}
			}else{
				if(lup[coiny+coinx].size()!=0){
					if(dx==-1){
						auto it=lup[coiny+coinx].rbegin();
						while(it!=lup[coiny+coinx].rend()&&it->first>coinx)it++;
						if(it!=lup[coiny+coinx].rend()){
							tmp.insert(it->second);
						}
					}else{
						auto it=lup[coiny+coinx].begin();
						while(it!=lup[coiny+coinx].end()&&it->first<coinx)it++;
						if(it!=lup[coiny+coinx].end()){
							tmp.insert(it->second);
						}
					}
				}
			}
			//壁にぶつかるまでの移動距離を求める。
			ll idoux,idouy;
			if(dx==-1)idoux=coinx;
			else idoux=a-coinx;
			if(dy==-1)idouy=coiny;
			else idouy=b-coiny;
	
			coinx+=dx*min(idoux,idouy);
			coiny+=dy*min(idoux,idouy);
	
			if(idoux==idouy)break;
			else if(idoux<idouy)dx*=-1;
			else dy*=-1;

			if(tmp.size()==2)break;
		}
	}
	if(ans.size()==0){
		cout<<"No"<<endl;
	}else{
		setdbg(ans);
	}
	return 0;
}

//メイン
int main(){
	while(!solve());
	return 0;
}
