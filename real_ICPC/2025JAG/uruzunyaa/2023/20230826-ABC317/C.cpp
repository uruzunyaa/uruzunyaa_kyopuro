#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
//loop(ループ変数、初期値、ループ回数)
#define loop(i,m,n) for(int i=m;i<n+m;i++)
#define rep(i,n) for(int i=0;i<n;i++)
int main(){
    int n,m;
    cin>>n>>m;
    vector<int> a(m),b(m),c(m);
    loop(i,0,m){
        cin>>a[i]>>b[i]>>c[i];
    }

    //並び順で計算時間を取られないためにソート
    loop (i,0,m-1) {
        loop (j,0,m-i-1) {
            // a[i] + b[i] の値を比較して、必要に応じて要素を交換
            if (a[j] + b[j] > a[j + 1] + b[j + 1]) {
                swap(a[j], a[j + 1]);
                swap(b[j], b[j + 1]);
                swap(c[j], c[j + 1]);
            }
        }
    }

    
    int len=0;
    int maxLen=0;
    int lastDel=0;

    deque<int> dfs;
    deque <int> sumLen;


    //外側のループがスタート地点の場所
    loop(i,1,n){
        //空のデックにスタート地点を初期値として入れる
        dfs.push_back(i);
        //距離0を初期値として代入
        sumLen.push_back(0);
        //初期値を変えたのでリセット
        lastDel=0;
        //dfsが空になるまで(全ての探索を終えるまで)繰り返す
        while(!dfs.empty()){
            //現在入っている辿り方から、最も小さい要素に飛び続けて、もう行ける場所がなくなるまで行く
            while(1){
                //次の場所の候補の中で最も小さいものを探す
                int min=n+1;
                loop(j,0,m){
                    //繋がってる要素を発見した時
                    if(a[j]==dfs.back()||b[j]==dfs.back()){
                        //次の場所の候補を取得
                        int target=(a[j]==dfs.back())?b[j]:a[j];
                        //現状の最有力候補よりも値が小さいなら値の更新、距離の更新
                        if(min>target&&lastDel<target){
                            //次の場所の候補が既に通った場所か検証する
                            if(find(dfs.begin(), dfs.end(), target)==dfs.end()){
                                len=c[j];
                                min=target;
                                //先にソートしてあるので、最小を見つけた瞬間にbreak。
                                break;
                            }
                        }
                    }
                }
                //同じものを選ぶのの防止が終わったのでリセット
                lastDel=0;
                //もし値を追加出来る場所があるなら値を追加、出来ないなら値の追加をやめる。
                if(min!=n+1){
                    //値を追加する時に、合わせて距離を計算
                    dfs.push_back(min);
                    sumLen.push_back(sumLen.back()+len);
                }else{
                    break;
                }
            }
            //最大値なら更新
            if(sumLen.back()>maxLen)maxLen=sumLen.back();

            //値を保管してから削除
            lastDel=dfs.back();
            dfs.pop_back();
            sumLen.pop_back();
        }
    }

    cout<<maxLen;

    return 0;
}