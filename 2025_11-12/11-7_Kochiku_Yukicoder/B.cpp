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

//グリッドを右に90度回転する。
vvl gridTurn(vvl &s){
	ll h=s[0].size();
	ll w=s.size();
	vvl res(h,vl(w));

	rep(i,h)rep(j,w){
		res[i][j]=s[w-j-1][i];
	}
	return res;
}


//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

void t(ll h,ll w){
	bool f=false;
	if(h<w){
		swap(h,w);
		f=true;
	}

	if(w==3&&h<6){
		cout<<-1<<endl;
		return;
	}

	//高さhの幅3,4,5を作る
	vvl three,four,five;

	three.push_back({1,1,1});
	three.push_back({2,1,3});
	three.push_back({2,2,3});
	three.push_back({2,3,3});
	three.push_back({2,4,3});
	rep(i,h-6)three.push_back({2,4,3});
	three.push_back({4,4,4});

	four.push_back({3,1,1,1});
	four.push_back({3,3,1,2});
	rep(i,h-4)four.push_back({3,4,1,2});
	four.push_back({3,4,2,2});
	four.push_back({4,4,4,2});

	five.push_back({1,2,2,2,3});
	five.push_back({1,1,2,3,3});
	five.push_back({1,4,2,5,3});
	rep(i,h-5)five.push_back({1,4,2,5,3});
	five.push_back({4,4,4,5,3});
	five.push_back({5,5,5,5,5});

	ll k=0;
	vvl ans(h);
	//3の倍数に帰着させる
	if(w%3==1){
		w-=4;
		rep(i,h){
			rep(j,4){
				ans[i].push_back(four[i][j]+k);
			}
		}
		k+=4;
	}
	if(w%3==2){
		w-=5;
		rep(i,h){
			rep(j,5){
				ans[i].push_back(five[i][j]+k);
			}
		}
		k+=5;
	}

	//3の倍数を処理
	rep(z,w/3){
		rep(i,h){
			rep(j,3){
				ans[i].push_back(three[i][j]+k);
			}
		}
		k+=4;
	}

	if(f)ans=gridTurn(ans);
	cout<<k<<endl;
	vvdbg(ans);
}

void c(ll h,ll w){
	bool f=false;
	if(h>w){
		swap(h,w);
		f=true;
	}

	if(h==3&&w%2==1){
		cout<<-1<<endl;
		return;
	}

	//高さhの幅4,5,6,7を作る
	vvl four,five,six,seven;

	four.push_back({1,1,1,2});
	four.push_back({1,2,1,2});
	rep(i,h-3)four.push_back({1,2,1,2});
	four.push_back({1,2,2,2});

	five.push_back({1,1,1,2,2});
	five.push_back({1,3,1,3,2});
	rep(i,h-4)five.push_back({1,3,1,3,2});
	five.push_back({1,3,3,3,2});
	five.push_back({1,2,2,2,2});

	six.push_back({1,1,1,2,2,2});
	six.push_back({1,3,1,2,3,2});
	rep(i,h-3)six.push_back({1,3,1,2,3,2});
	six.push_back({1,3,3,3,3,2});

	seven.push_back({1,2,2,2,2,3,3});
	seven.push_back({1,2,1,4,2,4,3});
	rep(i,h-4)seven.push_back({1,2,1,4,2,4,3});
	seven.push_back({1,1,1,4,4,4,3});
	seven.push_back({3,3,3,3,3,3,3});

	ll k=0;
	vvl ans(h);
	//4の倍数に帰着させる
	if(w%4==1){
		w-=5;
		rep(i,h){
			rep(j,5){
				ans[i].push_back(five[i][j]+k);
			}
		}
		k+=3;
	}
	if(w%4==2){
		w-=6;
		rep(i,h){
			rep(j,6){
				ans[i].push_back(six[i][j]+k);
			}
		}
		k+=3;
	}
	if(w%4==3){
		w-=7;
		rep(i,h){
			rep(j,7){
				ans[i].push_back(seven[i][j]+k);
			}
		}
		k+=4;
	}

	//4の倍数を処理
	rep(z,w/4){
		rep(i,h){
			rep(j,4){
				ans[i].push_back(four[i][j]+k);
			}
		}
		k+=2;
	}

	if(f)ans=gridTurn(ans);
	cout<<k<<endl;
	vvdbg(ans);
}

void ct(ll h,ll w){
	bool f=false;
	if(h<w){
		swap(h,w);
		f=true;
	}

	//高さhの幅3,4,5を作る
	vvl three,four,five;

	three.push_back({1,1,1});
	three.push_back({1,2,1});
	rep(i,h-3)three.push_back({1,2,1});
	three.push_back({2,2,2});

	four.push_back({1,1,1,2});
	four.push_back({3,1,2,2});
	rep(i,h-4)four.push_back({3,1,3,2});
	four.push_back({3,1,3,2});
	four.push_back({3,3,3,2});

	five.push_back({3,3,3,3,3});
	five.push_back({3,1,1,1,3});
	five.push_back({3,1,2,1,3});
	rep(i,h-4)five.push_back({3,1,2,1,3});
	five.push_back({2,2,2,2,2});

	ll k=0;
	vvl ans(h);
	//3の倍数に帰着させる
	if(w%3==1){
		w-=4;
		rep(i,h){
			rep(j,4){
				ans[i].push_back(four[i][j]+k);
			}
		}
		k+=3;
	}
	if(w%3==2){
		w-=5;
		rep(i,h){
			rep(j,5){
				ans[i].push_back(five[i][j]+k);
			}
		}
		k+=3;
	}

	//3の倍数を処理
	rep(z,w/3){
		rep(i,h){
			rep(j,3){
				ans[i].push_back(three[i][j]+k);
			}
		}
		k+=2;
	}

	if(f)ans=gridTurn(ans);
	cout<<k<<endl;
	vvdbg(ans);
}

//メイン
int main(){
	ll h,w;
	cin>>h>>w;
	if(min(h,w)<3){
		cout<<-1<<endl;
		cout<<-1<<endl;
		cout<<-1<<endl;
		return 0;
	}
	//Cのみ
	c(h,w);
	//Tのみ
	t(h,w);
	//CT両方
	ct(h,w);
	return 0;
}
