#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <map>
using namespace std;

//loop(ループ変数、初期値、最終ループ値)
#define loop(i,m,n) for(int i=m;i<=n;i++)

//rep(ループ変数、ループ数)
#define rep(i,n) for(int i=0;i<n;i++)

int main(){
    map<string, int> rated;

    string s;
    cin>>s;

    // 要素を追加
    rated["tourist"] = 3858;
    rated["ksun48"] = 3679;
    rated["Benq"] = 3658;
    rated["Um_nik"] = 3648;
    rated["apiad"] = 3638;
    rated["Stonefeang"] = 3630;
    rated["ecnerwala"] = 3613;
    rated["mnbvmar"] = 3555;
    rated["newbiedmy"] = 3516;
    rated["semiexp"] = 3481;

    cout<<rated[s];
    return 0;
}