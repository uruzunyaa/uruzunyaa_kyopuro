#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int n;
    cin>>n;
    long long a;
    long long A[n][n];

    //aに一度値を保管し、Aの配列に一桁づつ入れる。
    for(int i=0;i<n;i++){
        cin>>a;
        for(int j=0;j<n;j++){
            A[i][j]=a/(int)pow(10,(n-j-1))%10;
        }
    }

    //負の値は無いのでMAXを0に設定しておく。
    long long max=0;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            //i,jがスタートの位置、k,lが動く方向、mが何個進んだか。
            for(int k=-1;k<=1;k++){
                for(int l=-1;l<=1;l++){
                    //両方0の時は動かないのでスキップ
                    if(k==0&&l==0){
                        continue;
                    }
                    long long num=0;
                    //合計を計算。
                    for(int m=0;m<n;m++){
                        //配列のどの要素を参照するかをnで割ったあまりで求める。
                        //負の値のあまりを取るとおかしくなるのであらかじめnを加算する。
                        num+=(long long)pow(10,n-m-1)*A[(n+i+k*m)%n][(n+j+l*m)%n];
                    }
                    //最大かチェックし最大なら更新
                    if(max<num)max=num;
                    
                }
            }
        }
    }
    cout<<max;
    return 0;
}