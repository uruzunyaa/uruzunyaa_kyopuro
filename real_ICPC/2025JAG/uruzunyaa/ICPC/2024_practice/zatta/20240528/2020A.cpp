#include<bits/stdc++.h>
using namespace std;
int solve(){
	int n;
	cin>>n;
	if(n==0)return 1;
	vector<int> d(n);
	cin>>d[0]>>d[1]>>d[2];
	int ans=0;
	for(int i=3;i<n;i++){
		cin>>d[i];
		if(d[i-3]==2&&d[i-2]==0&&d[i-1]==2&&d[i]==0)ans++;
	}
	cout<<ans<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}