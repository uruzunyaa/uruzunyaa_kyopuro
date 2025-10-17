#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll h,m;
	cin>>h>>m;
	while(1){
		ll hh=(h/10)*10+m/10;
		ll mm=(h%10)*10+m%10;
		if(hh<24&&mm<60){
			cout<<h<<" "<<m<<endl;
			return 0;
		}
		m++;
		if(m==60)m=0,h++;
		if(h==24)h=0;
	}

	return 0;
}