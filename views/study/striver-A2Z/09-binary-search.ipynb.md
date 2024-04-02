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
    duration: 5.531613
    end_time: "2024-04-02T14:32:38.152717"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-04-02T14:32:32.621104"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:1.8833e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:33.693931&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:33.675098&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:33.731790Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:33.731110Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:33.842401Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:33.841506Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.133061,&quot;end_time&quot;:&quot;2024-04-02T14:32:33.845080&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:33.712019&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import random
import functools
import itertools
import heapq
import tqdm
import pdb
import numpy as np
import typing
```

</div>

<div id="1b645c9d" class="cell markdown"
papermill="{&quot;duration&quot;:1.7692e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:33.887090&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:33.869398&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:33.924563Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:33.923896Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:33.928953Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:33.928142Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5944e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:33.930736&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:33.904792&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Linear search
def lsearch(arr: list[int], target: int) -> int:
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    else:
        return -1
```

</div>

<div id="b06d330f" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:33.968256Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:33.967601Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:33.983405Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:33.982599Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6603e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:33.985262&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:33.948659&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Iterative solution
def bsearch_iter(arr: list[int], target: int) -> int:
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == target:
            return mid
        elif target > arr[mid]:
            low = mid + 1
        else:
            high = mid - 1
    else:
        return -1

# Test the algorithm
for i in tqdm.tqdm(range(100)):
    temp = random.sample(list(range(15, 30)), random.randint(1, 15))
    temp.sort()
    j = random.randint(0, 45)
    assert bsearch_iter(temp, j) == lsearch(temp, j), f"failed for {temp}, {j}"
```

<div class="output stream stderr">

      0%|          | 0/100 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 100/100 [00:00<00:00, 45679.63it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.023468Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.022892Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.035127Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.034374Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3127e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.036945&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.003818&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Recursive solution
def bsearch_rec(arr: list[int], target: int) -> int:
    def backtrack(low: int, high: int) -> int:
        if low > high:
            return -1
        else:
            mid = (low + high) // 2
            if arr[mid] == target:
                return mid
            elif target < arr[mid]:
                return backtrack(low, mid - 1)
            else:
                return backtrack(mid + 1, high)

    return backtrack(0, len(arr) - 1)

for i in tqdm.tqdm(range(100)):
    temp = random.sample(list(range(15, 30)), random.randint(1, 15))
    temp.sort()
    j = random.randint(0, 45)
    assert bsearch_rec(temp, j) == lsearch(temp, j), f"failed for {temp}, {j}"
```

