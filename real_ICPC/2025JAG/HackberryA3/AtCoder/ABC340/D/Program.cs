class Program
{
	static void Main(string[] args)
	{
		long N = long.Parse(Console.ReadLine());
		var graph = new Graph(N);
		for (var i = 0; i < N - 1; i++)
		{
			var inputs = Console.ReadLine().Split(' ').Select(long.Parse).ToArray();
			var cost1 = inputs[0];
			var cost2 = inputs[1];
			var v = inputs[2] - 1;

			graph.AddEdge(i, i + 1, cost1);
			graph.AddEdge(i, v, cost2);
		}

		var priorityQueue = new PriorityQueue<long, long>();
		priorityQueue.Enqueue(0, 0);

		var costs = new long[graph.NodeCount];
		var visited = new bool[graph.NodeCount];
		for (var i = 0; i < graph.NodeCount; i++)
		{
			costs[i] = long.MaxValue;
			visited[i] = false;
		}

		while (priorityQueue.TryDequeue(out long nodeIndex, out long currentCost))
		{
			if (visited[nodeIndex])
				continue;

			costs[nodeIndex] = currentCost;
			visited[nodeIndex] = true;

			foreach (var edge in graph.GetEdgesFrom(nodeIndex))
			{
				priorityQueue.Enqueue(edge.To, currentCost + edge.Cost);
			}
		}

		Console.WriteLine(costs[^1]);
	}
}

class Edge
{
	public readonly long From;
	public readonly long To;
	public readonly long Cost;

	public Edge(long from, long to, long cost)
	{
		From = from;
		To = to;
		Cost = cost;
	}
}

class Graph
{
	public readonly long NodeCount;
	readonly List<Edge>[] Edges;

	public Graph(long nodeCount)
	{
		NodeCount = nodeCount;
		Edges = new List<Edge>[NodeCount];
		for (var i = 0; i < NodeCount; i++)
		{
			Edges[i] = new List<Edge>();
		}
	}

	public void AddEdge(long from, long to, long cost)
	{
		Edges[from].Add(new Edge(from, to, cost));
	}

	public List<Edge> GetEdgesFrom(long from) => Edges[from];
}