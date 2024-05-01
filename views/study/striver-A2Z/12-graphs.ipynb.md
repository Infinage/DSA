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
    duration: 5.249735
    end_time: "2024-05-01T16:49:42.836677"
    environment_variables: {}
    input_path: study/striver-A2Z/12-graphs.ipynb
    output_path: study/striver-A2Z/12-graphs.ipynb
    parameters: {}
    start_time: "2024-05-01T16:49:37.586942"
    version: 2.5.0
---

<div id="b7c72dfd" class="cell markdown"
papermill="{&quot;duration&quot;:1.9863e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:38.649459&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.629596&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8757e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:38.687086&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.668329&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.841e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:38.728106&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.709696&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8514e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:38.765155&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.746641&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8482e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:38.802241&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.783759&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8179e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:38.839040&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.820861&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8701e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:38.876098&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.857397&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Minimum Spanning Tree (MST)

1.  Spanning Tree: A tree in which we have N nodes and N - 1 edges and
    all nodes are reachable from each other.
2.  MST: Out of all spanning trees that we can get, the one with the
    minimum edge weight sum is called the minimum spanning tree.

</div>

<div id="fe81afa5" class="cell markdown"
papermill="{&quot;duration&quot;:1.835e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:38.914731&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.896381&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8532e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:38.951966&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.933434&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper functions and definitions

</div>

<div id="8c79edc4" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:38.990454Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:38.989784Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:38.999777Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:38.999132Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1267e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.001596&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:38.970329&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8428e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.038672&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.020244&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-tgVpUgsQ5k?si=8HBt33CLyu9hTP1I> BFS
Search of a graph

</div>

<div id="2e42efd0" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.077455Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.076776Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.083676Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.082881Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8343e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.085440&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.057097&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9222e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.123900&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.104678&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Qzf1a--rhp8?si=Zb_XCqskGiK11gbB> DFS
Traversal

</div>

<div id="4a28e0ae" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.164708Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.164064Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.175778Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.174980Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4089e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.177547&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.143458&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8391e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.214538&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.196147&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of provinces:
<https://leetcode.com/problems/number-of-provinces/submissions/1237343247/>
Video Link: <https://youtu.be/ACzkVtewUYA?si=wpzBiKJoOJQnFR18>

</div>

<div id="672dd010" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.252922Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.252377Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.259357Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.258648Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8082e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.261083&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.233001&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8379e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.298089&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.279710&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/muncqlKJrH0?si=xcCfsKjX5tZd4kZJ> Number of
islands

</div>

<div id="968de0b8" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.336545Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.336003Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.343651Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.342880Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8658e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.345325&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.316667&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8299e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.382096&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.363797&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/C-2_uSRli8o?si=kwATM2glQc_Mpf76> Flood
fill: <https://leetcode.com/problems/flood-fill/submissions/1237381436>

</div>

<div id="1e1a36fc" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.420811Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.420197Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.427809Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.427040Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8959e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.429686&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.400727&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8453e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.466830&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.448377&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/yf3oUhkvqA0?si=A664tpMiA00GrxJV> Rotten
Oranges:
<https://leetcode.com/problems/rotting-oranges/submissions/1237760285>

</div>

<div id="8b72ec9b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.505271Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.504674Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.516473Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.515831Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2964e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.518266&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.485302&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8572e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.555518&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.536946&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle with Graph (BFS / DFS) Video Link BFS:
<https://youtu.be/BPlrALf1LDU?si=U9u9H_9xiHo8oflx> Video Link DFS:
<https://youtu.be/zQ3zgFypzX4?si=trbPI1I4DfRMcrj5>

</div>

<div id="342b6f3b" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.593842Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.593216Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.604724Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.604079Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.236e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.606345&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.573985&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.849e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.643509&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.625019&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/edXdVwkYHF8?si=oTave6oul5GbDHrn> 01
Matrix: <https://leetcode.com/problems/01-matrix/>

</div>

<div id="14c07211" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.700586Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.699903Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.710298Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.709551Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.9923e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.712073&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.662150&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.750652Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.750044Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.763290Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.762637Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4188e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.764892&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.730704&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.803616Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.802906Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.813419Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.812820Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1567e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.815095&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.783528&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8561e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.852448&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.833887&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/BtdgAys4yMk?si=BLc-UXXR9XvQV8Mf>
Surrounded Regions:
<https://leetcode.com/problems/surrounded-regions/description/>

</div>

<div id="3610e726" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.891113Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.890513Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.902135Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.901514Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3041e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.903884&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.870843&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8483e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.940965&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.922482&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of Enclaves Video Link:
<https://youtu.be/7zmgQSJghpo?si=XSGlRuO_V105V2XK>

</div>

