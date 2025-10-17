using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
	static void Main(string[] args)
	{
		var s = Console.ReadLine();
		Dictionary<char, int> count = new Dictionary<char, int>();
		foreach (var c in s)
		{
			if (count.ContainsKey(c))
			{
				count[c]++;
			}
			else
			{
				count.Add(c, 1);
			}
		}

		int max = count.Max(x => x.Value);
		char freq = count.Where(v => v.Value == max).OrderBy(v => v.Key).First().Key;
		Console.WriteLine(freq);
	}
}