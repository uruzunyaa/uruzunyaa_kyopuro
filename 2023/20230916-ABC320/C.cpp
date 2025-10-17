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
    int m;
    cin>>m;
    string s[3];
    
    int check[3][10][3];
    rep(i,3){
        rep(j,10){
            rep(k,3){
                //リール番号、数字、何回目の出現か
                //入力値は何秒後か
                check[i][j][k]=-1;
            }
        }
    }
    rep(i,3){
        cin>>s[i];
    }
    rep(i,m*3){
        rep(j,3){
            rep(k,3){
                if(check[j][s[j][i%m]-'0'][k]==-1){
                    check[j][s[j][i%m]-'0'][k]=i;
                    break;
                }
            }
            
        }
        rep(j,10){
            
            if(check[0][j][0]!=-1&&check[1][j][0]!=-1&&check[2][j][0]!=-1){
                rep(k,3){
                    rep(k2,3){
                        rep(k3,3){
                            if(check[0][j][k]!=check[1][j][k2]&&check[2][j][k3]!=check[1][j][k2]&&check[0][j][k]!=check[2][j][k3]&&check[0][j][k]!=-1&&check[1][j][k2]!=-1&&check[2][j][k3]!=-1){
                                cout<<i<<endl;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<-1<<endl;
    return 0;
}