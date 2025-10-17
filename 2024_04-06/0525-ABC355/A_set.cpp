#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ll a,b;
	cin>>a>>b;

	set<ll> c={1,2,3};
	c.erase(a);
	c.erase(b);

	if(c.size()==1)cout<<*c.begin()<<endl;
	else cout<<-1<<endl;
	return 0;
}
