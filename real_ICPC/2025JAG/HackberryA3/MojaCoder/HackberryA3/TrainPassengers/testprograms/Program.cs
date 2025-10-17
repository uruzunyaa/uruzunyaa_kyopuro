using System;
using System.Linq;

public static class Program {
	public static void Main() {
		int[] nm = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
		int n = nm[0];
		int m = nm[1];

		int[] a = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();

		long ans = 0;
		int cur = 0;
		for(int i = 0; i < n; i++) {
			if(a[i] < 0){
				cur += a[i];
				continue;
			}

			if(cur + a[i] <= m) {
				ans += a[i];
				cur += a[i];
			}
			else {
				ans += m - cur;
				cur = m;
			}
		}

		Console.WriteLine(ans);
	}
}