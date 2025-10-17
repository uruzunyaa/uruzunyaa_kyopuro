# 解説

各駅でどのようなパターンが起こり得るかを考えると、以下の3パターンになります。

- 乗客が降りるパターン
- 乗客が乗るパターン
  - 定員を超えないパターン
  - 定員を超えるパターン

それぞれのパターンで何を行うかを考えると、以下のようになります。

- 乗客が降りるパターン
  - 現在の乗客数から降りた人数を引く
  - 合計乗客数は変わらない

- 乗客が乗り、定員を超えないパターン
  - 現在の乗客数に乗った人数を足す
  - 合計乗客数にも乗った人数を足す

- 乗客が乗り、定員を超えるパターン
  - 現在の乗客数は定員になる
  - 合計乗客数は定員と現在の乗客数の差になる

これらを実装することで、問題を解くことができます。

## 実装例

- C++

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;

    ll sum = 0;
    int current = 0;

    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;

        if(a < 0) {
            current += a;
            continue;
        }

        if(current + a <= m) {
            sum += a;
            current += a;
        } else {
            sum += m - current;
            current = m;
        }
    }
}
```
