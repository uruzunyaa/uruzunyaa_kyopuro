#include<bits/stdc++.h>
using namespace std;
int solve(){
	int n,m;
	cin>>n>>m;
	if(n==0&&m==0)return 1;

	vector<int> sum(n,0);
	int ans=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			int p;
			cin>>p;

			sum[j]+=p;
		}
	}
	cout<<*max_element(sum.begin(),sum.end())<<endl;
	
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}