<div id="5647a7a1" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:39.979314Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:39.978646Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:39.988106Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:39.987468Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.038e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:39.989796&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:39.959416&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8456e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.026905&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.008449&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/7zmgQSJghpo?si=VR9VnvBwe-esRaau> Distinct
Islands

</div>

<div id="77dd14f8" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.065436Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.065147Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.076122Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.075402Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2272e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.077750&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.045478&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8633e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.115465&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.096832&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-vu34sct1g8?si=H2DEd5HB-B6oAU4p> Bipartite
Graph (BFS):
<https://leetcode.com/problems/is-graph-bipartite/description/>

</div>

<div id="8584fbc4" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.153620Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.153362Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.163082Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.162417Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0909e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.164812&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.133903&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8527e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.202042&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.183515&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle in directed graph with DFS:
<https://youtu.be/9twcmtQj4DU?si=2xZsVlk1bdtLbHz5>

</div>

<div id="f1cf48b4" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.240913Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.240261Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.249254Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.248647Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0135e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.250887&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.220752&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8555e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.288174&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.269619&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Eventual Safe states (DFS):
<https://youtu.be/uRbJ1OF9aYM?si=8J-ujp8LUkpO887c>

</div>

<div id="e3bfb6f2" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.326669Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.326021Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.334262Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.333530Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9461e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.336167&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.306706&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8495e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.373415&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.354920&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological sorting DFS:
<https://youtu.be/5lZ0iJMrUMk?si=lSTD3o2QoGGjiwxO>

</div>

