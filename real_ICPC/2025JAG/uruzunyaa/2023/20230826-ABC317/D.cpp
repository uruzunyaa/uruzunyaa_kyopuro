#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int n;
    cin>>n;

    //xとyから議席zを手に入れるための各コストを計算し代入する。（～20行目）
    int x,y,z[n],cost[n];
    int sumZ=0;
    for(int i=0;i<n;i++){
        cin>>x>>y>>z[i];
        if(x<y){
            cost[i]=(y+1-x)/2;
        }else{
            cost[i]=0;
        }
        sumZ+=z[i];
    }

    //Zの合計を全体に1を足す
    sumZ++;

    //特定の議席数を得るのに最小のコストを記録する。
    long long memo[n+1][sumZ];

    //配列初期化
    for(int i=0;i<=n;i++){
        memo[i][0]=0;
        for(int j=1;j<sumZ;j++){
            memo[i][j]=-1;
        }
    }
    
    //その選挙区まででの、各議席の獲得コストの最小を記録していき、動的計画法を用いて次の選挙区を追加していく。
    for(int i=0;i<n;i++){
        //次の選挙区の初期値生成
        for(int j=0;j<sumZ;j++){
            memo[i+1][j]=memo[i][j];
        }

        //最善が更新された時、代入する。
        for(int j=0;j<=sumZ/2;j++){
            if(memo[i][j]!=-1){
                if((memo[i][j+z[i]]>(memo[i][j]+cost[i]))||memo[i][j+z[i]]==-1) memo[i+1][j+z[i]]=memo[i][j]+cost[i];
            }
        }
    }

    //必要議席以上を獲得しているパターンの中で最低のコストのものを探し、出力する。
    long long min =-1;
    for(int i=sumZ/2;i<sumZ;i++){
        if((memo[n][i]!=-1)&&(memo[n][i]<min||min==-1)) min=memo[n][i];
    }
    cout<<min;
    return 0;
}