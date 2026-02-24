#include <iostream>

int main() {

    //入力値を読み込み
    long w, h, x, y;
    std::cin >> w >> h >> x >> y;

    //実は綺麗に2等分は必ず可能なので、面積の半分を計算。
    // w,h がint型だと、w * hの時点でint型の範囲を超えるので注意。
    double area = (w * h) / 2.0;

    //長方形の中心である時のみ、複数個の2等分線が引けるので、中心であるかどうか判定し出力。
    if (x * 2 == w && y * 2 == h) {
        std::cout << area << " 1";
    } else {
        std::cout << area << " 0";
    }
}