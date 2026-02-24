#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000

//メイン
int main(){
	ll n,m,l;
	cin>>n>>m>>l;
	vl a(n);
	vl a2(n);
	vl b(m);
	vl b2(m);
	vl c(l);
	vl d(l);
	rep(i,n){
		cin>>a[i];
		a2[i]=a[i];
	}
	rep(i,m){
		cin>>b[i];
		b2[i]=b[i];
	}
	rep(i,l)cin>>c[i]>>d[i],c[i]--,d[i]--;
	map<ll,ll>kiroku;
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	vl countA(n,m-1);
	vl countB(m,n-1);
	ll indexA=n-1;
	ll indexB=m-1;

	//値段が高い順にl+1個列挙
	rep(i,l+1){
		kiroku[a[indexA]+b[indexB]]++;
		countA[indexA]--;
		countB[indexB]--;
		if(indexA!=0&&indexB!=0){
			if(a[indexA-1]+b[countA[indexA-1]]<=b[indexB-1]+a[countB[indexB-1]]){
				//小さくすべきはBの時
				indexA=countB[indexB-1];
				indexB--;
			}else{
				//小さくすべきはAの時
				indexB=countA[indexA-1];
				indexA--;
			}
		}else{
			if(indexA==0){
				//小さくすべきはBの時
				indexA=countB[indexB-1];
				indexB--;
			}else{
				//小さくすべきはAの時
				indexB=countA[indexA-1];
				indexA--;
			}
		}
		
	}
	//数えた値段のリストから、食べ合わせが悪いものを引く
	rep(i,l){
		kiroku[a2[c[i]]+b2[d[i]]]--;
		if(kiroku[a2[c[i]]+b2[d[i]]]==0)kiroku.erase(a2[c[i]]+b2[d[i]]);
	}
	//もし異常が起きていたら無限ループに入れる。
	if(kiroku.rbegin()->second<0)while(1);

	//食べ合わせが悪くないもので最も大きいものを出力。
	cout<<kiroku.rbegin()->first<<endl;
	return 0;
}

