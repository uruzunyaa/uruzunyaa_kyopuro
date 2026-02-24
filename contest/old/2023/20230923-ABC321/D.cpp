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
    long long n,m,p;
    cin>>n>>m>>p;
    vector<long long> a(n);
    vector<long long> b(m);

    rep(i,n){
        cin>>a[i];
        if(a[i]>=p)a[i]=p;
    }
    rep(i,m){
        cin>>b[i];
        if(b[i]>=p)b[i]=p;
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    vector <long long> sumB(m);
    sumB[0]=b[0];
    loop(i,1,m-1){
        sumB[i]=sumB[i-1]+b[i];
    }

    long long ans=0;
    long long point=m-1;
    rep(i,n){
        long long nokori =p-a[i];
        while(point>-1){
            if(nokori>b[point])break;
            point--;
        }
        if(point>-1){
            ans+=sumB[point];
            ans+=(point+1)*a[i];
            ans+=(m-point-1)*p;
        }else{
            ans+=m*p;
        }
        
    }
    cout<<ans;
    
    return 0;
}