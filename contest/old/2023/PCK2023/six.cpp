#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<string>
#include<map>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)

int main(){
    int h,w;
    cin>>h>>w;
    int d[h][w+1],f[w][h+1];
    rep(i,h){
        d[i][0]=0;
        d[i][w]=0;
        rep(j,w-1){
            cin>>d[i][j+1];
        }
    }

    rep(i,w){
        f[i][0]=0;
        f[i][h]=0;
        rep(j,h-1){
            cin>>f[i][j+1];
        }
    }

    int tizu[3][h][w];
    rep(k,3){
        rep(i,h){
            rep(j,w){
                tizu[k][i][j]=0;
            }
        }
    }
    tizu[1][0][0]=1;

    int k=1;

    //何も書き込まなかったら増やす。
    int count=0;
    int ans=0;
    
    while(count!=3){
        //書き込んだかのチェック
        int check=0;
        ans++;

        rep(i,h){
            rep(j,w){
                if(tizu[k][i][j]==1){
                    if(d[i][j]==k){
                        if(tizu[(k+1)%3][i][j-1]==0){
                            tizu[(k+1)%3][i][j-1]=1;
                            check=1;
                        }
                    }
                    if(d[i][j+1]==k){
                        if(tizu[(k+1)%3][i][j+1]==0){
                            tizu[(k+1)%3][i][j+1]=1;
                            check=1;
                        }
                    }
                    if(f[j][i]==k){
                        if(tizu[(k+1)%3][i-1][j]==0){
                            tizu[(k+1)%3][i-1][j]=1;
                            check=1;
                        }
                    }
                    if(f[j][i+1]==k){
                        if(tizu[(k+1)%3][i+1][j]==0){
                            tizu[(k+1)%3][i+1][j]=1;
                            check=1;
                        }
                    }
                }
            }
        }
        if(tizu[k+1][h-1][w-1]==1){
            cout<<ans<<endl;
        }
        if(check==0){
            break;
        }
        k++;
        if(k==3) k=0;
    }

    cout<<-1<<endl;
    
    return 0;
}