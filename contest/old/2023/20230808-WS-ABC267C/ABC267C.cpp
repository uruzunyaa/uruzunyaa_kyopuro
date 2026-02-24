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

    //まず、配列aの要素数mの部分配列の、単純合計を計算。（32行目まで）
    //最初の要素から、1づつズラす方式で計算すると、
    //前回の値-前回の先頭要素+追加要素　で計算可能。
    
    //要素の部分合計格納用、int範囲外になる可能性があるのでlonglongを使用
    long long sum[n-m+1];
    //現在の値を保管する用
    long long currentSum = 0;

    //最初のm個の合計を計算し代入する
    for(int i=0;i<m;i++){
        currentSum += a[i];
    }
    sum[0]=currentSum;

    //前の値を利用して、m個の合計の配列を作る
    for(int i=1;i<=n-m;i++){
        currentSum += (a[i+m-1]-a[i-1]);
        sum[i]=currentSum;
    }

    //作成した単純合計を利用して、答えの配列を作成 （53行目まで）
    //方針は先程と同様に、1個づつズラして前回の結果を使い計算。
    //前回の値-前回の値の位置からw個の単純合計+追加要素のm倍　で計算可能
    
    //答え候補の格納用配列
    long long answer[n-m+1];
    //現在の値を保管する用
    long long currentAnswer = 0;

    //最初のm個の答え候補を計算し代入する
    for(int i=0;i<m;i++){
        currentAnswer += a[i]*(i+1);
    }
    answer[0]=currentAnswer;

    //前の値を利用して、m個の合計の配列を作る
    for(int i=1;i<=n-m;i++){
        currentAnswer += (a[i+m-1]*m-sum[i-1]);
        answer[i]=currentAnswer;
    }

    //答えの候補の中から最大値を見つけて出力
    std::cout<< *std::max_element(answer,answer+n-m+1);

    return 0;
}