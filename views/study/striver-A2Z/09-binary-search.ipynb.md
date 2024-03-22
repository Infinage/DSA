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
    version: 3.10.13
  nbformat: 4
  nbformat_minor: 5
  papermill:
    default_parameters: {}
    duration: 1.865454
    end_time: "2024-03-22T02:09:02.033037"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-22T02:09:00.167583"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:7.018e-3,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.328613&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.321595&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.342683Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.342378Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.356624Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.355753Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4114e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.358933&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.334819&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.87e-3,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.371170&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.365300&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.384825Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.384008Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.390370Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.389430Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6593e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.393631&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.377038&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.408648Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.408158Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.424830Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.423824Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5373e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.426692&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.401319&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 59224.85it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.441100Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.440837Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.454432Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.453498Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.344e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.456543&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.433103&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 34830.63it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:6.64e-3,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.470365&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.463725&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.484756Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.484178Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.494008Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.493168Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9431e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.496287&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.476856&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.510994Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.510240Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.524154Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.523313Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2898e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.525754&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.502856&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 61862.89it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.540650Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.539892Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.546912Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.546280Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6183e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.548553&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.532370&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.563641Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.562913Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.576439Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.575612Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.323e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.578575&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.555345&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 61658.27it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:7.247e-3,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.593104&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.585857&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.609295Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.608001Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.615914Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.615249Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7384e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.617538&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.600154&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.633615Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.632954Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.640365Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.639706Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7219e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.641988&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.624769&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.206e-3,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.656527&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.649321&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.672787Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.672222Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.677296Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.676507Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5354e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.679132&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.663778&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.695503Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.694830Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.706511Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.705832Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1633e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.708215&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.686582&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.701e-3,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.723337&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.715636&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.739724Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.739012Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.749783Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.749086Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0744e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.751499&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.730755&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.768278Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.767616Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.778105Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.777392Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0639e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.779777&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.759138&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.762e-3,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.795376&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.787614&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.812200Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.811580Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.820534Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.819793Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.918e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.822171&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.802991&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.737e-3,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.837723&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.829986&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.854995Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.854369Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.864265Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.863550Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0159e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.865895&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.845736&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.882e-3,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.881741&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.873859&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-22T02:09:01.899354Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-22T02:09:01.898702Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-22T02:09:01.906500Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-22T02:09:01.905844Z&quot;}"
papermill="{&quot;duration&quot;:1.8401e-2,&quot;end_time&quot;:&quot;2024-03-22T02:09:01.908160&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-22T02:09:01.889759&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
