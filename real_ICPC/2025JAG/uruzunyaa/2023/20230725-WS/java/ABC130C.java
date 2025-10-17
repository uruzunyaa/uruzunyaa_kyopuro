import java.util.Scanner;

public class ABC130C {
    public static void main(String[] args) {
        // 入力値を読み込み
        Scanner scanner = new Scanner(System.in);
        long w = scanner.nextLong();
        long h = scanner.nextLong();
        long x = scanner.nextLong();
        long y = scanner.nextLong();
        scanner.close();

        // 実は綺麗に2等分は必ず可能なので、面積の半分を計算。
        // w, h が int 型だと、w * h の時点で int 型の範囲を超えるので注意。
        double area = (double) (w * h) / 2.0;

        // 長方形の中心である時のみ、複数個の2等分線が引けるので、中心であるかどうか判定し出力。
        if (x * 2 == w && y * 2 == h) {
            System.out.println(area + " 1");
        } else {
            System.out.println(area + " 0");
        }
    }
}
