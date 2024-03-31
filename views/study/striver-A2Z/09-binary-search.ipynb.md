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
    duration: 4.232542
    end_time: "2024-03-31T04:08:07.996158"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-31T04:08:03.763616"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:1.5873e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:04.810547&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:04.794674&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:04.842049Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:04.841502Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:04.950008Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:04.949201Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.126818,&quot;end_time&quot;:&quot;2024-03-31T04:08:04.952403&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:04.825585&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
```

</div>

<div id="1b645c9d" class="cell markdown"
papermill="{&quot;duration&quot;:1.4865e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:04.989183&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:04.974318&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.020042Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.019753Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.024190Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.023547Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1789e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.025846&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.004057&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.057498Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.057034Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.072070Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.071252Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2626e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.073680&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.041054&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 63262.50it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.106082Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.105469Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.117107Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.116389Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9461e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.118704&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.089243&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 56941.41it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:1.5435e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.149745&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.134310&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.182166Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.181679Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.190897Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.190150Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7288e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.192578&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.165290&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.225283Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.224754Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.237296Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.236515Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0688e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.239021&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.208333&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 58587.85it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.271945Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.271706Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.277945Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.277171Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4784e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.279687&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.254903&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.313336Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.312744Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.326298Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.325505Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2194e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.328107&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.295913&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 57170.37it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:1.6296e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.360886&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.344590&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.394825Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.394215Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.401455Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.400821Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6013e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.403144&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.377131&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.437236Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.436661Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.444217Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.443453Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6394e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.445906&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.419512&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6484e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.479196&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.462712&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.513500Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.513256Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.518218Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.517441Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4327e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.519926&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.495599&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.554720Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.553941Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.565590Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.564844Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0662e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.567207&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.536545&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6733e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.600785&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.584052&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.635701Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.635033Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.645239Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.644513Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.945e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.646907&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.617457&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.683158Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.682580Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.692554Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.691827Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9266e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.694162&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.664896&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6954e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.728281&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.711327&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.763353Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.762865Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.771659Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.770903Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8083e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.773287&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.745204&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6911e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.807140&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.790229&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.842505Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.841979Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.851514Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.850782Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8937e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.853133&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.824196&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6962e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.887388&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.870426&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:05.922939Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:05.922334Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:05.929781Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:05.929051Z&quot;}"
papermill="{&quot;duration&quot;:2.6937e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.931434&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.904497&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7161e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:05.965860&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.948699&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.001459Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.000803Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.007831Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.007143Z&quot;}"
papermill="{&quot;duration&quot;:2.6532e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.009458&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:05.982926&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.577e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.062689&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.026919&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.099439Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.098816Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.105085Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.104256Z&quot;}"
papermill="{&quot;duration&quot;:2.6566e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.106833&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.080267&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.142632Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.142329Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.150751Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.149964Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8186e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.152390&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.124204&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7463e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.187425&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.169962&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.223945Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.223352Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.230294Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.229539Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7137e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.232132&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.204995&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7672e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.267394&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.249722&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.303911Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.303214Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.340941Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.340188Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:5.7686e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.342546&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.284860&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 10000/10000 [00:00<00:00, 332530.27it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="21ab1eeb" class="cell markdown"
papermill="{&quot;duration&quot;:1.7783e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.378362&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.360579&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=rjEJeYCasHs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=55>
Find Nth root of an integer

</div>

<div id="8e8ba6e9" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.414963Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.414675Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.419917Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.419153Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5453e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.421590&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.396137&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.458770Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.458165Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.464300Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.463682Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6443e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.465967&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.439524&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7779e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.501740&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.483961&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/qyfekrNni90?si=N28mkp8Cyx4lvNIq>  
Problem: Koko eating bananas

</div>

<div id="24fcadf8" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.538336Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.538079Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.543639Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.542995Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5656e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.545289&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.519633&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.582489Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.581795Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.589077Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.588424Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.76e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.590741&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.563141&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7684e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.626209&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.608525&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=TXAuxeYBTdg&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=57>
Minimum days to make M boquets

</div>

<div id="76ca4e35" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.662807Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.662563Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.671200Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.670425Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8908e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.672855&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.643947&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7596e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.708376&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.690780&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UvBKTVaG6U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=58>
Smallest divisor given the threshold

</div>

<div id="fbac3ba5" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.745590Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.744929Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.751996Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.751370Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7393e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.753633&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.726240&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7743e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.789341&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.771598&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MG-Ac4TAvTY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=59>
Capacity to ship packages in D Days

</div>

<div id="48336458" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.825949Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.825710Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.833629Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.832964Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8269e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.835355&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.807086&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7654e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.871013&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.853359&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=uZ0N_hZpyps&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=60>
Kth missing +ve number:
<https://leetcode.com/problems/kth-missing-positive-number/submissions/1215199274/>

</div>

<div id="fdbc80fd" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.907744Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.907203Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.915979Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.915221Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8889e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.917543&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.888654&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7707e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.953119&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.935412&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=R_Mfw4ew-Vo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=61>

</div>

<div id="8139b363" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:06.990265Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:06.989673Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:06.996323Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:06.995675Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6966e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:06.997988&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:06.971022&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.035179Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.034518Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.041886Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.041157Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7888e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.043669&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.015781&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.081213Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.080654Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.087789Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.087013Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7867e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.089410&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.061543&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7767e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.125292&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.107525&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=Z0hwjftStI4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=62>

</div>

<div id="4e6344ff" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.162261Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.161585Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.168522Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.167791Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7097e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.170169&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.143072&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.207422Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.206778Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.215039Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.214417Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8554e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.216665&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.188111&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7676e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.252169&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.234493&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=thUd_WJn6wk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=63>
Problem Link:
<https://leetcode.com/problems/split-array-largest-sum/submissions/1216912768>

</div>

<div id="2f94d583" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.289189Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.288599Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.296304Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.295568Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8122e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.298051&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.269929&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7702e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.333659&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.315957&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=kMSBvlZ-_HA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=64>

</div>

<div id="b31b6aea" class="cell code" execution_count="37"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.370877Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.370202Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.378588Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.377828Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8651e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.380148&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.351497&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.417243Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.416620Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.426573Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.425811Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.024e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.428219&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.397979&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7908e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.463955&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.446047&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=C2rRzz-JDk8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=65>
Median of two sorted ararys

</div>

<div id="f6508851" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.500974Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.500483Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.507725Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.507004Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7496e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.509351&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.481855&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.546566Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.545958Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.554404Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.553765Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8671e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.556030&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.527359&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.592826Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.592235Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.604074Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.603320Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2108e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.605879&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.573771&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.643018Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.642555Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.651142Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.650524Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8898e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.652771&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.623873&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7693e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.688325&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.670632&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=D1oDwWCq50g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=67>
Find kth element of two sorted arrays

</div>

<div id="394757ce" class="cell code" execution_count="43"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.725284Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.724699Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.731504Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.730898Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7056e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.733140&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.706084&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.770309Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.770018Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.778581Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.777800Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8906e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.780188&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.751282&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.781e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.816034&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.798224&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=SCz-1TtYxDI&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=68>
Row with maximum number of 1s

</div>

<div id="16ce254c" class="cell code" execution_count="45"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-31T04:08:07.853126Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-31T04:08:07.852704Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-31T04:08:07.859995Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-31T04:08:07.859255Z&quot;}"
papermill="{&quot;duration&quot;:2.7482e-2,&quot;end_time&quot;:&quot;2024-03-31T04:08:07.861545&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-31T04:08:07.834063&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
