using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
	static void Main(string[] args)
	{
		var matCount = int.Parse(Console.ReadLine());
		var mats = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
		var mealA = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
		var mealB = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();

		int max = 0;
		int mealAMax = mats.Select((x, i) => mealA[i] != 0 ? x / mealA[i] : int.MaxValue).Min();
		for (int i = 0; i <= mealAMax; i++)
		{
			// 料理Aの人数分の材料を減らす
			var lefts = mats.Select((x, j) => x - mealA[j] * i);

			// あまった材料で料理Bを作る
			int mealBMax = lefts.Select((x, j) => mealB[j] != 0 ? x / mealB[j] : int.MaxValue).Min();

			if (max < i + mealBMax)
			{
				max = i + mealBMax;
			}
		}

		Console.WriteLine(max);
	}
}