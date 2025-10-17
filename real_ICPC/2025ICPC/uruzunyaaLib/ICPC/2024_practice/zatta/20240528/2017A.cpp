#include<bits/stdc++.h>
using namespace std;
int solve(){
	int n,m;
	cin>>n>>m;
	if(n==0&&m==0)return 1;

	vector<int> a(n);
	for(int i=0;i<n;i++)cin>>a[i];

	int ans=0;
	//2つの選び方を全て調べる
	for(int i=0;i<n;i++){
		for(int j=0;j<i;j++){
			if(a[i]+a[j]<=m){
				ans=max(a[i]+a[j],ans);
			}
		}
	}
	if(ans!=0)cout<<ans<<endl;
	else cout<<"NONE"<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}