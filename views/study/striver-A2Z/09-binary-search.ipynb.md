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
    duration: 4.034817
    end_time: "2024-03-30T12:53:46.959539"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-30T12:53:42.924722"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:1.4953e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:43.989769&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:43.974816&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.019564Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.018973Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.129797Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.128910Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.128525,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.132443&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.003918&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3843e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.166665&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.152822&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.195967Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.195232Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.199917Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.199151Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1172e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.201573&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.180401&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.231478Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.230915Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.246417Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.245592Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2087e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.248222&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.216135&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 57535.03it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.278681Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.278170Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.289890Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.289106Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8731e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.291606&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.262875&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 53038.75it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:1.4349e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.320551&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.306202&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.350768Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.350207Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.359990Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.359285Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6638e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.361596&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.334958&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.392298Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.391691Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.404321Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.403519Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9736e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.406064&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.376328&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 62248.50it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.437261Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.436558Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.443636Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.442831Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4277e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.445256&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.420979&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.476484Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.476234Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.490491Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.489735Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1607e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.492229&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.460622&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 61235.19it/s]

</div>

<div class="output stream stderr">

</div>

<div class="output stream stdout">

    0
    5

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:1.5145e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.522704&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.507559&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.554288Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.553966Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.561777Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.560942Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5771e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.563523&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.537752&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.595632Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.595089Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.602554Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.601732Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5339e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.604250&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.578911&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5343e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.635311&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.619968&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.667541Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.666897Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.672572Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.671798Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3731e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.674385&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.650654&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.706395Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.706116Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.718030Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.717221Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9762e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.719624&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.689862&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5633e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.751045&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.735412&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.783260Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.782966Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.793726Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.792921Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8931e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.795447&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.766516&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.827903Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.827662Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.837921Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.837151Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8268e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.839512&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.811244&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5793e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.871337&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.855544&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.904779Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.904161Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.913406Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.912662Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7972e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.915143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.887171&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5761e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.946907&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.931146&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:44.980527Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:44.979910Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:44.989907Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:44.989199Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8602e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:44.991558&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:44.962956&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6033e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.023856&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.007823&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.057749Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.057090Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.064909Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.064153Z&quot;}"
papermill="{&quot;duration&quot;:2.663e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.066622&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.039992&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6151e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.099173&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.083022&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.132971Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.132262Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.139976Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.139339Z&quot;}"
papermill="{&quot;duration&quot;:2.6425e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.141645&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.115220&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.4952e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.192848&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.157896&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.227662Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.226933Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.233308Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.232579Z&quot;}"
papermill="{&quot;duration&quot;:2.5884e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.235059&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.209175&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.269007Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.268284Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.276989Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.276297Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7317e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.278689&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.251372&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6603e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.312026&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.295423&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.347250Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.346698Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.353728Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.352936Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6785e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.355565&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.328780&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6693e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.389228&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.372535&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.424600Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.423945Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.462009Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.461220Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:5.7806e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.463639&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.405833&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 10000/10000 [00:00<00:00, 335088.60it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="21ab1eeb" class="cell markdown"
papermill="{&quot;duration&quot;:1.6776e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.497708&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.480932&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=rjEJeYCasHs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=55>
Find Nth root of an integer

</div>

<div id="8e8ba6e9" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.532662Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.532020Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.537545Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.536891Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4793e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.539230&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.514437&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.574041Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.573471Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.579514Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.578747Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5246e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.581196&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.555950&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6759e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.615068&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.598309&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/qyfekrNni90?si=N28mkp8Cyx4lvNIq>  
Problem: Koko eating bananas

</div>

<div id="24fcadf8" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.650616Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.649904Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.655580Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.654941Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5338e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.657229&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.631891&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.692502Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.691902Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.699399Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.698653Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6844e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.701050&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.674206&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6815e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.734782&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.717967&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=TXAuxeYBTdg&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=57>
Minimum days to make M boquets

</div>

<div id="76ca4e35" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.769633Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.769085Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.778661Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.777869Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8967e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.780347&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.751380&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6654e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.813749&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.797095&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UvBKTVaG6U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=58>
Smallest divisor given the threshold

</div>

<div id="fbac3ba5" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.848759Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.848140Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.855424Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.854668Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.661e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.857096&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.830486&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6577e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.890464&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.873887&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MG-Ac4TAvTY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=59>
Capacity to ship packages in D Days

</div>

<div id="48336458" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:45.925359Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:45.924590Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:45.932978Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:45.932353Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7659e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.934692&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.907033&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6769e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:45.968452&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.951683&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=uZ0N_hZpyps&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=60>
Kth missing +ve number:
<https://leetcode.com/problems/kth-missing-positive-number/submissions/1215199274/>

</div>

<div id="fdbc80fd" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.003794Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.003114Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.012248Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.011497Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8731e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.013933&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:45.985202&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6649e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.047459&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.030810&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=R_Mfw4ew-Vo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=61>

</div>

<div id="8139b363" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.082983Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.082317Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.088945Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.088192Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6274e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.090629&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.064355&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.125778Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.125251Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.132761Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.132023Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.686e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.134478&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.107618&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.170083Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.169442Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.176792Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.176046Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6989e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.178422&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.151433&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6794e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.212305&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.195511&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=Z0hwjftStI4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=62>

</div>

<div id="4e6344ff" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.247613Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.247005Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.254107Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.253383Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6599e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.255881&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.229282&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.291091Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.290438Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.298622Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.297940Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7704e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.300354&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.272650&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7151e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.334609&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.317458&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=thUd_WJn6wk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=63>
Problem Link:
<https://leetcode.com/problems/split-array-largest-sum/submissions/1216912768>

</div>

<div id="2f94d583" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.369917Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.369253Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.377169Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.376429Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7442e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.378895&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.351453&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6895e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.412778&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.395883&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=kMSBvlZ-_HA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=64>

</div>

<div id="b31b6aea" class="cell code" execution_count="37"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.449061Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.448205Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.456994Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.456349Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8838e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.458734&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.429896&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.494372Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.493792Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.504158Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.503507Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9936e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.505837&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.475901&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6708e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.539379&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.522671&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=C2rRzz-JDk8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=65>
Median of two sorted ararys

</div>

<div id="f6508851" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.574953Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.574242Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.581682Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.580932Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7057e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.583278&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.556221&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.618454Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.617781Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.626102Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.625369Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7574e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.627680&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.600106&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.663413Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.662877Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.675108Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.674350Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1969e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.676785&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.644816&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-30T12:53:46.712660Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-30T12:53:46.712333Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-30T12:53:46.723149Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-30T12:53:46.722453Z&quot;}"
papermill="{&quot;duration&quot;:3.0651e-2,&quot;end_time&quot;:&quot;2024-03-30T12:53:46.724878&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-30T12:53:46.694227&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
        elif l1 > r2:
            high = mid1 - 1
        else:
            low = mid1 + 1

    return -1

# Testing the solution
assert median([1, 3], [2]) == 2
assert median([1, 2], [3, 4]) == 2.5
```

</div>
