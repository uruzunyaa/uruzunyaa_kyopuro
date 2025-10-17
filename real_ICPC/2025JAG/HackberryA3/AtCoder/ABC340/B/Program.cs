using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
	static void Main(string[] args)
	{
		int Q = int.Parse(Console.ReadLine());
		List<int> A = new List<int>();

		for (int i = 0; i < Q; i++)
		{
			string[] input = Console.ReadLine().Split(' ');
			int q = int.Parse(input[0]);
			int x = int.Parse(input[1]);

			if (q == 1)
			{
				A.Add(x);
			}
			else if (q == 2)
			{
				Console.WriteLine(A[^x]);
			}
		}
	}
}