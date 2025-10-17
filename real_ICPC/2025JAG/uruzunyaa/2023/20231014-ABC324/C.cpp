#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<deque>
#include<iomanip>
#include<tuple>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
#define ll long long
#define inf 100000000000000000

long long power(long long A, long long B) {
    long long result = 1;
    for (long long i = 0; i < B; i++) {
        result *= A;
    }
    return result;
}

int main(){
    int n;
    string t;
    cin>>n>>t;
    string s[n];
    rep(i,n){
        cin>>s[i];
    }

    vector<int> ans;
    rep(i,n){
        if(t==s[i]){
            ans.push_back(i+1);
            continue;
        }
        if(s[i].size()==t.size()){
            int wrong=0;
            rep(j,t.size()){
                if(t[j]!=s[i][j]) wrong++;
            }
            if(wrong==1) ans.push_back(i+1);
        }else if(s[i].size()==t.size()+1){
            int wrong=0;
            rep(j,t.size()){
                if(t[j]!=s[i][j+wrong]){
                    wrong++;
                    j--;
                }
                if(wrong==2)break;
            }
            if(wrong<=1)ans.push_back(i+1);
        }else if(s[i].size()==t.size()-1){
            int wrong=0;
            rep(j,s[i].size()){
                if(t[j+wrong]!=s[i][j]){
                    wrong++;
                    j--;
                }
                if(wrong==2)break;
            }
            if(wrong<=1)ans.push_back(i+1);
        }
    }
    cout<<ans.size()<<endl;
    rep(i,ans.size())cout<<ans[i]<<" ";
    return 0;
}