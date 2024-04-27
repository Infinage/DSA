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
    duration: 3.350869
    end_time: "2024-04-27T16:02:39.542412"
    environment_variables: {}
    input_path: study/striver-A2Z/12-graphs.ipynb
    output_path: study/striver-A2Z/12-graphs.ipynb
    parameters: {}
    start_time: "2024-04-27T16:02:36.191543"
    version: 2.5.0
---

<div id="b7c72dfd" class="cell markdown"
papermill="{&quot;duration&quot;:1.5853e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.250968&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.235115&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3265e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.277936&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.264671&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3225e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.305819&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.292594&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3044e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.332032&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.318988&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3136e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.358702&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.345566&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper functions and definitions

</div>

<div id="8c79edc4" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.387076Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.386423Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.396305Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.395563Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.592e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.398032&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.372112&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3105e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.426327&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.413222&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-tgVpUgsQ5k?si=8HBt33CLyu9hTP1I> BFS
Search of a graph

</div>

<div id="2e42efd0" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.454370Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.453680Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.460125Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.459512Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2218e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.461819&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.439601&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3273e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.488773&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.475500&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Qzf1a--rhp8?si=Zb_XCqskGiK11gbB> DFS
Traversal

</div>

<div id="4a28e0ae" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.516538Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.515885Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.525252Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.524639Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5113e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.526989&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.501876&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3147e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.553388&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.540241&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of provinces:
<https://leetcode.com/problems/number-of-provinces/submissions/1237343247/>
Video Link: <https://youtu.be/ACzkVtewUYA?si=wpzBiKJoOJQnFR18>

</div>

<div id="672dd010" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.581537Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.580838Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.587671Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.586924Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3039e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.589575&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.566536&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3717e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.617166&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.603449&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/muncqlKJrH0?si=xcCfsKjX5tZd4kZJ> Number of
islands

</div>

<div id="968de0b8" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.645052Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.644377Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.652037Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.651388Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3421e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.653744&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.630323&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2985e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.679951&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.666966&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/C-2_uSRli8o?si=kwATM2glQc_Mpf76> Flood
fill: <https://leetcode.com/problems/flood-fill/submissions/1237381436>

</div>

<div id="1e1a36fc" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.707528Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.706998Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.714592Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.713640Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3292e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.716329&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.693037&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3129e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.742918&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.729789&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/yf3oUhkvqA0?si=A664tpMiA00GrxJV> Rotten
Oranges:
<https://leetcode.com/problems/rotting-oranges/submissions/1237760285>

</div>

<div id="8b72ec9b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.770657Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.770128Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.782080Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.781409Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.766e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.783711&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.756051&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3114e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.810003&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.796889&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle with Graph (BFS / DFS) Video Link BFS:
<https://youtu.be/BPlrALf1LDU?si=U9u9H_9xiHo8oflx> Video Link DFS:
<https://youtu.be/zQ3zgFypzX4?si=trbPI1I4DfRMcrj5>

</div>

<div id="342b6f3b" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.837592Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.836943Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.848568Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.847833Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7443e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.850445&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.823002&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3168e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.877016&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.863848&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/edXdVwkYHF8?si=oTave6oul5GbDHrn> 01
Matrix: <https://leetcode.com/problems/01-matrix/>

</div>

<div id="14c07211" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.904331Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.904066Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.914454Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.913701Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5999e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.916036&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.890037&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.943745Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.943127Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.956136Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.955409Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8696e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.957911&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.929215&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:37.985898Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:37.985594Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:37.995723Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:37.995073Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5876e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:37.997293&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:37.971417&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3001e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.023428&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.010427&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/BtdgAys4yMk?si=BLc-UXXR9XvQV8Mf>
Surrounded Regions:
<https://leetcode.com/problems/surrounded-regions/description/>

</div>

<div id="3610e726" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.050747Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.050498Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.062423Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.061720Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7584e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.064087&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.036503&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3321e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.090766&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.077445&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of Enclaves Video Link:
<https://youtu.be/7zmgQSJghpo?si=XSGlRuO_V105V2XK>

</div>

<div id="5647a7a1" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.118962Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.118363Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.128022Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.127242Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5661e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.129649&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.103988&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.1153e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.173991&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.142838&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/7zmgQSJghpo?si=VR9VnvBwe-esRaau> Distinct
Islands

</div>

<div id="77dd14f8" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.202516Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.201804Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.212894Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.212145Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7341e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.214695&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.187354&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3344e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.241286&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.227942&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-vu34sct1g8?si=H2DEd5HB-B6oAU4p> Bipartite
Graph (BFS):
<https://leetcode.com/problems/is-graph-bipartite/description/>

</div>

<div id="8584fbc4" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.269217Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.268753Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.278652Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.277894Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5806e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.280239&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.254433&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3223e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.306837&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.293614&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle in directed graph with DFS:
<https://youtu.be/9twcmtQj4DU?si=2xZsVlk1bdtLbHz5>

</div>

