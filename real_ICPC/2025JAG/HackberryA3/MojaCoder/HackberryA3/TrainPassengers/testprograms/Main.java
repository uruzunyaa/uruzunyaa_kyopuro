import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int N = scan.nextInt();         // 駅の数
		int M = scan.nextInt();         // 定員

		int current = 0; 			    // 現在の乗客数
		long sum = 0; 				    // 乗客数の合計

		for (int i = 0; i < N; i++)     // 駅の数だけ繰り返す
		{
			int A = scan.nextInt();     // 駅iでの乗降人数を取得

			if (A < 0) {                // 降車の場合 (A_iが負の値)
				current += A;           // 現在の乗客数から、降りた人数を引く
			}
			else {                      // 乗車の場合 (A_iが正の値)
				if (current + A <= M) {	// 定員を超えない場合 (現在 + 乗りたい人数 <= 定員)
					sum += A;           // 合計人数に、乗った人数を加える
					current += A;       // 現在の乗客数に、乗った人数を加える
				}
				else {   				// 定員を超える場合 (現在 + 乗りたい人数 > 定員)
					sum += M - current; // 合計人数に、定員と現在の人数の差を加える
					current = M; 		// 現在の乗客数を、定員と同じにする
				}
			}
		}

		System.out.println(sum);        // 合計人数を出力

		scan.close();
	}
}



