<div id="806cdb46" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.411700Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.411141Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.423860Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.423201Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3701e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.425561&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.391860&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.464150Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.463873Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.472918Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.472179Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0282e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.474629&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.444347&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8825e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.512484&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.493659&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological Sorting with BFS (Kahn's Algorithm):
<https://youtu.be/73sneFXuTEg?si=TeG_vMqnXLz2NR6M>

</div>

<div id="9aca2f0e" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.551383Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.550980Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.561670Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.560871Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2077e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.563377&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.531300&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8837e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.601268&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.582431&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WAOfKpxYHR8?si=KdXRvzRuinvS50gx>

</div>

<div id="bd6a415c" class="cell markdown"
papermill="{&quot;duration&quot;:1.8919e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.639346&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.620427&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 1:
<https://leetcode.com/problems/course-schedule/submissions/1240848705/>

</div>

<div id="d2aca589" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.678786Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.678147Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.686807Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.686191Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0144e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.688486&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.658342&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8785e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.726312&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.707527&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 2:
<https://leetcode.com/problems/course-schedule-ii/submissions/1240905168/>

</div>

<div id="04331e57" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.765769Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.765148Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.775643Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.774999Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1787e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.777213&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.745426&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9053e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.815534&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.796481&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/2gtg3VsDGyc?si=l4U9ljeQk6vBufj-> Eventual
Safe States with BFS

</div>

<div id="f5f3c530" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.854842Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.854320Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.864152Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.863418Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1528e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.866012&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.834484&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9391e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.904624&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.885233&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/U3N_je7tWAs?si=ZkvYEfyaDOVehnEa> Alien
Dictionary

</div>

<div id="42166b86" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:40.944488Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:40.943730Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:40.956902Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:40.956230Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4841e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.958599&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.923758&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8933e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:40.996708&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:40.977775&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ZUFQfFaU-8U?si=SRwWuuRJN53CMn_w> Shortest
path in DAG (topological sorting)

</div>

<div id="29f9d887" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.036551Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.035907Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.048080Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.047450Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3853e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.049697&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.015844&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9017e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.087893&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.068876&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest path in undirected graph with unit weights

</div>

<div id="685cf4ef" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.127255Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.126967Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.138319Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.137678Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3068e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.140029&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.106961&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9209e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.178518&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.159309&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Word Ladder - 1:
<https://leetcode.com/problems/word-ladder/submissions/1242529557> Video
Link: <https://youtu.be/tRPda0rcf8E?si=IvDpS_6OSFIa-iAY>

</div>

<div id="ef9ed676" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.218216Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.217642Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.226485Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.225871Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0415e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.228129&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.197714&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8813e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.266049&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.247236&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/DREutrv2XD0?si=SbXR_WrwV0yPkM3t> Word
Ladder - 2: <https://leetcode.com/problems/word-ladder-ii/description/>

</div>

<div id="8c81ef46" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.305708Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.305112Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.317470Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.316872Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3926e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.319125&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.285199&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.358570Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.357952Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.372445Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.371819Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.597e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.374146&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.338176&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8977e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.412395&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.393418&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Dijkstra's Algorithm using Min Heap:
<https://youtu.be/V6H1qAeB-l4?si=rEGFRGwu-ojsYp-3>

</div>

<div id="f9b1c99b" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.452197Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.451567Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.459470Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.458786Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9564e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.461108&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.431544&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8966e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.499329&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.480363&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/rp1SMw7HSO8?si=7d4Jc-1NTMcKvbh8> Shortest
path in an undirected weighted graph

</div>

<div id="5fc33946" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.539005Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.538324Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.549160Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.548551Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2446e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.550790&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.518344&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9171e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.589223&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.570052&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest path in a binary maze:
<https://leetcode.com/problems/shortest-path-in-binary-matrix/submissions/1243256372/>
Video Link: <https://youtu.be/U5Mw4eyUmw4?si=SM3SONUWEFwd8XLt>

</div>

<div id="2f855e08" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.628596Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.628148Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.637983Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.637339Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1347e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.639608&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.608261&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8919e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.677614&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.658695&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/0ytpZyiZFhA?si=UwEDE7wIpbT_Q87y> Path with
minimum effort:
<https://leetcode.com/problems/path-with-minimum-effort/submissions/1243926425/>

</div>

<div id="85a0590c" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.717315Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.717040Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.728132Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.727395Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2768e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.729821&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.697053&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9052e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.768028&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.748976&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Cheapest flight within K stops:
<https://leetcode.com/problems/cheapest-flights-within-k-stops/submissions/1244248580>
Video Link: <https://youtu.be/9XybHVqTHcQ?si=jLIB9G9VQ184S2w6>

</div>

<div id="53b3f2f6" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.807688Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.807057Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.819280Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.818365Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3824e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.820984&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.787160&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9147e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.859654&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.840507&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Minimum Operations Video link:
<https://youtu.be/_BvEJ3VIDWw?si=0Kgpj58X7BYexE2k>

</div>

<div id="a5556478" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.899321Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.898611Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:41.912467Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:41.911844Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5535e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.914229&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.878694&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9102e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:41.952497&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.933395&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/_-0mx0SmYxA?si=6GOaqZSP-NDZ_Oq-> Number of
ways to arrive at a destination

</div>

<div id="6d28c0b9" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:41.992554Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:41.991905Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:42.008524Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:42.007786Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.8467e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.010198&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:41.971731&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:42.049970Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:42.049385Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:42.060086Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:42.059468Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2231e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.061724&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.029493&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9056e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.100042&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.080986&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=0vVofAhAYjc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=166>
Bellman Ford Algorithm

</div>

<div id="246f039f" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:42.140329Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:42.139638Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:42.146557Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:42.145806Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.877e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.148142&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.119372&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9026e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.186487&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.167461&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/YbY8cVwWAvw?si=_Soo7iiwWihY5G8w> Floyd
Warshall Algorithm

</div>

<div id="53a5b83f" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:42.226072Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:42.225843Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:42.235899Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:42.235156Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1712e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.237514&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.205802&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9364e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.276615&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.257251&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/PwMVNSJ5SLI?si=AbyQbGEgwGWk6lPZ> City with
smallest number of neighbours at threshold

</div>

<div id="2407a370" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:42.316694Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:42.316101Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:42.328528Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:42.327906Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4238e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.330195&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.295957&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9316e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.369020&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.349704&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:42.408983Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:42.408442Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:42.420711Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:42.419941Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4057e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.422372&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.388315&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimumSpanningTree(edges: list[tuple[int, int, int]], V: int, E: int) -> int:
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
minimumSpanningTree([(0, 1, 3), (0, 3, 5), (1, 2, 1), (2, 3, 8)], 4, 4)
```

<div class="output stream stdout">

    [(0, 1, 3), (1, 2, 1), (0, 3, 5)]

</div>

<div class="output execute_result" execution_count="41">

    9

</div>

</div>

<div id="388bd0af" class="cell markdown"
papermill="{&quot;duration&quot;:1.9694e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.461802&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.442108&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Disjoint set data structure

</div>

<div id="7b48003b" class="cell code" execution_count="42"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:42.502872Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:42.502218Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:42.516921Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:42.516227Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.7354e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.518931&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.481577&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.948e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.558858&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.539378&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find number of provinces (using disjoint set)

</div>

<div id="fc2419f0" class="cell code" execution_count="43"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:42.599305Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:42.599035Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:42.605619Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:42.604978Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8941e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.607323&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.578382&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9604e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.646580&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.626976&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of operations to make network connected - DSU Video Link:
<https://youtu.be/FYrl7iz9_ZU?si=SctG8sU5N_L_FYUt> Problem link:
<https://leetcode.com/problems/number-of-operations-to-make-network-connected/submissions/1246593300>

</div>

<div id="a5d00525" class="cell code" execution_count="44"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-01T16:49:42.687515Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-01T16:49:42.686799Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-01T16:49:42.698118Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-01T16:49:42.697501Z&quot;}"
papermill="{&quot;duration&quot;:3.3556e-2,&quot;end_time&quot;:&quot;2024-05-01T16:49:42.699867&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-01T16:49:42.666311&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
