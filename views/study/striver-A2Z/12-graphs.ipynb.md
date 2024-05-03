---
jupyter:
  kernelspec:
    display_name: Python 3 (ipykernel)
    language: python
    name: python3
  language_info:
    codemirror_mode:
      name: ipython
      version: 3
    file_extension: .py
    mimetype: text/x-python
    name: python
    nbconvert_exporter: python
    pygments_lexer: ipython3
    version: 3.10.14
  nbformat: 4
  nbformat_minor: 5
  papermill:
    default_parameters: {}
    duration: 6.206431
    end_time: "2024-05-03T16:50:23.954801"
    environment_variables: {}
    input_path: study/striver-A2Z/12-graphs.ipynb
    output_path: study/striver-A2Z/12-graphs.ipynb
    parameters: {}
    start_time: "2024-05-03T16:50:17.748370"
    version: 2.5.0
---

<div id="b7c72dfd" class="cell markdown"
papermill="{&quot;duration&quot;:2.1747e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:18.837982&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:18.816235&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Introduction to Graphs

Video link: <https://youtu.be/M3_pLsDdeuU?si=Bi_17bBfZUPqBU6K>

- Directed Graph: Graph with edges
- Undirected Graph: Graph without edges
- Cycle: Starting at node i, we are able to reach back to i again
- DAG (Directed Acyclic Graph): Directed graph without any cycles
- Degrees of a node (undirected): No of edges connected to that node
- Indegree of a node (directed): No of incoming edges to a node
- Outdegree of a node (directed): No of outgoing edges from a node
- Property of an undirected of graph: Total degree = 2 \* no. of edges
  (intuitively for edge we will be counting it twice on both ends of the
  connection)
- Edge weights: Every edge of a graph is assigned a weight. If not
  provided, we can assume unit weight
- Note that a graph can contain multiple components. A component is a
  set of nodes that can be reached from starting the traversal from one
  of the nodes.

</div>

<div id="cf960c9a" class="cell markdown" lines_to_next_cell="0"
papermill="{&quot;duration&quot;:2.1024e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:18.880007&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:18.858983&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Graph representation <br>

Video Link: <https://youtu.be/3oI-34aPMWM?si=ibTcfbzU8J9k-NHa>

1.  Adjacency matrix: If N is no of nodes, create N x N grid. Each cell
    contains the weight if the edge between the two nodes. Connections
    may or may not exist. For undirected graphs, the matrix is symmetric
    around the diagnol. Space: O (N ^ 2)

For eg:

    0 1 2 3 4 5
    0 0 0 0 0 0
    1 0 1 2 0 0
    2 1 0 0 1 1
    3 2 0 0 0 0
    4 0 1 0 0 0
    5 0 1 0 0 0

1.  Adjaceny list: Create an array of arrays or set of arrays. Each
    nested array at index denotes the nodes that index is connected to.
    Space: O(E), still be O (N ^ 2) in a complete graph. If it is a
    directed graph, each element in the nested array is a tuple of node
    that index is connected to along with the weight of that connection.

For eg:

    {
     1: [(2, 1), (3, 2)]
     2: [(4, 5)]
     3: [(2, 2), (4, 1)]
    }

</div>

<div id="d7ecd5e5" class="cell markdown"
papermill="{&quot;duration&quot;:2.0571e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:18.921004&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:18.900433&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Misc about graphs

- Bipartite Graph: Color the graph with 2 colors such that no adjacent
  nodes have the same color. More formally: A graph is bipartite if the
  nodes can be partitioned into two independent sets A and B such that
  every edge in the graph connects a node in set A and a node in set B.
- Linear graphs without any cycles are always bipartite.
- Cyclic graphs of even node length are always bipartite.
- Cyclic graphs of odd node length are NOT bipartite.
- Topological sortig is only valid for DAGs (Directed Acyclic graphs).
  Is topo sort, the vertices are ordered such that if there is an edge
  between vertex v1 and v2 then v1 appears before v2. There could be
  multiple ways in which the vertices are sorted.
- Topological sorting with DFS involves pushing onto a stack at the end
  of recursive function.
- Topological sorting with BFS involves an algorithm called as the
  Kahn's algorithm.

</div>

<div id="24f84e7c" class="cell markdown"
papermill="{&quot;duration&quot;:2.0284e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:18.961669&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:18.941385&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Dijkstra algorithm (Worst case time complexity: O (E log V)):

1.  Algorithm to find the shortest distance from source node to all
    nodes.
2.  It doesn't work for graphs with negative weights.
3.  Typically used with a priority queue. Can work with queue as well.
    With Q, it works as a typical BFS (Brute force). With PQ we consider
    the best path only instead of iterating all edges, we end up pruning
    non optimal paths.
4.  Logic:

<!-- -->

    - Create a vector of distances. Assign src as 0 and remaining nodes as infinite (not yet reached)
    - Initialize a min heap <dist, node>. Initially we start at src (0, src).
    - Repeat until min heap is exhausted.
      * Pop the smallest out
      * Iterate through all neighbours. If the dist to reach neighbour is smaller than currently known shortest distance, update the shortest dist and add to queue.
    - Return the distance vector.

</div>

<div id="d97a2dea" class="cell markdown"
papermill="{&quot;duration&quot;:2.0448e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.002680&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:18.982232&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Bellman Ford Algorithm (Worst case time complexity: O (V x E))

1.  Relax all the edges N - 1 times sequentially.
2.  N - 1 iterations because: In a graph of N nodes, in the worst case,
    we will take N - 1 edges to reach from the first to the last
    (consider a singly connected linked list), thereby we iterate for
    N - 1 iterations. (Best case each node has N - 1 edges and takes 1
    step to reach every other node, worst case is the linked list
    example where it takes N - 1 iterations to travel from 0 to N - 1
    node)
3.  To detect negative cycle, run another iteration. If the value of any
    node decreases still, the graph has a negative cycle.

</div>

<div id="037e1b1b" class="cell markdown"
papermill="{&quot;duration&quot;:2.0234e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.043210&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.022976&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Floyd Warshall Algorithm

1.  Multi source shortest path algorithm
2.  Helps detect negative cycles as well
3.  The idea is that for each node i and for each node j that we are
    trying to reach, check out all paths k and get the minimum:
    `min(d[i][k] + d[k][j])`
4.  Instead of storing a 1D distance vector, we store a 2D distance /
    cost matrix.
5.  This is a brute force approach that caches results.
6.  To detect a negative cycle, simply check if node to same node path
    is \< 0. It must be 0 for a graph without negative cycles.
7.  Logic:

``` python
for via in range(V):
  for i in range(V):
      for j in range(V):
          cost[i][j] = min(cost[i][j], cost[i][via] + cost[via][j])
```

1.  Running dijkstra on all nodes (O(E log V)) would be faster than
    Floyd Warshall. But dijkstra doesn't work on graphs with negative
    edges. We woulld need to run Johnson's algorithm to remove negative
    cycles and then run Dijkstra. It would still be faster than floyd
    warshall iff E \< V^2.

</div>

<div id="46672733" class="cell markdown"
papermill="{&quot;duration&quot;:2.0367e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.084481&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.064114&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Minimum Spanning Tree (MST)

1.  Spanning Tree: A tree in which we have N nodes and N - 1 edges and
    all nodes are reachable from each other.
2.  MST: Out of all spanning trees that we can get, the one with the
    minimum edge weight sum is called the minimum spanning tree.

</div>

<div id="fe81afa5" class="cell markdown"
papermill="{&quot;duration&quot;:2.0502e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.125469&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.104967&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Disjoint Set

1.  Useful for determining if two given vertices are part of the same
    component or not in O(1) time.
2.  It offers two functions: findParent(), union() (could be via rank or
    via size)
3.  It is especially useful in problems involving dynamic graphs, where
    the structure (connections) keeps changing frequently.
4.  Pseudo code for union of U, V by rank (O (4 alpha)):

<!-- -->

    - Find ultimate parent of U (pu), V (pv).
    - Find rank of pu, pv.
    - Connect smaller rank of the ultimate parents to the larger of the ultimate parents.

1.  Pseudo code for union of U, V by size (O (4 alpha)):

<!-- -->

    - Find ultimate parent of U, V
    - Find size of U (UR), V (VR)
    - Attach the smaller sized parent to the larger one.

1.  To ensure that find parent takes O(1) time instead of O(N), we
    perform path compression: first time we iterate through and find the
    parent, on subsequent calls the result is cached and parent list is
    updated.
2.  By connecting the smaller to the larger, we overall rank would
    remain unchanged and the graph would be more 'balanced'. Time taken
    to find parent is as minimal as possb.
3.  Post path compression, rank wouldn't make much sense.

</div>

<div id="a321425e" class="cell markdown" lines_to_next_cell="0"
papermill="{&quot;duration&quot;:2.0403e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.166122&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.145719&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper functions and definitions

</div>

<div id="8c79edc4" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:19.209349Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:19.208669Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:19.218826Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:19.218032Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3462e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.220584&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.187122&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import collections
import itertools
import typing
import heapq
import functools
```

</div>

<div id="fc260e41" class="cell markdown"
papermill="{&quot;duration&quot;:2.0417e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.261898&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.241481&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-tgVpUgsQ5k?si=8HBt33CLyu9hTP1I> BFS
Search of a graph

</div>

<div id="2e42efd0" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:19.304478Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:19.303762Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:19.310556Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:19.309775Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9969e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.312243&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.282274&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def bfsOfGraph(V: int, adj: list[list[int]]) -> list[int]:
    result: list[int] = []
    queue: collections.deque = collections.deque([0])
    visited: set[int] = set()
    while queue:
        curr = queue.popleft()
        if curr not in visited:
            result.append(curr)
            visited.add(curr)
        queue.extend(adj[curr])

    return result

# Testing the solution
assert bfsOfGraph(5, [[1,2,3],[],[4],[],[]]) == [0, 1, 2, 3, 4]
assert bfsOfGraph(5, [[1,2],[],[]]) == [0, 1, 2]
```

</div>

<div id="25de613f" class="cell markdown"
papermill="{&quot;duration&quot;:2.0299e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.353218&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.332919&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Qzf1a--rhp8?si=Zb_XCqskGiK11gbB> DFS
Traversal

</div>

<div id="4a28e0ae" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:19.396416Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:19.395731Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:19.404959Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:19.404134Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3127e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.406915&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.373788&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def depthFirstSearch(V: int, E: int, edges: list[list[int]]) -> list[list[int]]:
    adjl: dict[int, list[int]] = dict()
    for i in range(E):
        n1, n2 = edges[i]
        n1_edges, n2_edges = adjl.get(n1, []), adjl.get(n2, [])
        n1_edges.append(n2)
        n2_edges.append(n1)
        adjl[n1], adjl[n2] = n1_edges, n2_edges

    result: list[list[int]] = []
    visited: set[int] = set()

    # Time Complexity: O(N), Space: O(N)
    for i in range(V):
        stack: list[int] = [i]
        components: list[int] = []
        while stack:
            curr = stack.pop()
            if curr not in visited:
                visited.add(curr)
                components.append(curr)
                for next_ in adjl.get(curr, []):
                    stack.append(next_)

        if components:
            components.sort()
            result.append(components)

    return result

# Testing the result
assert depthFirstSearch(5, 4, [[0,2], [0,1], [1,2], [3,4]]) == [[0,1,2], [3,4]]
```

</div>

<div id="a12cfaca" class="cell markdown"
papermill="{&quot;duration&quot;:2.064e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.468449&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.447809&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of provinces:
<https://leetcode.com/problems/number-of-provinces/submissions/1237343247/>
Video Link: <https://youtu.be/ACzkVtewUYA?si=wpzBiKJoOJQnFR18>

</div>

<div id="672dd010" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:19.511533Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:19.511039Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:19.518251Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:19.517494Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1068e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.520126&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.489058&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def findCircleNum(adjM: list[list[int]]) -> int:
    N = len(adjM)

    visited: set[int] = set()
    def DFS(curr: int):
        if curr not in visited:
            visited.add(curr)
            for i in range(N):
                if adjM[curr][i]:
                    DFS(i)

    provinces: int = 0
    for curr in range(N):
        if curr not in visited:
            DFS(curr)
            provinces += 1

    return provinces

# Testing the solution
assert findCircleNum([[1,1,0],[1,1,0],[0,0,1]]) == 2
assert findCircleNum([[1,0,0],[0,1,0],[0,0,1]]) == 3
```

