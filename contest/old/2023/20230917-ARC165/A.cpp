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
    int t;
    cin>>t;
    rep(i,t){
        int n;
        cin>>n;
        vector<int>s;
        //素因数分解をする
        int j=2;
        while(n>=j*j){
            if(n%j==0){
                s.push_back(j);
                n/=j;
            }else{
                j++;
            }
        }
        s.push_back(n);

        //素因数の重複要素を削除
        s.erase(unique(s.begin(), s.end()),s.end());
        if(s.size()>=2){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}