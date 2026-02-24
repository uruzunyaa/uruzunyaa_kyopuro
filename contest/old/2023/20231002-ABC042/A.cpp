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
long long power(long long A, long long B) {
    long long result = 1;
    for (long long i = 0; i < B; i++) {
        result *= A;
    }
    return result;
}
int main(){
	int a,b,c;
	cin>>a>>b>>c;
	if(a>b)swap(a,b);
	if(c>b)swap(c,b);
	if(a==5&&b==7&&c==5)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
    return 0;
}