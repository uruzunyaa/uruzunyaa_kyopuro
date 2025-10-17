using System;
using System.Collections.Generic;

public class AVLTree<TKey, TValue> where TKey : IComparable<TKey>
{
	public AVLNode<TKey, TValue> Root { get; private set; }

	public void Add(TKey key, TValue value)
	{
		var newNode = new AVLNode<TKey, TValue>(key, value);
		if (Root == null)
			Root = newNode;
		else
		{
			InsertNode(Root, newNode);
			BalanceTree(newNode);
		}
	}
	private void InsertNode(AVLNode<TKey, TValue> root, AVLNode<TKey, TValue> newNode)
	{
		int compareResult = root.Key1.CompareTo(newNode.Key1);
		if (compareResult > 0)
		{
			if (root.Left == null)
			{
				root.Left = newNode;
				newNode.Parent = root;
				newNode.IsLeft = true;
			}
			else
			{
				InsertNode(root.Left, newNode);
			}
		}
		else if (compareResult < 0)
		{
			if (root.Right == null)
			{
				root.Right = newNode;
				newNode.Parent = root;
				newNode.isRight = true;
			}
			else
			{
				InsertNode(root.Right, newNode);
			}
		}
		else
		{
			throw new ArgumentException("An element with the same key already exists in the tree.");
		}
	}

	public AVLNode<TKey, TValue> Search(TKey key) => SearchNode(Root, key);
	private AVLNode<TKey, TValue> SearchNode(AVLNode<TKey, TValue> node, TKey key)
	{
		if (node == null)
			return null;

		int compareResult = key.CompareTo(node.Key1);
		if (compareResult == 0)
			return node;
		else if (compareResult < 0)
			return SearchNode(node.Left, key);
		else
			return SearchNode(node.Right, key);
	}



	private void BalanceTree(AVLNode<TKey, TValue> node)
	{
		UpdateNodeHeight(node);

		int balanceFactor = GetBalanceFactor(node);

		if (balanceFactor > 1)
		{
			if (GetBalanceFactor(node.Left) < 0)
			{
				RotateLeft(node.Left);
			}

			RotateRight(node);
		}
		else if (balanceFactor < -1)
		{
			if (GetBalanceFactor(node.Right) > 0)
			{
				RotateRight(node.Right);
			}

			RotateLeft(node);
		}

		if (node.Parent != null)
		{
			BalanceTree(node.Parent);
		}
	}

	private void UpdateNodeHeight(AVLNode<TKey, TValue> node)
	{
		int leftHeight = GetNodeHeight(node.Left);
		int rightHeight = GetNodeHeight(node.Right);
		node.Height = Math.Max(leftHeight, rightHeight) + 1;
	}

	private int GetNodeHeight(AVLNode<TKey, TValue> node)
	{
		return node?.Height ?? 0;
	}

	private int GetBalanceFactor(AVLNode<TKey, TValue> node)
	{
		int leftHeight = GetNodeHeight(node.Left);
		int rightHeight = GetNodeHeight(node.Right);
		return leftHeight - rightHeight;
	}

	private void RotateRight(AVLNode<TKey, TValue> node)
	{
		AVLNode<TKey, TValue> newParent = node.Left;
		ReplaceNode(node, newParent);

		node.Left = newParent.Right;
		if (newParent.Right != null)
		{
			newParent.Right.Parent = node;
			newParent.Right.IsLeft = true;
			newParent.Right.isRight = false;
		}

		newParent.Right = node;
		node.Parent = newParent;
		node.IsLeft = false;
		node.isRight = true;

		UpdateNodeHeight(node);
		UpdateNodeHeight(newParent);
	}

	private void RotateLeft(AVLNode<TKey, TValue> node)
	{
		AVLNode<TKey, TValue> newParent = node.Right;
		ReplaceNode(node, newParent);

		node.Right = newParent.Left;
		if (newParent.Left != null)
		{
			newParent.Left.Parent = node;
			newParent.Left.IsLeft = false;
			newParent.Left.isRight = true;
		}

		newParent.Left = node;
		node.Parent = newParent;
		node.IsLeft = true;
		node.isRight = false;

		UpdateNodeHeight(node);
		UpdateNodeHeight(newParent);
	}

	private void ReplaceNode(AVLNode<TKey, TValue> oldNode, AVLNode<TKey, TValue> newNode)
	{
		if (oldNode.Parent == null)
		{
			Root = newNode;
		}
		else
		{
			if (oldNode.IsLeft)
			{
				oldNode.Parent.Left = newNode;
			}
			else
			{
				oldNode.Parent.Right = newNode;
			}
		}

		if (newNode != null)
		{
			newNode.Parent = oldNode.Parent;
			newNode.IsLeft = oldNode.IsLeft;
			newNode.isRight = oldNode.isRight;
		}
	}
}
public class AVLNode<TKey, TValue>
{
	public TKey Key1 { get; }
	public TValue Value { get; }
	public AVLNode<TKey, TValue> Parent { get; internal set; }
	public AVLNode<TKey, TValue> Left { get; internal set; }
	public AVLNode<TKey, TValue> Right { get; internal set; }
	public bool IsLeft { get; internal set; }
	public bool isRight { get; internal set; }
	public int Height { get; internal set; }

	public AVLNode(TKey key, TValue value)
	{
		Key1 = key;
		Value = value;
		Height = 1;
	}

	public AVLNode<TKey, TValue> Next()
	{
		if (Right != null)
			return Right.GetMin();
		var node = this;
		while (node.isRight)
			node = node.Parent;
		return node.Parent;
	}

	public AVLNode<TKey, TValue> GetMin(bool left = true, bool right = true)
	{
		if (left && Left == null)
			return this;
		if (left)
			return Left.GetMin();

		if (right && Right == null)
			return this;
		if (right)
			return Right.GetMin();

		if (Parent != null)
			return Parent.GetMin(false, IsLeft);

		return null;
	}
}

class Program
{
	static void Main()
	{
		var tree = new AVLTree<int, int>();
		tree.Add(3, 3);
		tree.Add(5, 5);
		tree.Add(2, 2);
		tree.Add(1, 1);
		tree.Add(4, 4);
		tree.Add(6, 6);

		AVLNode<int, int> current = tree.Root.GetMin();
		while (current != null)
		{
			Console.WriteLine(current.Value);
			current = current.Next();
		}
	}
}