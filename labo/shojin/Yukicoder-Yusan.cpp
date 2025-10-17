#include<bits/stdc++.h>
using namespace std;
#define ll long long
//メイン
int main(){
	string n;
	cin>>n;
	if(n=="2"){
		cout<<1<<endl<<"Yes"<<endl;
		return 0;
	}
	if((n.back()-'0')%2==0){
		cout<<0<<endl<<"No"<<endl;
	}else{
		cout<<1<<endl<<"No"<<endl;
	}
	return 0;
}
