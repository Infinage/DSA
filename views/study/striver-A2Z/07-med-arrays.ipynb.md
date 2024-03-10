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
    duration: 2.113234
    end_time: "2024-03-10T09:22:51.970446"
    environment_variables: {}
    input_path: study/striver-A2Z/07-med-arrays.ipynb
    output_path: study/striver-A2Z/07-med-arrays.ipynb
    parameters: {}
    start_time: "2024-03-10T09:22:49.857212"
    version: 2.4.0
---

<div id="1fbe5a89" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.017872Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.017317Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.027647Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.026881Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1467e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.029276&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.007809&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.363e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.044329&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.036966&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UXDSeD9mN-k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="2f902cd9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.060537Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.059934Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.070121Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.069472Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0208e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.071790&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.051582&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.087889Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.087638Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.095359Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.094535Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7652e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.096966&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.079314&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.113511Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.112967Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.120442Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.119674Z&quot;}"
papermill="{&quot;duration&quot;:1.7504e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.122008&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.104504&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.655e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.137628&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.129973&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=tp8JIuCXBaU&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="6a698467" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.154764Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.154015Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.162157Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.161500Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.844e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.163826&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.145386&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.72e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.179365&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.171645&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.196440Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.195793Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.204669Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.203938Z&quot;}"
papermill="{&quot;duration&quot;:1.9223e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.206314&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.187091&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.223855Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.223127Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.229301Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.228626Z&quot;}"
papermill="{&quot;duration&quot;:1.661e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.230913&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.214303&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.216e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.247121&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.238905&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.264889Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.264195Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.271047Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.270250Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7525e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.272737&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.255212&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.079e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.289058&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.280979&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AHZpyENo7k4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=24>

</div>

<div id="39a84ac4" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.306895Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.306301Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.313594Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.312863Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8004e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.315218&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.297214&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.334741Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.334134Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.342293Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.341566Z&quot;}"
papermill="{&quot;duration&quot;:2.017e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.343891&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.323721&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.363357Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.362688Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.366104Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.365377Z&quot;}"
papermill="{&quot;duration&quot;:1.4255e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.367731&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.353476&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]" title="[markdowm]">

``` python
# Video Link: https://youtu.be/excAOvwF_Wk?si=gMRidcVfigxolP0g
# Best time to buy and sell stocks
```

</div>

<div id="d0ab96d2" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.387025Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.386486Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.392783Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.392067Z&quot;}"
papermill="{&quot;duration&quot;:1.7147e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.394424&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.377277&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.414570Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.413973Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.420460Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.419743Z&quot;}"
papermill="{&quot;duration&quot;:1.7426e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.422072&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.404646&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.635e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.440919&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.432284&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/h4aBagy4Uok?si=kTZx4kZSvEfrdO7o> Rearrange
elements by sign

</div>

<div id="31f5ec38" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.459810Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.459128Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.466876Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.466161Z&quot;}"
papermill="{&quot;duration&quot;:1.9012e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.468587&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.449575&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.490561Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.489958Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.498057Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.497378Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.061e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.499747&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.479137&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.91e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.519065&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.510155&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=JDOXKqF60RQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=27>
Next Permutation

</div>

<div id="19358d4f" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.538308Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.537738Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.546248Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.545502Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9943e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.547907&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.527964&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.569172Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.568590Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.578455Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.577737Z&quot;}"
papermill="{&quot;duration&quot;:2.1457e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.580117&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.558660&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.17e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.598606&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.589436&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/cHrH9CQ8pmY?si=Vl3mYSwTY727JgHV> Leaders
of an array

</div>

<div id="0416042b" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.619494Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.618875Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.625634Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.624997Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.834e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.627323&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.608983&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.394e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.647110&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.637716&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

</div>

<div id="0621b858" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.667009Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.666380Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.669911Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.669266Z&quot;}"
incorrectly_encoded_metadata="https://www.youtube.com/watch?v=oO5uLE7EUlM&amp;list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&amp;index=29"
papermill="{&quot;duration&quot;:1.5195e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.671552&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.656357&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]" title="Video Link:">

``` python
# Longest Common subsequence
```

</div>

<div id="49f655a3" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.692541Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.691986Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.699277Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.698474Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8971e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.700834&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.681863&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.278e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.720739&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.711461&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=N0MgLvceX7M&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=30>
Set Matrix 0s

</div>

<div id="49680d8b" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.742278Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.741658Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.758432Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.757696Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8726e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.760090&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.731364&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.561e-3,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.780575&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.771014&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=Z0R2u6gd3GU&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=31>
Rotate image by 90 deg

</div>

<div id="def229bc" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.801092Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.800430Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.809588Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.808977Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1156e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.811192&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.790036&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-10T09:22:51.832733Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-10T09:22:51.832169Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-10T09:22:51.840703Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-10T09:22:51.839960Z&quot;}"
papermill="{&quot;duration&quot;:2.0702e-2,&quot;end_time&quot;:&quot;2024-03-10T09:22:51.842418&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-10T09:22:51.821716&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
