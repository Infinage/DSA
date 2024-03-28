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
    duration: 2.979796
    end_time: "2024-03-28T02:15:11.912372"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-28T02:15:08.932576"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:1.2396e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:09.985589&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:09.973193&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.010502Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.009782Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.024310Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.023705Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9621e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.026801&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:09.997180&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import random
import functools
import itertools
import tqdm
import pdb
```

</div>

<div id="1b645c9d" class="cell markdown"
papermill="{&quot;duration&quot;:1.1202e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.049534&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.038332&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.073510Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.072832Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.077939Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.077259Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.963e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.080330&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.060700&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.104843Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.104252Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.119625Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.118832Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0408e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.122149&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.091741&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 59325.37it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.147294Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.146709Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.159121Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.158334Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.682e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.160924&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.134104&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 36814.75it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:1.192e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.184822&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.172902&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.209861Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.209620Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.218923Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.218198Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.374e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.220545&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.196805&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.245897Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.245358Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.258239Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.257458Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7249e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.259815&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.232566&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 60211.08it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.285644Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.285211Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.291432Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.290629Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0829e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.293094&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.272265&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.318548Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.318206Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.332001Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.331222Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8892e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.334165&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.305273&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 53261.00it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:1.2476e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.359319&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.346843&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.385670Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.385167Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.392440Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.391706Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2243e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.394082&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.371839&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.421003Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.420371Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.427688Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.426893Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2444e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.429308&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.406864&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2612e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.454653&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.442041&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.481588Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.480960Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.486206Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.485583Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0301e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.487756&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.467455&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.514881Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.514224Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.526295Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.525653Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7354e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.527912&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.500558&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2925e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.553922&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.540997&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.580999Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.580428Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.590488Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.589775Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.532e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.592118&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.566798&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.619816Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.619202Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.629215Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.628494Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5629e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.630867&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.605238&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3148e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.657446&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.644298&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.685087Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.684506Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.693103Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.692424Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4137e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.694709&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.670572&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3252e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.721389&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.708137&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.749596Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.748931Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.758173Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.757490Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4928e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.759724&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.734796&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3391e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.786804&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.773413&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.814968Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.814386Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.821999Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.821173Z&quot;}"
papermill="{&quot;duration&quot;:2.3401e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.823614&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.800213&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3401e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.850841&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.837440&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.879034Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.878426Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.885368Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.884649Z&quot;}"
papermill="{&quot;duration&quot;:2.288e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.887147&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.864267&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3594e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.914479&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.900885&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.961656Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.960937Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:10.966898Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:10.966142Z&quot;}"
papermill="{&quot;duration&quot;:2.25e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:10.968465&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.945965&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:10.997744Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:10.997127Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.005907Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.005192Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5197e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.007514&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:10.982317&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3815e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.035265&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.021450&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.064031Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.063543Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.070018Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.069341Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2607e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.071616&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.049009&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.368e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.099103&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.085423&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.127846Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.127344Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.165570Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.164806Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:5.4359e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.167217&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.112858&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 10000/10000 [00:00<00:00, 331319.34it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="21ab1eeb" class="cell markdown"
papermill="{&quot;duration&quot;:1.3965e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.195294&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.181329&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=rjEJeYCasHs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=55>
Find Nth root of an integer

</div>

<div id="8e8ba6e9" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.225243Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.224648Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.230404Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.229746Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2783e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.232027&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.209244&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.261313Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.261020Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.266979Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.266337Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.244e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.268631&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.246191&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4037e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.296826&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.282789&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/qyfekrNni90?si=N28mkp8Cyx4lvNIq>  
Problem: Koko eating bananas

</div>

<div id="24fcadf8" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.326335Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.325766Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.331116Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.330359Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1758e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.332738&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.310980&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.362240Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.361639Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.368906Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.368155Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3674e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.370492&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.346818&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4036e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.398821&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.384785&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=TXAuxeYBTdg&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=57>
Minimum days to make M boquets

</div>

<div id="76ca4e35" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.428248Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.427652Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.436408Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.435670Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5493e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.438238&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.412745&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4136e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.466512&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.452376&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UvBKTVaG6U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=58>
Smallest divisor given the threshold

</div>

<div id="fbac3ba5" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.496072Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.495579Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.502574Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.501845Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3671e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.504280&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.480609&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4043e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.532665&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.518622&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MG-Ac4TAvTY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=59>
Capacity to ship packages in D Days

</div>

<div id="48336458" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.562384Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.561728Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.569492Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.568757Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4428e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.571085&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.546657&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.401e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.599276&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.585266&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=uZ0N_hZpyps&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=60>
Kth missing +ve number:
<https://leetcode.com/problems/kth-missing-positive-number/submissions/1215199274/>

</div>

<div id="fdbc80fd" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.628800Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.628304Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.636832Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.636087Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5402e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.638687&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.613285&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4044e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.667010&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.652966&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=R_Mfw4ew-Vo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=61>

</div>

<div id="8139b363" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.696371Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.695758Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.702461Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.701843Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3061e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.704064&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.681003&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.733550Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.733253Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.740612Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.739971Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4038e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.742297&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.718259&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-28T02:15:11.772597Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-28T02:15:11.771907Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-28T02:15:11.779687Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-28T02:15:11.778945Z&quot;}"
papermill="{&quot;duration&quot;:2.4473e-2,&quot;end_time&quot;:&quot;2024-03-28T02:15:11.781335&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-28T02:15:11.756862&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
