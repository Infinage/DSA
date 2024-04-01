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
    duration: 5.132156
    end_time: "2024-04-01T17:06:10.298278"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-04-01T17:06:05.166122"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:1.7738e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.256069&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.238331&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:06.291179Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:06.290524Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:06.402600Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:06.401695Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.132518,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.405274&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.272756&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6472e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.443821&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.427349&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:06.480186Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:06.479377Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:06.484754Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:06.483925Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6228e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.487129&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.460901&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:06.525212Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:06.524472Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:06.544701Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:06.543671Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.0998e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.547086&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.506088&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 40427.03it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:06.606116Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:06.605728Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:06.619210Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:06.618427Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.7557e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.621004&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.573447&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 40556.02it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:7.4697e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.713045&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.638348&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:06.749592Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:06.748993Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:06.759521Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:06.758747Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0736e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.761376&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.730640&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:06.797730Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:06.796998Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:06.811355Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:06.810558Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4472e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.813158&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.778686&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 50530.74it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:06.850211Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:06.849402Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:06.856503Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:06.855753Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7313e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.858195&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.830882&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:06.894717Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:06.894079Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:06.908339Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:06.907517Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4753e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.910467&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.875714&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 54834.67it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:1.7578e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.946147&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.928569&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:06.983656Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:06.982891Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:06.990960Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:06.990219Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8753e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:06.992596&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:06.963843&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.029778Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.029178Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.036705Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.035865Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7959e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.038442&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.010483&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7864e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.074290&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.056426&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.112438Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.111577Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.117424Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.116746Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6819e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.119155&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.092336&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.157170Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.156382Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.169245Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.168436Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.365e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.171046&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.137396&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8271e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.207716&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.189445&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.245933Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.245303Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.256046Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.255292Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1733e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.257670&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.225937&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.296735Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.295942Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.308632Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.307847Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.4281e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.310337&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.276056&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8277e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.347573&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.329296&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.386099Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.385432Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.394598Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.393860Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0114e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.396180&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.366066&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8324e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.433219&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.414895&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.471913Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.471563Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.481528Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.480710Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.169e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.483259&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.451569&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8568e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.520665&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.502097&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.559103Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.558544Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.566467Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.565709Z&quot;}"
papermill="{&quot;duration&quot;:2.9072e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.568218&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.539146&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8549e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.605708&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.587159&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.663024Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.662271Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.669935Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.669268Z&quot;}"
papermill="{&quot;duration&quot;:4.7244e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.671561&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.624317&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8751e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.709434&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.690683&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.748760Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.748249Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.754458Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.753668Z&quot;}"
papermill="{&quot;duration&quot;:2.8016e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.756230&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.728214&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.795882Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.795268Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.803708Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.802961Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9966e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.805348&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.775382&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8945e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.843367&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.824422&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.883113Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.882365Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:07.889679Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:07.888910Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8982e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.891353&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.862371&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8849e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:07.929258&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.910409&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:07.968298Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:07.967991Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.008077Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.007272Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.1617e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.009810&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:07.948193&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 10000/10000 [00:00<00:00, 317370.42it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="21ab1eeb" class="cell markdown"
papermill="{&quot;duration&quot;:1.9008e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.048116&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.029108&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=rjEJeYCasHs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=55>
Find Nth root of an integer

</div>

<div id="8e8ba6e9" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.087713Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.087411Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.093189Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.092500Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.76e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.094897&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.067297&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.135199Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.134514Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.141538Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.140875Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9023e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.143259&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.114236&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9116e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.181649&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.162533&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/qyfekrNni90?si=N28mkp8Cyx4lvNIq>  
Problem: Koko eating bananas

</div>

<div id="24fcadf8" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.221639Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.220957Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.226992Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.226338Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7721e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.228659&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.200938&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.268819Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.268194Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.277012Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.276348Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0805e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.278670&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.247865&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.0282e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.318211&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.297929&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=TXAuxeYBTdg&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=57>
Minimum days to make M boquets

</div>

<div id="76ca4e35" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.358348Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.357735Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.367308Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.366656Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1439e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.368995&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.337556&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8931e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.407025&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.388094&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UvBKTVaG6U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=58>
Smallest divisor given the threshold

</div>

<div id="fbac3ba5" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.447298Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.446599Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.454273Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.453641Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.977e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.455981&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.426211&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9098e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.494712&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.475614&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MG-Ac4TAvTY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=59>
Capacity to ship packages in D Days

</div>

