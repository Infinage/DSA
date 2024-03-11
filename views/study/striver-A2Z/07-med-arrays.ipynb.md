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
    duration: 2.316907
    end_time: "2024-03-11T02:37:56.423600"
    environment_variables: {}
    input_path: study/striver-A2Z/07-med-arrays.ipynb
    output_path: study/striver-A2Z/07-med-arrays.ipynb
    parameters: {}
    start_time: "2024-03-11T02:37:54.106693"
    version: 2.4.0
---

<div id="1fbe5a89" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.275268Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.274726Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.284431Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.283781Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1853e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.286143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.264290&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Neccessary imports
import functools
import collections
import math
import random
import pdb
```

</div>

<div id="21da8de7" class="cell markdown"
papermill="{&quot;duration&quot;:8.179e-3,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.302878&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.294699&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UXDSeD9mN-k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="2f902cd9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.320680Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.320160Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.330451Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.329827Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0936e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.332081&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.311145&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Two Sum - Brute Force
def two_sum_brute(arr_: list[int], target: int) -> tuple[int, int]:
    "Time complexity - O(N^2)"
    N = len(arr_)
    for i in range(N - 1):
        for j in range(i + 1, N):
            if arr_[i] + arr_[j] == target:
                return i, j
    else:
        return -1, -1

two_sum_brute([2, 6, 5, 8, 11], 14)
```

<div class="output execute_result" execution_count="2">

    (1, 3)

</div>

</div>

<div id="f0629198" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.349810Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.349574Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.357100Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.356335Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8277e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.358770&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.340493&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Two sum - better
def two_sum_better(arr_: list[int], target: int) -> tuple[int, int]:
    "Time compelexity - O(N), Space - O(N)"
    N = len(arr_)
    dict_: dict[int, int] = {}
    for i in range(N):
        if target - arr_[i] in dict_:
            result = i, dict_[target - arr_[i]]
            return min(result), max(result)
        dict_[arr_[i]] = i
    return -1, -1

two_sum_better([2, 6, 5, 8, 11], 14)
```

<div class="output execute_result" execution_count="3">

    (1, 3)

</div>

</div>

<div id="e337b5a1" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.377167Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.376593Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.383969Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.383196Z&quot;}"
papermill="{&quot;duration&quot;:1.8289e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.385567&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.367278&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Two sum - Optimal
def two_sum_optimal(arr_: list[int], target: int) -> bool:
    "Time - O(N log N), Space - O(1)"
    arr_.sort()
    N = len(arr_)
    i, j = 0, N - 1
    while i < j and j < N:
        sum_ = arr_[i] + arr_[j]
        if sum_ == target:
            return True
        elif sum_ < target:
            i += 1
        else:
            j -= 1
    return False

two_sum_optimal([2, 6, 5, 8, 11], 14)
```

<div class="output execute_result" execution_count="4">

    True

</div>

</div>

<div id="5b551970" class="cell markdown"
papermill="{&quot;duration&quot;:8.446e-3,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.402614&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.394168&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=tp8JIuCXBaU&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="6a698467" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.421292Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.420830Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.428592Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.427756Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8938e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.430242&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.411304&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Sort an array of 0s, 1s, 2s
# Time - O(2N) - Better
arr = [0, 1, 2, 0, 1, 2, 1, 2, 0, 0, 0, 1]

N = len(arr)
counter: dict[int, int] = dict()
for j in arr:
    counter[j] = counter.get(j, 0) + 1

i = 0
for j in [0, 1, 2]:
    while counter[j]:
        arr[i] = j
        counter[j] -= 1
        i += 1

