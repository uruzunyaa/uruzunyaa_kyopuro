#include <bits/stdc++.h>
using namespace std;

static int idx_of_token(const string &t){
    if(t.size()!=1) return -1;
    char c=t[0];
    if('0'<=c && c<='9') return c-'0';
    if(c=='+') return 10;
    if(c=='-') return 11;
    if(c=='*') return 12;
    return -1;
}

static int sum_digits(const array<int,13>& cnt){
    int s=0;
    for(int i=0;i<10;i++) s+=cnt[i];
    return s;
}
static int sum_all(const array<int,13>& cnt){
    int s=0;
    for(int i=0;i<13;i++) s+=cnt[i];
    return s;
}

static long long parse_num_ll(const string &s){
    long long x=0;
    for(char c: s){
        x = x*10 + (c - '0'); // overflowは気にしない
    }
    return x;
}

// s は '=' を含まない片側の式。評価できれば true。
static bool eval_expr(const string &s, long long &out){
    vector<long long> nums;
    vector<char> ops;
    string cur;

    auto flush_num = [&]()->bool{
        if(cur.empty()) return false;
        if(cur.size() > 1 && cur[0]=='0') return false; // 先頭0禁止
        nums.push_back(parse_num_ll(cur));
        cur.clear();
        return true;
    };

    for(char c: s){
        if('0'<=c && c<='9'){
            cur.push_back(c);
        }else if(c=='+' || c=='-' || c=='*'){
            if(!flush_num()) return false;
            ops.push_back(c);
        }else return false;
    }
    if(!flush_num()) return false;
    if(nums.size() != ops.size()+1) return false;

    // 0単体との掛け算を禁止（0* や *0）
    for(size_t i=0;i<ops.size();i++){
        if(ops[i]=='*' && (nums[i]==0 || nums[i+1]==0)) return false;
    }

    // * を先に計算（overflowは無視）
    vector<long long> terms;
    vector<char> addops; // '+' or '-'
    long long term = nums[0];
    for(size_t i=0;i<ops.size();i++){
        char op = ops[i];
        if(op=='*'){
            term = term * nums[i+1];
        }else{
            terms.push_back(term);
            addops.push_back(op);
            term = nums[i+1];
        }
    }
    terms.push_back(term);

    long long val = terms[0];
    for(size_t i=1;i<terms.size();i++){
        if(addops[i-1]=='+') val = val + terms[i];
        else val = val - terms[i];
    }
    out = val;
    return true;
}

static unordered_set<string> answers;

// needDigit: 次は数字必須か？
// curLen/curIsZero: 「いま作ってる数」の状態（0単体なら curIsZero=true）
static void dfs(string &eq, array<int,13> &cnt,
                bool usedEqual, int side, bool needDigit,
                int curLen, bool curIsZero)
{
    if(needDigit && sum_digits(cnt)==0) return;

    if(sum_all(cnt)==0){
        if(usedEqual && side==1 && !needDigit){
            size_t p = eq.find('=');
            if(p==string::npos) return;
            string L = eq.substr(0,p);
            string R = eq.substr(p+1);
            long long lv, rv;
            if(eval_expr(L, lv) && eval_expr(R, rv) && lv==rv){
                answers.insert(eq);
            }
        }
        return;
    }

    if(!usedEqual && sum_digits(cnt)==0) return;

    // 1) 数字を置く
    for(int d=0; d<=9; d++){
        if(cnt[d]==0) continue;

        // *0 を禁止（右オペランドが 0単体 になる形）
        if(needDigit && !eq.empty() && eq.back()=='*' && d==0) continue;

        // 先頭0禁止（すでに0単体を作ってるなら桁追加不可）
        if(!needDigit && curIsZero) continue;

        cnt[d]--;
        eq.push_back(char('0'+d));

        bool nNeedDigit = false;
        int nCurLen = needDigit ? 1 : (curLen+1);
        bool nCurIsZero = (needDigit && d==0); // 数の開始が0なら「0単体」状態

        dfs(eq, cnt, usedEqual, side, nNeedDigit, nCurLen, nCurIsZero);

        eq.pop_back();
        cnt[d]++;
    }

    // 2) 演算子を置く（直前が数字のときだけ）
    if(!needDigit){
        const char ops[3] = {'+','-','*'};
        const int  idx[3] = {10, 11, 12};
        for(int i=0;i<3;i++){
            if(cnt[idx[i]]==0) continue;
            char op = ops[i];

            // 0* を禁止（左オペランドが0単体になる形）
            if(op=='*' && curIsZero) continue;

            cnt[idx[i]]--;
            eq.push_back(op);

            dfs(eq, cnt, usedEqual, side, true, 0, false);

            eq.pop_back();
            cnt[idx[i]]++;
        }
    }

    // 3) '=' を置く（左辺で、直前が数字、まだ未使用）
    if(side==0 && !usedEqual && !needDigit){
        // どれか1枚を裏返して '=' にする：その1枚を消費
        for(int k=0;k<13;k++){
            if(cnt[k]==0) continue;

            int digitsAfter = sum_digits(cnt) - (k<10 ? 1 : 0);
            int totalAfter  = sum_all(cnt) - 1;
            if(totalAfter <= 0) continue;   // 右辺が空
            if(digitsAfter <= 0) continue;  // 右辺に数字が無い

            cnt[k]--;
            eq.push_back('=');

            dfs(eq, cnt, true, 1, true, 0, false);

            eq.pop_back();
            cnt[k]++;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    array<int,13> cnt{};
    for(int i=0;i<N;i++){
        string a; cin >> a;
        int id = idx_of_token(a);
        if(id>=0) cnt[id]++;
    }

    string eq;
    dfs(eq, cnt, false, 0, true, 0, false);

    for(const auto &s: answers){
        cout << s << "\n";
    }
    return 0;
}
