#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
mt19937_64 mt64(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


ll rndnxt(ll mn,ll mx){
	ll range=mx-mn+1;
	return mn+(((mt64()%range)+range)%range);
}

int main(){
	rep(i,6)cout<<rndnxt(3,5)<<endl;
	return 0;
}