arr
```

<div class="output execute_result" execution_count="5">

    [0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2]

</div>

</div>

<div id="f50bbaee" class="cell markdown"
papermill="{&quot;duration&quot;:8.559e-3,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.447552&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.438993&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

##### Dutch National Flag Algorithm<br>

We can perform better than O(2N), by using this algorithm involving 3
pointers.

Imagine having a hypothetical array:

          [0, 0, 0, 0, 1, 1, 1, 1, _, _, _, _, _, _, 2, 2, 2]
                       L           M                 H

    L: low, M: mid, H: high

1.  0 - (low - 1): consists of only 0s
2.  low - (mid - 1): consists of onlys 1s
3.  mid - high: consists of unsorted numbers
4.  (high + 1) - (n - 1): consists of only 2s

Imagine the provided array is from mid - high, to sort the array we
manipulate the pointers

</div>

<div id="5b07cd07" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.466189Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.465615Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.474744Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.474131Z&quot;}"
papermill="{&quot;duration&quot;:2.0178e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.476381&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.456203&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Sort an array of 0s, 1s, 2s
# Time - O(N), Dutch National Flag Algorithm - Optimal
def DNF(arr_: list[int]) -> None:
    N = len(arr_)
    low, mid, high = 0, 0, N - 1
    while mid <= high:
        if arr_[mid] == 0:
            # Push it to where low is and inc both low and mid
            arr_[low], arr_[mid] = arr_[mid], arr_[low]
            low += 1
            mid += 1
        elif arr_[mid] == 1:
            # It is in the right place, simply inc mid
            mid += 1
        else:
            # Push to the right and decrement high, note that mid remains in the same spot
            arr_[mid], arr_[high] = arr_[high], arr_[mid]
            high -= 1

# Testing the algorithm
arr = [0, 1, 2, 0, 1, 2, 1, 2, 0, 0, 0, 1]
DNF(arr)
arr
```

<div class="output execute_result" execution_count="6">

    [0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2]

</div>

</div>

<div id="eee184d6" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.495532Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.494977Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.500653Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.499845Z&quot;}"
papermill="{&quot;duration&quot;:1.6876e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.502320&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.485444&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Majority element - Better
arr: list[int] = [2, 2, 3, 3, 1, 2, 2]

N = len(arr)
counter: dict[int, int] = dict()

for i in arr:
    counter[i] = counter.get(i, 0) + 1
    if counter[i] > N // 2:
        print (i)
        break
else:
    print (-1)
```

<div class="output stream stdout">

    2

</div>

</div>

<div id="9a783959" class="cell markdown"
papermill="{&quot;duration&quot;:8.954e-3,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.520336&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.511382&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://www.youtube.com/watch?v=vwZj1K0e9U8> This can be
solved with O(1) space in O(1) time by Moore's voting algorithm

##### Moore's algorithm:

    Have two variables - curr, count
    Iterate through array
      If i == curr -> inc count else decrement it
      If count == 0, curr = i, count = 1

As step 2 validate after iteration if curr is indeed the majority
element

</div>

<div id="7d9408ac" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.539488Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.538871Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.545615Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.544964Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7952e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.547182&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.529230&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
arr: list[int] = [2, 2, 3, 3, 1, 2, 2]
N = len(arr)

# Step 1: Run moore's voting algorithm
curr, count = None, 0
for i in arr:
    if count == 0:
        curr = i
        count = 1
    elif i == curr:
        count += 1
    else:
        count -= 1

# Step 2: Validate moore's result
if count > 0:
    count = 0
    for i in arr:
        if i == curr:
            count += 1
    if count > N // 2:
        print (curr)
    else:
        print (-1)
else:
    print (-1)
```

<div class="output stream stdout">

    2

</div>

</div>

<div id="bd2d6454" class="cell markdown"
papermill="{&quot;duration&quot;:1.0256e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.566557&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.556301&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AHZpyENo7k4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=24>

</div>

<div id="39a84ac4" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.585951Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.585430Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.592562Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.591793Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8682e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.594218&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.575536&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Maximum subarray sum - Brute Force
def max_subarray_sum_brute(arr_: list[int]) -> int:
    "Time - O(N ^ 2), Space - O(1)"
    N = len(arr_)
    max_ = -math.inf
    for i in range(N):
        sum_ = 0
        for j in range(i, N):
            sum_ += arr[j]
            max_ = max(max_, sum_)
    return max_

arr: list[int] = [-2, -3, 4, -1, -2, 1, 5, -3]
max_subarray_sum_brute(arr)
```

<div class="output execute_result" execution_count="9">

    7

</div>

</div>

<div id="67730685" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.615671Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.615167Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.623186Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.622482Z&quot;}"
papermill="{&quot;duration&quot;:1.9862e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.625046&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.605184&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Maximum subarray sum - Optimal
def max_subarray_sum_better(arr_: list[int]) -> int:
    """
    Kadane's algorithm: drop sum if sum < 0 else carry it forward
    Time - O(N), Space - O(1)
    """
    N = len(arr_)
    start_idx = 0

    # If empty subarrays allowed else -math.info
    # max_sum, start_idx, end_idx
    max_ = -math.inf, None, None
    sum_ = 0
    for i in range(N):
        sum_ += arr[i]
        if sum_ > max_[0]:
            max_ = sum_, start_idx, i
        if sum_ < 0: # Every time we chose to drop the sum, reset the start idx
            sum_ = 0
            start_idx = i + 1
    return max_

arr: list[int] = [-2, -3, 4, -1, -2, 1, 5, -3]
max_subarray_sum_better(arr)
```

