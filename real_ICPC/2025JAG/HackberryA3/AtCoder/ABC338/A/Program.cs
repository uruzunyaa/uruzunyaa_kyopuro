using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
	static void Main(string[] args)
	{
		var s = Console.ReadLine();

		Console.WriteLine(char.IsUpper(s[0]) && s[1..].All(char.IsLower) ? "Yes" : "No");
	}
}