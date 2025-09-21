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
    // subarray sum with target sum
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
    
    // Maximum Subarray - Kadane's Algorithm with -ve numbers
    public int MaxSubArray(int[] nums)
    {
        int MaxSum = nums[0];
        int MaxSoFar = nums[0];
        for (int i = 1; i < nums.Length; i++)
        {
            if (MaxSoFar < 0)
                MaxSoFar = nums[i];
            else
                MaxSoFar += nums[i];

            MaxSum = Math.Max(MaxSoFar, MaxSum);
        }
        return MaxSum;
    }

    // Top K Frequent Elements - Min Heap
    static List<int> topKFrequent(int[] arr, int k)
    {
        Dictionary<int, int> itemFreq = new Dictionary<int, int>();

        foreach (int val in arr)
        {
            itemFreq[val] = itemFreq.GetValueOrDefault(val, 0) + 1;
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

    static bool search2dWord(char[][] grid, int row, int col, string word)
    {
        int m = grid.Length;
        int n = grid[0].Length;

        // only start searching form the first matching word
        if (grid[row][col] != word[0])
            return false;

        int len = word.Length;

        int[] x = [-1, -1, -1, 0, 0, 1, 1, 1];
        int[] y = [-1, 0, 1, -1, 1, -1, 0, 1];

        for (int dir = 0; dir < 8; dir++)
        {
            int k, currX = row + x[dir], currY = col + y[dir];

            for (k = 1; k < len; k++)
            {
                if (currX >= m || currX < 0 || currY >= n || currY < 0)
                    break;

                if (grid[currX][currY] != word[k])
                    break;

                currX += x[dir];
                currY += y[dir];
            }

            if (k == len)
                return true;
        }

        return false;
    }

    static int CountWays(int n, int[] memo)
    {
        if (n == 0 || n == 1)
            return 1;

        if (memo[n] != -1)
            return memo[n];

        return memo[n] = CountWays(n - 1, memo) + CountWays(n - 2, memo);
    }

    // simplify unix path - stack
    static string SimplifyPath(string path)
    {
        string[] parts = path.Split('/');
        Stack<string> simplifiedPath = new Stack<string>();

        foreach (string section in parts)
        {
            if (section.StartsWith("/") || section == "." || string.IsNullOrEmpty(section))
            {
                continue;
            }
            else if (section == "..")
            {
                if (simplifiedPath.Count > 0)
                    simplifiedPath.Pop();
            }
            else
            {
                simplifiedPath.Push(section);
            }
        }

        string output = "";

        if (simplifiedPath.Count > 0)
        {
            foreach (string s in simplifiedPath.Reverse())
            {
                output += "/" + s;
            }
        }
        else
        {
            output = "/";
        }
        return output;
    }

    public int diameter = 0;

    int LengthTillLeaf(Node node)
    {
        if (node == null)
        {
            return 0;
        }

        int lenLeft = LengthTillLeaf(node.left);
        int lenRight = LengthTillLeaf(node.right);
        diameter = Math.Max(diameter, lenLeft + lenRight);
        return lenLeft > lenRight ? lenLeft + 1 : lenRight + 1;
    }

    public int DiameterOfBinaryTree(Node root) {
        LengthTillLeaf(root);
        return diameter;
    }
    
    // shortest path where k obstacles can be removed - BFS with state - 1 is obstacle 0 is empty
    static int ShortestPath(int[][] grid, int k)
    {
        int m = grid.Length; // Rows
        int n = grid[0].Length; // Columns

        // If the starting or ending point is an obstacle, and k is 0, it's impossible.
        if (grid[0][0] == 1 && k == 0) return -1;
        if (grid[m - 1][n - 1] == 1 && k == 0 && (m > 1 || n > 1)) return -1;


        // If we can eliminate all obstacles, the shortest path is Manhattan distance.
        // This is a significant optimization for large k.
        if (k >= m + n - 2)
        {
            return m + n - 2;
        }

        // State for BFS: (row, col, remaining_k)
        // We need to keep track of the minimum obstacles remaining to reach a cell
        // at a certain step count.
        // `visited[r, c]` stores the maximum `k` value with which cell (r, c) was reached.
        // We only visit a cell (r, c) if our current `k` is greater than the `k`
        // we previously used to reach it, indicating a potentially better path.
        int[,] visited = new int[m, n];
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                visited[i, j] = -1; // Initialize with -1 to indicate not visited or with 0 k.
            }
        }

        // BFS queue: stores tuples of (row, col, remaining_k_after_obstacle_elimination)
        Queue<(int r, int c, int remainingK)> q = new Queue<(int r, int c, int remainingK)>();

        // Starting point: (0, 0) with initial k.
        q.Enqueue((0, 0, k));
        visited[0, 0] = k; // Mark start as visited with initial k.

        int steps = 0;

        // Possible movements (up, down, left, right)
        int[] dr = { -1, 1, 0, 0 };
        int[] dc = { 0, 0, -1, 1 };

        while (q.Count > 0)
        {
            int levelSize = q.Count; // Process all nodes at the current level

            for (int i = 0; i < levelSize; i++)
            {
                var current = q.Dequeue();
                int r = current.r;
                int c = current.c;
                int currentK = current.remainingK;

                // If we reached the destination, this is the shortest path.
                if (r == m - 1 && c == n - 1)
                {
                    return steps;
                }

                // Explore neighbors
                for (int j = 0; j < 4; j++)
                {
                    int nr = r + dr[j];
                    int nc = c + dc[j];

                    // Check boundaries
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n)
                    {
                        int newK = currentK;
                        // If it's an obstacle, reduce k.
                        if (grid[nr][nc] == 1)
                        {
                            newK--;
                        }

                        // Check if we have enough k to pass through or if it's an empty cell.
                        // And if this path to (nr, nc) has more remaining k than a previously found path,
                        // or if it's the first time visiting (nr, nc).
                        if (newK >= 0 && newK > visited[nr, nc])
                        {
                            visited[nr, nc] = newK;
                            q.Enqueue((nr, nc, newK));
                        }
                    }
                }
            }
            steps++; // Increment steps after processing a whole level
        }

        return -1;
    }

    // Swim in Rising Water - BFS with priority queue, travel is instant, only wait for water to rise
    static int SwimInWater(int[][] grid)
    {
        // BFS with submerged condition
        int m = grid.Length;
        int n = grid[0].Length;

        // Take smallest number to traverse (it will be less than time always)
        PriorityQueue<(int r, int c), int> q = new();

        int[] dirX = [0, 1, -1, 0];
        int[] dirY = [1, 0, 0, -1];

        int[,] visited = new int[m, n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                visited[i, j] = -1;

        q.Enqueue((0, 0), 0);
        visited[0, 0] = 1;
        int maxDis = int.MinValue;

        while (q.Count > 0)
        {
            var currentCell = q.Dequeue();
            //max in path represents the total time taken rest traversal is instant
            maxDis = Math.Max(maxDis, grid[currentCell.r][currentCell.c]);

            if (currentCell.r == m - 1 && currentCell.c == n - 1)
                return maxDis;

            // queue neighbors
            for (int j = 0; j < 4; j++)
            {
                int nextR = currentCell.r + dirX[j];
                int nextC = currentCell.c + dirY[j];
                if (nextR >= 0 && nextR < m && nextC >= 0 && nextC < n
                        && visited[nextR, nextC] != 1)
                {
                    q.Enqueue((nextR, nextC), grid[nextR][nextC]);
                    visited[nextR, nextC] = 1;
                }
            }
        }

        return maxDis;
    }

    // Trapping Rain Water - Two Pointer - return total water trapped
    static int Trap(int[] height)
    {
        int total = 0, l = 0, r = height.Length - 1; // Initialize total and two pointers
        int lmax = 0, rmax = height[r]; // Initialize max heights for left and right

        while (l < r)
        {
            if (height[l] <= height[r])
            {
                // If left height is less than or equal to right height
                if (height[l] < lmax)
                {
                    total += lmax - height[l]; // Water trapped on the left
                }
                else
                {
                    lmax = height[l]; // Update left max height
                }
                l++; // Move left pointer
            }
            else
            {
                // If right height is less than left height
                if (height[r] < rmax)
                {
                    total += rmax - height[r]; // Water trapped on the right
                }
                else
                {
                    rmax = height[r]; // Update right max height
                }
                r--; // Move right pointer
            }
        }
        return total; // Return total water trapped
    }


    static void Main()
    {
        // Console.WriteLine("The quick brown fox jumps over the lazy dog.");
        // int[] arr = { 15, 2, 4, 8, 9, 5, 10, 23 };
        // int target = 23;
        // List<int> res = subArraySum(arr, target);

        // int[] arr = { 3, 1, 4, 4, 5, 1, 6, 1 };
        // List<int> res = topKFrequent(arr, 2);

        // Node root = new Node(10);
        // root.left = new Node(20);
        // root.right = new Node(30);
        // root.left.left = new Node(40);
        // root.left.right = new Node(60);

        // List<int> res = new List<int>();
        // serializePreOrder(root, res);

        // char[][] grid = [
        //     ['a', 'b', 'a', 'b'],
        //     ['a', 'b', 'e', 'b'],
        //     ['e', 'b', 'e', 'b']
        // ];
        // string word = "abe";

        // int m = grid.Length;
        // int n = grid[0].Length;

        // for (int i = 0; i < m; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         if (search2dWord(grid, i, j, word))
        //         {
        //             Console.WriteLine(i + "," + j);
        //         }
        //     }
        // }

        // int[] memo = new int[10 + 1];
        // Array.Fill(memo, -1);
        // Console.WriteLine(CountWays(10, memo));

        // foreach (var e in res)
        // {
        //     Console.Write(e + " ");
        // }

        // SimplifyPath("/home//foo/");

        Console.WriteLine(ShortestPath([
            [0,0,0],
            [1,1,0],
            [0,0,0],
            [0,1,1],
            [0,0,0]
        ], 1));
    }
}