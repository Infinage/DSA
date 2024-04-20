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
    duration: 1.381017
    end_time: "2024-04-20T14:34:45.724112"
    environment_variables: {}
    input_path: study/striver-A2Z/12-graphs.ipynb
    output_path: study/striver-A2Z/12-graphs.ipynb
    parameters: {}
    start_time: "2024-04-20T14:34:44.343095"
    version: 2.5.0
---

<div id="b7c72dfd" class="cell markdown"
papermill="{&quot;duration&quot;:3.857e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.444872&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.441015&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.147e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.451341&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.448194&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.941e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.457251&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.454310&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper functions and definitions

</div>

<div id="8c79edc4" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:45.465235Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:45.464497Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:45.474801Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:45.474124Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6221e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.476499&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.460278&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import collections
import itertools
import typing
```

</div>

<div id="fc260e41" class="cell markdown"
papermill="{&quot;duration&quot;:3.019e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.482870&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.479851&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-tgVpUgsQ5k?si=8HBt33CLyu9hTP1I> BFS
Search of a graph

</div>

<div id="2e42efd0" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:45.490859Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:45.490164Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:45.497455Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:45.496809Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3295e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.499224&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.485929&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.159e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.507926&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.503767&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Qzf1a--rhp8?si=Zb_XCqskGiK11gbB> DFS
Traversal

</div>

<div id="4a28e0ae" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:45.517668Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:45.517049Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:45.530892Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:45.530099Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0714e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.532717&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.512003&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.158e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.539219&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.536061&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of provinces:
<https://leetcode.com/problems/number-of-provinces/submissions/1237343247/>
Video Link: <https://youtu.be/ACzkVtewUYA?si=wpzBiKJoOJQnFR18>

</div>

<div id="672dd010" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:45.547003Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:45.546519Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:45.553921Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:45.553236Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3367e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.555696&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.542329&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.327e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.562532&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.559205&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/muncqlKJrH0?si=xcCfsKjX5tZd4kZJ> Number of
islands

</div>

<div id="968de0b8" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:45.570694Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:45.569945Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:45.578153Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:45.577408Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4122e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.579860&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.565738&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.227e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.586407&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.583180&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/C-2_uSRli8o?si=kwATM2glQc_Mpf76> Flood
fill: <https://leetcode.com/problems/flood-fill/submissions/1237381436>

</div>

<div id="1e1a36fc" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:45.594854Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:45.594124Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:45.602162Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:45.601491Z&quot;}"
papermill="{&quot;duration&quot;:1.4173e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:45.603961&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:45.589788&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
