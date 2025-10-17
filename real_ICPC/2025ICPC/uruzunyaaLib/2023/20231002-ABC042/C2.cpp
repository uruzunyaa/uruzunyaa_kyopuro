#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<string>
#include<map>
#include <iomanip> 
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
#define ll long long
#define inf 100000000000000000
long long power(long long A, long long B) {
    long long result = 1;
    for (long long i = 0; i < B; i++) {
        result *= A;
	}
	return result;
}

int ans=9999999;

void sub(const vector<int>& e,int n,int num){
	num*=10;
	rep(i,e.size()){
		if(num==0&&e[i]==0)continue;
		num+=e[i];
		if(num>=n){
			if(ans>num)ans=num;
			return;
		}
		sub(e,n,num);
		num-=e[i];
	}
	return;
}

int main(){
	int n,k;
	cin>>n>>k;
	int d[k];
	rep(i,k){
		cin>>d[i];
	}
	vector<int> e;
	rep(i,10){
		int flag=1;
		rep(j,k){
			if(i==d[j])flag=0;
		}
		if(flag==1)e.push_back(i);
	}
	
	sub(e,n,0);
	cout<<ans<<endl;

    return 0;
}