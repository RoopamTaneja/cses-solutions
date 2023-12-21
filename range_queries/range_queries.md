## Static Queries:

Array does not change between queries

### RSQ - Range Sum Queries ; RMQ - Range Min/Max Queries

## Static RSQ:
Best - Prefix array

## Static RMQ:
Best - Sparse Table

# Sparse Table:
- For static queries
- RMQ - O(1) for each, RSQ - O(lg n) for each
- Precomputation T.C : O(n*lg n)
- Intuition: 

Any non-negative number can be uniquely represented as a sum of decreasing powers of two. This is just a variant of the binary representation of a number. E.g.  
$13 = (1101)_2 = 8 + 4 + 1$ . For a number  
$x$  there can be at most  
$\lceil \log_2 x \rceil$  summands.

By the same reasoning any interval can be uniquely represented as a union of intervals with lengths that are decreasing powers of two. E.g.  
$[2, 14] = [2, 9] \cup [10, 13] \cup [14, 14]$ , where the complete interval has length 13, and the individual intervals have the lengths 8, 4 and 1 respectively. And also here the union consists of at most  
$\lceil \log_2(\text{length of interval}) \rceil$  many intervals.

The main idea behind Sparse Tables is to precompute all answers for range queries with power of two length. Afterwards a different range query can be answered by splitting the range into ranges with power of two lengths, looking up the precomputed answers, and combining them to receive a complete answer.

- We will use a 2-dimensional array for storing the answers to the precomputed queries.  
$\text{st}[i][j]$  will store the answer for the range  
$[j, j + 2^i - 1]$  of length  
$2^i$ . 

- Because the range  
$[j, j + 2^i - 1]$  of length  
$2^i$  splits nicely into the ranges  
$[j, j + 2^{i - 1} - 1]$  and  
$[j + 2^{i - 1}, j + 2^i - 1]$ , both of length  
$2^{i - 1}$ , we can generate the table efficiently using dynamic programming

- RSQ : To answer the sum query for the range 
$[L, R]$ , we iterate over all powers of two, starting from the biggest one. As soon as a power of two  
$2^i$  is smaller or equal to the length of the range ( 
$= R - L + 1$ ), we process the first part of range  
$[L, L + 2^i - 1]$ , and continue with the remaining range  
$[L + 2^i, R]$ .

```cpp
long long sum = 0;
for (int i = K; i >= 0; i--) {
    if ((1 << i) <= R - L + 1) {
        sum += st[i][L];
        L += 1 << i;
    }
}
```

Time complexity for a Range Sum Query is  
$O(K) = O(\log \text{MAXN})$ .

- RMQ : *When computing the minimum of a range, it doesn't matter if we process a value in the range once or twice.* **(Min is idempotent, sum is not)**
-  Therefore instead of splitting a range into multiple ranges, we can also split the range into only two overlapping ranges with power of two length. E.g. we can split the range  
$[1, 6]$  into the ranges  
$[1, 4]$  and  
$[3, 6]$ . The range minimum of  
$[1, 6]$  is clearly the same as the minimum of the range minimum of  
$[1, 4]$  and the range minimum of  
$[3, 6]$ . So we can compute the minimum of the range  
$[L, R]$  with:  
$$\min(\text{st}[i][L], \text{st}[i][R - 2^i + 1]) \quad \text{ where } i = \log_2(R - L + 1)$$

Time complexity for a Range Minimum Query is  
$O(1)$ .

**Impl : static_rmq.cpp**

# Dynamic Range Queries

# Segment Tree

- A 
segment tree
 allows you to do point update and range query in $\mathcal{O}(\log N)$
 time each for 
any associative operation, not just
summation.

- It is a binary tree, in the leaves of which there are elements of the original array, and each internal node contains the sum of the numbers in its children (for RSQ).

- If size is not a power of two, u can append 0s to make it so (TC not affected) or keep indices unused (like in our impl)
- The time complexity of construction of segtree is  
$O(n)$ , assuming that the merge operation is constant time (the merge operation gets called  
$n$  times, which is equal to the number of internal nodes in the segment tree)
- Operations:
  - Point Update : Set in leaf and update from bottom to up all affected nodes. No of affected nodes = No of layers - $\mathcal{O}(\log N)$ so that is the TC also. You can also move recursively from root.
  - Range Query : Sum of the segment [l..r) from these already calculated sums. To
    do this, run a recursive traversal of the segment tree. In this case, we will interrupt recursion in two situations.
    - The segment corresponding to the current node does not intersect the segment [l..r). In this case, all the elements in this subtree are outside the area in which we need to calculate the sum, so we can stop the recursion.
    - The segment corresponding to the current node is entirely nested in the segment [l..r)
In this case, all the elements in this subtree are in the area in which we need to calculate the sum, so we need to add to the answer their sum, which is recorded in the current node.

- RSQ and RMQ are handled similarly, just function is changed. Sum of segments while building and querying for RSQ, and min/max for RMQ.

- In addition to the sum and the minimum, associative operations which can be used for segtree are:
  - multiplication (including modulo multiplication, matrix multiplication, etc.),
  - bitwise operations: &, |, ^,
  - GCD - though gcd calc is not O(1)
- *With more analysis, you can also use segtree for some non-trivial operations, by modifying 1-value in any node & 2-merge operation for merging two children depending on the value.*
- One important property of Segment Trees is that they require only a linear amount of memory. The standard Segment Tree requires  
$4n$  vertices for working on an array of size  
$n$ .
- The first level of the tree contains a single node (the root), the second level will contain two vertices, in the third it will contain four vertices, until the number of vertices reaches  
$n$ . Thus the number of vertices in the worst case can be estimated by the sum  
$1 + 2 + 4 + \dots + 2^{\lceil\log_2 n\rceil} \lt 2^{\lceil\log_2 n\rceil + 1} \lt 4n$ .

**Dynamic RMQ impl - dynamic_rmq.cpp**

**Dynamic RSQ impl - dynamic_rsq.cpp**

## Range Update + Point Query

- Same segtree code as that of RSQ
- Define diff array : diff[i] = v[i] - v[i-1] for i>0 and diff[0] = diff[0] and build segtree using it
- Range update is same as : 2 (or 1) point updates : increase [a, b] by u is same as increasing diff[a] by u and decreasing diff[b+1] by u (iff b+1 < n) (0-based)
- Point Query is same as range query for [0, k] (0-based) since : v[i] = prefix sum of diff array till index k.