#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<n;i++)
#define vl vector<ll> 
#define inf 1000000000000000000LL

int main(){
	//上下右左
	string dd="NSEW";
	random_device seed_gen;
	mt19937_64 rnd(seed_gen());
	uniform_int_distribution<ll> distD(0,3);
	
	string res;
	cin>>res;
	
	//鍵を探す
	while(1){
		ll next;
		while(1){
			next=distD(rnd);
			if(res[next]=='0')break;
		}
		cout<<dd[next]<<endl;
		if(res[4]=='1')break;
	}

	vector<string> g(33,string(33,'?'));
	g[16][16]=k;
}