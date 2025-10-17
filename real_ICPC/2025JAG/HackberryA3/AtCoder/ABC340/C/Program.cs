using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
	static void Main(string[] args)
	{
		long N = long.Parse(Console.ReadLine());

		long price = GetPrice(N);

		Console.WriteLine(price);
	}

	static Dictionary<long, long> memo = new Dictionary<long, long>();
	static long GetPrice(long N)
	{
		if (N == 1)
			return 0;
		if (N == 2)
			return 2;

		if (memo.ContainsKey(N))
			return memo[N];

		long price = N + GetPrice(N / 2) + GetPrice((long)Math.Ceiling((decimal)N / 2));
		memo[N] = price;
		return price;
	}
}