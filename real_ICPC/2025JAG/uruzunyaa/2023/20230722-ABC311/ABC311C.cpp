#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a;
    int num;
    for (int i = 0;i < n;i++) { // スペース区切りで値を読み込む
        std::cin >> num;
        a.push_back(num); // 読み込んだ値を配列に追加
    }

    int gps = 1;
    std::vector<int> kiroku;
    for (int i = 0;i < n;i++) {
        gps = a[gps - 1];
        kiroku.push_back(gps);
        
    }

    int start = 0;
    for (int i = 0;i < n - 2;i++) {
        if (kiroku[n - 1] == kiroku[i]) start = i + 1;
    }

    std::cout << n - start << std::endl;
    for (int i = start;i < n;i++) {
        std::cout << kiroku[i] << " ";
    }

    return 0;
}
