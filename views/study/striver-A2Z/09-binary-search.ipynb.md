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
    duration: 3.495467
    end_time: "2024-03-29T07:38:06.431614"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-29T07:38:02.936147"
    version: 2.5.0
---

<div id="39385271" class="cell markdown"
papermill="{&quot;duration&quot;:2.2581e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.001470&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:03.978889&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd129096" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.140835Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.140084Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.154405Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.153750Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.133733,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.156161&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.022428&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2379e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.181309&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.168930&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="a8c5fd59" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.207452Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.206909Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.211730Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.210852Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9868e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.213584&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.193716&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.240659Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.240117Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.255130Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.254283Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9981e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.256777&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.226796&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 56980.08it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="59682a10" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.283957Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.283431Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.294508Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.293771Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6366e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.296100&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.269734&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 56269.17it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="1f2d9f50" class="cell markdown"
papermill="{&quot;duration&quot;:1.2995e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.322148&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.309153&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="f23024a2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.349773Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.348997Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.358486Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.357739Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4938e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.360103&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.335165&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.388140Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.387541Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.400231Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.399501Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8348e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.401839&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.373491&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 57197.65it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6609aa48" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.430054Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.429470Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.435655Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.434907Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1963e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.437312&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.415349&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.465761Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.465318Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.479598Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.478738Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0537e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.481502&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.450965&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 60142.01it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="5e497680" class="cell markdown"
papermill="{&quot;duration&quot;:1.3738e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.509231&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.495493&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="8abcbf56" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.538280Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.537675Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.544780Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.544060Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3335e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.546384&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.523049&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.575763Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.575122Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.582192Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.581421Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3389e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.583746&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.560357&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.399e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.611940&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.597950&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="e5e48474" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.641469Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.640802Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.645797Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.645043Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1553e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.647480&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.625927&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.676982Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.676574Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.687993Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.687269Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8042e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.689621&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.661579&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4186e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.718228&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.704042&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hjR1IYVx9lY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=47>

</div>

<div id="d11d7af8" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.747887Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.747299Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.757424Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.756698Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6697e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.759071&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.732374&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.789170Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.788498Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.798611Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.797865Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6838e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.800238&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.773400&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4386e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.829401&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.815015&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=5qGrJbHhqFs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=48>
Search in a rotated sorted array:
<https://leetcode.com/problems/search-in-rotated-sorted-array/>

</div>

<div id="07fd3a6e" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.859632Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.859071Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.867613Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.866881Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.548e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.869357&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.843877&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4705e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.898941&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.884236&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=w2G2W8l__pc&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=49>
Search in rotated sorted arrays (with duplicates) Leetcode link:
<https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/1210474431/>

</div>

<div id="310f82f5" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:04.929717Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.929098Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:04.938476Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:04.937707Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6429e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.940099&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.913670&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.467e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:04.969754&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.955084&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=nhEMDKMB44g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=50>
Leetcode:
<https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1210490796>

</div>

<div id="b50d9ac8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.000320Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:04.999822Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.007522Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.006863Z&quot;}"
papermill="{&quot;duration&quot;:2.4729e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.009143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:04.984414&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.461e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.038506&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.023896&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=jtSiWTPLwd0&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=51>
Count number of times an array has been rotated

</div>

<div id="f854c012" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.069023Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.068764Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.075910Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.075131Z&quot;}"
papermill="{&quot;duration&quot;:2.4365e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.077554&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.053189&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.5184e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.127784&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.092600&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AZOmHuHadxQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=52>
Leetcode link:
<https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/1211393503>

</div>

<div id="1abaf5dd" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.159081Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.158421Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.164595Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.163892Z&quot;}"
papermill="{&quot;duration&quot;:2.3596e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.166264&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.142668&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.197557Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.197263Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.205533Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.204752Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5799e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.207178&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.181379&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5552e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.238179&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.222627&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=cXxmbemS6XM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=53>
Find Peak element