</div>

<div id="bab63bca" class="cell markdown"
papermill="{&quot;duration&quot;:2.0629e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.561667&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.541038&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/muncqlKJrH0?si=xcCfsKjX5tZd4kZJ> Number of
islands

</div>

<div id="968de0b8" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:19.604441Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:19.603890Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:19.611963Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:19.611198Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1469e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.613685&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.582216&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def numIslands(grid: list[list[int]]) -> int:
    N = len(grid)
    M = len(grid[0])

    def DFS(i: int, j: int):
        if 0 <= i < N and 0 <= j < M and grid[i][j] == 1:
            grid[i][j] = 0
            for i_ in range(-1, 2):
                for j_ in range(-1, 2):
                    DFS(i + i_, j + j_)

    islands = 0
    for i_ in range(N):
        for j_ in range(M):
            if grid[i_][j_] == 1:
                islands += 1
                DFS(i_, j_)
    return islands

# Testing the solution
assert numIslands([[0,1,1,1,0,0,0],[0,0,1,1,0,1,0]]) == 2
assert numIslands([[0,1],[1,0],[1,1],[1,0]]) == 1
```

</div>

<div id="10f09e20" class="cell markdown"
papermill="{&quot;duration&quot;:2.0522e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.655099&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.634577&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/C-2_uSRli8o?si=kwATM2glQc_Mpf76> Flood
fill: <https://leetcode.com/problems/flood-fill/submissions/1237381436>

</div>

<div id="1e1a36fc" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:19.698089Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:19.697352Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:19.704999Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:19.704260Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1008e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.706743&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.675735&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def floodFill(image: list[list[int]], sr: int, sc: int, fill_color: int) -> list[list[int]]:

    N, M = len(image), len(image[0])

    start_color = image[sr][sc]
    if start_color != fill_color:
        queue: collections.deque = collections.deque([(sr, sc)])

        while queue:
            i, j = queue.popleft()
            if 0 <= i < N and 0 <= j < M and image[i][j] == start_color:
                image[i][j] = fill_color
                queue.extend([(i - 1, j), (i, j - 1), (i, j + 1), (i + 1, j)])

    return image

# Testing the solution
assert floodFill([[1,1,1],[1,1,0],[1,0,1]], 1, 1, 2) == [[2,2,2],[2,2,0],[2,0,1]]
```

</div>

<div id="cb576964" class="cell markdown"
papermill="{&quot;duration&quot;:2.0175e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.747457&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.727282&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/yf3oUhkvqA0?si=A664tpMiA00GrxJV> Rotten
Oranges:
<https://leetcode.com/problems/rotting-oranges/submissions/1237760285>

</div>

<div id="8b72ec9b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:19.790163Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:19.789414Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:19.801412Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:19.800667Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5396e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.803235&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.767839&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def orangesRotting(grid: list[list[int]]) -> int:
    """
    BFS function can be optimized by using a queue. Each element is (i, j, time).
    Further more instead of storing all fresh indices as a set, we can simply have a counter and decrement it every time we rot an orange.
    Simple check if this counter is 0 before returning minutes.

    Time: O(M x N), Space: O(M x N)
    """
    N, M = len(grid), len(grid[0])

    rotten: list[tuple[int, int]] = []
    def BFS() -> int:
        nonlocal rotten
        min_: int = 0
        while rotten:
            newly_rotten = False
            next_: list[tuple[int, int]] = []
            for i_, j_ in rotten:
                if 0 <= i_ < N and 0 <= j_ < M and grid[i_][j_] == 1:
                    grid[i_][j_] = 2
                    fresh.remove((i_, j_))
                    next_.extend([(i_ - 1, j_), (i_, j_ - 1), (i_, j_ + 1), (i_ + 1, j_)])
                    newly_rotten = True

            min_ += int(newly_rotten)
            rotten = next_

        return min_

    fresh: set[tuple[int, int]] = set()
    for i in range(N):
        for j in range(M):
            if grid[i][j] == 1:
                fresh.add((i, j))
            if grid[i][j] == 2:
                grid[i][j] = 2
                rotten.extend([(i - 1, j), (i, j - 1), (i, j + 1), (i + 1, j)])

    minutes = BFS()
    return minutes if not fresh else -1

# Testing the solution
assert orangesRotting([[2,1,1],[1,1,0],[0,1,1]]) == 4
assert orangesRotting([[2,1,1],[0,1,1],[1,0,1]]) == -1
assert orangesRotting([[2,1,1],[1,1,1],[0,1,2]]) == 2
```

</div>

<div id="eef4c409" class="cell markdown"
papermill="{&quot;duration&quot;:2.0662e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.844838&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.824176&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle with Graph (BFS / DFS) Video Link BFS:
<https://youtu.be/BPlrALf1LDU?si=U9u9H_9xiHo8oflx> Video Link DFS:
<https://youtu.be/zQ3zgFypzX4?si=trbPI1I4DfRMcrj5>

</div>

<div id="342b6f3b" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:19.888011Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:19.887355Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:19.899054Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:19.898381Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5291e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.900908&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.865617&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def detectCycle(V: int, E: int, edges: list[tuple[int, int]]):
    """
    BFS:

    Starting at node i we branch outwards. If some node is visited again and that node didn't come from curr node then we have a cycle
    We check if the next node comes from curr by storing the parent in the queue.

    We can save duplicate work for disconnected components by storing visited outside of the BFS function. Remember to add the parent != -1 condition.

    Time: O(N), Space: O(N)

    DFS:

    Starting at node i, if we are able to reach node i again via DFS, then the graph has a cycle.
    To make sure we don't visit the parent again, we store the parent node in the stack.

    Time: O(N), Space: O(N)
    """
    adjl: dict[int, list[int]] = dict()
    for n1, n2 in edges:
        n1_neighbours, n2_neighbours = adjl.get(n1, []), adjl.get(n2, [])
        n1_neighbours.append(n2)
        n2_neighbours.append(n1)
        adjl[n1], adjl[n2] = n1_neighbours, n2_neighbours

    def BFS(root: int) -> bool:
        queue: collections.deque = collections.deque([(root, -1)])
        while queue:
            curr, parent = queue.popleft()
            visited.add(curr)
            for next_ in adjl.get(curr, []):
                if next_ not in visited:
                    queue.append((next_, curr))
                elif parent != -1 and next_ != parent:
                    return True
        else:
            return False

    def DFS(root: int) -> bool:
        stack: list[tuple[int, int]] = [(root, -1)]
        while stack:
            curr, parent = stack.pop()
            if curr not in visited:
                visited.add(curr)
                for next_ in adjl.get(curr, []):
                    if next_ != parent:
                        stack.append((next_, curr))

            elif parent != -1:
                return True

        return False

    visited: set[int] = set()
    for curr in range(V):
        if DFS(curr):
            return True
    else:
        return False

assert detectCycle(5, 3, [(0, 1), (1, 2), (3, 4)]) == False
assert detectCycle(4, 4, [(0, 1), (1, 2), (2, 3), (3, 0)]) == True
```

</div>

<div id="86e956f5" class="cell markdown"
papermill="{&quot;duration&quot;:2.0763e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.942553&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.921790&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/edXdVwkYHF8?si=oTave6oul5GbDHrn> 01
Matrix: <https://leetcode.com/problems/01-matrix/>

</div>

<div id="14c07211" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:19.985616Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:19.985061Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:19.995535Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:19.994788Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3886e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:19.997103&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:19.963217&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def updateMatrixBrute(mat: list[list[int]]) -> list[list[int]]:
    M, N = len(mat), len(mat[0])
    result: list[list[int]] = [[-1 for i in range(N)] for j in range(M)]

    def BFS(row: int, col: int) -> int:
        queue: collections.deque = collections.deque([(row, col, 0)])
        visited: set[tuple[int, int]] = set()
        while queue:
            i, j, dist = queue.popleft()
            if (i, j) not in visited and 0 <= i < M and 0 <= j < N:
                visited.add((i, j))
                if mat[i][j] == 0:
                    return dist
                else:
                    queue.extend([(i - 1, j, dist + 1), (i, j - 1, dist + 1), (i, j + 1, dist + 1), (i + 1, j, dist + 1)])

        return -1

    for i in range(M):
        for j in range(N):
            result[i][j] = BFS(i, j)

    return result

# Testing the solution
assert updateMatrixBrute([[0,0,0],[0,1,0],[0,0,0]]) == [[0,0,0],[0,1,0],[0,0,0]]
assert updateMatrixBrute([[0,0,0],[0,1,0],[1,1,1]]) == [[0,0,0],[0,1,0],[1,2,1]]
```

</div>

<div id="251805ef" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.040348Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.039693Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.052997Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.052344Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.683e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.054748&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.017918&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/01-matrix/submissions/1238008344
def updateMatrixBetter(mat: list[list[int]]) -> list[list[float]]:
    M, N = len(mat), len(mat[0])
    result: list[list[float]] = [[math.inf for j in range(N)] for i in range(M)]

    # Go right to left to find the nearest 0 on the right
    for i in range(M):
        for j in range(N - 1, -1, -1):
            if mat[i][j] == 0:
                result[i][j] = 0
            else:
                dist = result[i][j + 1] + 1 if j < N - 1 else math.inf
                result[i][j] = min(dist, result[i][j])

    # Go left to right to find the nearest 0 on the left
    for i in range(M):
        for j in range(N):
            if mat[i][j] == 0:
                result[i][j] = 0
            else:
                dist = result[i][j - 1] + 1 if j > 0 else math.inf
                result[i][j] = min(dist, result[i][j])

    # Go top to bottom to find the nearest 0 on the top
    for i in range(M):
        for j in range(N):
            if mat[i][j] == 0:
                result[i][j] = 0
            else:
                dist = result[i - 1][j] + 1 if i > 0 else math.inf
                result[i][j] = min(dist, result[i][j])

    # Go bottom to top to find the nearest 0 on the bottom
    for i in range(M - 1, -1, -1):
        for j in range(N):
            if mat[i][j] == 0:
                result[i][j] = 0
            else:
                dist = result[i + 1][j] + 1 if i < M - 1 else math.inf
                result[i][j] = min(dist, result[i][j])

    return result

# Testing the solution
assert updateMatrixBetter([[0,0,0],[0,1,0],[0,0,0]]) == [[0,0,0],[0,1,0],[0,0,0]]
assert updateMatrixBetter([[0,0,0],[0,1,0],[1,1,1]]) == [[0,0,0],[0,1,0],[1,2,1]]
```

</div>

<div id="9469ade5" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.098193Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.097903Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.108112Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.107369Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3595e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.109713&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.076118&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/01-matrix/submissions/1238019317/
def updateMatrix(mat: list[list[int]]) -> list[list[float]]:
    """Time: O(M x N), Space: O(M x N)"""

    M, N = len(mat), len(mat[0])
    result: list[list[float]] = [[math.inf for j in range(N)] for i in range(M)]

    # Collect all nodes that are having 0 values: i, j, dist
    queue: collections.deque = collections.deque()
    for i in range(M):
        for j in range(N):
            if mat[i][j] == 0:
                queue.append((i, j, 0))

    # Start to traverse BFS together
    visited: set[tuple[int, int]] = set()
    while queue:
        i, j, dist = queue.popleft()
        if 0 <= i < M and 0 <= j < N and (i, j) not in visited:
            result[i][j] = dist
            visited.add((i, j))
            queue.extend([(i - 1, j, dist + 1), (i, j - 1, dist + 1), (i, j + 1, dist + 1), (i + 1, j, dist + 1)])

    return result

