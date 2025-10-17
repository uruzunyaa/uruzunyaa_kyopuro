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
long long power(long long A, long long B) {
    long long result = 1;
    for (long long i = 0; i < B; i++) {
        result *= A;
    }
    return result;
}
int main(){
    int n;
    cin>>n;
    int s[n],e[n];
    vector <int> memo(288,0);
    rep(i,n){
        string m;
        cin>>m;
        s[i]=(m[0]-'0')*600+(m[1]-'0')*60+(m[2]-'0')*10+(m[3]-'0');
        e[i]=(m[5]-'0')*600+(m[6]-'0')*60+(m[7]-'0')*10+(m[8]-'0');
        
        s[i]=s[i]-(s[i]%5);
        if(e[i]%5!=0)e[i]=e[i]+(5-(e[i]%5));
        e[i]-=5;

        s[i]/=5;
        e[i]/=5;
        

        loop(j,s[i],e[i]){
            memo[j]=1;
        }
    }
    vector <int>start;
    vector <int>end;
    int flag=0;
    rep(i,288){
        if(memo[i]==1&&flag==0){
            start.push_back(i);
            flag=1;
        }
        if(memo[i]==0&&flag==1){
            end.push_back(i);
            flag=0;
        }
    }
    if(flag==1)end.push_back(288);

    rep(i,start.size()){
        int starth,startm,endh,endm;
        starth=start[i]/12;
        startm=(start[i]*5)%60;
        endh=end[i]/12;
        endm=(end[i]*5)%60;
        cout<<setw(2)<<setfill('0')<<starth;
        cout<<setw(2)<<setfill('0')<<startm<<"-";
        cout<<setw(2)<<setfill('0')<<endh;
        cout<<setw(2)<<setfill('0')<<endm<<endl;
    }
    return 0;
}