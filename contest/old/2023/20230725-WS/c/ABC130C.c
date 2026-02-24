#include <stdio.h>

int main() {
    // 入力値を読み込み
    long w, h, x, y;
    scanf("%ld %ld %ld %ld", &w, &h, &x, &y);

    // 実は綺麗に2等分は必ず可能なので、面積の半分を計算。
    // w,h が int 型だと、w * h の時点で int 型の範囲を超えるので注意。
    double area = (w * h) / 2.0;

    // 長方形の中心である時のみ、複数個の2等分線が引けるので、中心であるかどうか判定し出力。
    if (x * 2 == w && y * 2 == h) {
        printf("%lf 1", area);
    } else {
        printf("%lf 0", area);
    }

    return 0;
}