<div class="output execute_result" execution_count="10">

    (7, 2, 6)

</div>

</div>

<div id="26800f05" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.646321Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.645660Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.649243Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.648644Z&quot;}"
papermill="{&quot;duration&quot;:1.5261e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.650817&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.635556&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]" title="[markdowm]">

``` python
# Video Link: https://youtu.be/excAOvwF_Wk?si=gMRidcVfigxolP0g
# Best time to buy and sell stocks
```

</div>

<div id="d0ab96d2" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.671683Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.671451Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.677787Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.677060Z&quot;}"
papermill="{&quot;duration&quot;:1.8022e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.679426&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.661404&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force - O(N ^ 2)
arr: list[int] = [7, 1, 5, 3, 6, 4]
N = len(arr)
max_ = -math.inf
for i in range(N):
    for j in range(i + 1, N):
        max_ = max(max_, arr[j] - arr[i])
max_
```

<div class="output execute_result" execution_count="12">

    5

</div>

</div>

<div id="41896d89" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.701325Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.700872Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.707790Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.707018Z&quot;}"
papermill="{&quot;duration&quot;:1.8962e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.709526&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.690564&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better solution: Time - O(N), Space - O(1)
arr: list[int] = [7, 1, 5, 3, 6, 4]
N = len(arr)

max_ = -math.inf
highest_ = arr[N - 1]
i = N - 2
while i >= 0:
    max_ = max(max_, highest_ - arr[i])
    highest_ = max(highest_, arr[i])
    i -= 1
max_
```

<div class="output execute_result" execution_count="13">

    5

</div>

</div>

<div id="3c63de23" class="cell markdown"
papermill="{&quot;duration&quot;:9.405e-3,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.729873&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.720468&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/h4aBagy4Uok?si=kTZx4kZSvEfrdO7o> Rearrange
elements by sign

</div>

<div id="31f5ec38" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.750246Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.749954Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.758106Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.757435Z&quot;}"
papermill="{&quot;duration&quot;:2.0182e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.759721&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.739539&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force: Time - O(N), Space - O(N)
arr: list[int] = [3, 1, -2, -5, 2, -4]
N = len(arr)
arr1: list[int] = []
arr2: list[int] = []
for i in range(N):
    if arr[i] > 0:
        arr1.append(arr[i])
    else:
        arr2.append(arr[i])

i = 0
while i < N // 2:
    arr[(2 * i)] = arr1[i]
    arr[(2 * i) + 1] = arr2[i]
    i += 1

arr
```

<div class="output execute_result" execution_count="14">

    [3, -2, 1, -5, 2, -4]

</div>

</div>

<div id="c82df348" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.781765Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.781139Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.789297Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.788668Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0208e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.790899&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.770691&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Rearrange elements by sign, where len(+ve) != len(-ve)
arr: list[int] = [-1, 2, 3, 4, -3, 1]

# O(4N): Got tired :(
arr1: list[int] = list(filter(lambda x: x > 0, arr))[::-1]
arr2: list[int] = list(filter(lambda x: x < 0, arr))[::-1]

i = 0
while arr1 or arr2:
    if arr1:
        arr[i] = arr1.pop()
        i += 1
    if arr2:
        arr[i] = arr2.pop()
        i += 1

arr
```

<div class="output execute_result" execution_count="15">

    [2, -1, 3, -3, 4, 1]

</div>

</div>

<div id="319b376d" class="cell markdown"
papermill="{&quot;duration&quot;:9.682e-3,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.812021&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.802339&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=JDOXKqF60RQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=27>
Next Permutation

</div>

<div id="19358d4f" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.833011Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.832424Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.841065Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.840440Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0868e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.842674&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.821806&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute Force
def generate_perms(arr_: list[int]) -> list[list[int]]:
    # Time - O(N!), Space - O(N!)
    N = len(arr_)
    if N <= 1:
        return [arr_]
    else:
        result: list[list[int]] = []
        for i in range(N):
            for next_ in generate_perms(arr_[:i] + arr_[i+1:]):
                result.append([arr_[i]] + next_)
        return result