</div>

<div id="7126b9cc" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.269750Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.269168Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.275618Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.274975Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3938e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.277221&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.253283&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5119e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.307502&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.292383&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.339097Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.338740Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.378792Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.377986Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:5.7659e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.380439&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.322780&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 10000/10000 [00:00<00:00, 313349.17it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="21ab1eeb" class="cell markdown"
papermill="{&quot;duration&quot;:1.5284e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.411117&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.395833&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=rjEJeYCasHs&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=55>
Find Nth root of an integer

</div>

<div id="8e8ba6e9" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.443212Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.442630Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.448093Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.447482Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3246e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.449757&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.426511&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.482247Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.481734Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.487770Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.486989Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4051e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.489510&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.465459&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5285e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.520202&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.504917&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link: <https://youtu.be/qyfekrNni90?si=N28mkp8Cyx4lvNIq>  
Problem: Koko eating bananas

</div>

<div id="24fcadf8" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.552251Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.551656Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.556961Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.556200Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3235e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.558773&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.535538&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.591134Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.590590Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.597823Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.597067Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5177e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.599455&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.574278&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5367e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.630330&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.614963&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=TXAuxeYBTdg&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=57>
Minimum days to make M boquets

</div>

<div id="76ca4e35" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.662387Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.661844Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.670626Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.669858Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6596e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.672231&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.645635&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5455e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.703275&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.687820&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UvBKTVaG6U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=58>
Smallest divisor given the threshold

</div>

<div id="fbac3ba5" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.735328Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.734710Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.741672Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.740940Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4751e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.743300&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.718549&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5178e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.773860&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.758682&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MG-Ac4TAvTY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=59>
Capacity to ship packages in D Days

</div>

<div id="48336458" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.806182Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.805559Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.813336Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.812603Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5886e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.815202&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.789316&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5212e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.845818&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.830606&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=uZ0N_hZpyps&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=60>
Kth missing +ve number:
<https://leetcode.com/problems/kth-missing-positive-number/submissions/1215199274/>

</div>

<div id="fdbc80fd" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.877871Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.877263Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.885840Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.885102Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6667e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.887768&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.861101&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5393e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.918918&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.903525&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=R_Mfw4ew-Vo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=61>

</div>

<div id="8139b363" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.951026Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.950400Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.956874Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.956142Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.451e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.958770&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.934260&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:05.990884Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:05.990272Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:05.997727Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:05.996999Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5304e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:05.999540&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:05.974236&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:06.032111Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:06.031432Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:06.038881Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:06.038259Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5385e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:06.040530&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:06.015145&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5359e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:06.071408&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:06.056049&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=Z0hwjftStI4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=62>

</div>

<div id="4e6344ff" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:06.103591Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:06.103033Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:06.109875Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:06.109122Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4544e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:06.111419&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:06.086875&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:06.143889Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:06.143301Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:06.151156Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:06.150407Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5832e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:06.152853&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:06.127021&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5398e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:06.183735&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:06.168337&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=thUd_WJn6wk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=63>
Problem Link:
<https://leetcode.com/problems/split-array-largest-sum/submissions/1216912768>

</div>

<div id="2f94d583" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:06.216262Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:06.215554Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:06.223772Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:06.223153Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6256e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:06.225440&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:06.199184&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5552e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:06.256932&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:06.241380&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=kMSBvlZ-_HA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=64>

</div>

<div id="b31b6aea" class="cell code" execution_count="37"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-29T07:38:06.289302Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-29T07:38:06.288753Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-29T07:38:06.297777Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-29T07:38:06.297010Z&quot;}"
papermill="{&quot;duration&quot;:2.6912e-2,&quot;end_time&quot;:&quot;2024-03-29T07:38:06.299359&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-29T07:38:06.272447&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
    while low < high:
        mid = round((low + high) / 2, 7)
        if mid == high or low == mid:
            break
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