# Testing the solution
assert updateMatrix([[0,0,0],[0,1,0],[0,0,0]]) == [[0,0,0],[0,1,0],[0,0,0]]
assert updateMatrix([[0,0,0],[0,1,0],[1,1,1]]) == [[0,0,0],[0,1,0],[1,2,1]]
```

</div>

<div id="0b3a1d29" class="cell markdown"
papermill="{&quot;duration&quot;:2.0522e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.151002&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.130480&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/BtdgAys4yMk?si=BLc-UXXR9XvQV8Mf>
Surrounded Regions:
<https://leetcode.com/problems/surrounded-regions/description/>

</div>

<div id="3610e726" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.194122Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.193429Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.205519Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.204853Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5646e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.207289&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.171643&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/surrounded-regions/submissions/1238092752
def solve(board: list[list[str]]) -> None:
    "Time: O(M x N), Time: O(M x N)"
    M, N = len(board), len(board[0])

    stack: list[tuple[int, int]] = []
    visited: set[tuple[int, int]] = set()

    # Capture all zeros at the borders
    for i in range(M):
        for j in range(N):
            if (i in (0, M - 1) or j in (0, N - 1)) and board[i][j] == "O":
                stack.append((i, j))

    # Do a DFS and mark zeros into visited
    while stack:
        i, j = stack.pop()
        visited.add((i, j))
        for x, y in [(-1, 0), (0, -1), (0, 1), (1, 0)]:
            row, col = i + x, j + y
            if 0 <= row < M and 0 <= col < N and board[row][col] == 'O' and (row, col) not in visited:
                stack.append((row, col))

    # Visited set contains all 'O' adjacent to 'O's that cannot be flipped
    for i in range(M):
        for j in range(N):
            if (i, j) not in visited:
                board[i][j] = "X"

# Testing the solution
for inp, op in [
    (
        [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]],
        [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
    ),
    (
        [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","X","O","X"]],
        [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","X","O","X"]]
    )
]:
    solve(inp)
    assert inp == op
```

</div>

<div id="0b264d5d" class="cell markdown"
papermill="{&quot;duration&quot;:2.0452e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.248417&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.227965&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of Enclaves Video Link:
<https://youtu.be/7zmgQSJghpo?si=XSGlRuO_V105V2XK>

</div>

<div id="5647a7a1" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.291438Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.290729Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.300220Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.299582Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2849e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.301938&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.269089&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/number-of-enclaves/submissions/1238117024
def numEnclaves(grid: list[list[int]]) -> int:
    "Time: O(M x N), Space: O(M x N) recursion stack space"
    M, N = len(grid), len(grid[0])

    def DFS(row: int, col: int):
        grid[row][col] = 0
        for x, y in [(-1, 0), (0, -1), (0, 1), (1, 0)]:
            i_, j_ = row + x, col + y
            if 0 <= i_ < M and 0 <= j_ < N and grid[i_][j_] == 1:
                DFS(i_, j_)

    for i in range(M):
        for j in range(N):
            if (i in (0, M - 1) or j in (0, N - 1)) and grid[i][j] == 1:
                DFS(i, j)

    enclaves = 0
    for i in range(M):
        for j in range(N):
            if grid[i][j] == 1:
                enclaves += 1

    return enclaves

