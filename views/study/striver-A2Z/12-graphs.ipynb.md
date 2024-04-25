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
    duration: 2.653111
    end_time: "2024-04-25T16:58:40.731513"
    environment_variables: {}
    input_path: study/striver-A2Z/12-graphs.ipynb
    output_path: study/striver-A2Z/12-graphs.ipynb
    parameters: {}
    start_time: "2024-04-25T16:58:38.078402"
    version: 2.5.0
---

<div id="b7c72dfd" class="cell markdown"
papermill="{&quot;duration&quot;:1.2042e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.132441&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.120399&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0997e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.154837&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.143840&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.093e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.176793&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.165863&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="a321425e" class="cell markdown" lines_to_next_cell="0"
papermill="{&quot;duration&quot;:1.1035e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.198937&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.187902&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper functions and definitions

</div>

<div id="8c79edc4" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.223230Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.222907Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.233244Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.232571Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5074e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.235123&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.210049&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import collections
import itertools
import typing
```

</div>

<div id="fc260e41" class="cell markdown"
papermill="{&quot;duration&quot;:1.1377e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.257995&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.246618&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-tgVpUgsQ5k?si=8HBt33CLyu9hTP1I> BFS
Search of a graph

</div>

<div id="2e42efd0" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.283685Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.283084Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.290175Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.289372Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0815e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.291919&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.271104&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0879e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.313646&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.302767&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Qzf1a--rhp8?si=Zb_XCqskGiK11gbB> DFS
Traversal

</div>

<div id="4a28e0ae" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.336697Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.336113Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.345106Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.344417Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2431e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.346891&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.324460&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1236e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.369281&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.358045&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of provinces:
<https://leetcode.com/problems/number-of-provinces/submissions/1237343247/>
Video Link: <https://youtu.be/ACzkVtewUYA?si=wpzBiKJoOJQnFR18>

</div>

<div id="672dd010" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.392490Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.391866Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.398814Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.398059Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0435e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.400545&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.380110&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.085e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.422249&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.411399&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/muncqlKJrH0?si=xcCfsKjX5tZd4kZJ> Number of
islands

</div>

<div id="968de0b8" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.445077Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.444810Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.452283Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.451631Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0914e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.454002&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.433088&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0837e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.475777&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.464940&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/C-2_uSRli8o?si=kwATM2glQc_Mpf76> Flood
fill: <https://leetcode.com/problems/flood-fill/submissions/1237381436>

</div>

<div id="1e1a36fc" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.498440Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.498209Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.505620Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.504936Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0801e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.507393&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.486592&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0802e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.529049&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.518247&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/yf3oUhkvqA0?si=A664tpMiA00GrxJV> Rotten
Oranges:
<https://leetcode.com/problems/rotting-oranges/submissions/1237760285>

</div>

<div id="8b72ec9b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.552095Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.551465Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.563192Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.562444Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5066e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.564932&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.539866&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0975e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.586924&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.575949&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle with Graph (BFS / DFS) Video Link BFS:
<https://youtu.be/BPlrALf1LDU?si=U9u9H_9xiHo8oflx> Video Link DFS:
<https://youtu.be/zQ3zgFypzX4?si=trbPI1I4DfRMcrj5>

</div>

<div id="342b6f3b" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.610267Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.609626Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.621176Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.620431Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5165e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.623074&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.597909&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0865e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.644958&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.634093&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/edXdVwkYHF8?si=oTave6oul5GbDHrn> 01
Matrix: <https://leetcode.com/problems/01-matrix/>

</div>

<div id="14c07211" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.668045Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.667467Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.678000Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.677264Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3845e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.679636&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.655791&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.702982Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.702368Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.715401Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.714755Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6382e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.716996&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.690614&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.740604Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.739770Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.750029Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.749376Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3766e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.751758&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.727992&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0886e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.773656&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.762770&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/BtdgAys4yMk?si=BLc-UXXR9XvQV8Mf>
Surrounded Regions:
<https://leetcode.com/problems/surrounded-regions/description/>

</div>

<div id="3610e726" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.796903Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.796213Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.807934Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.807176Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5155e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.809648&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.784493&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1058e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.831791&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.820733&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of Enclaves Video Link:
<https://youtu.be/7zmgQSJghpo?si=XSGlRuO_V105V2XK>

</div>

<div id="5647a7a1" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.855230Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.854571Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.863827Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.863082Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2914e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.865522&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.842608&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0932e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.887470&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.876538&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/7zmgQSJghpo?si=VR9VnvBwe-esRaau> Distinct
Islands

</div>

<div id="77dd14f8" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.911163Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.910444Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.921491Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.920739Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4887e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.923316&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.898429&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1062e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.945435&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.934373&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-vu34sct1g8?si=H2DEd5HB-B6oAU4p> Bipartite
Graph (BFS):
<https://leetcode.com/problems/is-graph-bipartite/description/>

</div>

<div id="8584fbc4" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:39.968688Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:39.968003Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:39.977831Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:39.977054Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3208e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:39.979442&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.956234&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0827e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.001193&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:39.990366&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle in directed graph with DFS:
<https://youtu.be/9twcmtQj4DU?si=2xZsVlk1bdtLbHz5>

</div>

<div id="f1cf48b4" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.025251Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.024541Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.033227Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.032578Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2891e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.034953&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.012062&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1058e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.057245&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.046187&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Eventual Safe states (DFS):
<https://youtu.be/uRbJ1OF9aYM?si=8J-ujp8LUkpO887c>

</div>

<div id="e3bfb6f2" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.080918Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.080182Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.090702Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.089949Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4391e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.092491&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.068100&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0868e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.114547&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.103679&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological sorting DFS:
<https://youtu.be/5lZ0iJMrUMk?si=lSTD3o2QoGGjiwxO>

</div>

<div id="806cdb46" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.137859Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.137241Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.149486Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.148743Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5693e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.151082&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.125389&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.174933Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.174225Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.183272Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.182538Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2502e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.184859&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.162357&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1066e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.207136&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.196070&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Topological Sorting with BFS (Kahn's Algorithm):
<https://youtu.be/73sneFXuTEg?si=TeG_vMqnXLz2NR6M>

</div>

<div id="9aca2f0e" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.231067Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.230402Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.241148Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.240419Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4497e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.242783&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.218286&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1222e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.265387&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.254165&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WAOfKpxYHR8?si=KdXRvzRuinvS50gx>

</div>

<div id="bd6a415c" class="cell markdown"
papermill="{&quot;duration&quot;:1.1289e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.288144&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.276855&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 1:
<https://leetcode.com/problems/course-schedule/submissions/1240848705/>

</div>

<div id="d2aca589" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.312450Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.311761Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.321188Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.320562Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3469e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.322900&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.299431&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1198e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.345410&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.334212&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Course schedule - 2:
<https://leetcode.com/problems/course-schedule-ii/submissions/1240905168/>

</div>

<div id="04331e57" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.369877Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.369125Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.380279Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.379448Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5488e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.382322&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.356834&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1422e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.423600&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.412178&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/2gtg3VsDGyc?si=l4U9ljeQk6vBufj-> Eventual
Safe States with BFS

</div>

<div id="f5f3c530" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.448033Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.447341Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.457061Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.456315Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3803e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.458766&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.434963&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1311e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.481500&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.470189&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/U3N_je7tWAs?si=ZkvYEfyaDOVehnEa> Alien
Dictionary

</div>

<div id="42166b86" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.506365Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.505788Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.517936Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.517216Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6162e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.519572&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.493410&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1553e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.542980&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.531427&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ZUFQfFaU-8U?si=SRwWuuRJN53CMn_w> Shortest
path in DAG (topological sorting)

</div>

<div id="29f9d887" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-25T16:58:40.567393Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-25T16:58:40.566781Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-25T16:58:40.577659Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-25T16:58:40.576855Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4823e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.579407&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.554584&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1541e-2,&quot;end_time&quot;:&quot;2024-04-25T16:58:40.602733&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-25T16:58:40.591192&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest path in undirected graph with unit weights Video link:
<https://youtu.be/C4gxoTaI71U?si=NQRmSQ7skeZnz9V0> def
shortestPath(edges: list\[list\[int\]\], N: int, M: int, src: int) -\>
list\[int\]: \# Create an adjacency list adj: dict\[int, list\[int\]\] =
dict() for n1, n2 in edges: n1_neighbours, n2_neighbours = adj.get(n1,
\[\]), adj.get(n2, \[\]) n1_neighbours.append(n2)
n2_neighbours.append(n1) adj\[n1\], adj\[n2\] = n1_neighbours,
n2_neighbours

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

Testing the solution assert
shortestPath(\[\[0,1\],\[0,3\],\[3,4\],\[4,5\],\[5,6\],\[1,2\],\[2,6\],\[6,7\],\[7,8\],\[6,8\]\],
9, 10, 0) == \[0,1,2,1,2,3,3,4,4\] assert
shortestPath(\[\[0,0\],\[1,1\],\[1,3\],\[3,0\]\], 4, 4, 3) ==
\[1,1,-1,0\]

</div>
