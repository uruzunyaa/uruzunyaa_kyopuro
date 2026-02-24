#include<iostream>//入出力
#include<algorithm>//アルゴリズム
#include<vector>//配列
#include<string>//文字列
#include<map>//連想配列
#include<deque>//スタックとキュー
#include<iomanip>//出力形式調整
#include<tuple>//pairの複数型
#include<cmath>//数学。ルートとか
#include<cctype>//大文字小文字のチェックなど
#include<fstream>//ファイル入出力
#include<random>//乱数
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000
#define mod 998244353
//乱数、ファイル入出力
	random_device rnd;// 非決定的な乱数生成器
	mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
	ifstream fin("./DefaultFile");
	ofstream fout("./DefaultFile");//出力する場合の出力先を指定

ll n;
string r,c;
//メイン
bool dfs(ll left,vector<string>& a){
    if(left==-1){
        rep(i,n)fout<<a[i]<<endl;
        fout<<endl;
        rep(i,n){
            ll p=0;
            while(a[p][i]=='.')p++;
            if(a[p][i]!=c[i]||n==p)return false;
            vl check(3,0);
            rep(j,n)if(a[j][i]!='.')check[a[j][i]-'A']++;
            rep(j,3)if(check[j]!=1)return false;
        }
        return true;
    }
    string b(n,'.');
    rep(i,3)b[i]=i+'A';
    sort(b.begin(),b.end());
    do{
        ll p=0;
        while(b[p]=='.')p++;
        if(b[p]!=r[left])continue;
        a[left]=b;
        if(dfs(left-1,a))return true;
        a[left]=string(n,'.');
    }while(next_permutation(b.begin(),b.end()));
    return false;
}

int main(){
    cin>>n>>r>>c;
	vector<string> a(n,string(n,'.'));
    
    if(dfs(n-1,a)){
        cout<<"Yes"<<endl;
        rep(i,n)cout<<a[i]<<endl;
    }
    else cout<<"No"<<endl;
    return 0;
}
