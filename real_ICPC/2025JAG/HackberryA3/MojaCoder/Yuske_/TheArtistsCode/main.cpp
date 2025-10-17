#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  string s; cin >> s;

  string ans = "";
  for(int i = 0; i < n; i++) {
    int a; cin >> a;
    ans += s[a];
  }
  
  cout << ans << endl;
  return 0;
}
