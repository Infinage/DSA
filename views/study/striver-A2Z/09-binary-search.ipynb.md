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
    duration: 2.509967
    end_time: "2024-03-23T16:33:34.031014"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-23T16:33:31.521047"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:8.625e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.687310&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.678685&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:32.703929Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:32.703243Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:32.716440Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:32.715803Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4014e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.718840&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.694826&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.169e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.733298&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.726129&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:32.751838Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:32.751594Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:32.757777Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:32.756106Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0534e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.760998&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.740464&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:32.781060Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:32.780447Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:32.798450Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:32.797487Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0872e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.801163&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.770291&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 39151.54it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:32.823807Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:32.823220Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:32.839126Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:32.838150Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8735e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.841054&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.812319&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 33439.40it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:7.757e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.856649&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.848892&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:32.873971Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:32.873636Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:32.883578Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:32.882741Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0598e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.885207&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.864609&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:32.902993Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:32.902359Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:32.919613Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:32.918829Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.816e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.921319&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.893159&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 33990.87it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:32.948612Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:32.948313Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:32.956007Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:32.955076Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4668e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:32.957884&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.933216&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.036705Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.035813Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.052372Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.051432Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.7528e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.054284&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:32.986756&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 52527.29it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:0.183294,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.246219&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.062925&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.397766Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.397122Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.404780Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.403921Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9189e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.406522&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.387333&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.425016Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.424771Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.431965Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.431175Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8409e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.433635&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.415226&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.611e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.451117&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.442506&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.469657Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.469065Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.473985Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.473243Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.595e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.475761&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.459811&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.494613Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.494056Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.505668Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.505043Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2778e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.507279&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.484501&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.859e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.525167&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.516308&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.543985Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.543477Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.554203Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.553518Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1914e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.555881&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.533967&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.575501Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.574831Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.585185Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.584456Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1821e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.586829&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.565008&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.08e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.605028&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.595948&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.624545Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.624301Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.633147Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.632340Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0515e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.634767&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.614252&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.198e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.653360&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.644162&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.673053Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.672400Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.682406Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.681717Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1551e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.684022&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.662471&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.197e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.703106&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.693909&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.723073Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.722484Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.730428Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.729813Z&quot;}"
papermill="{&quot;duration&quot;:1.9703e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.732101&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.712398&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.101e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.750519&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.741418&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.770600Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.770175Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.777376Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.776563Z&quot;}"
papermill="{&quot;duration&quot;:1.9085e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.779035&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.759950&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.338e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.798130&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.788792&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.819007Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.818386Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.824150Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.823400Z&quot;}"
papermill="{&quot;duration&quot;:1.8069e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.825867&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.807798&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.846904Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.846251Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.854794Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.854070Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0856e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.856460&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.835604&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.967e-3,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.876349&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.866382&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-23T16:33:33.897051Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-23T16:33:33.896810Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-23T16:33:33.903162Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-23T16:33:33.902500Z&quot;}"
papermill="{&quot;duration&quot;:1.8676e-2,&quot;end_time&quot;:&quot;2024-03-23T16:33:33.904785&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-23T16:33:33.886109&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