<div class="output stream stderr">

      0%|          | 0/100 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 100/100 [00:00<00:00, 55036.14it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:1.8112e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.073678&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.055566&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.111520Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.111234Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.121202Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.120334Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0963e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.122921&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.091958&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Lower bound with Linear Search
def lower_bound_linear(arr: list[int], target: int) -> int:
    N = len(arr)
    for i in range(N):
        if arr[i] >= target:
            return i
    return N

lower_bound_linear([3, 5, 8, 15, 19], 20)
```

<div class="output execute_result" execution_count="5">

    5

</div>

</div>

<div id="a0b8bf3a" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.161437Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.160836Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.174240Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.173479Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4356e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.175880&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.141524&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def lower_bound_binary(arr: list[int], target: int):
    N = len(arr)
    low, high = 0, N - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid - 1] < target and arr[mid] >= target:
            return mid
        elif arr[mid] >= target:
            high = mid - 1
        else:
            low = mid + 1
    else:
        return 0 if target <= arr[0] else N

for i in tqdm.tqdm(range(200)):
    temp = random.choices(list(range(100, 200)), k=random.randint(1, 50))
    temp.sort()
    j = random.randint(95, 205)
    assert lower_bound_binary(temp, j) == lower_bound_linear(temp, j), f"failed for {temp}, {j}"
```

<div class="output stream stderr">

      0%|          | 0/200 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 200/200 [00:00<00:00, 60345.36it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.214920Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.214192Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.221316Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.220572Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8341e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.222984&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.194643&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Upper bound - Brute O(N)
def upper_bound_linear(arr: list[int], target: int) -> int:
    N = len(arr)
    for i in range(N):
        if arr[i] > target:
            return i
    return N

upper_bound_linear([3, 5, 8, 15, 19, 19], 15)
```

<div class="output execute_result" execution_count="7">

    4

</div>

</div>

<div id="4606b347" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.262879Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.262371Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.276583Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.275755Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6436e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.278811&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.242375&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Binary Search
def upper_bound_binary(arr: list[int], target: int) -> int:
    N = len(arr)
    low, high = 0, N - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] > target and arr[mid - 1] <= target:
            return mid
        elif arr[mid] <= target:
            low = mid + 1
        else:
            high = mid - 1
    else:
        return 0 if target < arr[0] else N

for i in tqdm.tqdm(range(200)):
    temp = random.choices(list(range(100, 200)), k=random.randint(1, 50))
    temp.sort()
    j = random.randint(95, 205)
    assert upper_bound_binary(temp, j) == upper_bound_linear(temp, j), f"failed for {temp}, {j}"

# Note the difference between the UB / LB
print(lower_bound_binary([1, 1, 1, 1, 1], 1))
print(upper_bound_binary([1, 1, 1, 1, 1], 1))
```

<div class="output stream stderr">

      0%|          | 0/200 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 200/200 [00:00<00:00, 57574.52it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:1.8845e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.316791&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.297946&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.356202Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.355587Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.363171Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.362353Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.926e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.364941&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.335681&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Lower bound Binary (Striver's approach)
def lower_bound_striver(arr: list[int], target: int) -> int:
    "Smallest index, greater than or equal to target"
    N = len(arr)
    low, high, ans = 0, N - 1, N
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] >= target:
            ans = mid
            high = mid - 1
        else:
            low = mid + 1

    return ans

lower_bound_striver([1, 1, 1, 1], 1)
```

<div class="output execute_result" execution_count="9">

    0

</div>

</div>

<div id="5ab0dd9c" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.404965Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.404335Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.411627Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.410896Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9113e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.413474&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.384361&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Upper bound Binary (Striver's approach)
def upper_bound_striver(arr: list[int], target: int) -> int:
    "Smallest index, greater than target"
    N = len(arr)
    low, high, ans = 0, N - 1, N
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] > target:
            ans = mid
            high = mid - 1
        else:
            low = mid + 1
    return ans

upper_bound_striver([1, 1, 1, 1], 1)
```

<div class="output execute_result" execution_count="10">

    4

</div>

</div>

<div id="6df8578a" class="cell markdown"
papermill="{&quot;duration&quot;:1.9133e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.451982&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.432849&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.491898Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.491294Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.496809Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.495966Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7303e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.498441&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.471138&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def searchInsert(arr: list[int], target: int) -> int:
    "Lower bound - Smallest index, greater than or equal to target"
    N = len(arr)
    low, high, ans = 0, N - 1, N
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] >= target:
            ans = mid
            high = mid - 1
        else:
            low = mid + 1

    return ans
```

</div>

<div id="d3f82851" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.538408Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.538104Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.550098Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.549309Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3918e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.551789&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.517871&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Floor and Ceil of a target from a given array
def getFloorAndCeil(arr: list[int], N: int, target: int):
    def brute() -> tuple[int, int]:
        "Brute force solution"
        floor = -1
        for i in range(N):
            if arr[i] > target:
                break
            else:
                floor = arr[i]

        ceil = -1
        for i in range(N - 1, -1, -1):
            if arr[i] < target:
                break
            else:
                ceil = arr[i]

        return floor, ceil

    def binary() -> tuple[int, int]:
        low, high, LB = 0, N - 1, -1
        while low <= high:
            mid = (low + high) // 2
            if arr[mid] <= target:
                LB = arr[mid]
                low = mid + 1
            else:
                high = mid - 1

        low, high, UB = 0, N - 1, -1
        while low <= high:
            mid = (low + high) // 2
            if arr[mid] >= target:
                UB = arr[mid]
                high = mid - 1
            else:
                low = mid + 1

        return LB, UB

    return binary()

# Testing the solution
getFloorAndCeil([3, 4, 4, 7, 8, 10], 6, 8)
```

<div class="output execute_result" execution_count="12">

    (8, 8)

</div>

</div>

<div id="d066d6da" class="cell markdown"
papermill="{&quot;duration&quot;:1.9228e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.590471&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.571243&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.630766Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.630165Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.640775Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.640007Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2759e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.642560&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.609801&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Coding studio link: https://bit.ly/3Mdw2FX
def firstAndLastPosition(arr: list[int], N: int, target: int) -> tuple[int, int]:
    def findFirst() -> int:
        low, high, ans = 0, N - 1, -1
        while low <= high:
            mid = (low + high) // 2
            if arr[mid] >= target:
                if arr[mid] == target:
                    ans = mid
                high = mid - 1
            else:
                low = mid + 1

        return ans

    def findLast() -> int:
        low, high, ans = 0, N - 1, -1
        while low <= high:
            mid = (low + high) // 2
            if arr[mid] <= target:
                if arr[mid] == target:
                    ans = mid
                low = mid + 1
            else:
                high = mid - 1

        return ans

    first = findFirst()
    if first == -1: # If not found, don't have to search again
        return first, first
    else:
        return first, findLast()

# Testing the solution
firstAndLastPosition([1, 2, 3, 3, 3, 4, 5], 7, 9)
```

<div class="output execute_result" execution_count="13">

    (-1, -1)

</div>

</div>

<div id="44578564" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.684001Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.683333Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.695674Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.694920Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4945e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.697371&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.662426&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Coding Studio link: https://bit.ly/42ZDqM4
def count_occurances(arr: list[int], N: int, target: int) -> int:
    def findFirst() -> int:
        low, high, ans = 0, N - 1, -1
        while low <= high:
            mid = (low + high) // 2
            if arr[mid] >= target:
                if arr[mid] == target:
                    ans = mid
                high = mid - 1
            else:
                low = mid + 1

        return ans

    def findLast() -> int:
        low, high, ans = 0, N - 1, -1
        while low <= high:
            mid = (low + high) // 2
            if arr[mid] <= target:
                if arr[mid] == target:
                    ans = mid
                low = mid + 1
            else:
                high = mid - 1

        return ans

    firstIdx = findFirst()
    if firstIdx == -1:
        return 0
    else:
        return findLast() - firstIdx + 1

# Testing the solution
count_occurances([1, 2, 2, 3, 4, 4, 4, 5, 6], 9, 9)
```

<div class="output execute_result" execution_count="14">

    0

</div>

</div>

<div id="7ae08467" class="cell markdown"
papermill="{&quot;duration&quot;:1.9443e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.736724&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.717281&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.777587Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.777041Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.786532Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.785876Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1934e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.788273&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.756339&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def search_rotated_sorted1(arr: list[int], target: int) -> int:
    N = len(arr)
    low, high = 0, N - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == target:
            return mid

        # Left half is sorted
        elif arr[low] <= arr[mid]:
            # Element can be found in the left half
            if arr[low] <= target <= arr[mid]:
                high = mid - 1
            else:
                low = mid + 1

        # Right half is sorted
        else:
            # Element can be found in the right half
            if arr[mid] <= target <= arr[high]:
                low = mid + 1
            else:
                high = mid - 1
    else:
        return -1

search_rotated_sorted1([7, 8, 9, 1, 2, 3, 4, 5, 6], 6)
```

<div class="output execute_result" execution_count="15">

    8

</div>

</div>

<div id="fd5e97f9" class="cell markdown"
papermill="{&quot;duration&quot;:1.9727e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.828319&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.808592&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.869588Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.868929Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.878862Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.878108Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2404e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.880570&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.848166&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Time complexity: O(n / 2)
# If there are a lot of duplicates we might need to need to trim the left/right
# repeatedly until arr[left] != arr[mid] != arr[right]
def search_rotated_sorted2(arr: list[int], target: int) -> bool:
    N = len(arr)
    low, high = 0, N - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == target:
            return True

        # Special Case - [3, 1, 2, 3, 3, 3, 3, 3], eliminating left or right is not possible
        elif arr[low] == arr[mid] == arr[high]:
            low, high = low + 1, high - 1

        # Left half is sorted
        elif arr[low] <= arr[mid]:
            # Element can be found in the left half
            if arr[low] <= target <= arr[mid]:
                high = mid - 1
            else:
                low = mid + 1

        # Right half is sorted
        else:
            # Element can be found in the right half
            if arr[mid] <= target <= arr[high]:
                low = mid + 1
            else:
                high = mid - 1
    else:
        return False

search_rotated_sorted2([3, 1, 2, 3, 3, 3, 3], 1)
```

<div class="output execute_result" execution_count="16">

    True

</div>

</div>

<div id="6657c71c" class="cell markdown"
papermill="{&quot;duration&quot;:1.9896e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.920743&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.900847&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:34.982176Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:34.981574Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:34.989984Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:34.989310Z&quot;}"
papermill="{&quot;duration&quot;:3.1245e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:34.991632&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:34.960387&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class Solution:
    def findMin(self, nums: list[int]) -> int:
        N = len(nums)
        low, high, ans = 0, N - 1, nums[0]
        while low <= high:
            mid = (low + high) // 2
            # Left half and right half is sorted (happens when we have crossed the pivot point or if the array was rotated 0 times)
            if nums[low] < nums[mid] < nums[high]:
                ans = min(ans, nums[low])
                low, high = mid + 1, mid - 1

            # Left half is sorted, take the min from left half and trim search space to the right half
            elif nums[low] <= nums[mid]:
                ans = min(ans, nums[low])
                low = mid + 1

            # Right half is sorted, take the min from the right half and trim search space to the left half
            else:
                ans = min(ans, nums[mid])
                high = mid - 1

        return ans

# Testing the solution
assert Solution().findMin([3,4,5,1,2]) == 1
assert Solution().findMin([4,5,6,7,0,1,2]) == 0
assert Solution().findMin([11,13,15,17]) == 11
```

</div>

<div id="c2e4d69a" class="cell markdown"
papermill="{&quot;duration&quot;:2.023e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.031916&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.011686&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.073534Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.072927Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.080489Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.079686Z&quot;}"
papermill="{&quot;duration&quot;:3.0252e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.082224&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.051972&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
arr = [2, 3, 4, 5, 1]
N = len(arr)
low, high, ans = 0, N - 1, 0
while low <= high:
    mid = (low + high) // 2
    if arr[low] <= arr[mid]:
        if arr[ans] > arr[low]:
            ans = low
        low = mid + 1
    else:
        if arr[ans] > arr[mid]:
            ans = mid
        high = mid - 1

ans
```

<div class="output execute_result" execution_count="18">

    4

</div>

</div>

<div id="5769e9e8" class="cell markdown"
papermill="{&quot;duration&quot;:2.0122e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.122729&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.102607&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.165131Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.164405Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.170656Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.169872Z&quot;}"
papermill="{&quot;duration&quot;:2.9649e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.172470&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.142821&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force approach
# Time - O(N)
arr = [1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6]
res = 0
for i in arr:
    res ^= i
res
```

<div class="output execute_result" execution_count="19">

    4

</div>

</div>

<div id="69d77039" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.215023Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.214513Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.223551Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.222693Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1965e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.225213&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.193248&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better approach: O(log N)
"""
[1, 2, 2]
[1, 1, 2]
[1, 2, 2, 3, 3]
[1, 1, 2, 3, 3]
[1, 1, 2, 2, 3]
[1, 2, 2, 3, 3, 4, 4]
[1, 1, 2, 3, 3, 4, 4]
[1, 1, 2, 2, 3, 4, 4]
[1, 1, 2, 2, 3, 3, 4]
# if mid is odd, mid - 1, mid should be same for left to be okay: low = mid + 1 / high = mid + 1
# if mid is even, mid, mid + 1 should be the same for left to be okay: low = mid / high = mid
"""
arr = [1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6]
N = len(arr)
low, high = 0, N - 1
while low < high:
    mid = (low + high) // 2
    if mid % 2 == 0:
        if arr[mid] == arr[mid + 1]:
            low = mid
        else:
            high = mid
    else:
        if arr[mid] == arr[mid - 1]:
            low = mid + 1
        else:
            high = mid - 1

arr[low]
```

<div class="output execute_result" execution_count="20">

    4

</div>

</div>

<div id="1879fb32" class="cell markdown"
papermill="{&quot;duration&quot;:2.0392e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.266373&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.245981&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.308648Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.308031Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.314884Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.314137Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9953e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.316619&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.286666&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def findPeakElement(arr: [int]) -> int:
    N = len(arr)
    low, high = 0, N - 1
    while low <= high:
        mid = (low + high) // 2
        l, m, r = arr[mid - 1] if mid > 0 else -math.inf, arr[mid], arr[mid + 1] if mid < N - 1 else -math.inf
        if l <  m > r:
            return mid
        elif l < m < r:
            low = mid + 1
        # handles both cases - l > m > r and l > m < r
        # If the case is l > m < r, multiple peak exists, going any dir we would be able to reach a peak
        else:
            high = mid - 1
    return -1

# Testing the solution
assert findPeakElement([1, 2, 3, 1]) == 2
assert findPeakElement([1,2,1,3,5,6,4]) == 5
```

</div>

<div id="399ae8e1" class="cell markdown"
papermill="{&quot;duration&quot;:2.0127e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.357198&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.337071&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=Bsv3FPUX_BA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=54>
Square root of a number using binary search Take home:

1.  For questions involving patterns where ans is possible uptil a
    certain extent and post which answers are not possible, we can apply
    our binary search algorithm (we always know the range of possible
    answers)
2.  When we are having regions of possible and not possible like so:
    \[ans, ans, ans, not ans, not ans\] - at the end of binary search,
    low will end up pointing at a position that is 1 greater than the
    ans (3) while high will end up pointing at the ans (2)

</div>

<div id="64144c7a" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.399491Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.399227Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.438113Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.437288Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.1957e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.439760&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.377803&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def floorSqrt(n: int) -> int:
    'Time - O(log n)'
    low, high = 1, n
    while low <= high:
        mid = (low + high) // 2
        if mid * mid > n:
            high = mid - 1
        else:
            low = mid + 1

    return high

# Testing the solution
for i in tqdm.tqdm(range(int(1e4))):
    assert floorSqrt(i) == int(math.sqrt(i))
```

<div class="output stream stderr">

      0%|          | 0/10000 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 10000/10000 [00:00<00:00, 329974.35it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="21ab1eeb" class="cell markdown"
papermill="{&quot;duration&quot;:2.0662e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.482303&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.461641&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=rjEJeYCasHs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=55>
Find Nth root of an integer

</div>

<div id="8e8ba6e9" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.524760Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.524446Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.530330Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.529657Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9158e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.532027&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.502869&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force
def NthRoot_brute(n: int, m: int) -> int:
    "Brute force - O(m * n)"
    for i in range(m):
        curr = 1
        for _ in range(n):
            curr *= i
            if curr > m:
                break
        if curr == m:
            return i
        elif curr > m:
            break
    return -1

# Testing the solution
assert NthRoot_brute(3, 27) == 3
assert NthRoot_brute(4, 69) == -1
```

</div>

<div id="accd0d1c" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.574908Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.574636Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.581318Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.580618Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0067e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.583034&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.552967&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal - Binary Search
def NthRoot_binary(n: int, m: int) -> int:
    "Using binary search - O(log m * n)"
    low, high = 0, m
    while low <= high:
        mid = (low + high) // 2

        curr = 1
        for _ in range(n):
            curr *= mid
            if curr > m:
                break

        if curr == m:
            return mid
        elif curr < m:
            low = mid + 1
        else:
            high = mid - 1

    return -1

# Testing the solution
assert NthRoot_binary(3, 27) == 3
assert NthRoot_binary(4, 69) == -1
```

</div>

<div id="201c8d96" class="cell markdown"
papermill="{&quot;duration&quot;:2.0513e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.624336&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.603823&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/qyfekrNni90?si=N28mkp8Cyx4lvNIq>  
Problem: Koko eating bananas

</div>

<div id="24fcadf8" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.667508Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.666781Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.672946Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.672272Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.945e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.674595&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.645145&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force solution: O(v * h)
def minimumRateToEatBananas_brute(v: list[int], h: int) -> int:
    m, min_hours = 0, sum(v)
    while min_hours > h:
        m += 1
        min_hours = 0
        for p in v:
            min_hours += math.ceil(p / m)

    return m

# Testing the solution
assert minimumRateToEatBananas_brute([7, 15, 6, 3], 8) == 5
assert minimumRateToEatBananas_brute([25, 12, 8, 14, 19], 5) == 25
```

</div>

<div id="77605b2a" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.717815Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.717213Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.725975Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.725341Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2048e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.727584&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.695536&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better solution
def minimumRateToEatBananas_better(v: list[int], h: int) -> int:
    def compute_hours(m: int) -> int:
        "Assumes piles is sorted in asc order"
        V = N # Copy N for modification
        hours = 0
        while v[V - 1] > m and V > 0:
            hours += math.ceil(v[V - 1] / m)
            V -= 1

        return hours + V

    N = len(v)

    # Time: O(v log v)
    v.sort()

    # Binary search
    low, high = 1, v[-1]
    while low <= high:
        mid = (low + high) // 2
        curr = compute_hours(mid)
        if curr > h:
            low = mid + 1
        else:
            high = mid - 1

    return low

# Testing the solution
assert minimumRateToEatBananas_better([9], 2) == 5
assert minimumRateToEatBananas_better([7, 15, 6, 3], 8) == 5
assert minimumRateToEatBananas_better([25, 12, 8, 14, 19], 5) == 25
```

</div>

<div id="81512acb" class="cell markdown"
papermill="{&quot;duration&quot;:2.0587e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.768913&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.748326&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=TXAuxeYBTdg&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=57>
Minimum days to make M boquets

</div>

<div id="76ca4e35" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.811469Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.811003Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.820603Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.819882Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2756e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.822232&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.789476&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Solution link: https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/submissions/1213963810
class Solution:
    def minDays(self, bloomDay: list[int], m: int, k: int) -> int:
        def countBoquets(day: int) -> int:
            "Count boquets in O(N) time"
            flower_count, boquet_count = 0, 0
            for i in range(N):
                if bloomDay[i] <= day:
                    flower_count += 1
                else:
                    flower_count = 0

                if flower_count == k:
                    boquet_count += 1
                    flower_count = 0

            return boquet_count

        N = len(bloomDay)

        answer_range = sorted(set(bloomDay))
        answer_range_length = len(answer_range)
        low, high = 0, answer_range_length - 1
        while low <= high:
            mid = (low + high) // 2
            boquet_count = countBoquets(answer_range[mid])
            if boquet_count >= m:
                high = mid - 1
            else:
                low = mid + 1

        return answer_range[low] if low < answer_range_length else -1

# Testing the solution
assert Solution().minDays([1,10,3,10,2], 3, 1) == 3
assert Solution().minDays([1,10,3,10,2], 3, 2) == -1
assert Solution().minDays([7,7,7,7,12,7,7], 2, 3) == 12
```

</div>

<div id="03f3ffa2" class="cell markdown"
papermill="{&quot;duration&quot;:2.0613e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.863751&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.843138&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UvBKTVaG6U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=58>
Smallest divisor given the threshold

</div>

<div id="fbac3ba5" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:35.906867Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.906389Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:35.913975Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:35.913183Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1184e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.915582&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.884398&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Solution Link: https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/submissions/1213975584
class Solution:
    def smallestDivisor(self, nums: list[int], threshold: int) -> int:
        def calcThresh(divisor: int) -> int:
            thresh = 0
            for n in nums:
                thresh += math.ceil(n / divisor)
            return thresh

        N = len(nums)
        low, high = 1, max(nums)
        while low <= high:
            mid = (low + high) // 2
            if calcThresh(mid) <= threshold:
                high = mid - 1
            else:
                low = mid + 1

        return low

# Testing the solution
assert Solution().smallestDivisor([1,2,5,9], 6) == 5
assert Solution().smallestDivisor([44,22,33,11,1], 5) == 44
assert Solution().smallestDivisor([21212,10101,12121], 1000000) == 1
```

</div>

<div id="01e65497" class="cell markdown"
papermill="{&quot;duration&quot;:2.0942e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:35.957398&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.936456&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MG-Ac4TAvTY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=59>
Capacity to ship packages in D Days

</div>

<div id="48336458" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.000325Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:35.999741Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.007939Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.007296Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1404e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.009613&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:35.978209&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Problem link: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/submissions/1214006136
class Solution:
    def shipWithinDays(self, weights: list[int], days: int) -> int:
        def countDays(capacity: int) -> int:
            day_count = 0
            weight = 0
            for w in weights:
                if weight + w <= capacity:
                    weight += w
                else:
                    day_count += 1
                    weight = w

            return day_count + 1

        # Sort the weights
        N = len(weights)

        # Min, max possibile answer - Binary search
        low, high = max(weights), sum(weights)
        while low <= high:
            mid = (low + high) // 2
            day_count = countDays(mid)
            if day_count <= days:
                high = mid - 1
            else:
                low = mid + 1

        return low

# Testing the solution
assert Solution().shipWithinDays([1,2,3,4,5,6,7,8,9,10], 5) == 15
assert Solution().shipWithinDays([3,2,2,4,1,4], 3) == 6
assert Solution().shipWithinDays([1,2,3,1,1], 4) == 3
```

</div>

<div id="0a0d2642" class="cell markdown"
papermill="{&quot;duration&quot;:2.0699e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.051546&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.030847&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=uZ0N_hZpyps&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=60>
Kth missing +ve number:
<https://leetcode.com/problems/kth-missing-positive-number/submissions/1215199274/>

</div>

<div id="fdbc80fd" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.094427Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.093791Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.102689Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.101934Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2267e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.104467&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.072200&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Linear run time solution
class Solution:
    def findKthPositive_brute(self, arr: list[int], k: int) -> int:
        "Brute force: Time - O(N), Space - O(N)"
        present: set[int] = set(arr)
        max_ = arr[-1] + k
        for i in range(1, max_ + 1):
            if i not in present:
                k -= 1
            if k == 0:
                break
        return i

    def findKthPositive_better(self, arr: list[int], k: int) -> int:
        "Striver Better solution: Time - O(N), Space - O(1)"
        for n in arr:
            if n <= k:
                k += 1
            else:
                break
        return k

    def findKthPositive(self, arr: list[int], k: int) -> int:
        """
        Optimal - Binary search: Time - O(log N)
        Primary Observation: Count of missing elements prior to index: arr[idx] - idx - 1.
        This is because if there were no missing elements, at any idx the number should be idx + 1.

        With this logic in mind, we can apply binary search.
        """
        N = len(arr)
        low, high = 0, N - 1
        while low <= high:
            mid = (low + high) // 2
            missing_count = arr[mid] - mid - 1
            if missing_count < k:
                low = mid + 1
            else:
                high = mid - 1

        # arr[high] + more 
        # arr[high] + k - missing 
        # arr[high] + k - arr[high] + high + 1
        return high + k + 1

# Testing the solution
assert Solution().findKthPositive([2, 3, 4, 7, 11], 5) == 9
```

</div>

<div id="5275fb71" class="cell markdown"
papermill="{&quot;duration&quot;:2.0787e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.146124&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.125337&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=R_Mfw4ew-Vo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=61>

</div>

<div id="8139b363" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.188841Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.188151Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.194874Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.194115Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9879e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.196482&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.166603&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force: ~ O(2 ^ N)
def aggressiveCows(stalls: list[int], k: int) -> int:
    def compute_min_distance(placement: tuple[int]) -> int:
        dist = stalls[-1] - stalls[0]
        for i in range(k - 1):
            dist = min(dist, placement[i + 1] - placement[i])

        return dist

    # Sort the stalls so that the min dist would always be between 2 consequtive stalls
    stalls.sort()

    # Generate all subsequences
    result = 0
    for placement in itertools.combinations(stalls, k):
        result = max(result, compute_min_distance(placement))
    return result

# Testing the solution
assert aggressiveCows([0, 3, 4, 7, 10, 9], 4) == 3
assert aggressiveCows([4, 2, 1, 3, 6], 2) == 5
```

</div>

<div id="ba2f0950" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.239386Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.238855Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.246513Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.245766Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.102e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.248288&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.217268&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better: ~ O(N ^ 2) 
def aggressiveCows(stalls: list[int], k: int) -> int:
    stalls.sort()

    N = len(stalls)

    distances = []
    for i in range(N - 1):
        distances.append(stalls[i + 1] - stalls[i])

    # Eliminate N - k stalls
    for i in range(N - k):
        # Find min dist idx
        min_ = 0
        for j in range(N - i - 1):
            if distances[j] < distances[min_]:
                min_ = j
        # Combine with the smaller value
        if min_ == 0 or (min_ < N - i - 2 and distances[min_ + 1] < distances[min_ - 1]):
            distances[min_ + 1] += distances[min_]
        else:
            distances[min_ - 1] += distances[min_]

        # Remove that distance
        distances.pop(min_)

    return min(distances)

# Testing the solution
assert aggressiveCows([0, 3, 4, 7, 10, 9], 4) == 3
assert aggressiveCows([4, 2, 1, 3, 6], 2) == 5
```

</div>

<div id="64f42a77" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.291595Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.291023Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.298533Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.297814Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0762e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.300152&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.269390&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal Striver: O(N log N)
def aggressiveCows(stalls: list[int], k: int) -> int:
    def place_cows(dist: int) -> bool:
        "Place k cows with a min of k dist (>= dist)"

        # Place 1st cow at idx 0
        k_, prev = k - 1, 0
        for i in range(1, N):
            if stalls[i] - stalls[prev] >= dist:
                prev = i
                k_ -= 1
            if k_ == 0:
                break

        return k_ == 0

    N = len(stalls)
    stalls.sort()

    low, high = 1, stalls[-1] - stalls[0]
    while low <= high:
        mid = (low + high) // 2
        if place_cows(mid):
            low = mid + 1
        else:
            high = mid - 1

    return high

# Testing the solution
assert aggressiveCows([0, 3, 4, 7, 10, 9], 4) == 3
assert aggressiveCows([4, 2, 1, 3, 6], 2) == 5
```

</div>

<div id="c6415f70" class="cell markdown"
papermill="{&quot;duration&quot;:2.0609e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.341615&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.321006&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=Z0hwjftStI4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=62>

</div>

<div id="4e6344ff" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.384674Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.383994Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.391244Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.390498Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0812e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.393110&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.362298&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force solution, Time, Space: O(N!)
def findPages(arr: list[int], n: int, m: int) -> float:
    N = len(arr)

    @functools.cache
    def backtrack(start: int, n_students: int) -> float:
        if n_students == 1:
            return sum(arr[start:])

        else:
            result = math.inf
            sum_ = 0
            for i in range(start, N - n_students + 1):
                sum_ += arr[i]
                result = min(result, max(sum_, backtrack(i + 1, n_students - 1)))

            return result

    result = backtrack(0, m)
    return -1 if math.isinf(result) else result

# Testing the solution
assert findPages([12, 34, 67, 90], 4, 2) == 113
assert findPages([25, 46, 28, 49, 24], 5, 4) == 71
```

</div>

<div id="569cb019" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.436607Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.435901Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.444477Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.443833Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2109e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.446223&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.414114&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal - Binary search, Time - O(N log N)
def findPages(arr: list[int], n: int, m: int) -> float:
    N = len(arr)

    def assign(maxPages: int) -> bool:
        """
        Logic for this is more crucial than binary search itself.

        Tip: Splits, Subarrays (contiguous).

        To check if the maxPages is possible we GREEDILY assign as much as
        possible to each guy before moving to the next guy.
        """
        n_std, curr = 1, 0
        for i in range(N):
            if curr + arr[i] <= maxPages:
                curr += arr[i]
            else:
                n_std, curr = n_std + 1, arr[i]

        return n_std <= m

    if N < m:
        return -1
    else:
        low, high = max(arr), sum(arr)
        while low <= high:
            mid = (low + high) // 2
            if assign(mid):
                high = mid - 1
            else:
                low = mid + 1

        return low

# Testing the solution
assert findPages([12, 34, 67, 90], 4, 2) == 113
assert findPages([25, 46, 28, 49, 24], 5, 4) == 71
assert findPages([2, 8, 8, 4, 5], 5, 6) == -1
```

</div>

<div id="693edc5b" class="cell markdown"
papermill="{&quot;duration&quot;:2.0506e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.487570&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.467064&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=thUd_WJn6wk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=63>
Problem Link:
<https://leetcode.com/problems/split-array-largest-sum/submissions/1216912768>

</div>

<div id="2f94d583" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.530199Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.529568Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.537857Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.537219Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1367e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.539452&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.508085&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class Solution:
    def splitArray(self, nums: list[int], k: int) -> int:
        N = len(nums)

        def countSplits(max_: int) -> bool:
            """
            Greedily assign as much as possible to each guy before moving forward.
            Same logic as the problem above. Remember only applicable for contigous
            array slices: subarrays, splits, etc.
            """
            n_splits, sum_ = 1, 0
            for i in range(N):
                if sum_ + nums[i] <= max_:
                    sum_ += nums[i]
                else:
                    n_splits, sum_ = n_splits + 1, nums[i]

            return n_splits <= k

        if k > N:
            return -1
        else:
            low, high = max(nums), sum(nums)
            while low <= high:
                mid = (low + high) // 2
                if countSplits(mid):
                    high = mid - 1
                else:
                    low = mid + 1

            return low

# Testing the solution
assert Solution().splitArray([7,2,5,10,8], 2) == 18
assert Solution().splitArray([1, 2, 3, 4, 5], 2) == 9
```

</div>

<div id="b17280b3" class="cell markdown"
papermill="{&quot;duration&quot;:2.067e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.581288&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.560618&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=kMSBvlZ-_HA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=64>

</div>

<div id="b31b6aea" class="cell code" execution_count="37"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.624245Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.623544Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.632060Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.631394Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.185e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.633765&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.601915&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimiseMaxDistance(arr: list[int], k: float) -> float:

    def check(thresh: float) -> bool:
        """
        If curr_dist is > thresh, try to split just until dist = thresh

        >>> curr_dist / (n + 1) == thresh
        >>> curr_dist / thresh - 1 = n 
        """

        n_splits = 0
        for i in range(N - 1):
            curr_dist = arr[i + 1] - arr[i]
            if curr_dist > thresh:
                # Ceil without using math.ceil => -(-x // 1)
                splits_required = -(-curr_dist // thresh) - 1
                n_splits += int(splits_required)

        return n_splits <= k

    N = len(arr)
    max_dist = 0.
    for i in range(N - 1):
        max_dist = max(max_dist, arr[i + 1] - arr[i])

    low, high = 0., max_dist
    while high - low > 1e-7:
        mid = (low + high) / 2
        if check(mid):
            high = mid
        else:
            low = mid

    return low

# Testing the solution
assert round(minimiseMaxDistance([1, 2, 3, 4, 5], 4), 6) == 0.5
assert round(minimiseMaxDistance([1, 2, 5], 4), 6) == 0.75
assert round(minimiseMaxDistance([1, 3], 2), 6) == 0.666667
```

</div>

<div id="d0e0c3f2" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.676743Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.676096Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.686435Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.685778Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3648e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.688173&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.654525&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Striver - Brute force approach (simpler)
def minimiseMaxDistance(arr: list[int], k: int) -> float:
    """
    Time - O(N^2) originally, optimized with the usage of heaps to O(N log N)

    We place the k one by one. Keeping track of how many gas stations we placed
    at each gap. If we are to place additional gas station into a gap that already
    contains a gas station, we would remove existing gas station and place both gas
    stations at equal distances.

    [1, _, 2], 1 => [1, 1.5, 2]
    [1, _, 2], 2 => [1, 1.3, 1.6, 2]
    [1, _, 2], 3 => [1, 1.25, 1.5, 1.75, 2]

    """

    class Node:
        def __init__(self, dist: int, placed: int = 0):
            self.dist = dist
            self.placed = placed
            self.compute_gap()

        def compute_gap(self):
            self.gap = - self.dist / (self.placed + 1)

        def increment_placed(self):
            self.placed += 1
            self.compute_gap()

        def __repr__(self):
            return f'{self.dist}/{self.placed}:{self.gap}'

        def __lt__(self, other: 'Node'):
            return self.gap < other.gap

    N = len(arr)
    nodes: list[Node] = []
    for i in range(N - 1):
        nodes.append(Node(dist=arr[i + 1] - arr[i], placed=0))

    # Convert into max heap
    heapq.heapify(nodes)

    for i in range(k):
        # Find the max distance and try to minimize it
        max_node = heapq.heappop(nodes)
        max_node.increment_placed()
        heapq.heappush(nodes, max_node)

    # Compute the max distance
    return -nodes[0].gap

# Testing the solution
assert round(minimiseMaxDistance([1, 2, 3, 4, 5], 4), 6) == 0.5
assert round(minimiseMaxDistance([1, 2, 5], 4), 6) == 0.75
assert round(minimiseMaxDistance([1, 3], 2), 6) == 0.666667
```

</div>

<div id="355b5a37" class="cell markdown"
papermill="{&quot;duration&quot;:2.0635e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.729794&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.709159&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=C2rRzz-JDk8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=65>
Median of two sorted ararys

</div>

<div id="f6508851" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.772533Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.772031Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.779734Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.779050Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1106e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.781461&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.750355&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force solution: Time, Space: O(M + N)
class Solution:
    def findMedianSortedArrays(self, nums1: list[int], nums2: list[int]) -> float:
        # Merge both arrays in sorted order 
        N1, N2 = len(nums1), len(nums2)
        N = N1 + N2
        i = j = 0
        nums: list[int] = []
        while i < N1 or j < N2:
            if j == N2 or (i < N1 and nums1[i] < nums2[j]):
                nums.append(nums1[i])
                i += 1
            else:
                nums.append(nums2[j])
                j += 1

        # Return median
        mid = -(-N // 2) # Ceil of the number
        if N % 2 == 0:
            return (nums[mid - 1] + nums[mid]) / 2
        else:
            return nums[mid - 1]

# Testing the solution
assert Solution().findMedianSortedArrays([1, 3], [2]) == 2
assert Solution().findMedianSortedArrays([1, 2], [3, 4]) == 2.5
```

</div>

<div id="612f92c2" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.824419Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.823900Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.832014Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.831340Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1571e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.833878&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.802307&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better solution: Time: O(M + N), Space: O(1)
class Solution:
    def findMedianSortedArrays(self, nums1: list[int], nums2: list[int]) -> float:
        N1, N2 = len(nums1), len(nums2)
        N = N1 + N2
        curr_idx = i = j = 0

        # Left, Right based on N
        mid = -(-N // 2) # Ceil of the number
        if N % 2 == 0:
            left_idx, right_idx = mid - 1, mid
        else:
            left_idx = right_idx = mid - 1

        while i < N1 or j < N2:
            if (j == N2) or (i < N1 and nums1[i] < nums2[j]):
                curr = nums1[i]
                i += 1
            else:
                curr = nums2[j]
                j += 1
            if curr_idx == left_idx:
                left = curr
            if curr_idx == right_idx:
                right = curr
                break

            curr_idx += 1

        return (left + right) / 2

# Testing the solution
assert Solution().findMedianSortedArrays([1, 3], [2]) == 2
assert Solution().findMedianSortedArrays([1, 2], [3, 4]) == 2.5
```

</div>

<div id="0daf9188" class="cell code" execution_count="41"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.877713Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.876978Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.889986Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.889199Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6654e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.891718&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.855064&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better solution, Time - O(log N * log N)
class Solution:
    @staticmethod
    def find_boundary_indices(target: int, arr: list[int], N: int) -> tuple[int, int]:
        low, high = 0, N - 1
        while low <= high:
            mid = (low + high) // 2
            if arr[mid] >= target:
                high = mid - 1
            else:
                low = mid + 1

        GTE_IDX = low

        # Upper bound Binary (Striver's approach)
        low, high = 0, N - 1
        while low <= high:
            mid = (low + high) // 2
            if arr[mid] > target:
                high = mid - 1
            else:
                low = mid + 1

        LTE_IDX = low

        return LTE_IDX, GTE_IDX

    def findMedianSortedArrays(self, nums1: list[float], nums2: list[float]) -> float:
        N1, N2 = len(nums1), len(nums2)
        low, high = min(nums1[0], nums2[0]), max(nums1[-1], nums2[-1])
        while low < high:
            mid = (low + high) / 2
            lte_idx1, gte_idx1 = Solution.find_boundary_indices(mid, nums1, N1)
            lte_idx2, gte_idx2 = Solution.find_boundary_indices(mid, nums2, N2)
            lte = lte_idx1 + lte_idx2
            gte = N1 - gte_idx1 + N2 - gte_idx2
            if lte == gte:
                low = high = mid
            elif lte < gte:
                low = -(-mid // 1)
            else:
                high = mid // 1

        lte_idx1, gte_idx1 = Solution.find_boundary_indices(low, nums1, N1)
        lte_idx2, gte_idx2 = Solution.find_boundary_indices(low, nums2, N2)

        lte = max(nums1[lte_idx1 - 1] if lte_idx1 > 0 else -math.inf, nums2[lte_idx2 - 1] if lte_idx2 > 0 else -math.inf)
        gte = min(nums1[gte_idx1] if gte_idx1 < N1 else math.inf, nums2[gte_idx2] if gte_idx2 < N2 else math.inf)
        return (lte + gte) / 2

# Testing the solution
assert Solution().findMedianSortedArrays([1, 3], [2]) == 2
assert Solution().findMedianSortedArrays([1, 2], [3, 4]) == 2.5
```

</div>

<div id="cf415db1" class="cell code" execution_count="42"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:36.934718Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:36.934041Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:36.943226Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:36.942599Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2493e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.944987&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.912494&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Striver Optimal Solution - O(log N)
# Video Link: https://www.youtube.com/watch?v=F9c7LpRZWVQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=67
def median(nums1: list[int], nums2: list[int]) -> float:
    N1, N2 = len(nums1), len(nums2)
    N = N1 + N2

    if N1 > N2:
        return median(nums2, nums1)

    low, high = 0, N1
    left_len = (N1 + N2 + 1) // 2
    while low <= high:
        mid1 = (low + high) // 2
        mid2 = left_len - mid1
        l1 = nums1[mid1 - 1] if mid1 > 0 else -math.inf
        l2 = nums2[mid2 - 1] if mid2 > 0 else -math.inf
        r1 = nums1[mid1] if mid1 < N1 else math.inf
        r2 = nums2[mid2] if mid2 < N2 else math.inf

        if l1 <= r2 and l2 <= r1:
            if N % 2 == 0:
                return (max(l1, l2) + min(r1, r2)) / 2
            else:
                return max(l1, l2)

        # Smaller array is not centered, arr1 is on the left part
        elif l1 > r2:
            high = mid1 - 1

        # (l2 > r1) Larger array is not centered, arr2 is on the right part (arr1 is on the left part)
        else:
            low = mid1 + 1

    return -1

# Testing the solution
assert median([1, 3], [2]) == 2
assert median([1, 2], [3, 4]) == 2.5
```

</div>

<div id="6ed3c9e0" class="cell markdown"
papermill="{&quot;duration&quot;:2.0704e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:36.986894&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:36.966190&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=D1oDwWCq50g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=67>
Find kth element of two sorted arrays

</div>

<div id="394757ce" class="cell code" execution_count="43"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.031231Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.030704Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.037878Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.037167Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1869e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.039551&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.007682&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force - Time: O(M + N), Space: O(1)
def kthElement_brute(arr1: list[int], N1: int, arr2: list[int], N2: int, k: int) -> int:
    i = j = 0
    while i < N1 or j < N2:
        if j == N2 or (i < N1 and arr1[i] <= arr2[j]):
            curr = arr1[i]
            i += 1
        else:
            curr = arr2[j]
            j += 1

        k -= 1
        if k == 0:
            return curr

    else:
        return -1

# Testing the solution
assert kthElement_brute([2, 3, 45], 3, [4, 6, 7, 8], 4, 4) == 6
assert kthElement_brute([1, 2, 3, 5, 6], 5, [4, 7, 8, 9, 100], 5, 6) == 6
```

</div>

<div id="633de9ca" class="cell code" execution_count="44"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.082566Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.081881Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.090924Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.090263Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2249e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.092620&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.060371&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def kthElement(arr1: list[int], N1: int, arr2: list[int], N2: int, k: int) -> float:
    N1, N2 = len(arr1), len(arr2)
    N = N1 + N2

    if N1 > N2:
        return kthElement(arr2, N2, arr1, N1, k)

    left_length = k
    low, high = max(0, k - N2), min(N1, k)
    while low <= high:
        mid1 = (low + high + 1) // 2
        mid2 = left_length - mid1
        l1 = arr1[mid1 - 1] if mid1 > 0 else -math.inf
        l2 = arr2[mid2 - 1] if mid2 > 0 else -math.inf
        r1 = arr1[mid1] if mid1 < N1 else math.inf
        r2 = arr2[mid2] if mid2 < N2 else math.inf

        if l1 <= r2 and l2 <= r1:
            return max(l1, l2)
        elif l1 > r2:
            high = mid1 - 1
        else: # l2 > r1
            low = mid1 + 1

    else:
        return -1

# Testing the solution
assert kthElement([2, 3, 45], 3, [4, 6, 7, 8], 4, 4) == 6
assert kthElement([1, 2, 3, 5, 6], 5, [4, 7, 8, 9, 100], 5, 6) == 6
```

</div>

<div id="dfcc5868" class="cell markdown"
papermill="{&quot;duration&quot;:2.0477e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.133858&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.113381&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=SCz-1TtYxDI&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=68>
Row with maximum number of 1s

</div>

<div id="16ce254c" class="cell code" execution_count="45"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.177052Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.176321Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.184104Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.183351Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1199e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.185896&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.154697&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Time complexity: O(n * log m)
def rowWithMax1s(matrix: list[list[int]], n: int, m: int) -> int:
    def count1s(row_idx: int) -> int:
        low, high = 0, m - 1
        while low <= high:
            mid = (low + high) // 2
            if matrix[row_idx][mid] == 1:
                high = mid - 1
            else:
                low = mid + 1

        return m - low

    # Row Idx, Count
    max_ = -1, 0
    for i in range(n):
        curr_count = count1s(i)
        if curr_count > max_[1]:
            max_ = i, curr_count

    return max_[0]

# Testing the solution
assert rowWithMax1s([[0], [0]], 2, 1) == -1
assert rowWithMax1s([[1, 1], [1, 1]], 2, 2) == 0
assert rowWithMax1s([[1, 1, 1], [0, 0, 1], [0, 0, 0]], 3, 3) == 0
```

</div>

<div id="749c2af1" class="cell markdown"
papermill="{&quot;duration&quot;:2.0782e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.227588&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.206806&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=JXU4Akft7yk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=69>
Problem: Search in a 2D Matrix Leetcode Link:
<https://leetcode.com/problems/search-a-2d-matrix/submissions/1219630053>

</div>

<div id="2ffd05c3" class="cell code" execution_count="46"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.270831Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.270146Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.275560Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.274808Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8823e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.277266&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.248443&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force Solution, Time: O(M * N)
def searchMatrix_brute(matrix: list[list[int]], target: int) -> bool:
    M = len(matrix)
    N = len(matrix[0])
    for i in range(M):
        for j in range(N):
            if matrix[i][j] == target:
                return True
    return False
```

</div>

<div id="f2e9197e" class="cell code" execution_count="47"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.320402Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.319846Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.336421Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.335685Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.9762e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.338101&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.298339&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal Solution, Time: O(log M + log N) = O(log MN)
def searchMatrix(matrix: list[list[int]], target: int) -> bool:
    M = len(matrix)
    N = len(matrix[0])

    row_low, row_high = 0, M - 1
    while row_low <= row_high:
        row_mid = (row_low + row_high) // 2

        # Check if present in this row
        if matrix[row_mid][0] <= target <= matrix[row_mid][N - 1]:

            # Binary search inside to find the column idx
            col_low, col_high = 0, N - 1
            while col_low <= col_high:
                col_mid = (col_low + col_high) // 2
                if matrix[row_mid][col_mid] == target:
                    return True
                elif matrix[row_mid][col_mid] < target:
                    col_low = col_mid + 1
                else:
                    col_high = col_mid - 1
            else:
                return False

        # If row[0] > target, search for row before curr
        elif matrix[row_mid][0] > target:
            row_high = row_mid - 1

        # If row[-1] < target, search for row after curr
        else:
            row_low = row_mid + 1

    else:
        return False

# Create a simple generator that returns random numbers in order
def generate_random_range() -> typing.Generator[int, bool, None]:
    "Can be reset by sending in a `True` value"
    i = 0
    while True:
        if random.random() > 0.5:
            reset = yield i
            if reset:
                yield True
                i = -1
        i += 1

# Testing the solution
rand_gen = generate_random_range()
for i in tqdm.tqdm(range(100)):

    temp: tuple[list[list[int]], int] = [[next(rand_gen) for j in range(5)] for i in range(5)], random.randint(1, 100)
    assert searchMatrix(temp[0], temp[1]) == searchMatrix_brute(temp[0], temp[1])

    # Reset the random number generator
    rand_gen.send(True)
```

<div class="output stream stderr">

      0%|          | 0/100 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 100/100 [00:00<00:00, 31595.51it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="cb866bec" class="cell code" execution_count="48"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.382051Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.381447Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.394174Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.393425Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6359e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.395813&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.359454&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Striverr Optimal Solution, Time: O(log MN)
def searchMatrix_striverr(matrix: list[list[int]], target: int) -> bool:
    "Idea is flatten the matrix into 1D conceptually and perform binary search"
    M, N = len(matrix), len(matrix[0])

    low, high = 0, M * N - 1
    while low <= high:
        mid = (low + high) // 2
        row, col = mid // M, mid % N
        if matrix[row][col] == target:
            return True
        elif matrix[row][col] < target:
            low = mid + 1
        else:
            high = mid - 1

    return False

# Testing the solution
for i in tqdm.tqdm(range(100)):
    temp: tuple[list[list[int]], int] = [[next(rand_gen) for j in range(5)] for i in range(5)], random.randint(1, 100) 
    assert searchMatrix_striverr(temp[0], temp[1]) == searchMatrix(temp[0], temp[1])
    rand_gen.send(True)
```

<div class="output stream stderr">

      0%|          | 0/100 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 100/100 [00:00<00:00, 42586.09it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="95c1c00b" class="cell markdown"
papermill="{&quot;duration&quot;:2.1203e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.438874&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.417671&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=9ZbB397jU4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=71>
Search in 2D matrix - II Problem Link:
<https://leetcode.com/problems/search-a-2d-matrix-ii/submissions/1220185663>

</div>

<div id="d4f067da" class="cell code" execution_count="49"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.483127Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.482550Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.528475Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.527648Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.9916e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.530202&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.460286&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def searchMatrix_II(matrix: list[list[int]], target: int) -> bool:
    """
    1. Given two pairs, (i1, j1), (i2, j2): the 2D slice can only contain values
    between matrix[i1][j1] <= val <= matrix[i2][j2]

    2. Take max of col, row. Split into half check if number can exist inside.
    If number can exist, recurse - searchFirst || searchSecond. Else don't check inside range.
    """
    def is_present(i1: int, j1: int, i2: int, j2: int) -> bool:
        return i1 <= i2 and j1 <= j2 and (matrix[i1][j1] <= target <= matrix[i2][j2])

    def binary_search(i1: int, j1: int, i2: int, j2: int):
        if is_present(i1, j1, i2, j2):

            if i1 == i2 and j1 == j2:
                return matrix[i1][j1] == target

            # Row length >= col length
            if i2 - i1 >= j2 - j1:
                mid = (i1 + i2) // 2
                recurse_ = binary_search(i1, j1, mid, j2) or binary_search(mid + 1, j1, i2, j2)
            else:
                mid = (j1 + j2) // 2
                recurse_ = binary_search(i1, j1, i2, mid) or binary_search(i1, mid + 1, i2, j2)

            return recurse_

        else:
            return False

    M, N = len(matrix), len(matrix[0])
    return binary_search(0, 0, M - 1, N - 1)

for i in tqdm.tqdm(range(100)):
    temp = np.random.randint(1, 1000, size=(30, 30)), random.randint(1, 1000)
    temp[0].sort(axis=1)
    temp[0].sort(axis=0)
    assert searchMatrix_brute(temp[0], temp[1]) == searchMatrix_II(temp[0], temp[1])
```

<div class="output stream stderr">

      0%|          | 0/100 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 100/100 [00:00<00:00, 3082.64it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="f019b7cc" class="cell code" execution_count="50"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.575070Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.574436Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.601379Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.600549Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:5.1037e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.603064&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.552027&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Striver Optimal Solution
# Time - O(M + N)
def searchMatrix_II_striverr(matrix: list[list[int]], target: int) -> bool:
    M, N = len(matrix), len(matrix[0])
    col, row = N - 1, 0
    while row < M and col >= 0:
        curr = matrix[row][col]
        if  curr == target:
            return True
        elif target < curr:
            col -= 1
        else:
            row += 1
    return False

# Testing the solution
for i in tqdm.tqdm(range(100)):
    temp = np.random.randint(1, 1000, size=(30, 30)), random.randint(1, 1000)
    temp[0].sort(axis=1)
    temp[0].sort(axis=0)
    assert searchMatrix_II(temp[0], temp[1]) == searchMatrix_II_striverr(temp[0], temp[1])
```

<div class="output stream stderr">

      0%|          | 0/100 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 100/100 [00:00<00:00, 5983.91it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="a54162f0" class="cell markdown"
papermill="{&quot;duration&quot;:2.1598e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.646909&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.625311&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nGGp5XBzC4g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=71>
Find Peak Element - II

</div>

<div id="0cbfa572" class="cell code" execution_count="51"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.691845Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.691139Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.701420Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.700778Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4405e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.703009&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.668604&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Time Complexity - O(M + N), Space Complexity - O(M + N)
# https://leetcode.com/problems/find-a-peak-element-ii/submissions/1220609319
def findPeakGrid(mat: list[list[int]]) -> tuple[int, int]:
    def getPeak(i: int, j: int) -> tuple[int, int]:
        peak = i, j
        if j > 0 and mat[i][j - 1] > mat[peak[0]][peak[1]]:
            peak = i, j - 1
        if j < N - 1 and mat[i][j + 1] > mat[peak[0]][peak[1]]:
            peak = i, j + 1
        if i > 0 and mat[i - 1][j] > mat[peak[0]][peak[1]]:
            peak = i - 1, j
        if i < M - 1 and mat[i + 1][j] > mat[peak[0]][peak[1]]:
            peak = i + 1, j
        return peak

    M, N = len(mat), len(mat[0])
    i, j = 0, 0
    while getPeak(i, j) != (i, j):
        i, j = getPeak(i, j)
    return i, j

# Testing the solution
assert findPeakGrid([[10,20,15],[21,30,14],[7,16,32]]) in ((1, 1), (2, 2))
assert findPeakGrid([[1,4],[3,2]]) in ((0, 1), (1, 0))
assert findPeakGrid([[7,2,3,1,2],[6,5,4,2,1]]) in ((0, 0),)
```

</div>

<div id="529479ab" class="cell code" execution_count="52"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.748359Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.747646Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.756985Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.756305Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3717e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.758591&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.724874&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Reduced Time Complexity: O(N log M)
# https://leetcode.com/problems/find-a-peak-element-ii/submissions/1220636332/
def findPeakGrid(mat: list[list[int]]) -> tuple[int, int]:
    M, N = len(mat), len(mat[0])
    low, high = 0, M - 1
    while low <= high:
        middle_row = (low + high) // 2
        max_col = 0
        for i in range(1, N):
            if mat[middle_row][i] > mat[middle_row][max_col]:
                max_col = i

        top = mat[middle_row - 1][max_col] if middle_row - 1 >= 0 else -math.inf
        bottom = mat[middle_row + 1][max_col] if middle_row + 1 < M else -math.inf
        curr = mat[middle_row][max_col]
        if top < curr > bottom:
            return middle_row, max_col
        elif top > curr:
            high = middle_row - 1
        else:
            low = middle_row + 1

    return -1, -1

# Testing the solution
assert findPeakGrid([[10,20,15],[21,30,14],[7,16,32]]) in ((1, 1), (2, 2))
assert findPeakGrid([[1,4],[3,2]]) in ((0, 1), (1, 0))
assert findPeakGrid([[7,2,3,1,2],[6,5,4,2,1]]) in ((0, 0),)
```

</div>

<div id="d90f55f6" class="cell markdown"
papermill="{&quot;duration&quot;:2.1728e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.802342&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.780614&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Q9wXgdxJq48?si=AvyxHYbdotetHALU>
<https://www.naukri.com/code360/problems/median-of-a-row-wise-sorted-matrix_1115473>

</div>

<div id="cb475dc7" class="cell code" execution_count="53"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.847255Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.846567Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.854119Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.853472Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1765e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.855738&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.823973&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force - O(M * N)
def matrixMedian_brute(matrix: list[list[int]], M: int, N: int) -> float:

    # Total count of elements
    T = M * N

    # Flatten  & sort the matrix - O(M * N) + O(M + N log (M + N))
    flattened: list[int] = sorted([n for row in matrix for n in row])

    # Return median - O(1)
    if T % 2 == 0:
        return (flattened[T // 2 - 1] + flattened[T // 2]) / 2
    else:
        return flattened[T // 2]

# Testing the solution
assert matrixMedian_brute([[1, 5, 7, 9, 11], [2, 3, 4, 8, 9], [4, 11, 14, 19, 20], [6, 10, 22, 99, 100], [7, 15, 17, 24, 28]], 5, 5) == 10
assert matrixMedian_brute([[1, 2, 3, 4, 5], [8, 9, 11, 12, 13], [21, 23, 25, 27, 29]], 3, 5) == 11
```

</div>

<div id="3ade4ca0" class="cell code" execution_count="54"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-02T14:32:37.901407Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-02T14:32:37.900916Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-02T14:32:37.911980Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-02T14:32:37.911203Z&quot;}"
papermill="{&quot;duration&quot;:3.5939e-2,&quot;end_time&quot;:&quot;2024-04-02T14:32:37.913626&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-02T14:32:37.877687&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better solution, O(M log (M + N))
def matrixMedian(matrix: list[list[int]], M: int, N: int) -> float:

    def count_row(row_idx: int, target: int) -> int:
        # Upper Bound
        low, high = 0, N - 1
        while low <= high:
            mid = (low + high) // 2
            curr = matrix[row_idx][mid]
            if curr <= target:
                low = mid + 1
            else:
                high = mid - 1

        return high + 1

    def count_matrix(target: int) -> int:
        count = 0
        for row in range(M):
            count  += count_row(row, target)
        return count

    # Total count of elements
    T = M * N

    # Find Min, Max
    min_, max_ = matrix[0][0], matrix[0][-1]
    for i in range(M):
        min_ = min(min_, matrix[i][0])
        max_ = max(max_, matrix[i][-1])

    # Binary search for median
    low, high = min_, max_
    while low <= high:
        mid = (low + high) // 2
        if count_matrix(mid) > (T // 2):
            high = mid - 1
        else:
            low = mid + 1
    return low

# Testing the solution
assert matrixMedian([[1, 5, 7, 9, 11], [2, 3, 4, 8, 9], [4, 11, 14, 19, 20], [6, 10, 22, 99, 100], [7, 15, 17, 24, 28]], 5, 5) == 10
assert matrixMedian([[1, 2, 3, 4, 5], [8, 9, 11, 12, 13], [21, 23, 25, 27, 29]], 3, 5) == 11
```

</div>
