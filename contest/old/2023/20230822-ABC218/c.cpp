//全体方針:最外層の除去(上下左右の開始座標の保持)→回転→比較
//上のみを回転させる
#include <algorithm>
#include<iostream>
using namespace std;
int main(){
    //入力の読み込み
    int n;
    cin>>n;
    //文字列を読み取る時、終端文字や改行文字等が入る事を考慮し2個長めに確保
    char s [n][n+2];
    char t [n][n+2];
    //1行づつ読み取り
    for(int i=0;i<n;i++){
        cin>>s[i];
    }
    for(int i=0;i<n;i++){
        cin>>t[i];
    }

    //上下左右のカットする数 初期化
    int upS=-1,downS=-1,leftS=-1,rightS=-1,upT=-1,downT=-1,leftT=-1,rightT=-1;

    //上下左右からi行目の列や行を見て、#を発見した瞬間その直前の行までを削減対象とする。
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(upS==-1&&s[i][j]=='#') upS=i;
            if(downS==-1&&s[n-i-1][j]=='#') downS=i;
            if(leftS==-1&&s[j][i]=='#') leftS=i;
            if(rightS==-1&&s[j][n-i-1]=='#') rightS=i;
            

            if(upT==-1&&t[i][j]=='#') upT=i;
            if(downT==-1&&t[n-i-1][j]=='#') downT=i;
            if(leftT==-1&&t[j][i]=='#') leftT=i;
            if(rightT==-1&&t[j][n-i-1]=='#') rightT=i;
        }
    }
    //ここまではOK

    //合致するものが見つかればflagの値が1になる
    int flag=0;
    for(int i=0;i<4;i++){
        //回転配列の格納
        char temp[n][n];
        //sを右に90度回転した配列を生成
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                temp[j][k]=s[n-k-1][j];
            }
        }
        //sに上書き
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                s[j][k]=temp[j][k];
            }
        }
        //削減した位置も90度回転
        int temp2=leftS;
        leftS=downS;
        downS=rightS;
        rightS=upS;
        upS=temp2;
        
        //まずサイズが一緒かを確認、サイズが一緒じゃなければ検証の必要がないのでスキップ
        if(upS+downS!=upT+downT||leftS+rightS!=leftT+rightT)continue;
        //サイズが一緒だったので切り出した配列が同一かをチェック    
        int flag2=1;
        for(int j=0;j<n-upS-downS;j++){
            for(int k=0;k<n-leftS-rightS;k++){
                //1つでも違ったらフラグを0に変える
                if(s[j+upS][k+leftS]!=t[j+upT][k+leftT])flag2=0;
            }
        }
        //完全一致していた場合答えを発見したのでフラグを立ててループを抜ける
        if(flag2==1){
            flag=1;
            break;
        }
    }

    //出力
    if(flag==1)
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
    return 0;
}