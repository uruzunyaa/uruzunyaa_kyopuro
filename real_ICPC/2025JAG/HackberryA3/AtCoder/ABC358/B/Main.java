import java.util.*;
import static java.lang.System.out;

public class Main {
	public static void main(String[] args) {
		var scan = new Scanner(System.in);
		int n = scan.nextInt();
		int a = scan.nextInt();

		int passed = 0;
		for(int i = 0; i < n; i++) {
			int t = scan.nextInt();

			if (t < passed) passed += a;
			else passed = t + a;

			out.println(passed);
		}
	}
}
