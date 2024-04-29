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
    duration: 3.721871
    end_time: "2024-04-29T03:08:41.810891"
    environment_variables: {}
    input_path: study/striver-A2Z/12-graphs.ipynb
    output_path: study/striver-A2Z/12-graphs.ipynb
    parameters: {}
    start_time: "2024-04-29T03:08:38.089020"
    version: 2.5.0
---

<div id="b7c72dfd" class="cell markdown"
papermill="{&quot;duration&quot;:1.5657e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.149178&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.133521&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4635e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.178748&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.164113&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4452e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.207741&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.193289&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4493e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.236782&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.222289&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="a321425e" class="cell markdown" lines_to_next_cell="0"
papermill="{&quot;duration&quot;:1.451e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.266371&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.251861&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper functions and definitions

</div>

<div id="8c79edc4" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.297531Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.296928Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.306589Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.305821Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7665e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.308750&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.281085&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import collections
import itertools
import typing
import heapq
```

</div>

<div id="fc260e41" class="cell markdown"
papermill="{&quot;duration&quot;:1.4369e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.337804&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.323435&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-tgVpUgsQ5k?si=8HBt33CLyu9hTP1I> BFS
Search of a graph

</div>

<div id="2e42efd0" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.368014Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.367379Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.373865Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.373105Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3624e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.375763&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.352139&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.44e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.404746&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.390346&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Qzf1a--rhp8?si=Zb_XCqskGiK11gbB> DFS
Traversal

</div>

<div id="4a28e0ae" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.435086Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.434466Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.443190Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.442448Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.575e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.444943&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.419193&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4418e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.473887&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.459469&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of provinces:
<https://leetcode.com/problems/number-of-provinces/submissions/1237343247/>
Video Link: <https://youtu.be/ACzkVtewUYA?si=wpzBiKJoOJQnFR18>

</div>

<div id="672dd010" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.504165Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.503677Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.510490Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.509809Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3784e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.512143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.488359&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4416e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.541061&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.526645&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/muncqlKJrH0?si=xcCfsKjX5tZd4kZJ> Number of
islands

</div>

<div id="968de0b8" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.571335Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.570711Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.578560Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.577902Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4713e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.580193&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.555480&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4251e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.608881&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.594630&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/C-2_uSRli8o?si=kwATM2glQc_Mpf76> Flood
fill: <https://leetcode.com/problems/flood-fill/submissions/1237381436>

</div>

<div id="1e1a36fc" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.638652Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.638428Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.645579Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.644845Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4046e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.647226&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.623180&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4404e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.676125&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.661721&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/yf3oUhkvqA0?si=A664tpMiA00GrxJV> Rotten
Oranges:
<https://leetcode.com/problems/rotting-oranges/submissions/1237760285>

</div>

<div id="8b72ec9b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.706204Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.705666Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.717225Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.716586Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8312e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.718833&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.690521&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4317e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.747633&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.733316&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle with Graph (BFS / DFS) Video Link BFS:
<https://youtu.be/BPlrALf1LDU?si=U9u9H_9xiHo8oflx> Video Link DFS:
<https://youtu.be/zQ3zgFypzX4?si=trbPI1I4DfRMcrj5>

</div>

<div id="342b6f3b" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.778308Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.777638Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.789189Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.788455Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.875e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.791068&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.762318&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4358e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.819842&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.805484&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/edXdVwkYHF8?si=oTave6oul5GbDHrn> 01
Matrix: <https://leetcode.com/problems/01-matrix/>

</div>

<div id="14c07211" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.850098Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.849426Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.860055Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.859427Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7374e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.861612&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.834238&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.892119Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.891460Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.904725Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.904094Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0168e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.906348&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.876180&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:39.936526Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:39.936270Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:39.946224Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:39.945555Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.692e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.947782&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.920862&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4294e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:39.976571&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.962277&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/BtdgAys4yMk?si=BLc-UXXR9XvQV8Mf>
Surrounded Regions:
<https://leetcode.com/problems/surrounded-regions/description/>

</div>

<div id="3610e726" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.007018Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.006435Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.018684Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.017900Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9152e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.020244&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:39.991092&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4379e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.049122&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.034743&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of Enclaves Video Link:
<https://youtu.be/7zmgQSJghpo?si=XSGlRuO_V105V2XK>

</div>

<div id="5647a7a1" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.080267Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.079975Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.089316Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.088584Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7521e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.091047&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.063526&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.1566e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.137183&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.105617&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/7zmgQSJghpo?si=VR9VnvBwe-esRaau> Distinct
Islands

</div>

<div id="77dd14f8" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.167521Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.167231Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.178301Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.177514Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8262e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.179942&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.151680&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4473e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.208963&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.194490&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-vu34sct1g8?si=H2DEd5HB-B6oAU4p> Bipartite
Graph (BFS):
<https://leetcode.com/problems/is-graph-bipartite/description/>

</div>

<div id="8584fbc4" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.239543Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.238921Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.248541Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.247813Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6835e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.250366&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.223531&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4498e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.279523&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.265025&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle in directed graph with DFS:
<https://youtu.be/9twcmtQj4DU?si=2xZsVlk1bdtLbHz5>

</div>

<div id="f1cf48b4" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.309918Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.309225Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.317730Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.317002Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5457e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.319500&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.294043&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4555e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.348725&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.334170&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Eventual Safe states (DFS):
<https://youtu.be/uRbJ1OF9aYM?si=8J-ujp8LUkpO887c>

</div>

<div id="e3bfb6f2" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.379213Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.378578Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.386800Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.386066Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5228e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.388376&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.363148&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4353e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.417362&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.403009&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological sorting DFS:
<https://youtu.be/5lZ0iJMrUMk?si=lSTD3o2QoGGjiwxO>

</div>

<div id="806cdb46" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.447782Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.447195Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.459187Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.458471Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8979e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.460882&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.431903&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.491693Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.491207Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.500138Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.499411Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5938e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.501694&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.475756&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4656e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.531119&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.516463&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological Sorting with BFS (Kahn's Algorithm):
<https://youtu.be/73sneFXuTEg?si=TeG_vMqnXLz2NR6M>

</div>

<div id="9aca2f0e" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.562038Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.561387Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.571901Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.571175Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7762e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.573546&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.545784&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5027e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.603718&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.588691&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WAOfKpxYHR8?si=KdXRvzRuinvS50gx>

</div>

<div id="bd6a415c" class="cell markdown"
papermill="{&quot;duration&quot;:1.4827e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.633484&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.618657&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 1:
<https://leetcode.com/problems/course-schedule/submissions/1240848705/>

</div>

<div id="d2aca589" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.664976Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.664178Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.673277Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.672670Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6587e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.675025&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.648438&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4759e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.705005&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.690246&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 2:
<https://leetcode.com/problems/course-schedule-ii/submissions/1240905168/>

</div>

<div id="04331e57" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.736044Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.735473Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.746278Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.745635Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8235e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.748018&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.719783&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4797e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.777909&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.763112&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/2gtg3VsDGyc?si=l4U9ljeQk6vBufj-> Eventual
Safe States with BFS

</div>

<div id="f5f3c530" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.809004Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.808481Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.818822Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.818193Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.761e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.820410&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.792800&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4759e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.850162&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.835403&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/U3N_je7tWAs?si=ZkvYEfyaDOVehnEa> Alien
Dictionary

</div>

<div id="42166b86" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.881185Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.880552Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.893238Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.892597Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9984e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.894905&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.864921&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4949e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.925053&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.910104&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ZUFQfFaU-8U?si=SRwWuuRJN53CMn_w> Shortest
path in DAG (topological sorting)

</div>

<div id="29f9d887" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:40.956991Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:40.956323Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:40.968627Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:40.968006Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0233e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:40.970339&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.940106&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4976e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.000308&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:40.985332&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest path in undirected graph with unit weights

</div>

<div id="685cf4ef" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.031645Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.031110Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.042255Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.041503Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8505e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.043945&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.015440&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4975e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.074055&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.059080&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Word Ladder - 1:
<https://leetcode.com/problems/word-ladder/submissions/1242529557> Video
Link: <https://youtu.be/tRPda0rcf8E?si=IvDpS_6OSFIa-iAY>

</div>

<div id="ef9ed676" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.105408Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.104827Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.113422Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.112777Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6071e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.115055&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.088984&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4977e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.145245&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.130268&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/DREutrv2XD0?si=SbXR_WrwV0yPkM3t> Word
Ladder - 2: <https://leetcode.com/problems/word-ladder-ii/description/>

</div>

<div id="8c81ef46" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.176473Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.175801Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.188063Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.187460Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.951e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.189705&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.160195&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.221039Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.220446Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.235472Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.234774Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2467e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.237097&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.204630&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5198e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.267549&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.252351&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Dijkstra's Algorithm using Min Heap:
<https://youtu.be/V6H1qAeB-l4?si=rEGFRGwu-ojsYp-3>

</div>

<div id="f9b1c99b" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.299029Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.298532Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.306485Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.305801Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5461e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.308076&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.282615&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4885e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.338023&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.323138&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/rp1SMw7HSO8?si=7d4Jc-1NTMcKvbh8> Shortest
path in an undirected weighted graph

</div>

<div id="5fc33946" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.369542Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.368850Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.380013Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.379391Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8556e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.381632&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.353076&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4945e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.411559&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.396614&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest path in a binary maze:
<https://leetcode.com/problems/shortest-path-in-binary-matrix/submissions/1243256372/>
Video Link: <https://youtu.be/U5Mw4eyUmw4?si=SM3SONUWEFwd8XLt>

</div>

<div id="2f855e08" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.443387Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.442857Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.453004Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.452351Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7636e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.454643&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.427007&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5009e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.484890&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.469881&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/0ytpZyiZFhA?si=UwEDE7wIpbT_Q87y> Path with
minimum effort:
<https://leetcode.com/problems/path-with-minimum-effort/submissions/1243926425/>

</div>

<div id="85a0590c" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.516135Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.515598Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.527040Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.526300Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8914e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.528709&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.499795&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="635b22b1" class="cell markdown"
papermill="{&quot;duration&quot;:1.493e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.558700&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.543770&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Cheapest flight within K stops:
<https://leetcode.com/problems/cheapest-flights-within-k-stops/submissions/1244248580>
Video Link: <https://youtu.be/9XybHVqTHcQ?si=jLIB9G9VQ184S2w6>

</div>

<div id="0f58c4e2" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.590186Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.589674Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.601255Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.600610Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9045e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.602838&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.573793&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="1afdfff7" class="cell markdown"
papermill="{&quot;duration&quot;:1.4936e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.632843&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.617907&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/_BvEJ3VIDWw?si=s5MuN9kdmF2j9G-Z> Minimum
Multiplications to reach end

</div>

<div id="7dc68bdb" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-29T03:08:41.664169Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-29T03:08:41.663645Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-29T03:08:41.677062Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-29T03:08:41.676332Z&quot;}"
lines_to_next_cell="3"
papermill="{&quot;duration&quot;:3.1058e-2,&quot;end_time&quot;:&quot;2024-04-29T03:08:41.678911&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-29T03:08:41.647853&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimumOperationsBrute(N: int, start: int, end: int, arr: list[int]):
    """Time: O(N * 1e3), Space: O(N * 1e3)"""
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

# Testing the solution
assert minimumOperationsBrute(2, 1, 12, [3, 2]) == 3
assert minimumOperationsBrute(4, 8, 320, [4, 6, 1, 10]) == 2
assert minimumOperationsBrute(42, 54, 98, [1, 70, 25, 79, 59, 63, 65, 6, 46, 82, 28, 62, 92, 96, 43, 28, 37, 92, 5, 3, 54, 93, 83, 22, 17, 19, 96, 48, 27, 72, 39, 70, 13, 68, 100, 36, 95, 4, 12, 23, 34, 74]) == 3
```

</div>
