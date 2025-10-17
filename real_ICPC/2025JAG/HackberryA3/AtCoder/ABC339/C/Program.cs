using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
	static void Main(string[] args)
	{
		int N = int.Parse(Console.ReadLine());
		long[] A = Console.ReadLine().Split(' ').Select(long.Parse).ToArray();

		long min = 0;
		long sum = 0;
		for (int i = 0; i < N; i++)
		{
			sum += A[i];
			min = Math.Min(min, sum);
		}

		Console.WriteLine(Math.Abs(min) + sum);
	}
}