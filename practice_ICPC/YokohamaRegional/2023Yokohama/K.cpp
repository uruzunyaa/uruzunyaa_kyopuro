#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= (ll)b; ++i)

int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};

int main(){
	ll ld=0;
    ll ru=100000;
	string notfound="0.0000000";
	//円を探す
	ll mn,mx;
	for(ll i=198;i<100000;i+=198){
		cout<<"query "<<i<<" "<<ld<<" "<<i<<" "<<ru<<endl;
		string res;
		cin>>res;
		if(notfound!=res){
			mn=i-198;
			mx=i;
			break;
		}
	}

	
	//円の左端を探す
	ll left;
	while(mn!=mx){
		ll mid=mn+mx+1;
		mid/=2;
		cout<<"query "<<mid<<" "<<ld<<" "<<mid<<" "<<ru<<endl;
		string res;
		cin>>res;
		if(res==notfound){
			mn=mid;
		}else{
			mx=mid-1;
		}
	}
	left=mx;

	//円の右端を探す
	ll right;
	mn=left+200;
	mx=ru;
	while(mn!=mx){
		ll mid=mn+mx;
		mid/=2;
		cout<<"query "<<mid<<" "<<ld<<" "<<mid<<" "<<ru<<endl;
		string res;
		cin>>res;
		if(res==notfound){
			mx=mid;
		}else{
			mn=mid+1;
		}
	}
	right=mx;

	ll ansx=left+right;
	ansx/=2;

	ll ansr=right-left;
	ansr/=2;

	//円の上を探す
	double tmp=ansr*2;

	mn=ansr*2;
	mx=ru;
	while(mn!=mx){
		ll mid=mn+mx;
		mid/=2;
		cout<<"query "<<ansx<<" "<<ld<<" "<<ansx<<" "<<mid<<endl;
		double res;
		cin>>res;
		if(res==tmp){
			mx=mid;
		}else{
			mn=mid+1;
		}
	}
	ll ansy=mx-ansr;
	cout<<"answer "<<ansx<<" "<<ansy<<" "<<ansr<<endl;
}