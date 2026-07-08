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

void two(){
	ll n,m;
	cin>>n>>m;
	vl bk(m+1,0);
	vl aite(m+1,0);
	rep(i,n){
		ll c;
		cin>>c;
		bk[c]++;
	}
	map<ll,ll> mp;

	//自分の手札を出力
	ofstream fout("./two");//出力する場合の出力先を指定
	rep(i,m+1){
		fout<<bk[i]<<" ";
	}
	fout.flush();   // バッファをOS側へ流す
	fout.close();   // ファイルを閉じる

	std::this_thread::sleep_for(std::chrono::milliseconds(1500));

	//相手の手札を取得
	ifstream fin("./one");
	rep(i,m+1){
		fin>>aite[i];
	}
	
	bool guessed=false;

	while(1){
		string turn,res;
		cin>>turn;
		if(turn=="TURN"){
			ll mex=m;
			loop(i,1,m-1){
				if(mp.count(i))continue;
				mex=i;
				break;
			}
			if(mex==m)break;
			cout<<"ASK "<<mex<<endl;
		}
		cin>>res;
		ll type,cnt;
		cin>>type>>cnt;

		if(res=="GUESSED"){
			guessed=true;
			continue;
		}
		mp[type]=cnt;
	}

	vl ans;
	loop(i,1,m-1){
		ll cnt=mp[i]-bk[i]-aite[i];
		rep(z,cnt)ans.push_back(i);
	}
	while(ans.size()<n)ans.push_back(m);
	cout<<"GUESS ";
	vdbg(ans);

	string tmp;
	rep(i,5)cin>>tmp;
	if(!guessed)rep(i,4)cin>>tmp;
}

void one(){
	ll n,m;
	cin>>n>>m;
	vl bk(m+1,0);
	vl aite(m+1,0);
	rep(i,n){
		ll c;
		cin>>c;
		bk[c]++;
	}
	map<ll,ll> mp;

	//自分の手札を出力
	ofstream fout("./one");//出力する場合の出力先を指定
	rep(i,m+1){
		fout<<bk[i]<<" ";
	}
	fout.flush();   // バッファをOS側へ流す
	fout.close();   // ファイルを閉じる

	std::this_thread::sleep_for(std::chrono::milliseconds(1500));

	//相手の手札を取得
	ifstream fin("./two");
	rep(i,m+1){
		fin>>aite[i];
	}

	bool guessed=false;
	while(1){
		string turn,res;
		cin>>turn;
		if(turn=="TURN"){
			ll mex=m;
			loop(i,1,m-1){
				if(mp.count(i))continue;
				mex=i;
				break;
			}
			if(mex==m)break;
			cout<<"ASK "<<mex<<endl;
		}
		cin>>res;
		ll type,cnt;
		cin>>type>>cnt;

		if(res=="GUESSED"){
			guessed=true;
			continue;
		}
		mp[type]=cnt;
	}

	vl ans;
	loop(i,1,m-1){
		ll cnt=mp[i]-bk[i]-aite[i];
		// cout<<i<<" "<<cnt<<endl;
		// cout<<mp[i]<<" "<<bk[i]<<" "<<aite[i]<<endl;
		rep(z,cnt)ans.push_back(i);
	}
	while(ans.size()<n)ans.push_back(m);
	cout<<"GUESS ";
	vdbg(ans);

	string tmp;
	rep(i,5)cin>>tmp;
	if(!guessed)rep(i,4)cin>>tmp;
}

//メイン
int main(){
	ll p;
	cin>>p;
	if(p==1)one();
	else two();
	
	return 0;
}
