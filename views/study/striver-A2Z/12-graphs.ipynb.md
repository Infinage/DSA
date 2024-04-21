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
    duration: 1.627561
    end_time: "2024-04-21T15:47:37.776243"
    environment_variables: {}
    input_path: study/striver-A2Z/12-graphs.ipynb
    output_path: study/striver-A2Z/12-graphs.ipynb
    parameters: {}
    start_time: "2024-04-21T15:47:36.148682"
    version: 2.5.0
---

<div id="b7c72dfd" class="cell markdown"
papermill="{&quot;duration&quot;:6.663e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.190736&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.184073&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="cf960c9a" class="cell markdown"
papermill="{&quot;duration&quot;:5.629e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.202222&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.196593&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="a321425e" class="cell markdown" lines_to_next_cell="0"
papermill="{&quot;duration&quot;:5.48e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.213330&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.207850&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper functions and definitions

</div>

<div id="8c79edc4" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.226165Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.225466Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.235168Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.234425Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9011e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.237889&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.218878&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import collections
import itertools
import typing
```

</div>

<div id="fc260e41" class="cell markdown"
papermill="{&quot;duration&quot;:5.683e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.249312&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.243629&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-tgVpUgsQ5k?si=8HBt33CLyu9hTP1I> BFS
Search of a graph

</div>

<div id="2e42efd0" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.262272Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.261745Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.269179Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.268389Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6657e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.271766&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.255109&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.698e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.289280&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.280582&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Qzf1a--rhp8?si=Zb_XCqskGiK11gbB> DFS
Traversal

</div>

<div id="4a28e0ae" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.308203Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.307392Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.317961Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.317335Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1758e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.319724&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.297966&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.542e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.331072&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.325530&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of provinces:
<https://leetcode.com/problems/number-of-provinces/submissions/1237343247/>
Video Link: <https://youtu.be/ACzkVtewUYA?si=wpzBiKJoOJQnFR18>

</div>

<div id="672dd010" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.343758Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.343193Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.350584Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.349712Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6287e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.352977&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.336690&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.602e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.364291&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.358689&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/muncqlKJrH0?si=xcCfsKjX5tZd4kZJ> Number of
islands

</div>

<div id="968de0b8" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.376831Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.376597Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.384239Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.383493Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6429e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.386475&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.370046&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.53e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.397579&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.392049&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/C-2_uSRli8o?si=kwATM2glQc_Mpf76> Flood
fill: <https://leetcode.com/problems/flood-fill/submissions/1237381436>

</div>

<div id="1e1a36fc" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.410631Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.409969Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.417421Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.416667Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6241e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.419538&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.403297&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.606e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.431097&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.425491&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/yf3oUhkvqA0?si=A664tpMiA00GrxJV> Rotten
Oranges:
<https://leetcode.com/problems/rotting-oranges/submissions/1237760285>

</div>

<div id="8b72ec9b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.443821Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.443212Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.454980Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.454239Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0052e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.456801&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.436749&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.512e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.468238&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.462726&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle with Graph (BFS / DFS) Video Link BFS:
<https://youtu.be/BPlrALf1LDU?si=U9u9H_9xiHo8oflx> Video Link DFS:
<https://youtu.be/zQ3zgFypzX4?si=trbPI1I4DfRMcrj5>

</div>

<div id="342b6f3b" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.480605Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.480067Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.491832Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.491179Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9736e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.493507&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.473771&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def detectCycleBFS(V: int, E: int, edges: list[tuple[int, int]]):
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
        if BFS(curr):
            return True
    else:
        return False

assert detectCycleBFS(5, 3, [(0, 1), (1, 2), (3, 4)]) == False
assert detectCycleBFS(4, 4, [(0, 1), (1, 2), (2, 3), (3, 0)]) == True
```

</div>

<div id="86e956f5" class="cell markdown"
papermill="{&quot;duration&quot;:5.685e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.504852&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.499167&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/edXdVwkYHF8?si=oTave6oul5GbDHrn> 01
Matrix: <https://leetcode.com/problems/01-matrix/>

</div>

<div id="14c07211" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.517956Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.517452Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.528127Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.527418Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9236e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.529893&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.510657&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.543212Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.542486Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.556368Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.555746Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2416e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.558118&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.535702&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.570888Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.570268Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.580240Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.579503Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8217e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.582101&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.563884&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.604e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.593434&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.587830&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/BtdgAys4yMk?si=BLc-UXXR9XvQV8Mf>
Surrounded Regions:
<https://leetcode.com/problems/surrounded-regions/description/>

</div>

<div id="3610e726" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.606010Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.605772Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.617351Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.616664Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9944e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.619039&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.599095&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.753e-3,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.630600&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.624847&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of Enclaves Video Link:
<https://youtu.be/7zmgQSJghpo?si=XSGlRuO_V105V2XK>

</div>

<div id="5647a7a1" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-21T15:47:37.643384Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-21T15:47:37.642765Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-21T15:47:37.652063Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-21T15:47:37.651329Z&quot;}"
papermill="{&quot;duration&quot;:1.7529e-2,&quot;end_time&quot;:&quot;2024-04-21T15:47:37.653841&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-21T15:47:37.636312&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
