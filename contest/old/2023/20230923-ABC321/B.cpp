#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<string>
#include<map>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
long long power(long long A, long long B) {
    long long result = 1;
    for (long long i = 0; i < B; i++) {
        result *= A;
    }
    return result;
}
int main(){
    int n,x;
    cin>>n>>x;
    vector <int> a(n-1);
    rep(i,n-1){
        cin>>a[i];
    }
    
    sort(a.begin(),a.end());
    int summin=0;
    int summax=0;
    rep(i,n-2){
        summin+=a[i];
        summax+=a[i+1];
    }
    if(summin>=x){
        cout<<0;
    }else if(summax<x){
        cout<<-1;
    }else{
        int sum=summin-a[0];
        if(x-sum<=a[n-2]){
            cout<<x-sum;
        }else{
            cout<<a[n-2];
        }
        
    }
    return 0;
}