# Testing the solution
arr: list[int] = [1, 2, 3]
arr1: list[list[int]] = sorted(generate_perms(arr))
i = arr1.index(arr)
arr1[i + 1] if i < len(arr1) - 1 else arr1[0]
```

<div class="output execute_result" execution_count="16">

    [1, 3, 2]

</div>

</div>

<div id="97d071df" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.865435Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.864906Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.875233Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.874452Z&quot;}"
papermill="{&quot;duration&quot;:2.2605e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.876862&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.854257&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better
def next_perm(arr_: list[int]) -> list[int]:

    def reverse_(start: int, end: int):
        while start < end:
            arr_[start], arr_[end] = arr_[end], arr_[start]
            start += 1
            end -= 1

    N = len(arr_)
    max_ = arr_[N - 1]
    i = N - 2
    while i >= 0:
        if arr_[i] < max_:
            # Find minimum element inside slice that is greater than arr_[i]
            min_idx = i + 1
            for j in range(i + 1, N):
                if arr_[j] > arr_[i] and arr_[j] <= arr_[min_idx]:
                    min_idx = j
            arr_[i], arr_[min_idx] = arr_[min_idx], arr_[i]
            reverse_(i + 1, N - 1)
            return arr_
        else:
            max_ = arr_[i]
            i -= 1
    else:
        arr_.reverse()
        return arr_

# Testing the solution
arr: list[int] = [2, 1, 5, 4, 3]
next_perm(arr)
```

<div class="output execute_result" execution_count="17">

    [2, 3, 1, 4, 5]

</div>

</div>

<div id="c61e4105" class="cell markdown"
papermill="{&quot;duration&quot;:9.88e-3,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.898131&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.888251&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/cHrH9CQ8pmY?si=Vl3mYSwTY727JgHV> Leaders
of an array

</div>

<div id="0416042b" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.919510Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.918837Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.925462Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.924748Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9029e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.927167&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.908138&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Time - O(N), Space - O(N)
arr = [10, 22, 12, 3, 0, 6]

N = len(arr)
max_ = arr[N - 1]
arr1 = [max_]
i = N - 1
while i >= 0:
    if arr[i] > max_:
        arr1.append(arr[i])
        max_ = arr[i]
    i -= 1

arr1
```

<div class="output execute_result" execution_count="18">

    [6, 12, 22]

</div>

</div>

<div id="c084b1a7" class="cell markdown" lines_to_next_cell="0"
papermill="{&quot;duration&quot;:1.0015e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.948879&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.938864&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

</div>

<div id="0621b858" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.971013Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.970266Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:55.974128Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:55.973521Z&quot;}"
incorrectly_encoded_metadata="https://www.youtube.com/watch?v=oO5uLE7EUlM&amp;list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&amp;index=29"
papermill="{&quot;duration&quot;:1.6558e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:55.975721&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.959163&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]" title="Video Link:">

``` python
# Longest Common subsequence
```

</div>

<div id="49f655a3" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:55.997998Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:55.997758Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:56.005198Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:56.004563Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9879e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.006712&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:55.986833&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        counter: dict[int, int] = {n: 1 for n in nums}
        for n in nums:
            if n in counter:
                count = counter[n]
                curr = n
                while curr + 1 in counter:
                    count += counter.pop(curr + 1)
                    curr += 1
                counter[n] = count

        return max(counter.values()) if counter else 0

# Testing the solution
assert Solution().longestConsecutive([100,4,200,1,3,2]) == 4
assert Solution().longestConsecutive([0,3,7,2,5,8,4,6,0,1]) == 9
assert Solution().longestConsecutive([1,2,2,3]) == 3
assert Solution().longestConsecutive([1,1,1,1,2,2,2,3,3,3,3]) == 3
```

</div>

<div id="de8b0b7b" class="cell markdown"
papermill="{&quot;duration&quot;:9.91e-3,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.027514&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.017604&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=N0MgLvceX7M&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=30>
Set Matrix 0s

</div>

