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
    duration: 1.81667
    end_time: "2024-03-21T15:53:56.971005"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-21T15:53:55.154335"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:6.284e-3,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.310690&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.304406&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.322308Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.321602Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.334972Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.334255Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0688e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.336675&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.315987&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.703e-3,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.346983&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.342280&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.357225Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.356713Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.361196Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.360474Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1397e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.362813&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.351416&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.374427Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.373858Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.388550Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.387681Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.152e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.390214&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.368694&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 61025.81it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.404268Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.403603Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.417482Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.416677Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3425e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.419938&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.396513&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 31066.62it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:1.1249e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.447460&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.436211&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.462359Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.461688Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.472739Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.471801Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0441e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.474872&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.454431&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.489893Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.489233Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.506808Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.505691Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.703e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.508688&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.481658&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 47016.07it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.522084Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.521639Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.530109Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.528449Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7401e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.532271&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.514870&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.591158Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.590345Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.605179Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.604436Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.8655e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.606955&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.538300&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 57992.45it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:6.189e-3,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.627017&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.620828&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.641162Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.640438Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.648265Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.647472Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6627e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.649843&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.633216&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.664642Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.663905Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.671458Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.670669Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6665e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.673080&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.656415&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.587e-3,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.686363&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.679776&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.700899Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.700221Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.705378Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.704704Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4257e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.707054&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.692797&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.721137Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.720906Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.732620Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.731784Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0588e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.734159&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.713571&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.531e-3,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.747439&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.740908&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.762087Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.761533Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.771592Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.770970Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9181e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.773256&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.754075&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.796802Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.796159Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.806770Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.806044Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8259e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.808574&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.780315&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.874e-3,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.822381&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.815507&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-21T15:53:56.837691Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-21T15:53:56.837055Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-21T15:53:56.846091Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-21T15:53:56.845339Z&quot;}"
papermill="{&quot;duration&quot;:1.8568e-2,&quot;end_time&quot;:&quot;2024-03-21T15:53:56.847860&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-21T15:53:56.829292&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def search(arr: list[int], target: int) -> int:
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

search([7, 8, 9, 1, 2, 3, 4, 5, 6], 6)
```

<div class="output execute_result" execution_count="15">

    8

</div>

</div>
