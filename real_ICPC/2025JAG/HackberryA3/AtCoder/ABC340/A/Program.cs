using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
	static void Main(string[] args)
	{
		int[] ABD = Console.ReadLine().Split().Select(int.Parse).ToArray();
		int A = ABD[0];
		int B = ABD[1];
		int D = ABD[2];

		for (int i = A; i <= B; i += D)
		{
			Console.Write(i);
			Console.Write(" ");
		}
		Console.WriteLine();
	}
}