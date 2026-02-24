#include<iostream>//入出力
#include<algorithm>//アルゴリズム
#include<vector>//配列
#include<string>//文字列
#include<map>//連想配列
#include<deque>//スタックとキュー
#include<iomanip>//出力形式調整
#include<tuple>//pairの複数型
#include<cmath>//数学。ルートとか
#include<cctype>//大文字小文字のチェックなど
#include<fstream>//ファイル入出力
#include<random>//乱数
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>

#define vvl vector<vector<long long>>
#define inf 4000000000000000000
#define mod 998244353
//#define mod 1000000007

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k) {
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}
ifstream fin("./DefaultFile");
ofstream fout("./DefaultOut");//出力する場合の出力先を指定

//メイン
int main(){
	ll h,w;
	cin>>h>>w;
	vector<string> ss(h);
	rep(i,h)cin>>ss[i];
	vvl s(h,vl(w));
	rep(i,h)rep(j,w){
		if(ss[i][j]=='#')s[i][j]=-1;
		else s[i][j]=0;
	}

	vl dx={1,-1,0,0};
	vl dy={0,0,1,-1};
	ll gc=0;
	ll debug=0;
	rep(i,h){
		rep(j,w){
			deque <pair<ll,ll>> bfs;
			if(s[i][j]==-1)bfs.emplace_back(i,j),gc++,s[i][j]=gc;
			while(!bfs.empty()){
				debug++;
				auto [x,y]=bfs.front();
				bfs.pop_front();
				rep(v,4){
					if(x+dx[v]<h&&0<=x+dx[v]&&y+dy[v]<w&&0<=y+dy[v]){
						if(s[x+dx[v]][y+dy[v]]==-1){
							bfs.emplace_back(x+dx[v],y+dy[v]);
							s[x+dx[v]][y+dy[v]]=gc;
							
						}
					}
				}
			}
		}
	}
	//cout<<debug<<endl;
	//cout<<gc<<endl;
	ll dc=0;
	ll sum=0;
	rep(i,h){
		rep(j,w){
			if(s[i][j]==0){
				dc++;
				map<ll,ll> ec;
				ec[0]=1;
				rep(v,4){
					if(i+dx[v]<h&&0<=i+dx[v]&&j+dy[v]<w&&0<=j+dy[v]){
						ec[s[i+dx[v]][j+dy[v]]]=1;
					}
				}
				sum+=gc+2-ec.size();
				sum%=mod;
			}
		}
	}
	sum*=power_mod(dc,mod-2);
	sum%=mod;

	cout<<sum<<endl;

	return 0;
}
