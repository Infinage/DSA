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
    duration: 2.980766
    end_time: "2024-03-26T03:05:10.748681"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-26T03:05:07.767915"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:1.11e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:08.960350&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:08.949250&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:08.983150Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:08.982605Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:08.997122Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:08.996452Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.884e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:08.999771&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:08.970931&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0577e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.020902&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.010325&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.043698Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.043067Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.048431Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.047540Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9423e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.050835&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.031412&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.073972Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.073633Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.089206Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.088301Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0266e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.091634&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.061368&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 60401.84it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.115470Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.114745Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.127478Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.126598Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7075e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.129813&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.102738&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 56066.09it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:1.1096e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.151915&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.140819&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.175843Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.175129Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.185144Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.184269Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4676e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.187613&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.162937&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.211708Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.210999Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.225254Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.224362Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8815e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.227604&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.198789&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 59645.96it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.252269Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.251679Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.258752Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.257863Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2513e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.261659&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.239146&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.286192Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.285499Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.299623Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.298791Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8974e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.301923&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.272949&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 56144.89it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:1.1496e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.325127&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.313631&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.350528Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.349966Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.357911Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.357090Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3034e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.359794&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.336760&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.386463Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.385833Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.393746Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.392943Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3117e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.395546&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.372429&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1925e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.419798&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.407873&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.445528Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.444975Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.450282Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.449500Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0217e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.452001&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.431784&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.478062Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.477375Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.489303Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.488541Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7001e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.491061&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.464060&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1913e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.515325&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.503412&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.541003Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.540266Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.551449Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.550693Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6007e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.553171&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.527164&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.579601Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.578901Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.589535Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.588729Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5872e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.591313&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.565441&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2604e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.616815&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.604211&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.643921Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.643291Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.652987Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.652190Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5175e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.654687&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.629512&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2508e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.679905&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.667397&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.706918Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.706188Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.716738Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.716027Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6098e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.718519&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.692421&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2849e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.744393&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.731544&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.771832Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.771135Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.779369Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.778524Z&quot;}"
papermill="{&quot;duration&quot;:2.3968e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.781135&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.757167&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2692e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.806735&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.794043&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.833897Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.833213Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.840881Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.840102Z&quot;}"
papermill="{&quot;duration&quot;:2.3334e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.842671&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.819337&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2767e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.868597&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.855830&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.895889Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.895256Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.901458Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.900682Z&quot;}"
papermill="{&quot;duration&quot;:2.1807e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.903215&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.881408&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.930589Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.929970Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:09.938971Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:09.938097Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4555e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.940691&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.916136&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3042e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:09.966943&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.953901&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:09.994901Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:09.994306Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:10.001413Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:10.000669Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3193e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.003159&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:09.979966&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3055e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.057029&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.043974&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:10.085668Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:10.084948Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:10.124042Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:10.123153Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:5.5728e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.125872&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.070144&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 10000/10000 [00:00<00:00, 331980.18it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="21ab1eeb" class="cell markdown"
papermill="{&quot;duration&quot;:1.3081e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.152510&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.139429&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=rjEJeYCasHs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=55>
Find Nth root of an integer

</div>

<div id="8e8ba6e9" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:10.180875Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:10.180183Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:10.185858Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:10.185047Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1762e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.187514&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.165752&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:10.215991Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:10.215413Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:10.221648Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:10.220850Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2397e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.223413&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.201016&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3275e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.250077&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.236802&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/qyfekrNni90?si=N28mkp8Cyx4lvNIq>  
Problem: Koko eating bananas

</div>

<div id="24fcadf8" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:10.278970Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:10.278302Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:10.284233Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:10.283416Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2299e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.285929&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.263630&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:10.315352Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:10.314697Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:10.322713Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:10.321789Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4604e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.324423&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.299819&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3256e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.351192&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.337936&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=TXAuxeYBTdg&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=57>
Minimum days to make M boquets

</div>

<div id="76ca4e35" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:10.379940Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:10.379301Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:10.388806Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:10.388107Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6041e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.390560&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.364519&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.315e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.417410&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.404260&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UvBKTVaG6U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=58>
Smallest divisor given the threshold

</div>

<div id="fbac3ba5" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:10.445248Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:10.444583Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:10.452105Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:10.451413Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3436e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.453807&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.430371&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2964e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.479982&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.467018&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MG-Ac4TAvTY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=59>
Capacity to ship packages in D Days

</div>

<div id="48336458" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-26T03:05:10.508224Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-26T03:05:10.507472Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-26T03:05:10.516110Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-26T03:05:10.515439Z&quot;}"
papermill="{&quot;duration&quot;:2.4815e-2,&quot;end_time&quot;:&quot;2024-03-26T03:05:10.517783&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-26T03:05:10.492968&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
