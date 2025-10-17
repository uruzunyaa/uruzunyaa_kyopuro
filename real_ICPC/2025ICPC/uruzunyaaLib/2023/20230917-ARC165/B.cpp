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
    int n,k;
    cin>>n>>k;
    int p[n];
    rep(i,n){
        cin>>p[i];
    }
    int count=0;
    int maxcount=0;
    rep(i,n-1){
        if(p[i]<p[i+1]){
            count++;
            if(maxcount<count)maxcount=count;
        }else{
            count=0;
        }
    }
    if(maxcount>=k){
        rep(i,n){
            cout<<p[i]<<" ";
        }
        return 0;
    }
    
    int min=9000000;
    loop(i,n-k,n-2){
        if(min>p[i])min=p[i];
    }
    int start=n-k;
    while(1){
        if(start!=0&&p[start-1]<min){
            min=p[start-1];
            start--;
        }else{
            break;
        }
    }
    vector <int> b;
    rep(i,k){
        b.push_back(p[start+i]);
    }
    sort(b.begin(),b.end());
    rep(i,n){
        if(start<=i&&i<=start+k-1){
            cout<<b[i-start]<<" ";
        }else{
            cout<<p[i]<<" ";
        }
        
    }
    
    return 0;
    

}