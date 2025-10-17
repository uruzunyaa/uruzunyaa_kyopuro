#include <bits/stdc++.h>
// #include <atcoder/all>

#define all(v) (v).begin(), (v).end()
#define ssum(v) accumulate(all(v), 0)
#define mmax(v) *max_element(all(v))
#define mmin(v) *min_element(all(v))
#define imax(v) max_element(all(v)) - (v).begin() + 1
#define imin(v) min_element(all(v)) - (v).begin() + 1
#define st(v) sort((v).begin(), (v).end())
#define rst(v) sort((v).rbegin(), (v).rend())
#define rmv(v, l) v.erase(remove(all(v),l),v.end())
#define pb push_back
#define pob pop_back
#define endl '\n'
#define rrep(i, n) for (int i = 1; i <= n; i++)
#define repp(i, n) for (int i = n - 1; i >= 0; i--) 
#define yn(ok) cout<<(ok?"Yes":"No")<<endl;
#define YN(ok) cout<<(ok?"YES":"NO")<<endl;
#define OVERLOAD_REP(_1, _2, _3, name, ...) name
#define REP1(i, n) for (auto i = std::decay_t<decltype(n)>{}; (i) != (n); ++(i))
#define REP2(i, l, r) for (auto i = (l); (i) != (r); ++(i))
#define rep(...) OVERLOAD_REP(__VA_ARGS__, REP2, REP1)(__VA_ARGS__)

using namespace std;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vll = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vii = vector<vector<int>>;
using vb = vector<bool>;
using pii = pair<int,int>;

const long long mint=998244353;
const long long mod=1e9+7;
const long long inf = 1LL << 60;

template <class T>inline bool chmax(T &a, T b){if (a < b){a = b;return true;}return false;}
template <class T>inline bool chmin(T &a, T b){if (a > b){a = b;return true;}return false;}

string dtp(ll a, ll l)
{
    std::string result;
    for (ll i = l - 1; i >= 0; i--)
    {
        ll w = (1 << i);
        result += std::to_string((a / w) % 2);
    }
    return result;
}

string toB(int N) {
    if (N == 0) return "0";
    
    std::string binary;
    while (N > 0) {
        binary = std::to_string(N % 2) + binary; // 余りを先頭に追加
        N /= 2; // Nを2で割る
    }
    return binary;
}

int countOccurrences(const string& str, const string& target) {
    int count = 0;

    for (size_t i=0;i<=str.length()-target.length();++i) {
        if (str.substr(i,target.length())==target) {
            ++count;
        }
    }
    return count;
}

void printVector(const vector<string>& vec) {
    for (string value : vec) {
        cout << value << " ";
    }
    cout << endl;
}

//全列挙した文字列の一部にtargetが含まれているかどうかの判断
bool containsPermutation(const string& s, const string& target) {
    vector<char> ss(s.begin(), s.end()); // 文字列をベクトルに変換
    sort(ss.begin(), ss.end()); // next_permutationのためにソート

    do {
        string currentPermutation(ss.begin(), ss.end());
        // 現在の順列の中にターゲットが含まれているかチェック
        if (currentPermutation.find(target) != string::npos) {
            return true; // ターゲットが見つかった
        }
    } while (next_permutation(ss.begin(), ss.end()));
    
    return false; // 一致する順列が見つからなかった
}

bool IsPrime(ll num)
{
	if (num < 2) return false;
	else if (num == 2) return true;
	else if (num % 2 == 0) return false; // 偶数はあらかじめ除く

	double sqrtNum = sqrt(num);
	for (int i = 3; i <= sqrtNum; i += 2)
	{
		if (num % i == 0)
		{
			// 素数ではない
			return false;
		}
	}

	// 素数である
	return true;
}

#include<cmath>

// 素数判定プログラム
bool isPrimeNumber(int n){
    bool p = true;
    for(int i=2;i<=sqrt(n);i++){
        // nがiで割り切れる => 因数を持つ => 素数でない(合成数) 
        if( n % i == 0 ){
            p = false;
            return p;
        }
    }
    return p;
}


// バブルソートで交換回数をカウント
int bubbleSortCount(vector<int>& arr) {
    int n = arr.size();
    int count = 0;  // 交換回数のカウント
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 要素の交換
                swap(arr[j], arr[j + 1]);
                count++;  // 交換回数を増加
            }
        }
    }
    return count;
}

bool isGeometricSequence(vector<int>& arr) {
    int n = arr.size();
    
    // 要素数が2以下なら、等比数列とみなす
    if (n <= 2) return true;

    // 配列を昇順にソート
    sort(arr.begin(), arr.end());

    // 比が同じかどうかをチェック
    double ratio = (double)arr[1] / arr[0]; // 最初の比を計算

    for (int i = 2; i < n; ++i) {
        // 隣接する項の比を計算
        if ((double)arr[i] / arr[i-1] != ratio) {
            return false;  // 比が異なる場合は等比数列でない
        }
    }
    
    return true;  // 全ての比が同じなら等比数列
}

int sum(int n){
    if(n==0){
        return 0;
    }
    int s=sum(n-1);
return s+n;
}

int countConsecutiveCharactersCustom(const string& str) {
    int maxCount = 0;
    int currentCount = 0;

    // 「K」「B」「Y」の連続性を判定
    for (char ch : str) {
        if (ch == 'K' || ch == 'B' || ch == 'Y') {
            currentCount++;
            maxCount = max(maxCount, currentCount);
        } else {
            currentCount = 0; // 他の文字が出現したらリセット
        }
    }

    return maxCount;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vi a(8);
    vi b(8);
    int cnt=0;
    rrep(i,7)cin>>a[i];
    st(a);
    bool b2=true;
    rrep(i,7){
        if(a[i]!=a[i+1])b[i]=count(all(a),a[i]);
        if(b[i]==3)cnt+=3;
        else if(b[i]==2&&b2)cnt+=2,b2=false;
        }
    yn(cnt>=5);
    return 0;
}