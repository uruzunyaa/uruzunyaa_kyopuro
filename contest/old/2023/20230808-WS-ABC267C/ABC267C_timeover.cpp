//このプログラムは実行時間オーバーする事を確認するためのプログラムです。

#include<iostream>
#include<algorithm>
int main(){
    //n,mを標準入力から取得
    int n,m;
    std::cin>>n>>m;
    
    //aを全て標準入力から取得
    long long a[n];
    for(int i=0;i<n;i++){
        std::cin>>a[i];
    }

    //答え候補の格納用配列
    long long answer[n-m+1];

    //iがm個選ぶ際の先頭の配列番号、jが実際に計算を行うためのループ
    for(int i=0;i<=n-m;i++){
        answer[i]=0;
        for(int j=0;j<m;j++){
            answer[i]+=a[j+i]*(j+1);
        }
    }

    //答えの候補の中から最大値を見つけて出力
    std::cout<< *std::max_element(answer,answer+n-m+1);

    return 0;
}