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
    duration: 2.345471
    end_time: "2024-03-24T01:55:57.087660"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-24T01:55:54.742189"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:8.665e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:55.907963&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:55.899298&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:55.925618Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:55.924978Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:55.939303Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:55.938634Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5827e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:55.941787&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:55.915960&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.824e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:55.957551&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:55.949727&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:55.974605Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:55.974106Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:55.979098Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:55.978299Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5984e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:55.981263&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:55.965279&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:55.998635Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:55.997936Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.013431Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.012553Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6806e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.015812&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:55.989006&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 61644.68it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.035610Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.035000Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.049038Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.048105Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.622e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.050839&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.024619&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 30077.48it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:8.412e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.067734&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.059322&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.086088Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.085572Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.095295Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.094435Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2724e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.098778&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.076054&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.117874Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.117170Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.131098Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.130202Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5335e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.132772&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.107437&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 59233.22it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.152171Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.151526Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.158519Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.157673Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8553e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.160249&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.141696&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.180062Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.179413Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.194252Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.193428Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7131e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.196299&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.169168&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 57713.16it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:9.039e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.214494&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.205455&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.234047Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.233671Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.241396Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.240552Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9648e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.243160&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.223512&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.263537Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.262946Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.270595Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.269769Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9762e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.272331&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.252569&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.237e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.291375&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.282138&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.311886Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.311313Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.316784Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.316047Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7688e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.318498&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.300810&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.338626Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.338335Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.350488Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.349671Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4243e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.352152&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.327909&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.502e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.371275&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.361773&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.392080Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.391260Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.401834Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.401077Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2922e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.403563&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.380641&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.424683Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.424078Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.434872Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.434168Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3208e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.436563&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.413355&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.537e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.455990&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.446453&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.477719Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.476992Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.486157Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.485366Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1966e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.487933&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.465967&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.697e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.507642&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.497945&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.529084Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.528399Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.539009Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.538309Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.332e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.540737&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.517417&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.691e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.560563&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.550872&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.582110Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.581540Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.589645Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.588816Z&quot;}"
papermill="{&quot;duration&quot;:2.0761e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.591314&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.570553&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.95e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.611505&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.601555&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.633531Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.632768Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.640853Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.640108Z&quot;}"
papermill="{&quot;duration&quot;:2.0984e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.642515&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.621531&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.853e-3,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.662584&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.652731&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.684471Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.683908Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.690414Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.689557Z&quot;}"
papermill="{&quot;duration&quot;:1.944e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.692154&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.672714&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.714326Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.713658Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.722276Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.721529Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1522e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.723906&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.702384&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0257e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.744723&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.734466&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.766965Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.766553Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.773300Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.772536Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0003e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.775029&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.755026&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0303e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.795923&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.785620&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-24T01:55:56.818283Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-24T01:55:56.817599Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-24T01:55:56.857301Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-24T01:55:56.856470Z&quot;}"
papermill="{&quot;duration&quot;:5.2861e-2,&quot;end_time&quot;:&quot;2024-03-24T01:55:56.859021&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-24T01:55:56.806160&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 10000/10000 [00:00<00:00, 322291.69it/s]

</div>

<div class="output stream stderr">

</div>

</div>
