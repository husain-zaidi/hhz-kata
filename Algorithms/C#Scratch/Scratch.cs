using System;
using System.Collections.Generic;
using System.Linq;

class Node {
    public int data;
    public Node left, right;
    public Node(int x) {
        data = x;
        left = null;
        right = null;
    }
}

class Scratch
{

    static List<int> subArraySum(int[] arr, int target)
    {
        int s = 0, e = 0;
        List<int> res = new List<int>();

        int curr = 0;
        for (int i = 0; i < arr.Length; i++)
        {
            curr += arr[i];

            if (curr >= target)
            {
                e = i;

                while (curr > target && s < e)
                {
                    curr -= arr[s];
                    ++s;
                }

                if (curr == target)
                {
                    res.Add(s + 1);
                    res.Add(e + 1);
                    return res;
                }
            }
        }
        res.Add(-1);
        return res;
    }

    static List<int> topKFrequent(int[] arr, int k)
    {
        Dictionary<int, int> itemFreq = new Dictionary<int, int>();

        foreach (int val in arr)
        {
            itemFreq[val] =  itemFreq.GetValueOrDefault(val, 0) + 1;
        }

        PriorityQueue<int, int> pq = new PriorityQueue<int, int>();

        foreach (var item in itemFreq)
        {
            pq.Enqueue(item.Key, item.Value);
            if (pq.Count > k)
            {
                pq.Dequeue();
            }
        }

        Stack<int> stack = new Stack<int>();
        while (pq.Count > 0)
        {
            stack.Push(pq.Dequeue());
        }

        List<int> result = new List<int>();
        while (stack.Count > 0)
        {
            result.Add(stack.Pop());
        }

        return result;
    }

    static void serializePreOrder(Node root, List<int> arr) {
        // Push -1 if root is null.
        if (root == null) {
            arr.Add(-1);
            return;
        }
        arr.Add(root.data);
        serializePreOrder(root.left, arr);  
        serializePreOrder(root.right, arr);
    }

     static Node deserializePreOrder(ref int i, List<int> arr) {
        
        // -1 meres null.
        if (arr[i] == -1) {
            i++;
            return null;
        }
        
        // Create the root node.
        Node root = new Node(arr[i]);
        i++;
        
        root.left = deserializePreOrder(ref i, arr);
        root.right = deserializePreOrder(ref i, arr);
        
        return root;
    }

    static void Main()
    {
        // Console.WriteLine("The quick brown fox jumps over the lazy dog.");
        // int[] arr = { 15, 2, 4, 8, 9, 5, 10, 23 };
        // int target = 23;
        // List<int> res = subArraySum(arr, target);

        // int[] arr = { 3, 1, 4, 4, 5, 1, 6, 1 };
        // List<int> res = topKFrequent(arr, 2);

        Node root = new Node(10);
        root.left = new Node(20);
        root.right = new Node(30);
        root.left.left = new Node(40);
        root.left.right = new Node(60);

        List<int> res = new List<int>();
        serializePreOrder(root, res);

        foreach (var e in res)
        {
            Console.Write(e + " ");
        }
    }
}