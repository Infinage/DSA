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
    duration: 2.4783
    end_time: "2024-03-25T02:34:43.058950"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-25T02:34:40.580650"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:9.797e-3,&quot;end_time&quot;:&quot;2024-03-25T02:34:41.750025&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.740228&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:41.769667Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:41.769070Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:41.782091Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:41.781363Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6136e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:41.785363&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.759227&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.995e-3,&quot;end_time&quot;:&quot;2024-03-25T02:34:41.803872&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.794877&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:41.823494Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:41.822850Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:41.827362Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:41.826645Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6498e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:41.829519&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.813021&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:41.848981Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:41.848343Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:41.863078Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:41.862246Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6454e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:41.864969&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.838515&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 57377.62it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:41.885110Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:41.884639Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:41.896503Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:41.895600Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3822e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:41.898267&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.874445&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 56111.09it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:9.567e-3,&quot;end_time&quot;:&quot;2024-03-25T02:34:41.917499&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.907932&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:41.937528Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:41.937284Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:41.946481Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:41.945710Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1262e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:41.948276&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.927014&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:41.968868Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:41.968390Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:41.981791Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:41.980976Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5394e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:41.983372&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.957978&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 60937.15it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.005212Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.004576Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.010823Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.010088Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8871e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.012506&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:41.993635&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.033957Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.033362Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.046706Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.045960Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5908e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.048463&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.022555&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 57538.98it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:1.0256e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.069077&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.058821&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.090867Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.090260Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.097387Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.096581Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9786e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.099096&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.079310&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.121170Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.120874Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.127940Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.127166Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9979e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.129621&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.109642&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0295e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.150521&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.140226&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.172882Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.172249Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.177340Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.176695Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7983e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.178932&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.160949&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.200870Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.200631Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.212192Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.211356Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4451e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.213845&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.189394&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0557e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.235210&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.224653&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.257841Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.257409Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.268067Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.267432Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3871e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.269733&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.245862&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.292108Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.291856Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.302236Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.301438Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3399e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.303890&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.280491&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0745e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.325508&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.314763&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.348829Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.348203Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.357240Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.356525Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2441e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.358947&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.336506&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1023e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.381132&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.370109&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.404740Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.404091Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.413910Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.413286Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3269e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.415531&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.392262&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0978e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.437720&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.426742&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.461435Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.460888Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.468424Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.467754Z&quot;}"
papermill="{&quot;duration&quot;:2.1155e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.470085&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.448930&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1016e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.492262&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.481246&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.516101Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.515472Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.523059Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.522444Z&quot;}"
papermill="{&quot;duration&quot;:2.1323e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.524725&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.503402&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1196e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.547300&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.536104&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.571208Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.570719Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.576317Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.575516Z&quot;}"
papermill="{&quot;duration&quot;:1.9344e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.577969&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.558625&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.602524Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.601816Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.610391Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.609660Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2539e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.612057&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.589518&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1482e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.635204&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.623722&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.659859Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.659259Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.665803Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.665044Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0614e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.667440&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.646826&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1527e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.690684&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.679157&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.715188Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.714538Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.753224Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.752451Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:5.272e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.754914&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.702194&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 10000/10000 [00:00<00:00, 323627.08it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="21ab1eeb" class="cell markdown"
papermill="{&quot;duration&quot;:1.1672e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.778347&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.766675&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=rjEJeYCasHs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=55>
Find Nth root of an integer

</div>

<div id="8e8ba6e9" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.803201Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.802573Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.807849Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.807071Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9455e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.809496&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.790041&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.834865Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.834220Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.839932Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.839308Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.013e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.841666&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.821536&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2128e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.865724&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.853596&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/qyfekrNni90?si=N28mkp8Cyx4lvNIq>  
Problem: Koko eating bananas

</div>

<div id="24fcadf8" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.890704Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.890410Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.895704Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.894936Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9667e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.897309&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.877642&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-25T02:34:42.922487Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-25T02:34:42.921846Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-25T02:34:42.928999Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-25T02:34:42.928272Z&quot;}"
papermill="{&quot;duration&quot;:2.1565e-2,&quot;end_time&quot;:&quot;2024-03-25T02:34:42.930790&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-25T02:34:42.909225&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
