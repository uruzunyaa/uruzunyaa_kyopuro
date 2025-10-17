#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // firstでソートされたpairのvectorを用意
    std::vector<std::pair<int, int>> vec = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};

    // 検索したいfirstの値
    int first_val = 6;

    // upper_boundを用いてfirst_valより大きい最初の要素を探索
    auto it = std::upper_bound(vec.begin(), vec.end(), std::make_pair(first_val, std::numeric_limits<int>::min()));

    if (it != vec.end()) {
        std::cout << "Found: (" << it->first << ", " << it->second << ")" << std::endl;
    } else {
        std::cout << "No element with first > " << first_val << std::endl;
    }

    return 0;
}