<div id="48336458" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.534515Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.533917Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.542262Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.541489Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0006e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.543879&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.513873&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9029e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.582093&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.563064&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=uZ0N_hZpyps&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=60>
Kth missing +ve number:
<https://leetcode.com/problems/kth-missing-positive-number/submissions/1215199274/>

</div>

<div id="fdbc80fd" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.621822Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.621507Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.630540Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.629866Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0855e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.632166&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.601311&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.914e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.670609&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.651469&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=R_Mfw4ew-Vo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=61>

</div>

<div id="8139b363" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.711053Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.710382Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.717173Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.716522Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9065e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.718927&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.689862&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.759909Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.759211Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.767255Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.766613Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0389e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.769069&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.738680&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.809593Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.808885Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.816712Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.816017Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.98e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.818356&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.788556&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9146e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.856737&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.837591&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=Z0hwjftStI4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=62>

</div>

<div id="4e6344ff" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.897020Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.896350Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.903827Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.903037Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9597e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.905580&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.875983&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:08.946108Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:08.945388Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:08.953960Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:08.953284Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0705e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.955669&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.924964&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9676e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:08.995161&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:08.975485&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=thUd_WJn6wk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=63>
Problem Link:
<https://leetcode.com/problems/split-array-largest-sum/submissions/1216912768>

</div>

<div id="2f94d583" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.035747Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.035055Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.043308Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.042547Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0481e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.045183&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.014702&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.914e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.083672&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.064532&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=kMSBvlZ-_HA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=64>

</div>

<div id="b31b6aea" class="cell code" execution_count="37"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.124762Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.124012Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.132838Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.132112Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1128e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.134546&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.103418&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.175557Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.174892Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.185685Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.184925Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3016e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.187419&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.154403&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9138e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.225924&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.206786&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=C2rRzz-JDk8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=65>
Median of two sorted ararys

</div>

<div id="f6508851" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.265808Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.265501Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.273464Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.272696Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0074e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.275156&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.245082&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.315687Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.315105Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.323240Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.322481Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0112e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.324938&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.294826&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.365039Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.364731Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.378046Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.377282Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5492e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.379867&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.344375&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.422624Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.421954Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.430905Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.430201Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3213e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.432702&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.399489&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9308e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.473606&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.454298&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=D1oDwWCq50g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=67>
Find kth element of two sorted arrays

</div>

<div id="394757ce" class="cell code" execution_count="43"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.514259Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.513774Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.520884Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.520083Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9151e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.522541&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.493390&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.562724Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.562055Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.570714Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.570089Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0492e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.572414&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.541922&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9119e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.610896&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.591777&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=SCz-1TtYxDI&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=68>
Row with maximum number of 1s

</div>

<div id="16ce254c" class="cell code" execution_count="45"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.651074Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.650457Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.658331Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.657560Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9759e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.659915&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.630156&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9297e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.698685&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.679388&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=JXU4Akft7yk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=69>
Problem: Search in a 2D Matrix Leetcode Link:
<https://leetcode.com/problems/search-a-2d-matrix/submissions/1219630053>

</div>

<div id="2ffd05c3" class="cell code" execution_count="46"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.740352Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.739710Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.746003Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.744962Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9724e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.747851&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.718127&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.788473Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.787914Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.804760Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.803853Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.9011e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.806445&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.767434&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 40217.70it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="cb866bec" class="cell code" execution_count="48"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.847798Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.847155Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.859906Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.859164Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.5066e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.861574&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.826508&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 43053.83it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="95c1c00b" class="cell markdown"
papermill="{&quot;duration&quot;:1.9809e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.901447&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.881638&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=9ZbB397jU4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=71>
Search in 2D matrix - II Problem Link:
<https://leetcode.com/problems/search-a-2d-matrix-ii/submissions/1220185663>

</div>

<div id="d4f067da" class="cell code" execution_count="49"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:09.942697Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:09.942061Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:09.987179Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:09.986390Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.7639e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:09.988853&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:09.921214&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 3142.20it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="f019b7cc" class="cell code" execution_count="50"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-01T17:06:10.031297Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-01T17:06:10.030947Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-01T17:06:10.057779Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-01T17:06:10.056955Z&quot;}"
papermill="{&quot;duration&quot;:4.9831e-2,&quot;end_time&quot;:&quot;2024-04-01T17:06:10.059381&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-01T17:06:10.009550&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 5941.11it/s]

</div>

<div class="output stream stderr">

</div>

</div>