<div id="f1cf48b4" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.335032Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.334225Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.343095Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.342339Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4929e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.344879&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.319950&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3133e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.371357&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.358224&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Eventual Safe states (DFS):
<https://youtu.be/uRbJ1OF9aYM?si=8J-ujp8LUkpO887c>

</div>

<div id="e3bfb6f2" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.399250Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.398541Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.407069Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.406326Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4303e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.408721&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.384418&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3221e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.435324&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.422103&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological sorting DFS:
<https://youtu.be/5lZ0iJMrUMk?si=lSTD3o2QoGGjiwxO>

</div>

<div id="806cdb46" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.463421Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.462710Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.475149Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.474418Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8399e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.476891&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.448492&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.505275Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.504493Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.513695Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.512948Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4898e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.515241&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.490343&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3513e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.542427&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.528914&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological Sorting with BFS (Kahn's Algorithm):
<https://youtu.be/73sneFXuTEg?si=TeG_vMqnXLz2NR6M>

</div>

<div id="9aca2f0e" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.570716Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.570094Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.580778Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.580144Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6677e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.582432&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.555755&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3584e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.609766&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.596182&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WAOfKpxYHR8?si=KdXRvzRuinvS50gx>

</div>

<div id="bd6a415c" class="cell markdown"
papermill="{&quot;duration&quot;:1.3503e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.636879&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.623376&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 1:
<https://leetcode.com/problems/course-schedule/submissions/1240848705/>

</div>

<div id="d2aca589" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.665827Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.665133Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.673715Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.672945Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.468e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.675307&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.650627&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3573e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.702630&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.689057&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 2:
<https://leetcode.com/problems/course-schedule-ii/submissions/1240905168/>

</div>

<div id="04331e57" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.731020Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.730768Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.741451Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.740714Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6972e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.743077&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.716105&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3562e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.770310&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.756748&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/2gtg3VsDGyc?si=l4U9ljeQk6vBufj-> Eventual
Safe States with BFS

</div>

<div id="f5f3c530" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.799233Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.798633Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.808743Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.807999Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6373e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.810353&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.783980&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3563e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.837734&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.824171&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/U3N_je7tWAs?si=ZkvYEfyaDOVehnEa> Alien
Dictionary

</div>

<div id="42166b86" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.866677Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.865982Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.879042Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.878381Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.943e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.880735&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.851305&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3914e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.908519&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.894605&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ZUFQfFaU-8U?si=SRwWuuRJN53CMn_w> Shortest
path in DAG (topological sorting)

</div>

<div id="29f9d887" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:38.938555Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:38.938190Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:38.950628Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:38.949842Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9598e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.952320&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.922722&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3903e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:38.980451&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.966548&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest path in undirected graph with unit weights

</div>

<div id="685cf4ef" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:39.009779Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:39.009120Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:39.020839Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:39.020171Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.829e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.022501&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:38.994211&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3815e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.050516&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.036701&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Word Ladder - 1:
<https://leetcode.com/problems/word-ladder/submissions/1242529557> Video
Link: <https://youtu.be/tRPda0rcf8E?si=IvDpS_6OSFIa-iAY>

</div>

<div id="ef9ed676" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:39.079691Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:39.079208Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:39.088059Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:39.087368Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5478e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.089739&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.064261&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3808e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.117515&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.103707&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/DREutrv2XD0?si=SbXR_WrwV0yPkM3t> Word
Ladder - 2: <https://leetcode.com/problems/word-ladder-ii/description/>

</div>

<div id="8c81ef46" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:39.146918Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:39.146255Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:39.158370Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:39.157597Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8672e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.159955&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.131283&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:39.189992Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:39.189316Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:39.204171Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:39.203420Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.175e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.206017&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.174267&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3933e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.234125&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.220192&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Dijkstra's Algorithm using Min Heap:
<https://youtu.be/V6H1qAeB-l4?si=rEGFRGwu-ojsYp-3>

</div>

<div id="f9b1c99b" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:39.263769Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:39.263258Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:39.271500Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:39.270830Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5027e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.273164&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.248137&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.394e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.301287&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.287347&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/rp1SMw7HSO8?si=7d4Jc-1NTMcKvbh8> Shortest
path in an undirected weighted graph

</div>

<div id="5fc33946" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:39.330786Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:39.330159Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:39.341523Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:39.340877Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7977e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.343211&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.315234&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3942e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.371225&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.357283&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest path in a binary maze:
<https://leetcode.com/problems/shortest-path-in-binary-matrix/submissions/1243256372/>
Video Link: <https://youtu.be/U5Mw4eyUmw4?si=SM3SONUWEFwd8XLt>

</div>

<div id="2f855e08" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-27T16:02:39.400774Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-27T16:02:39.400126Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-27T16:02:39.410114Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-27T16:02:39.409337Z&quot;}"
papermill="{&quot;duration&quot;:2.6531e-2,&quot;end_time&quot;:&quot;2024-04-27T16:02:39.411736&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-27T16:02:39.385205&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
