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
    duration: 1.677787
    end_time: "2024-03-20T17:43:16.095050"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-20T17:43:14.417263"
    version: 2.5.0
---

<div id="d1410f7f" class="cell markdown"
papermill="{&quot;duration&quot;:3.891e-3,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.569023&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.565132&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="fd0fe7ed" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.577279Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.576788Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.589900Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.589316Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9073e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.591579&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.572506&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="8ad30d2a" class="cell markdown"
papermill="{&quot;duration&quot;:3.248e-3,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.598278&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.595030&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="0719094e" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.606218Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.605680Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.610185Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.609341Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0214e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.611820&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.601606&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="328d499d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.620100Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.619430Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.633802Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.633020Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0199e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.635449&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.615250&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 65017.89it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="9e6cb028" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.644126Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.643809Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.657159Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.656186Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0136e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.659345&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.639209&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 100/100 [00:00<00:00, 33819.58it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="58c6735d" class="cell markdown"
papermill="{&quot;duration&quot;:4.887e-3,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.669692&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.664805&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=6zhGS79oQ4k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=46>
Implement lower / bound

</div>

<div id="69b3ccc2" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.682586Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.681775Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.693422Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.692490Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0102e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.695595&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.675493&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="0ad6eebf" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.712234Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.711489Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.724713Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.723839Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3862e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.726977&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.703115&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 62336.39it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6073daf2" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.746587Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.746076Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.753446Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.752549Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1171e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.755751&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.734580&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="ba0c14c0" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.770344Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.770008Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.785495Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.784571Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5338e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.787452&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.762114&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

    100%|██████████| 200/200 [00:00<00:00, 56953.00it/s]

</div>

<div class="output stream stdout">

    0
    5

</div>

<div class="output stream stderr">

</div>

</div>

<div id="6c5c8b30" class="cell markdown"
papermill="{&quot;duration&quot;:5.63e-3,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.801096&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.795466&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Much more intutive approach by Striver: Retain a variable ans to N,
update this variable when: arr\[mid\] \>= target - Lower bound
arr\[mid\] \> target - Upper bound

</div>

<div id="2236af54" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.823253Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.822722Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.831559Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.830528Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8032e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.834206&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.806174&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="c96b4979" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.856981Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.856207Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.866205Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.865381Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0896e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.867904&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.847008&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="f029f61e" class="cell markdown"
papermill="{&quot;duration&quot;:9.114e-3,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.916715&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.907601&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search Insert position

</div>

<div id="5821849e" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-20T17:43:15.964998Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-20T17:43:15.964257Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-20T17:43:15.969933Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-20T17:43:15.969056Z&quot;}"
papermill="{&quot;duration&quot;:1.3957e-2,&quot;end_time&quot;:&quot;2024-03-20T17:43:15.971627&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-20T17:43:15.957670&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