# Testing the solution
assert numEnclaves([[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]) == 3
assert numEnclaves([[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]) == 0
```

</div>

<div id="83ddc4a6" class="cell markdown"
papermill="{&quot;duration&quot;:2.0335e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.342800&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.322465&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/7zmgQSJghpo?si=VR9VnvBwe-esRaau> Distinct
Islands

</div>

<div id="77dd14f8" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.385768Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.385025Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.396222Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.395559Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4632e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.397936&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.363304&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def distinctIsland(arr: list[list[int]], N: int, M: int) :
    "Time: O(M x N), Space: O(M x N)"

    islands: set[tuple[tuple[int, int], ...]] = set()
    visited: set[tuple[int, int]] = set()

    def BFS(row: int, col: int) -> tuple[tuple[int, int], ...]:
        # Time: O(M x N)
        queue: collections.deque = collections.deque([(row, col)])
        island: list[tuple[int, int]] = []
        while queue:
            i, j = queue.popleft()
            if 0 <= i < N and 0 <= j < M and (i, j) not in visited and arr[i][j] == 1:
                visited.add((i, j))
                island.append((i - row, j - col))
                queue.extend([(i - 1, j), (i, j - 1), (i, j + 1), (i + 1, j)])

        return tuple(island)

    for i in range(N):
        for j in range(M):
            if arr[i][j] == 1:
                island: tuple[tuple[int, int], ...] = BFS(i, j)
                if island:
                    islands.add(island)

    return len(islands)

# Testing the solution
assert distinctIsland([[1, 1, 0, 0, 0], [1, 1, 0, 0, 0], [0, 0, 0, 1, 1], [0, 0, 0, 1, 1]], 4, 5) == 1
assert distinctIsland([[1, 1, 0, 1, 1], [1, 0, 0, 0, 0], [0, 0, 0, 0, 1], [1, 1, 0, 1, 1]], 4, 5) == 3
```

</div>

<div id="f49a3367" class="cell markdown"
papermill="{&quot;duration&quot;:2.059e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.439411&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.418821&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-vu34sct1g8?si=H2DEd5HB-B6oAU4p> Bipartite
Graph (BFS):
<https://leetcode.com/problems/is-graph-bipartite/description/>

</div>

<div id="8584fbc4" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.481840Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.481507Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.491681Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.490984Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.347e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.493357&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.459887&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def isBipartite(graph: list[list[int]]) -> bool:
    "Time: O(N), Space: O(N)"
    visited: dict[int, bool] = dict()
    def checkBipartiteBFS(root: int) -> bool:
        # https://leetcode.com/problems/is-graph-bipartite/submissions/1238665067
        queue: collections.deque = collections.deque([(root, True)])
        while queue:
            curr, color = queue.popleft()
            if curr not in visited:
                visited[curr] = color
                for next_ in graph[curr]:
                    queue.append((next_, not color))
            elif color != visited[curr]:
                return False
        return True

    def checkBipartiteDFS(root: int) -> bool:
        # https://leetcode.com/problems/is-graph-bipartite/submissions/1238671846/
        stack: list[tuple[int, bool]] = [(root, True)]
        while stack:
            curr, color = stack.pop()
            if curr not in visited:
                visited[curr] = color
                for next_ in graph[curr]:
                    stack.append((next_, not color))
            elif color != visited[curr]:
                return False

        return True

    for curr in range(len(graph)):
        if curr not in visited and not checkBipartiteDFS(curr):
            return False

    return True

# Testing the solution
assert isBipartite([[1,2,3],[0,2],[0,1,3],[0,2]]) == False
assert isBipartite([[1,3],[0,2],[1,3],[0,2]]) == True
```

</div>

<div id="b8c8a001" class="cell markdown"
papermill="{&quot;duration&quot;:2.0344e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.534278&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.513934&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle in directed graph with DFS:
<https://youtu.be/9twcmtQj4DU?si=2xZsVlk1bdtLbHz5>

</div>

<div id="f1cf48b4" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.577693Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.577043Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.586340Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.585592Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2722e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.587995&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.555273&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def isCyclicDFS(V: int, E: int, edges: list[tuple[int, int]]) -> bool:
    adjl: dict[int, list[int]] = dict()
    for n1, n2 in edges:
        n1_neighbours = adjl.get(n1, [])
        n1_neighbours.append(n2)
        adjl[n1] = n1_neighbours

    def checkCycle(root: int, paths: set[int] = set()) -> bool:
        if root in paths:
            return True
        elif root in visited:
            return False
        else:
            visited.add(root)
            paths.add(root)
            for next_ in adjl.get(root, []):
                if checkCycle(next_, paths):
                    return True
            paths.remove(root)
            return False

    visited: set[int] = set()
    for curr in range(V):
        if checkCycle(curr):
            return True
    else:
        return False

# Testing the solution
assert isCyclicDFS(4, 4, [(0,1), (1,2), (2,3), (3,0)]) == True
assert isCyclicDFS(3, 3, [(1,0), (1,2), (0,2)]) == False
```

</div>

<div id="a75c6088" class="cell markdown"
papermill="{&quot;duration&quot;:2.0582e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.629271&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.608689&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Eventual Safe states (DFS):
<https://youtu.be/uRbJ1OF9aYM?si=8J-ujp8LUkpO887c>

</div>

<div id="e3bfb6f2" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.672437Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.671710Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.680380Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.679715Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2142e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.682064&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.649922&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/find-eventual-safe-states/submissions/1239573858
def eventualSafeNodes(V: int, adj: list[list[int]]) -> list[int]:

    # Visited - True if unsafe, False otherwise
    visited: dict[int, bool] = dict()

    def checkCycle(root: int, paths: set[int] = set()) -> bool:
        if root in visited:
            return visited[root]
        elif root in paths:
            return True
        else:
            paths.add(root)
            for next_ in adj[root]:
                if checkCycle(next_, paths):
                    visited[root] = True
                    return True

            paths.remove(root)
            visited[root] = False
            return False

    result: list[int] = []
    for curr in range(V):
        if not checkCycle(curr):
            result.append(curr)

    return result

# Testing the solution
assert eventualSafeNodes(7, [[1, 2], [2, 3], [5], [0], [5], [], []]) == [2, 4, 5, 6]
assert eventualSafeNodes(4, [[1], [2], [0,3], []]) == [3]
```

</div>

<div id="e2a1e13b" class="cell markdown"
papermill="{&quot;duration&quot;:2.0539e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.723543&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.703004&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological sorting DFS:
<https://youtu.be/5lZ0iJMrUMk?si=lSTD3o2QoGGjiwxO>

</div>

<div id="806cdb46" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.766803Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.766094Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.778451Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.777683Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5893e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.780046&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.744153&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def topologicalSortBetter(adj: dict[int, list[int]], V: int, E: int):
    "Time: O((V + E) x log (V + E)), Space: O(N)"
    def calcWeights(root: int) -> int:
        if root in weights:
            return weights[root]
        else:
            weight = 1
            for next_ in adj.get(root, []):
                weight += calcWeights(next_)

            weights[root] = weight
            return weight

    weights: dict[int, int] = dict()
    result: list[int] = []
    for curr in range(V):
        calcWeights(curr)
        result.append(curr)

    result.sort(key=lambda x: weights[x], reverse=True)
    return result

# Testing the solution
topologicalSortBetter({0: [2,4], 1: [2], 3: [1]}, 5, 4)
```

<div class="output execute_result" execution_count="18">

    [0, 3, 1, 2, 4]

</div>

</div>

<div id="8365f0a8" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.823592Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.822900Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.832257Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.831585Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2797e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.833973&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.801176&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Much more brilliant and clean approach from Striver
def topologicalSortDFS(adj: dict[int, list[int]], V: int, E: int):
    "Time: O(V + E), Space: O(N)"
    def backtrack(root: int):
        if root in visited:
            return
        else:
            visited.add(root)
            for next_ in adj.get(root, []):
                backtrack(next_)
            stack.append(root)

    visited: set[int] = set()
    stack: list[int] = []
    for curr in range(V):
        backtrack(curr)

    stack.reverse()
    return stack

# Testing the solution
topologicalSortDFS({0: [], 1: [], 2: [3], 3: [1], 4: [0,1], 5: [0,2]}, 6, 6)
```

<div class="output execute_result" execution_count="19">

    [5, 4, 2, 3, 1, 0]

</div>

</div>

<div id="166e867d" class="cell markdown"
papermill="{&quot;duration&quot;:2.0788e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.875967&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.855179&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological Sorting with BFS (Kahn's Algorithm):
<https://youtu.be/73sneFXuTEg?si=TeG_vMqnXLz2NR6M>

</div>

<div id="9aca2f0e" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:20.919418Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:20.918703Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:20.929661Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:20.928924Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4692e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.931371&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.896679&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def topologicalSortBFS(adj: dict[int, list[int]], V: int, E: int):
    """
    Topo sort using BFS - Kahn's Algo.

    1. Figure out all nodes with indegree 0 and insert them into a queue.
    2. Iterate across the elements of the queue and on each step, we decrease indegree of all adjancent nodes.
    3. Once iterated across all neighbouring nodes we insert the node into our linear ordering.

    Time: O(V + E), Space: O(N)
    """

    # Compute the indegree of all nodes
    indegree: dict[int, int] = dict()
    for n1 in range(V):
        for n2 in adj[n1]:
            indegree[n2] = indegree.get(n2, 0) + 1

    # All nodes with indegree 0 are added to our queue
    queue: collections.deque = collections.deque()
    for n1 in range(V):
        if n1 not in indegree:
            indegree[n1] = 0
            queue.append(n1)

    # BFS, popout nodes with 0 indegrees.
    # Iterate through neighbours and decrease indegree by 1.
    # If indegree becomes 0, append to our queue.
    result: list[int] = []
    while queue:
        n1 = queue.popleft()
        for n2 in adj.get(n1, []):
            indegree[n2] = indegree[n2] - 1
            if indegree[n2] == 0:
                queue.append(n2)
        result.append(n1)

    return result

# Testing the solution
topologicalSortBFS({0: [], 1: [], 2: [3], 3: [1], 4: [0,1], 5: [0,2]}, 6, 6)
```

<div class="output execute_result" execution_count="20">

    [4, 5, 0, 2, 3, 1]

</div>

</div>

<div id="318e0702" class="cell markdown"
papermill="{&quot;duration&quot;:2.082e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:20.973436&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.952616&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WAOfKpxYHR8?si=KdXRvzRuinvS50gx>

</div>

<div id="bd6a415c" class="cell markdown"
papermill="{&quot;duration&quot;:2.1171e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.015636&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:20.994465&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 1:
<https://leetcode.com/problems/course-schedule/submissions/1240848705/>

</div>

<div id="d2aca589" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.059246Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.058595Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.067594Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.066960Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.275e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.069202&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.036452&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def canFinish(numCourses: int, prerequisites: list[list[int]]) -> bool:
    """
    Run Kahn's algorithm and check the topological sort output. If length of op < numCourses, we have a cycle.

    Time: O(V + E), Space: O(V)
    """

    # Create an adjacency list
    adj: dict[int, list[int]] = dict()
    for n1, n2 in prerequisites:
        n1_neighbours = adj.get(n1, [])
        n1_neighbours.append(n2)
        adj[n1] = n1_neighbours

    # Compute indegree for all nodes
    indegree: dict[int, int] = dict()
    for edges in adj.values():
        for n1 in edges:
            indegree[n1] = indegree.get(n1, 0) + 1

    # Find out nodes with 0 indegree (terminal nodes)
    queue: collections.deque = collections.deque()
    for n1 in range(numCourses):
        if n1 not in indegree:
            indegree[n1] = 0
            queue.append(n1)

    # BFS on queue, remove indegree to all neighbours of curr node. If neighbour indegree becomes 0, append to queue.
    while queue:
        curr = queue.popleft()
        for next_ in adj.get(curr, []):
            indegree[next_] -= 1
            if indegree[next_] == 0:
                queue.append(next_)

        numCourses -= 1

    return numCourses == 0

# Testing the solution
assert canFinish(2, [[1,0]]) == True
assert canFinish(2, [[1,0],[0,1]]) == False
```

</div>

<div id="f8a6e7b3" class="cell markdown"
papermill="{&quot;duration&quot;:2.0904e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.111701&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.090797&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 2:
<https://leetcode.com/problems/course-schedule-ii/submissions/1240905168/>

</div>

<div id="04331e57" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.155506Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.154835Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.166299Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.165483Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5396e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.167996&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.132600&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def findOrder(numCourses: int, prerequisites: list[tuple[int, int]]) -> list[int]:
    # Create an adjacency list
    adj: dict[int, list[int]] = dict()
    for n1, n2 in prerequisites:
        n1_neighbours = adj.get(n1, [])
        n1_neighbours.append(n2)
        adj[n1] = n1_neighbours

    # Compute indegree for all nodes
    indegree: dict[int, int] = dict()
    for edges in adj.values():
        for n1 in edges:
            indegree[n1] = indegree.get(n1, 0) + 1

    # Find out nodes with 0 indegree (terminal nodes)
    queue: collections.deque = collections.deque()
    for n1 in range(numCourses):
        if n1 not in indegree:
            indegree[n1] = 0
            queue.append(n1)

    # Store the ordering into a list
    result: list[int] = []
    while queue:
        n1 = queue.popleft()
        for n2 in adj.get(n1, []):
            indegree[n2] -= 1
            if indegree[n2] == 0:
                queue.append(n2)
        result.append(n1)

    result.reverse()
    return result if len(result) == numCourses else []

# Testing the solution
for inp in [
        [(1,0),(2,0),(3,1),(3,2)], [(1,0)], [(0,1),(1,2),(2,0)]
    ]:
        op = {n: i for i, n in enumerate(findOrder(4, inp))}
        if not op:
            V, E = max(map(max, inp)), len(inp)
            assert isCyclicDFS(V, E, inp)
        else:
            for n1, n2 in inp:
                assert op[n1] > op[n2]
```

</div>

<div id="7cc4aaeb" class="cell markdown"
papermill="{&quot;duration&quot;:2.083e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.210164&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.189334&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/2gtg3VsDGyc?si=l4U9ljeQk6vBufj-> Eventual
Safe States with BFS

</div>

<div id="f5f3c530" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.253852Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.253170Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.263450Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.262704Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4137e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.265210&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.231073&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/find-eventual-safe-states/submissions/1241269468
def eventualSafeNodesBFS(V: int, graph: list[list[int]]) -> list[int]:
    """
    1. Reverse all edges and perform a topo sort.
    2. All unsafe elements are auto eliminated.

    The way Kahn's algorithm works is to BFS across the nodes with indegree 0 and eliminating the edges one by one.
    By swapping the edges we get terminal nodes to have an indegree of 0 (outdegree was 0 initially).

    We traverse until we cover all nodes that are connected to terminal nodes. Nodes that are not connected to terminal nodes are unsafe.

    Time: O(V log V), Space: O(V + E)
    """

    # Swap the edges, compute the indegree
    indegree: dict[int, int] = dict()
    adj: dict[int, list[int]] = dict()
    for n1 in range(V):
        for n2 in graph[n1]:
            n2_neighbours = adj.get(n2, [])
            n2_neighbours.append(n1)
            adj[n2] = n2_neighbours
            indegree[n1] = indegree.get(n1, 0) + 1

    # Store all nodes with 0 indegree to our queue
    queue: collections.deque = collections.deque()
    for n1 in range(V):
        if n1 not in indegree:
            indegree[n1] = 0
            queue.append(n1)

    # Do a BFS traversal
    result: list[int] = []
    while queue:
        n1 = queue.popleft()
        result.append(n1)
        for n2 in adj.get(n1, []):
            indegree[n2] -= 1
            if indegree[n2] == 0:
                queue.append(n2)

    return sorted(result)

# Testing the solution
assert eventualSafeNodesBFS(7, [[1, 2], [2, 3], [5], [0], [5], [], []]) == [2, 4, 5, 6]
assert eventualSafeNodesBFS(4, [[1], [2], [0,3], []]) == [3]
```

</div>

<div id="08156d76" class="cell markdown"
papermill="{&quot;duration&quot;:2.1029e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.307507&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.286478&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/U3N_je7tWAs?si=ZkvYEfyaDOVehnEa> Alien
Dictionary

</div>

<div id="42166b86" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.351145Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.350493Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.363307Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.362443Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6592e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.365066&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.328474&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def alienDictionaryOrder(alien_dict: list[str], N: int, K: int) -> list[str]:
    """
    Define a function that given two strings inorder as they appear in dictionary, can calculate relative ordering of characters in it.
    Run the above function across all words in the dictionary (all possible pairs) to get the edges of the graph.

    Once the relative ordering is captured, perform a topo sort.

    Follow up: What if the dictionary is incorrect?
    Check 1: String of larger length say: "abc" appears before string of smaller length: "ab" (char are matching until min length)
    Check 2: If there is a cycle: ["abc", "bcd", "ade"] (when inserting an edge to adj, we can check if opp edge doesn't exist: a -> b exists, then b -> a should not exist)
    """

    adj: dict[str, set[str]] = dict()
    nodes: list[str] = [chr(i + ord('a')) for i in range(K)]
    def computeOrdering(str1: str, str2: str):
        N1, N2 = len(str1), len(str2)
        i = 0
        while i < N1 and i < N2:
            n1, n2 = str1[i], str2[i]
            i += 1
            if n1 != n2:
                n1_neighbours = adj.get(n1, set())
                n1_neighbours.add(n2)
                adj[n1] = n1_neighbours
                return

    # Compute ordering for all pairs
    for i in range(N - 1):
        computeOrdering(alien_dict[i], alien_dict[i + 1])

    # Compute the indegree
    indegree: dict[str, int] = dict()
    for k in adj:
        for v in adj[k]:
            indegree[v] = indegree.get(v, 0) + 1

    # Store all nodes with 0 indegree to queue
    queue: collections.deque = collections.deque()
    for curr in nodes:
        if curr not in indegree:
            indegree[curr] = 0
            queue.append(curr)

    result: list[str] = []
    while queue:
        curr = queue.popleft()
        result.append(curr)
        for next_ in adj.get(curr, []):
            indegree[next_] -= 1
            if indegree[next_] == 0:
                queue.append(next_)

    return result

# Testing the solution
print(alienDictionaryOrder(["baa","abcd","abca","cab","cad"], 5, 4))
print(alienDictionaryOrder(["caa","aaa","aab"], 3, 3))
```

<div class="output stream stdout">

    ['b', 'd', 'a', 'c']
    ['c', 'a', 'b']

</div>

</div>

<div id="ddb547c5" class="cell markdown"
papermill="{&quot;duration&quot;:2.0805e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.407066&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.386261&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ZUFQfFaU-8U?si=SRwWuuRJN53CMn_w> Shortest
path in DAG (topological sorting)

</div>

<div id="29f9d887" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.452419Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.451712Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.464635Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.463983Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.8011e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.466334&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.428323&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def shortestPathInDAG(N: int, edges: list[list[int]], src: int) -> list[int]:
    """
    1. Do a topo sort: DFS (stack).
    2. Take nodes out of the stack and relax the edges.

    Topo sorted stack works before we start with the guy that doesn't have any nodes before it.
    As we progress into the stack, we would have travelled sequentially and nodes that comes before have already been computed.
    """

    # Create the adjacency list out of the edges provided
    adj: dict[int, list[tuple[int, int]]] = dict()
    for n1, n2, w in edges:
        n1_neighbours = adj.get(n1, [])
        n1_neighbours.append((n2, w))
        adj[n1] = n1_neighbours

    # Perform a Topo sort and store result to stack
    def topoDFS(root: int):
        if root not in visited:
            visited.add(root)
            for next_, _ in adj.get(root, []):
                topoDFS(next_)
            stack.append(root)

    stack: list[int] = []
    visited: set[int] = set()
    for curr in range(N):
        topoDFS(curr)

    # No appending to stack, simply continue popping and relax the edges
    result: list[float] = [math.inf for _ in range(N)]
    result[src] = 0
    while stack:
        curr = stack.pop()
        for next_, next_dist in adj.get(curr, []):
            result[next_] = min(result[curr] + next_dist, result[next_])

    for i in range(N):
        result[i] = result[i] if math.isfinite(result[i]) else -1

    return list(map(int, result))

# Testing the solution
assert shortestPathInDAG(3, [[0,1,2], [1,2,3], [0,2,6]], 0) == [0, 2, 5]
assert shortestPathInDAG(3, [[2,0,4],[0,1,3],[2,1,2]], 0) == [0, 3, -1]
```

</div>

<div id="59089a00" class="cell markdown"
papermill="{&quot;duration&quot;:2.0845e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.508368&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.487523&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest path in undirected graph with unit weights

</div>

<div id="685cf4ef" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.552427Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.551668Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.563595Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.562961Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5819e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.565254&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.529435&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Video link: https://youtu.be/C4gxoTaI71U?si=NQRmSQ7skeZnz9V0
def shortestPath(edges: list[list[int]], N: int, M: int, src: int) -> list[int]:
    # Create an adjacency list
    adj: dict[int, list[int]] = dict()
    for n1, n2 in edges:
        n1_neighbours, n2_neighbours = adj.get(n1, []), adj.get(n2, [])
        n1_neighbours.append(n2)
        n2_neighbours.append(n1)
        adj[n1], adj[n2] = n1_neighbours, n2_neighbours

    # Perform a DFS traversal starting from source
    def DFS(root: int, dist: int):
        if distances[root] == -1 or distances[root] > dist:
            distances[root] = dist
            for next_ in adj.get(root, []):
                DFS(next_, dist + 1)

    # Perform BFS, only visit nodes not already visited, that way the shortest distance would already be saved.
    # Since all edges are unit dist, we are guaranteed not to get a shorter distance.
    def BFS(root: int):
        queue: collections.deque = collections.deque([root])
        distances[root] = 0
        while queue:
            curr = queue.popleft()
            for next_ in adj.get(curr, []):
                if distances[next_] == -1:
                    queue.append(next_)
                    distances[next_] = distances[curr] + 1

    distances: list[int] = [-1 for _ in range(N)]
    # DFS(src, 0)
    BFS(src)
    return distances

# Testing the solution
assert shortestPath([[0,1],[0,3],[3,4],[4,5],[5,6],[1,2],[2,6],[6,7],[7,8],[6,8]], 9, 10, 0) == [0,1,2,1,2,3,3,4,4]
assert shortestPath([[0,0],[1,1],[1,3],[3,0]], 4, 4, 3) == [1,1,-1,0]
```

</div>

<div id="0dee3c9a" class="cell markdown"
papermill="{&quot;duration&quot;:2.1036e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.607703&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.586667&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Word Ladder - 1:
<https://leetcode.com/problems/word-ladder/submissions/1242529557> Video
Link: <https://youtu.be/tRPda0rcf8E?si=IvDpS_6OSFIa-iAY>

</div>

<div id="ef9ed676" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.651580Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.651045Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.660210Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.659582Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3056e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.661898&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.628842&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def ladderLength(beginWord: str, endWord: str, wordList: list[str]) -> int:
    """Time: O(N x len(word) * 26), Space: O(len(word))"""

    # Compute length of all strings
    N: int = len(beginWord)

    # Create a hashmap for quick lookups
    wordMap: dict[str, int] = {word: 0 for word in wordList}
    wordMap[beginWord] = 1

    # BFS to find out the sequence length of transformation
    queue: collections.deque = collections.deque([(beginWord, 1)])
    while queue:
        curr, dist = queue.popleft()

        # Generate all possible transformations (1 char changes)
        for i in range(N):
            for j in range(ord('a'), ord('z') + 1):
                next_ = curr[:i] + chr(j) + curr[i + 1:]
                if next_ in wordMap and wordMap[next_] == 0:
                    wordMap[next_] = dist + 1
                    queue.append((next_, dist + 1))

    # endWord may or may not exist, return 0 if not found
    return wordMap.get(endWord, 0)

# Testing the solution
assert ladderLength("hit", "cog", ["hot","dot","dog","lot","log","cog"]) == 5
assert ladderLength("hit", "cog", ["hot","dot","dog","lot","log"]) == 0
```

</div>

<div id="d0da149f" class="cell markdown"
papermill="{&quot;duration&quot;:2.1126e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.704064&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.682938&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/DREutrv2XD0?si=SbXR_WrwV0yPkM3t> Word
Ladder - 2: <https://leetcode.com/problems/word-ladder-ii/description/>

</div>

<div id="8c81ef46" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.748485Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.747792Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.760576Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.759961Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6897e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.762301&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.725404&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# TLE :(
def findLaddersBetter(beginWord: str, endWord: str, wordList: list[str]) -> list[list[str]]:
    # Compute the length of words
    N = len(beginWord)

    # Convert list to set for constant lookup times
    wordSet: set[str] = set(wordList)

    # Store the results to a list
    results: list[list[str]] = []

    # Do a DFS traversal, we only remove elements with wordSet of completion of a level
    queue: list[list[str]] = [[beginWord]]
    while queue and wordSet:
        next_queue: list[list[str]] = []
        to_remove: set[str] = set()
        for path in queue:
            curr = path[-1]
            for i in range(N):
                for j in range(ord('a'), ord('z') + 1):
                    next_ = curr[:i] + chr(j) + curr[i + 1:]
                    if next_ in wordSet:
                        path.append(next_)
                        path_ = list(path)
                        next_queue.append(path_)
                        to_remove.add(next_)
                        if next_ == endWord:
                            results.append(path_)
                        path.pop()

        for next_ in to_remove:
            wordSet.remove(next_)
        queue = next_queue

    return sorted(results)

# Testing the solution
assert findLaddersBetter("hit", "cog", ["hot","dot","dog","lot","log","cog"]) == [['hit', 'hot', 'dot', 'dog', 'cog'], ['hit', 'hot', 'lot', 'log', 'cog']]
assert findLaddersBetter("hit", "cog", ["hot","dot","dog","lot","log"]) == []
assert findLaddersBetter("a", "c", ["a", "b", "c"]) == [["a", "c"]]
assert findLaddersBetter("red", "tax", ["ted","tex","red","tax","tad","den","rex","pee"]) == [['red', 'rex', 'tex', 'tax'],['red', 'ted', 'tad', 'tax'],['red', 'ted', 'tex', 'tax']]
```

</div>

<div id="184290e3" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.806930Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.806425Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.821346Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.820507Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.9402e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.823113&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.783711&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Striver Leetcode optimized: https://leetcode.com/problems/word-ladder-ii/submissions/1242920059
def findLadders(beginWord: str, endWord: str, wordList: list[str]) -> list[list[str]]:
    """
    Video link: https://youtu.be/AD4SFl7tu7I?si=koBVo4hgse94Ruvn

    Step 1: BFS and compute the shortest distance to words.
    Step 2: Backtrack from backwards and only traverse to paths that are curr level - 1.

    This works better because we are starting backwards and thus the exploration of paths would be minimal.
    Further more we only take up paths which are one level below not more not less.
    """

    N = len(beginWord)

    # Store the shortest distances to reach word
    distances: dict[str, float] = {word: math.inf for word in wordList}
    distances[beginWord] = 0

    # BFS traversal
    queue: collections.deque = collections.deque([beginWord])
    while queue:
        curr = queue.popleft()
        for i in range(N):
            for j in range(ord('a'), ord('z') + 1):
                next_ = curr[:i] + chr(j) + curr[i + 1:]
                if next_ in distances and distances[curr] + 1 < distances[next_]:
                    distances[next_] = distances[curr] + 1
                    queue.append(next_)

    # Backtrack and find the shortest paths with DFS
    results: list[list[str]] = []
    def DFS(root: str, paths: list[str]):
        if root not in distances or math.isinf(distances[root]):
            return
        elif root == beginWord:
            results.append(paths)
            return
        else:
            for i in range(N):
                for j in range(ord('a'), ord('z') + 1):
                    next_ = root[:i] + chr(j) + root[i + 1:]
                    if distances.get(next_, -1) == distances[root] - 1:
                        DFS(next_, [next_, *paths])

    DFS(endWord, [endWord])
    return sorted(results)

# Testing the solution
assert findLadders("hit", "cog", ["hot","dot","dog","lot","log","cog"]) == [['hit', 'hot', 'dot', 'dog', 'cog'], ['hit', 'hot', 'lot', 'log', 'cog']]
assert findLadders("hit", "cog", ["hot","dot","dog","lot","log"]) == []
assert findLadders("a", "c", ["a", "b", "c"]) == [["a", "c"]]
assert findLadders("red", "tax", ["ted","tex","red","tax","tad","den","rex","pee"]) == [['red', 'rex', 'tex', 'tax'],['red', 'ted', 'tad', 'tax'],['red', 'ted', 'tex', 'tax']]
```

</div>

<div id="ac91aeb8" class="cell markdown"
papermill="{&quot;duration&quot;:2.1292e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.866125&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.844833&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Dijkstra's Algorithm using Min Heap:
<https://youtu.be/V6H1qAeB-l4?si=rEGFRGwu-ojsYp-3>

</div>

<div id="f9b1c99b" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:21.910477Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:21.909913Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:21.918130Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:21.917453Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2379e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.919807&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.887428&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def dijkstra(V: int, adj: list[list[list[int]]], src: int):
    # Number of vertices
    N = len(adj)

    # Store all the distances into an array
    distances: list[int] = [-1 for _ in range(V)]
    distances[src] = 0

    # Apply Dijkstra
    min_heap: list[tuple[int, int]] = [(0, src)]
    while min_heap:
        curr_dist, curr = heapq.heappop(min_heap)
        for next_, next_dist in adj[curr]:
            if distances[next_] == -1 or distances[next_] > curr_dist + next_dist:
                distances[next_] = curr_dist + next_dist
                heapq.heappush(min_heap, (curr_dist + next_dist, next_))

    return distances

# Testing the solution
assert dijkstra(2, [[[1, 9]], [[0, 9]]], 0) == [0, 9]
assert dijkstra(3, [[[1, 1], [2, 6]], [[2, 3], [0, 1]], [[1, 3], [0, 6]]], 2) == [4, 3, 0]
```

</div>

<div id="1ef6f6db" class="cell markdown"
papermill="{&quot;duration&quot;:2.1173e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:21.962222&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.941049&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/rp1SMw7HSO8?si=7d4Jc-1NTMcKvbh8> Shortest
path in an undirected weighted graph

</div>

<div id="5fc33946" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.006162Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.005495Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.016699Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.016034Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5231e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.018401&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:21.983170&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def shortestPathGFG(V: int, E: int, edges: list[list[int]]) -> list[int]:
    # Convert the edges into an adjacency list
    adj: dict[int, list[tuple[int, int]]] = dict() # n1: (n2, w)
    for n1, n2, w in edges:
        n1_neighbours, n2_neighbours = adj.get(n1, []), adj.get(n2, [])
        n1_neighbours.append((n2, w))
        n2_neighbours.append((n1, w))
        adj[n1], adj[n2] = n1_neighbours, n2_neighbours

    # Apply Dijkstra algorithm, store the shortest distances to a hashmap, also store the previous node
    distances: dict[int, tuple[int, int]] = {n1: (-1, -1) for n1 in range(V + 1)} # node: (dist, prev)
    distances[1] = (0, -1)
    heap: list[tuple[int, int]] = [(0, 1)] # dist, node
    while heap:
        curr_dist, curr = heapq.heappop(heap)
        for next_, next_dist in adj.get(curr, []):
            if distances[next_][0] == -1 or distances[next_][0] > curr_dist + next_dist:
                distances[next_] = (curr_dist + next_dist, curr)
                heapq.heappush(heap, (curr_dist + next_dist, next_))

    dist = distances[V]
    if dist[0] == -1:
        return [-1]
    else:
        result = [V]
        curr = dist[1]
        while curr != -1:
            result.append(curr)
            curr = distances[curr][1]

        result.append(dist[0])
        result.reverse()
        return result

# Testing the solution
assert shortestPathGFG(5, 6, [[1,2,2], [2,5,5], [2,3,4], [1,4,1],[4,3,3],[3,5,1]]) == [5, 1, 4, 3, 5]
```

</div>

<div id="6de11f44" class="cell markdown"
papermill="{&quot;duration&quot;:2.118e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.061076&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.039896&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest path in a binary maze:
<https://leetcode.com/problems/shortest-path-in-binary-matrix/submissions/1243256372/>
Video Link: <https://youtu.be/U5Mw4eyUmw4?si=SM3SONUWEFwd8XLt>

</div>

<div id="2f855e08" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.105319Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.104584Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.114843Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.114083Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4691e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.116687&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.081996&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def shortestPathBinaryMatrix(grid: list[list[int]]) -> int:
    """
    A priority queue is only needed when we are having weighted graphs.
    Since we have a unit weights, we can use a simple queue.

    Time: O(N ^ 2), Space: O(N ^ 2)
    """

    N = len(grid)
    distances: list[list[float]] = [[math.inf for i in range(N)] for j in range(N)]
    distances[0][0] = 1
    queue: collections.deque[tuple[tuple[int, int], float]] = collections.deque([((0, 0), 1.)])
    while queue:
        curr, dist = queue.popleft()
        for x in range(-1, 2):
            for y in range(-1, 2):
                i, j = curr[0] + x, curr[1] + y
                if 0 <= i < N and 0 <= j < N and grid[i][j] == 0 and distances[i][j] > dist + 1:
                    distances[i][j] = dist + 1
                    queue.append(((i, j), dist + 1))

    result = distances[N - 1][N - 1]
    return int(result) if grid[0][0] == 0 and not math.isinf(result) else -1

# Testing the solution
assert shortestPathBinaryMatrix([[0,0,0],[1,1,0],[1,1,0]]) == 4
assert shortestPathBinaryMatrix([[0,1],[1,0]]) == 2
assert shortestPathBinaryMatrix([[1,0,0],[1,1,0],[1,1,0]]) == -1
assert shortestPathBinaryMatrix([[1]]) == -1
```

</div>

<div id="52e6e87d" class="cell markdown"
papermill="{&quot;duration&quot;:2.1012e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.158901&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.137889&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/0ytpZyiZFhA?si=UwEDE7wIpbT_Q87y> Path with
minimum effort:
<https://leetcode.com/problems/path-with-minimum-effort/submissions/1243926425/>

</div>

<div id="85a0590c" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.203065Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.202415Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.213876Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.213116Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5312e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.215532&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.180220&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimumEffortPath(heights: list[list[int]]) -> int:
    """
    Time: O(M x N x log (M x N)), Space: O(M x N).

    Apparantly from striver: once we reach our destination we can return the dist.
    We should however check while taking out of PQ and not while inserting into PQ.
    """
    # Compute the dimensions
    N, M = len(heights), len(heights[0])

    # Store the efforts into a 2D matrix
    efforts: list[list[float]] = [[math.inf for j in range(M)] for i in range(N)]
    efforts[0][0] = 0

    # Apply Dijkstra, create a heap datastructure
    heap: list[tuple[float, tuple[int, int]]] = [(0., (0, 0))]
    while heap:
        curr_effort, curr = heapq.heappop(heap)
        for x, y in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            i, j = curr[0] + x, curr[1] + y
            next_effort = max(abs(heights[i][j] - heights[curr[0]][curr[1]]) if 0 <= i < N and 0 <= j < M else math.inf, curr_effort)
            if not math.isinf(next_effort) and next_effort < efforts[i][j]:
                efforts[i][j] = next_effort
                heapq.heappush(heap, (next_effort, (i, j)))

    result = efforts[N - 1][M - 1]
    return int(result) if not math.isinf(result) else -1

# Testing the solution
assert minimumEffortPath([[1,2,2],[3,8,2],[5,3,5]]) == 2
assert minimumEffortPath([[1,2,3],[3,8,4],[5,3,5]]) == 1
assert minimumEffortPath([[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]) == 0
```

</div>

<div id="ba06d57b" class="cell markdown"
papermill="{&quot;duration&quot;:2.1096e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.258097&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.237001&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Cheapest flight within K stops:
<https://leetcode.com/problems/cheapest-flights-within-k-stops/submissions/1244248580>
Video Link: <https://youtu.be/9XybHVqTHcQ?si=jLIB9G9VQ184S2w6>

</div>

<div id="53b3f2f6" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.301953Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.301340Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.313464Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.312800Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5959e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.315180&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.279221&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def findCheapestPrice(n: int, flights: list[list[int]], src: int, dst: int, k: int) -> int:
    """
    The trick here is to realize that if we made dist our priority, dijkstra would find the shortest path sooner even if it costs us a lot of steps preventing us from proceeding further.
    To overcome this, we prioritize steps over distance. This way even if we aren't travelling to the shortest distance first, we still would be able to traverse the full breadth of k.

    PQ can be steps, dist, node

    Time: O(len(flights) log N)
    Space: O(len(flights))
    """
    # Create an adjaceny list out of the edges
    adj: dict[int, list[tuple[int, float]]] = dict()
    for n1, n2, w in flights:
        n1_neighbours = adj.get(n1, [])
        n1_neighbours.append((n2, w))
        adj[n1] = n1_neighbours

    # Compute the distances and store to a dictionary
    distances: dict[int, float] = {n1: math.inf for n1 in range(n)}
    distances[src] = 0

    # Apply Dijkstra with slight modification - store the stops to reach the destination as well: steps, dist, node
    heap: list[tuple[int, float, int]] = [(0, 0., src)]
    while heap:
        curr_steps, curr_dist, curr = heapq.heappop(heap)
        for next_, next_dist in adj.get(curr, []):
            if curr_dist + next_dist < distances[next_] and curr_steps <= k:
                distances[next_] = curr_dist + next_dist
                heapq.heappush(heap, (curr_steps + 1, curr_dist + next_dist, next_))

    result = distances[dst]
    return int(result) if not math.isinf(result) else -1

# Testing the solution
assert findCheapestPrice(n=4, flights=[[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src=0, dst=3, k=1) == 700
assert findCheapestPrice(n=3, flights=[[0,1,100],[1,2,100],[0,2,500]], src=0, dst=2, k=1) == 200
assert findCheapestPrice(n=5, flights=[[0,1,5],[1,2,5],[0,3,2],[3,1,2],[1,4,1],[4,2,1]], src=0, dst=2, k=2) == 7
```

</div>

<div id="f0f3185e" class="cell markdown"
papermill="{&quot;duration&quot;:2.1412e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.357984&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.336572&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Minimum Operations Video link:
<https://youtu.be/_BvEJ3VIDWw?si=0Kgpj58X7BYexE2k>

</div>

<div id="a5556478" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.401903Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.401205Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.415896Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.415137Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.8439e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.417627&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.379188&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimumOperations(N: int, start: int, end: int, arr: list[int]) -> int:
    distances: dict[int, float] = {n1: math.inf for n1 in range(0, int(1e3) + 1)}
    distances[start] = 0

    queue: collections.deque[tuple[int, int]] = collections.deque([(start, 0)])
    while queue:
        curr, dist = queue.popleft()
        for edge in arr:
            next_ = (curr * edge) % 1000
            if dist + 1 < distances[next_]:
                distances[next_] = dist + 1
                queue.append((next_, dist + 1))

    result = distances[end]
    return int(result) if not math.isinf(result) else -1

assert minimumOperations(2, 1, 12, [3, 2]) == 3
assert minimumOperations(4, 8, 320, [4, 6, 1, 10]) == 2
assert minimumOperations(42, 54, 98, [1, 70, 25, 79, 59, 63, 65, 6, 46, 82, 28, 62, 92, 96, 43, 28, 37, 92, 5, 3, 54, 93, 83, 22, 17, 19, 96, 48, 27, 72, 39, 70, 13, 68, 100, 36, 95, 4, 12, 23, 34, 74]) == 3
```

</div>

<div id="a12fb431" class="cell markdown"
papermill="{&quot;duration&quot;:2.1364e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.460551&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.439187&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/_-0mx0SmYxA?si=6GOaqZSP-NDZ_Oq-> Number of
ways to arrive at a destination

</div>

<div id="6d28c0b9" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.504937Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.504430Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.521480Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.520704Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.1806e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.523290&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.481484&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/submissions/1244856247/
def countPaths(N: int, roads: list[list[int]]) -> int:
    # Convert edges to adjacency list
    adj: dict[int, list[tuple[int, float]]] = dict()
    for n1, n2, w in roads:
        n1_neighbours, n2_neighbours = adj.get(n1, []), adj.get(n2, [])
        n1_neighbours.append((n2, w))
        n2_neighbours.append((n1, w))
        adj[n1] = n1_neighbours
        adj[n2] = n2_neighbours

    # Distances to store a set of prev nodes with shortest distance
    distances: dict[int, tuple[float, set[int]]] = {n1: (math.inf, set()) for n1 in range(N)}
    distances[0] = (0, set())

    # Apply Dijkstra algorithm to find the shortest paths
    heap: list[tuple[float, int]] = [(0, 0)]
    while heap:
        curr_dist, curr = heapq.heappop(heap)
        for next_, next_dist in adj.get(curr, []):
            if next_dist + curr_dist < distances[next_][0]:
                distances[next_] = (next_dist + curr_dist, {curr})
                heapq.heappush(heap, (next_dist + curr_dist, next_))
            elif next_dist + curr_dist == distances[next_][0]:
                distances[next_][1].add(curr)

    @functools.cache
    def backtrack(root: int) -> int:
        if root == 0:
            return 1
        else:
            count = 0
            for next_ in distances[root][1]:
                count += backtrack(next_)
            return count

    return backtrack(N - 1) % (int(1e9) + 7)

# Testing the solution
countPaths(7, [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]) == 4
```

<div class="output execute_result" execution_count="36">

    True

</div>

</div>

<div id="ef161cf7" class="cell code" execution_count="37"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.569043Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.568390Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.579674Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.579030Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5929e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.581428&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.545499&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/submissions/1244866094
def countPathsStriver(N: int, roads: list[list[int]]) -> int:
    # Convert edges to adjacency list
    adj: dict[int, list[tuple[int, float]]] = dict()
    for n1, n2, w in roads:
        n1_neighbours, n2_neighbours = adj.get(n1, []), adj.get(n2, [])
        n1_neighbours.append((n2, w))
        n2_neighbours.append((n1, w))
        adj[n1] = n1_neighbours
        adj[n2] = n2_neighbours

    # Distances to store a shortest distance for each node along with the count of shortest paths
    distances: dict[int, tuple[float, int]] = {n1: (math.inf, 0) for n1 in range(N)}
    distances[0] = (0, 1)

    # Apply dijkstra algorithm
    heap: list[tuple[float, int]] = [(0., 0)]
    while heap:
        curr_dist, curr = heapq.heappop(heap)
        for next_, next_dist in adj.get(curr, []):
            if curr_dist + next_dist < distances[next_][0]:
                distances[next_] = (curr_dist + next_dist, distances[curr][1])
                heapq.heappush(heap, (curr_dist + next_dist, next_))
            elif curr_dist + next_dist == distances[next_][0]:
                distances[next_] = (curr_dist + next_dist, distances[next_][1] + distances[curr][1])

    return int(distances[N - 1][1])

# Testing the solution
assert countPathsStriver(7, [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]) == 4
```

</div>

<div id="b3016690" class="cell markdown"
papermill="{&quot;duration&quot;:2.1167e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.624126&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.602959&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=0vVofAhAYjc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=166>
Bellman Ford Algorithm

</div>

<div id="246f039f" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.668688Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.668064Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.675121Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.674345Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1205e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.676816&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.645611&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def bellman_ford(V: int, edges: list[list[int]], S: int) -> list[float]:
    # Store the results to distance vector
    distances: list[float] = [math.inf for n1 in range(V)]
    distances[S] = 0

    # Relax for V - 1 iterations
    for i in range(V - 1):
        for n1, n2, w in edges:
            distances[n2] = min(distances[n2], distances[n1] + w)

    # Check for cycle by relaxing 1 more time
    for n1, n2, w in edges:
        if distances[n1] + w < distances[n2]:
            return [-1]

    # No cycles, we are good to return
    return distances

# Testing the solution
assert bellman_ford(3, [[0,1,5],[1,0,3],[1,2,-1],[2,0,1]], 2) == [1, 6, 0]
```

</div>

<div id="b07a5eb6" class="cell markdown"
papermill="{&quot;duration&quot;:2.1417e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.719765&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.698348&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/YbY8cVwWAvw?si=_Soo7iiwWihY5G8w> Floyd
Warshall Algorithm

</div>

<div id="53a5b83f" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.763984Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.763404Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.773387Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.772641Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3955e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.774976&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.741021&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def floyd_warshall(matrix: list[list[int]]) -> list[list[int]]:
    "Time: O(V ^ 3), Space: O(V ^ 2)"
    V = len(matrix)
    cost: list[list[int]] = [[matrix[i][j] for j in range(V)] for i in range(V)]

    # For each node i -> j check if the path i -> k -> j could be a better path
    for via in range(V):
        for i in range(V):
            for j in range(V):
                if cost[i][via] != -1 and cost[via][j] != -1 and cost[i][j] > cost[i][via] + cost[via][j]:
                    cost[i][j] = cost[i][via] + cost[via][j]

    return cost

# Testing the solution
floyd_warshall([[0,1,43],[1,0,6],[-1,-1,0]])
```

<div class="output execute_result" execution_count="39">

    [[0, 1, 7], [1, 0, 6], [-1, -1, 0]]

</div>

</div>

<div id="e45383b2" class="cell markdown"
papermill="{&quot;duration&quot;:2.1339e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.817913&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.796574&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/PwMVNSJ5SLI?si=AbyQbGEgwGWk6lPZ> City with
smallest number of neighbours at threshold

</div>

<div id="2407a370" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.862157Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.861752Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.874335Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.873642Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6767e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.875999&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.839232&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/submissions/1244969227/
def findTheCity(N: int, edges: list[list[int]], distanceThreshold: int) -> int:
    # We would be running dijkstra on all nodes and storing to this array
    distances: list[list[float]] = [[math.inf if i != j else 0 for j in range(N)] for i in range(N)]

    # Function to run Dijkstra
    def dijkstra(src: int):
        nonlocal distances
        heap: list[tuple[float, int]] = [(0, src)]
        while heap:
            curr_dist, curr = heapq.heappop(heap)
            for next_, next_dist in adj.get(curr, []):
                if curr_dist + next_dist < distances[src][next_]:
                    distances[src][next_] = curr_dist + next_dist
                    heapq.heappush(heap, (curr_dist + next_dist, next_))

    # Convert edges to adj list
    adj: dict[int, list[tuple[int, int]]] = dict()
    for n1, n2, w in edges:
        n1_neighbours, n2_neighbours = adj.get(n1, []), adj.get(n2, [])
        n1_neighbours.append((n2, w))
        n2_neighbours.append((n1, w))
        adj[n1], adj[n2] = n1_neighbours, n2_neighbours

    # Run Dijkstra algorithm for all nodes
    for curr in range(N):
        dijkstra(curr)

    # Starting backwards find the city with smallest neighbouring cities at threshold
    minCity, minCount = -1, math.inf
    for curr in range(N - 1, -1, -1):
        count = 0
        for dist in distances[curr]:
            if 0 < dist <= distanceThreshold:
                count += 1
        if count < minCount:
            minCount = count
            minCity = curr

    return minCity

# Testing the solution
assert findTheCity(5, [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], 2) == 0
assert findTheCity(4, [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], 4) == 3
```

</div>

<div id="bdfd48db" class="cell markdown"
papermill="{&quot;duration&quot;:2.136e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.918906&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.897546&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Prim's algorithm Video Link:
<https://youtu.be/mJcZjjKzeqk?si=64UoFQXWB8rjf2iB>

1.  Initial Config: Priority Queue, Visited array, MST weight sum, MST
    list storing all edges part of MST
2.  Start with any node: (weight, node, parent) =\> (0, 0, -1). Visited
    array is NOT MARKED for that node.
3.  Mark them as visited when you are visiting the node from PQ. Add the
    edge weight to sum and add the edges to the MST list. Iterate
    through all the adjancent edges and add to our PQ.
4.  Repeat until PQ is empty.
5.  Prim's algorithm is a greedy algorithm.

</div>

<div id="08777d03" class="cell code" execution_count="41"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:22.963343Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:22.962815Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:22.975912Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:22.975161Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.736e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:22.977512&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.940152&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimumSpanningTreePrim(edges: list[tuple[int, int, int]], V: int, E: int) -> int:
    """Time: O(E log E), Space: O(V)"""

    # Create an adjacency list
    adj: dict[int, list[tuple[int, int]]] = dict()
    for n1, n2, w in edges:
        n1_neighbours, n2_neighbours = adj.get(n1, []), adj.get(n2, [])
        n1_neighbours.append((n2, w))
        n2_neighbours.append((n1, w))
        adj[n1], adj[n2] = n1_neighbours, n2_neighbours

    # Initial config
    visited: set[int] = set()
    heap: list[tuple[int, int, int]] = [(0, 0, -1)] # weight, curr, parent
    mst: list[tuple[int, int, int]] = []
    mst_weight: int = 0

    while heap:
        curr_weight, curr, prev = heapq.heappop(heap)
        if curr not in visited:
            if prev != -1:
                mst_weight += curr_weight
                mst.append((prev, curr, curr_weight))

            visited.add(curr)
            for next_, next_weight in adj.get(curr, []):
                heapq.heappush(heap, (next_weight, next_, curr))

    print(mst)
    return mst_weight

# Testing the solution
minimumSpanningTreePrim([(0, 1, 3), (0, 3, 5), (1, 2, 1), (2, 3, 8)], 4, 4)
```

<div class="output stream stdout">

    [(0, 1, 3), (1, 2, 1), (0, 3, 5)]

</div>

<div class="output execute_result" execution_count="41">

    9

</div>

</div>

<div id="388bd0af" class="cell markdown"
papermill="{&quot;duration&quot;:2.1523e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.021123&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:22.999600&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Disjoint set data structure

</div>

<div id="7b48003b" class="cell code" execution_count="42"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:23.065898Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:23.065143Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:23.079484Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:23.078843Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.858e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.081101&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.042521&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class DisjointSet:
    def __init__(self, V: int):
        self.rank: list[int] = [0 for i in range(V + 1)]
        self.size: list[int] = [1 for i in range(V + 1)]
        self.parent = [i for i in range(V + 1)]

    def findUltimateParent(self, node: int) -> int:
        """Recursively find the parent, once found do a path compression"""
        if self.parent[node] == node:
            return node
        else:
            self.parent[node] = self.findUltimateParent(self.parent[node])
            return self.parent[node]

    def unionBySize(self, u: int, v: int):
        # Find the ultimate parent of U, V
        up, vp = self.findUltimateParent(u), self.findUltimateParent(v)

        # Find the size of the ultimate parents
        ups, vps = self.size[up], self.size[vp]

        # Both are already connected, do nothing
        if up == vp:
            return

        # Ultimate parent of U has a smaller size, update parent of UP to V
        elif ups < vps:
            self.parent[up] = v
            self.size[vp] += self.size[up]

        # Ultimate parent of V has a smaller size, update parent of VP to U
        else:
            self.parent[vp] = u
            self.size[up] += self.size[vp]

    def unionByRank(self, u: int, v: int):
        # Find the ultimate parents of u, v
        up, vp = self.findUltimateParent(u), self.findUltimateParent(v)

        # Find the ranks of the ultimate parents
        upr, vpr = self.rank[up], self.rank[vp]

        # If both ultimate parents are the same, the edge makes no difference
        if up == vp:
            return

        # If rank of vp is smaller, the parent of vp is set to up
        elif vpr < upr:
            self.parent[vp] = up

        # If rank of up is smaller, the parent of up is set to vp
        elif upr < vpr:
            self.parent[up] = vp

        # If rank of both are equal, we join anyone to anyone and increment rank of the parent
        else:
            self.parent[up] = vp
            self.rank[vp] += 1

# Testing the solution
ds: DisjointSet = DisjointSet(7)

ds.unionBySize(1, 2)
ds.unionBySize(2, 3)
ds.unionBySize(4, 5)
ds.unionBySize(6, 7)
ds.unionBySize(5, 6)

# Check if 3 and 7 are part of the same component
print("Same component" if ds.findUltimateParent(3) == ds.findUltimateParent(7) else "Diff component")

ds.unionBySize(3, 7)
print("Same component" if ds.findUltimateParent(3) == ds.findUltimateParent(7) else "Diff component")
```

<div class="output stream stdout">

    Diff component
    Same component

</div>

</div>

<div id="c3e65c2d" class="cell markdown"
papermill="{&quot;duration&quot;:2.2474e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.125393&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.102919&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find number of provinces (using disjoint set)

</div>

<div id="fc2419f0" class="cell code" execution_count="43"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:23.171016Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:23.170278Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:23.177135Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:23.176385Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1708e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.178983&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.147275&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def numProvinces(adj: list[list[int]], V: int):
    ds: DisjointSet = DisjointSet(V - 1)
    for i in range(V):
        for j in range(V):
            if adj[i][j]:
                ds.unionBySize(i, j)

    # Not advisable since we may or may not have compressed it
    # return len(set(ds.parent))

    result: set[int] = set()
    for node in range(V):
        result.add(ds.findUltimateParent(node))
    return len(result)

# Testing the solution
assert numProvinces([[1, 0, 1], [0, 1, 0], [1, 0, 1]], 3) == 2
assert numProvinces([[1, 1], [1, 1]], 2) == 1
```

</div>

<div id="3dc02bdf" class="cell markdown"
papermill="{&quot;duration&quot;:2.1777e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.222709&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.200932&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of operations to make network connected - DSU Video Link:
<https://youtu.be/FYrl7iz9_ZU?si=SctG8sU5N_L_FYUt> Problem link:
<https://leetcode.com/problems/number-of-operations-to-make-network-connected/submissions/1246593300>

</div>

<div id="a5d00525" class="cell code" execution_count="44"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:23.267799Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:23.267169Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:23.278762Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:23.278108Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6002e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.280371&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.244369&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def makeConnected(N: int, connections: list[list[int]]) -> int:
    # Create a disjoint set and create edges such that there is only one ultimate parent
    class DS:
        def __init__(self, V: int):
            self.parents = [i for i in range(V)]
            self.size = [1 for i in range(V)]

        def findUltimateParent(self, node: int) -> int:
            if self.parents[node] == node:
                return node
            else:
                self.parents[node] = self.findUltimateParent(self.parents[node])
                return self.parents[node]

        def unionBySize(self, u: int, v: int):
            up, vp = self.findUltimateParent(u), self.findUltimateParent(v)
            if up == vp:
                return
            elif self.size[up] < self.size[vp]:
                self.parents[up] = vp
                self.size[vp] += self.size[up]
            else:
                self.parents[vp] = up
                self.size[up] += self.size[vp]

    ds = DS(N)
    extra_connections = 0
    for n1, n2 in connections:
        if ds.findUltimateParent(n1) == ds.findUltimateParent(n2):
            extra_connections += 1
        else:
            ds.unionBySize(n1, n2)

    # Find the number of components
    components = set()
    for node in range(N):
        components.add(ds.findUltimateParent(node))

    result = len(components) - 1
    return result if result <= extra_connections else -1

# Testing the solution
assert makeConnected(4, [[0,1],[0,2],[1,2]]) == 1
assert makeConnected(6, [[0,1],[0,2],[0,3],[1,2],[1,3]]) == 2
assert makeConnected(6, [[0,1],[0,2],[0,3],[1,2]]) == -1
```

</div>

<div id="8030c685" class="cell markdown"
papermill="{&quot;duration&quot;:2.1556e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.323696&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.302140&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/FMwpt_aQOGw?si=ql3wSSNQsQKjwyts> Accounts
Merge: DSU

</div>

<div id="f37b2281" class="cell code" execution_count="45"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:23.368710Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:23.368019Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:23.384396Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:23.383748Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.0802e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.386057&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.345255&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def accountsMerge(accounts: list[list[str]]) -> list[list[str]]:
    class DS:
        def __init__(self) -> None:
            self.size: dict[str, int] = {}
            self.parent: dict[str, str] = {}

        def findUltimateParent(self, node: str) -> str:
            if node not in self.parent:
                self.parent[node] = node
                self.size[node] = 1

            if self.parent[node] == node:
                return node
            else:
                self.parent[node] = self.findUltimateParent(self.parent[node])
                return self.parent[node]

        def unionBySize(self, u: str, i: str) -> None:
            up, ip = self.findUltimateParent(u), self.findUltimateParent(i)
            ups, ips = self.size[up], self.size[ip]
            if up == ip:
                return
            elif ups <= ips:
                self.parent[up] = ip
                self.size[ip] += self.size[up]
            else:
                self.parent[ip] = up
                self.size[up] += self.size[ip]

    ds = DS()
    emails: dict[str, str] = dict()
    for i in range(len(accounts)):
        name = accounts[i][0]
        for email in accounts[i][1:]:
            emails[email] = name
            ds.unionBySize(email, str(i))

    result: list[list[str]] = [[] for _ in range(len(accounts))]
    for email in sorted(ds.parent.keys()):
        loc: int = int(ds.findUltimateParent(ds.parent[email]))
        if email in emails:
            if not result[loc]:
                result[loc].append(emails[email])
            result[loc].append(email)

    return list(filter(lambda x: len(x), result))

# Testing the solution
accountsMerge([
    ["John","johnsmith@mail.com","john_newyork@mail.com"],
    ["John","johnsmith@mail.com","john00@mail.com"],
    ["Mary","mary@mail.com"],
    ["John","johnnybravo@mail.com"]
])
```

<div class="output execute_result" execution_count="45">

    [['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],
     ['Mary', 'mary@mail.com'],
     ['John', 'johnnybravo@mail.com']]

</div>

</div>

<div id="c7f391b0" class="cell markdown"
papermill="{&quot;duration&quot;:2.2196e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.430266&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.408070&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of Islands - 2

</div>

<div id="1fbebc60" class="cell code" execution_count="46"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:23.475532Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:23.475227Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:23.492942Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:23.492183Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.3087e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.495077&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.451990&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def numOfIslands(rows: int, cols : int, operators : list[list[int]]) -> list[int]:
    class DS:
        def __init__(self, M: int, N: int):
            self.M, self.N = M, N
            self.parents: list[list[tuple[int, int]]] = [[(-1, -1) for j in range(N)] for i in range(M)]
            self.size: list[list[int]] = [[0 for j in range(N)] for i in range(M)]
            self.islands = 0

        def getUltimateParent(self, node: tuple[int, int]) -> tuple[int, int]:
            if self.parents[node[0]][node[1]] == node:
                return node
            else:
                self.parents[node[0]][node[1]] = self.getUltimateParent(self.parents[node[0]][node[1]])
                return self.parents[node[0]][node[1]]

        def union(self, n1: tuple[int, int]) -> int:
            if self.size[n1[0]][n1[1]] == 0:

                self.size[n1[0]][n1[1]] = 1
                self.parents[n1[0]][n1[1]] = (n1[0], n1[1])
                self.islands += 1

                for x, y in [(-1, 0), (0, -1), (0, 1), (1, 0)]:
                    n2 = n1[0] + x, n1[1] + y
                    if 0 <= n2[0] < self.M and 0 <= n2[1] < self.N and self.size[n2[0]][n2[1]] > 0:
                        n1p, n2p = self.getUltimateParent(n1), self.getUltimateParent(n2)
                        n1s, n2s = self.parents[n1p[0]][n1p[1]], self.parents[n2p[0]][n2p[1]]
                        if n1p != n2p:
                            self.islands -= 1
                            if n1s < n2s:
                                self.parents[n1p[0]][n1p[1]] = n2p
                                self.size[n2p[0]][n2p[1]] += self.size[n1p[0]][n1p[1]]
                            else:
                                self.parents[n2p[0]][n2p[1]] = n1p
                                self.size[n1p[0]][n1p[1]] += self.size[n2p[0]][n2p[1]]

            return self.islands

    results: list[int] = []
    ds = DS(rows, cols)
    for op in operators:
        results.append(ds.union((op[0], op[1])))

    return results

# Testing the solution
assert numOfIslands(4, 5, [[1,1],[0,1],[3,3],[3,4],[1,2],[2,3],[1,3]]) == [1, 1, 2, 2, 2, 2, 1]
assert numOfIslands(4, 5, [[0,0],[0,0],[1,1],[1,0],[0,1]]) == [1, 1, 2, 1, 1]
```

</div>

<div id="668325c8" class="cell markdown"
papermill="{&quot;duration&quot;:2.175e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.539763&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.518013&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/lgiz0Oup6gM?si=bsmknViNfMryXaX5> Making a
large island:
<https://leetcode.com/problems/making-a-large-island/submissions/1247859032>

</div>

<div id="b071d182" class="cell code" execution_count="47"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:23.585036Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:23.584390Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:23.603912Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:23.603156Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.4254e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.605755&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.561501&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def largestIsland(grid: list[list[int]]) -> int:
    class DS:
        def __init__(self, N: int):
            self.N = N
            self.size: list[list[int]] = [[0 for j in range(N)] for i in range(N)]
            self.parent: list[list[tuple[int, int]]] = [[(-1, -1) for j in range(N)] for i in range(N)]

        def findUltimateParent(self, node: tuple[int, int]) -> tuple[int, int]:
            if node == (-1, -1) or self.parent[node[0]][node[1]] == node:
                return node
            else:
                self.parent[node[0]][node[1]] = self.findUltimateParent(self.parent[node[0]][node[1]])
                return self.parent[node[0]][node[1]]

        def unionBySize(self, n1: tuple[int, int]):
            self.size[n1[0]][n1[1]] = 1
            self.parent[n1[0]][n1[1]] = n1

            for x, y in [(-1,0), (0,-1), (0,1), (1,0)]:
                n2 = n1[0] + x, n1[1] + y
                if 0 <= n2[0] < self.N and 0 <= n2[1] < self.N and self.size[n2[0]][n2[1]] > 0:
                    n1p, n2p = self.findUltimateParent(n1), self.findUltimateParent(n2)
                    n1s, n2s = self.size[n1p[0]][n1p[1]], self.size[n2p[0]][n2p[1]]
                    if n1p != n2p:
                        if n1s < n2s:
                            self.parent[n1p[0]][n1p[1]] = n2p
                            self.size[n2p[0]][n2p[1]] += self.size[n1p[0]][n1p[1]]
                        else:
                            self.parent[n2p[0]][n2p[1]] = n1p
                            self.size[n1p[0]][n1p[1]] += self.size[n2p[0]][n2p[1]]

    # Add to the Disjoint set datastructure
    N = len(grid)
    ds = DS(N)
    for i in range(N):
        for j in range(N):
            if grid[i][j]:
                ds.unionBySize((i, j))

    # Iterate through the grid, for each cell we check the max size of island flipping that cell would result in
    maxSize = -1
    for i in range(N):
        for j in range(N):
            if grid[i][j] == 0:

                # Find all unique neighbouring islands
                neighbours: set[tuple[int, int]] = set()
                for x, y in [(-1,0), (0,-1), (0,1), (1,0)]:
                    i_, j_ = i + x, j + y
                    if 0 <= i_ < N and 0 <= j_ < N and ds.size[i_][j_] > 0:
                        neighbours.add(ds.findUltimateParent((i_, j_)))

                # Find total if this cell was to be converted to land
                size = 1
                for i_, j_ in neighbours:
                    size += ds.size[i_][j_]

                # If curr size is greater, we update our result
                maxSize = max(maxSize, size)

            # Maybe the largest island already exists, for completeness lets include existing island sizes as well.
            else:
                i_, j_ = ds.findUltimateParent((i, j))
                maxSize = max(maxSize, ds.size[i_][j_])

    return maxSize

# Testing the solution
assert largestIsland([[0,0,0],[1,1,0],[0,0,1]]) == 4
assert largestIsland([[1,0],[0,1]]) == 3
```

</div>

<div id="ab069300" class="cell markdown"
papermill="{&quot;duration&quot;:2.2021e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.650129&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.628108&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Kruskal's algorithm Video:
<https://youtu.be/DMnDM_sxVig?si=gx3twzTFXAtY5deT> Complexity: Time -
O(E log E), Space: O(E) Logic:

    1. Sort the edges according to the weights.
    2. Iterate through all edges and add the edge if the n1 and n2 and not already connected.

</div>

<div id="888f5d21" class="cell code" execution_count="48"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:23.695861Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:23.695259Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:23.710747Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:23.709857Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.0133e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.712360&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.672227&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimumSpanningTreeKruskal(edges: list[tuple[int, int, int]], V: int, E: int) -> int:
    class DisjointSet:
        def __init__(self, N: int):
            self.size: list[int] = [1 for i in range(N)]
            self.parents: list[int] = [i for i in range(N)]

        def findUltimateParent(self, node: int) -> int:
            if self.parents[node] == node:
                return node
            else:
                self.parents[node] = self.findUltimateParent(self.parents[node])
                return self.parents[node]

        def unionBySize(self, n1: int, n2: int):
            n1p, n2p = self.findUltimateParent(n1), self.findUltimateParent(n2)
            n1s, n2s = self.size[n1p], self.size[n2p]
            if n1p == n2p:
                return
            elif n1s < n2s:
                self.parents[n1p] = n2p
                self.size[n2p] += self.size[n1p]
            else:
                self.parents[n2p] = n1p
                self.size[n1p] += self.size[n2p]

    # Sort edges based on the weights: O(E log E)
    edges.sort(key=lambda x: x[2])

    # Create a disjoint set, iterate through edges and add edges if a connection doesn't already exist: O(E)
    ds = DisjointSet(V)
    mst: list[tuple[int, int, int]] = []
    mst_weight = 0
    for n1, n2, w in edges:
        n1p, n2p = ds.findUltimateParent(n1), ds.findUltimateParent(n2)
        if n1p != n2p:
            ds.unionBySize(n1, n2)
            mst.append((n1, n2, w))
            mst_weight += w

    print(mst)
    return mst_weight

# Testing the solution
minimumSpanningTreeKruskal([(0, 1, 3), (0, 3, 5), (1, 2, 1), (2, 3, 8)], 4, 4)
```

<div class="output stream stdout">

    [(1, 2, 1), (0, 1, 3), (0, 3, 5)]

</div>

<div class="output execute_result" execution_count="48">

    9

</div>

</div>

<div id="df3bfcb9" class="cell markdown"
papermill="{&quot;duration&quot;:2.1804e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.756427&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.734623&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/OwMNX8SPavM?si=MWkOXvyzLmRKxhSQ> Most
stones removed from same row / column

</div>

<div id="a0c4c2d4" class="cell code" execution_count="49"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-03T16:50:23.801743Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-03T16:50:23.801182Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-03T16:50:23.813571Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-03T16:50:23.812799Z&quot;}"
papermill="{&quot;duration&quot;:3.7067e-2,&quot;end_time&quot;:&quot;2024-05-03T16:50:23.815325&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-03T16:50:23.778258&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/submissions/1248392383
def removeStones(stones: list[list[int]]) -> int:
    """
    Max stones that can be removed is (island_size - 1).
    This can be boiled down to len(stones) [total stones] - no of components
    """
    class DS:
        def __init__(self) -> None:
            self.size: dict[str, int] = {}
            self.parents: dict[str, str] = {}

        def findUltimateParent(self, node: str) -> str:
            if node not in self.parents:
                self.parents[node] = node
                self.size[node] = 1 if 'r' in node else 0

            if self.parents[node] == node:
                return node
            else:
                self.parents[node] = self.findUltimateParent(self.parents[node])
                return self.parents[node]

        def unionBySize(self, row: str, col: str):
            rp, cp = self.findUltimateParent(row), self.findUltimateParent(col)
            rps, cps = self.size[rp], self.size[cp]
            if rp == cp:
                return
            elif rps < cps:
                self.parents[rp] = cp
                self.size[cp] += self.size[rp]
            else:
                self.parents[cp] = rp
                self.size[rp] += self.size[cp]

    ds = DS()
    for i, j in stones:
        row, col = f'r{i}', f'c{j}'
        ds.unionBySize(row, col)

    parents: set[str] = set()
    for parent in ds.parents:
        parents.add(ds.findUltimateParent(parent))

    return len(stones) - len(parents)

# Testing the solution
assert removeStones([[0,0],[0,2],[1,3],[3,1],[3,2],[4,3]]) == 4
assert removeStones([[0,0],[1,1],[2,2],[2,3],[2,4],[3,2]]) == 3
```

</div>