<div id="49680d8b" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:56.049107Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:56.048467Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:56.065533Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:56.064902Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9491e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.067121&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.037630&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force - O((M * N)(M + N))
class Solution:
    def setZeroes(self, matrix: list[list[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """

        def BFS(i: int, j: int):
            for k in range(M):
                matrix[k][j] = 2
            for k in range(N):
                matrix[i][k] = 2

        M, N = len(matrix), len(matrix[0])
        for i in range(M):
            for j in range(N):
                if matrix[i][j] == 0:
                    BFS(i, j)

        for i in range(M):
            for j in range(N):
                if matrix[i][j] == 2:
                    matrix[i][j] = 0

        print (matrix)

# Testing the solution
temp = [[1,1,1],[1,0,1],[1,1,1]]
Solution().setZeroes(temp)
assert temp == [[1,0,1],[0,0,0],[1,0,1]]

# Better solution
class Solution:
    def setZeroes(self, matrix: list[list[int]]) -> None:
        M, N = len(matrix), len(matrix[0])

        row0 = 1
        for i in range(M):
            for j in range(N):
                if matrix[i][j] == 0:
                    if i == 0:
                        row0 = 0
                    else:
                        matrix[i][0] = 0
                    matrix[0][j] = 0

        for i in range(1, M):
            for j in range(1, N):
                if matrix[0][j] == 0:
                    matrix[i][j] = 0
                if matrix[i][0] == 0:
                    matrix[i][j] = 0

        if row0 == 0:
            for j in range(1, N):
                matrix[0][j] = 0

        if matrix[0][0] == 0:
            for i in range(M):
                matrix[i][0] = 0

        matrix[0][0] = 0 if row0 == 0 else matrix[0][0]

# Testing the solution
for temp in (
    [[[1,1,1],[1,0,1],[1,1,1]], [[1,0,1],[0,0,0],[1,0,1]]],
    [[[0,1,2,0],[3,4,5,2],[1,3,1,5]], [[0,0,0,0],[0,4,5,0],[0,3,1,0]]],
    [[[-4,10,6,-7,0],[-8,6,-8,-6,0],[3,2,-9,-6,-10]], [[0,0,0,0,0],[0,0,0,0,0],[3,2,-9,-6,0]]]
):
    Solution().setZeroes(temp[0])
    assert temp[0] == temp[1]
```

<div class="output stream stdout">

    [[1, 0, 1], [0, 0, 0], [1, 0, 1]]

</div>

</div>

<div id="bb05528f" class="cell markdown"
papermill="{&quot;duration&quot;:1.0158e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.088819&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.078661&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=Z0R2u6gd3GU&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=31>
Rotate image by 90 deg

</div>

<div id="def229bc" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:56.112183Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:56.111430Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:56.120692Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:56.120065Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1944e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.122337&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.100393&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class Solution:
    def rotate(self, matrix: list[list[int]]) -> None:
        """
        N = 4, i = 0

        j = 0: (0, 0), (0, 3), (3, 3), (3, 0)
        j = 1: (0, 1), (1, 3), (3, 2), (2, 0)
        j = 2: (0, 2), (2, 3), (3, 1), (1, 0)

        N = 4, i = 1

        j = 1: (1, 1), (1, 2), (2, 2), (2, 1)

        Generally put: (i, j), (j, N - i - 1), (N - i - 1, N - j - 1), (N - j - 1, i)
        """

        N = len(matrix)
        for i in range(math.ceil(N / 2)):
            for j in range(i, N - 1 - i):
                i_, j_ = N - i - 1, N - j - 1
                matrix[i][j], matrix[j][i_], matrix[i_][j_], matrix[j_][i] = matrix[j_][i], matrix[i][j], matrix[j][i_], matrix[i_][j_]


# Testing the solution
for temp in (
    [[[1,2,3],[4,5,6],[7,8,9]], [[7,4,1],[8,5,2],[9,6,3]]],
    [[[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]], [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]]
):
    Solution().rotate(temp[0])
    assert temp[0] == temp[1]
```

</div>

<div id="a6c38a1b" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:56.145026Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:56.144560Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:56.153502Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:56.152771Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1524e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.155091&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.133567&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Solution from striver
class Solution:
    def rotate(self, matrix: list[list[int]]) -> None:
        """
        1. Transpose the matrix
        2. Reverse each row elements
        """

        N = len(matrix)

        # Transpose the matrix
        for i in range(N):
            for j in range(i, N):
                matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]

        # Reverse each row 
        for i in range(N):
            for j in range(N // 2):
                matrix[i][j], matrix[i][N - j - 1] = matrix[i][N - j - 1], matrix[i][j]


# Testing the solution
for temp in (
    [[[1,2,3],[4,5,6],[7,8,9]], [[7,4,1],[8,5,2],[9,6,3]]],
    [[[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]], [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]]
):
    Solution().rotate(temp[0])
    assert temp[0] == temp[1]
```

</div>

<div id="2b214952" class="cell markdown"
papermill="{&quot;duration&quot;:1.0126e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.176501&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.166375&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=3Zv-s9UUrFM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=32>
Spiral matrix

</div>

<div id="670d322e" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:56.198454Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:56.197866Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:56.210167Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:56.209441Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5055e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.211903&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.186848&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class Solution:
    def spiralOrder(self, matrix: list[list[int | None]]) -> list[int | None]:
        M, N = len(matrix), len(matrix[0])
        i, j = 0, 0
        result: list[int | None] = []
        while i < M and j < N and matrix[i][j] != None:
            # Go right
            while j < N and matrix[i][j] != None:
                result.append(matrix[i][j])
                matrix[i][j] = None
                j += 1

            # Go down
            i, j = i + 1, j - 1
            while i < M and matrix[i][j] != None:
                result.append(matrix[i][j])
                matrix[i][j] = None
                i += 1

            # Go left
            i, j = i - 1, j - 1
            while j >= 0 and matrix[i][j] != None:
                result.append(matrix[i][j])
                matrix[i][j] = None
                j -= 1

            # Go up
            i, j = i - 1, j + 1
            while i > 0 and matrix[i][j] != None:
                result.append(matrix[i][j])
                matrix[i][j] = None
                i -= 1

            # For next iteration
            i, j = i + 1, j + 1

        return result

# Testing the solution
assert Solution().spiralOrder([[1, 2, 3], [4, 5, 6], [7, 8, 9]]) == [1, 2, 3, 6, 9, 8, 7, 4, 5]
assert Solution().spiralOrder([[1, 2, 3, 4]]) == [1, 2, 3, 4]
assert Solution().spiralOrder([[1], [2], [3], [4]]) == [1, 2, 3, 4]
assert Solution().spiralOrder([[1]]) == [1]
assert Solution().spiralOrder([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]]) == [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]
```

</div>

<div id="fbecbabd" class="cell markdown"
papermill="{&quot;duration&quot;:1.0251e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.234272&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.224021&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=xvNwoz-ufXA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=33>
Count subarray sum equals k

</div>

<div id="7586edcb" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:56.255994Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:56.255477Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:56.262357Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:56.261541Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9431e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.263971&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.244540&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force
class Solution:
    def subarraySum(self, nums: list[int], K: int) -> int:
        "Time - O(N ^ 2)"
        N = len(nums)
        count_ = 0
        for i in range(N):
            sum_ = 0
            for j in range(i, N):
               sum_ += nums[j]
               if sum_ == K:
                   print(nums[i: j + 1])
                   count_ += 1

        return count_

# Testing the solution
assert Solution().subarraySum([1, 2, 3, -3, 1, 1, 1, 4, 2, -3], 3) == 8
```

<div class="output stream stdout">

    [1, 2]
    [1, 2, 3, -3]
    [2, 3, -3, 1]
    [3]
    [3, -3, 1, 1, 1]
    [-3, 1, 1, 1, 4, 2, -3]
    [1, 1, 1]
    [4, 2, -3]

</div>

</div>

<div id="75940c41" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-11T02:37:56.288012Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-11T02:37:56.287392Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-11T02:37:56.293962Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-11T02:37:56.293243Z&quot;}"
papermill="{&quot;duration&quot;:1.9371e-2,&quot;end_time&quot;:&quot;2024-03-11T02:37:56.295553&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-11T02:37:56.276182&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal
class Solution:
    def subarraySum(self, nums: list[int], K: int) -> int:
        """
        Time - O(N), Space - O(N)
        Prefix Sum: For curr sum as sum_, how many prefix sum exists sum_ - k?
        """
        hashmap: dict[int, int] = {0: 1}
        count = sum_ = 0
        for i in range(len(nums)):
            sum_ += nums[i]
            if sum_ - K in hashmap:
                count += hashmap[sum_ - K]
            hashmap[sum_] = hashmap.get(sum_, 0) + 1
        return count

# Testing the solution
assert Solution().subarraySum([1, 2, 3, -3, 1, 1, 1, 4, 2, -3], 3) == 8
assert Solution().subarraySum([1, 1, 1], 2) == 2
assert Solution().subarraySum([1, 2, 3], 3) == 2
```

</div>
