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
    duration: 1.897545
    end_time: "2024-03-08T02:48:58.452060"
    environment_variables: {}
    input_path: study/striver-A2Z/07-med-arrays.ipynb
    output_path: study/striver-A2Z/07-med-arrays.ipynb
    parameters: {}
    start_time: "2024-03-08T02:48:56.554515"
    version: 2.4.0
---

<div id="1fbe5a89" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.716095Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.715439Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:57.725039Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:57.724308Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9464e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.726855&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.707391&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Neccessary imports
import functools
import collections
import math
import random
```

</div>

<div id="21da8de7" class="cell markdown"
papermill="{&quot;duration&quot;:6.161e-3,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.739539&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.733378&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UXDSeD9mN-k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="2f902cd9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.752886Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.752648Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:57.763031Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:57.762196Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8961e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.764650&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.745689&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.778570Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.778067Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:57.786027Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:57.785298Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6683e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.787701&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.771018&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.801771Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.801188Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:57.808493Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:57.807726Z&quot;}"
papermill="{&quot;duration&quot;:1.6055e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.810144&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.794089&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.727e-3,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.823668&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.816941&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=tp8JIuCXBaU&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="6a698467" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.838445Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.837942Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:57.845330Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:57.844581Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6504e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.847015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.830511&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.741e-3,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.860639&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.853898&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.875326Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.874781Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:57.883351Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:57.882578Z&quot;}"
papermill="{&quot;duration&quot;:1.7683e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.885049&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.867366&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.900395Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.899618Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:57.905739Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:57.905101Z&quot;}"
papermill="{&quot;duration&quot;:1.5441e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.907363&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.891922&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.739e-3,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.920968&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.914229&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.935970Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.935463Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:57.941909Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:57.941137Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5881e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.943673&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.927792&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.884e-3,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.957601&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.950717&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AHZpyENo7k4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=24>

</div>

<div id="39a84ac4" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.973252Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.973011Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:57.980253Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:57.979485Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7147e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:57.981908&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.964761&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:57.997493Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:57.996986Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.005392Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.004682Z&quot;}"
papermill="{&quot;duration&quot;:1.7901e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.006989&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:57.989088&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.022903Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.022228Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.025603Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.024886Z&quot;}"
papermill="{&quot;duration&quot;:1.3226e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.027478&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.014252&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]" title="[markdowm]">

``` python
# Video Link: https://youtu.be/excAOvwF_Wk?si=gMRidcVfigxolP0g
# Best time to buy and sell stocks
```

</div>

<div id="d0ab96d2" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.043465Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.042792Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.049423Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.048760Z&quot;}"
papermill="{&quot;duration&quot;:1.6293e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.051048&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.034755&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.067483Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.066941Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.073385Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.072672Z&quot;}"
papermill="{&quot;duration&quot;:1.6419e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.075040&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.058621&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.7e-3,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.090700&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.083000&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/h4aBagy4Uok?si=kTZx4kZSvEfrdO7o> Rearrange
elements by sign

</div>

<div id="31f5ec38" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.107444Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.106816Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.114781Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.114112Z&quot;}"
papermill="{&quot;duration&quot;:1.8025e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.116403&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.098378&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.133434Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.132827Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.140830Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.140154Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8151e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.142431&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.124280&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.188e-3,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.158683&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.150495&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=JDOXKqF60RQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=27>
Next Permutation

</div>

<div id="19358d4f" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.176058Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.175459Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.184505Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.183871Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9549e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.186129&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.166580&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.204394Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.203709Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.214184Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.213491Z&quot;}"
papermill="{&quot;duration&quot;:2.1368e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.215882&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.194514&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.375e-3,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.232835&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.224460&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/cHrH9CQ8pmY?si=Vl3mYSwTY727JgHV> Leaders
of an array

</div>

<div id="0416042b" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.250765Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.250272Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.256806Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.256092Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7349e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.258486&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.241137&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.596e-3,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.275878&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.267282&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

</div>

<div id="0621b858" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.294336Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.294046Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.297546Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.296816Z&quot;}"
incorrectly_encoded_metadata="https://www.youtube.com/watch?v=oO5uLE7EUlM&amp;list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&amp;index=29"
papermill="{&quot;duration&quot;:1.465e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.299197&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.284547&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]" title="Video Link:">

``` python
# Longest Common subsequence
```

</div>

<div id="49f655a3" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-08T02:48:58.318049Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-08T02:48:58.317386Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-08T02:48:58.324908Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-08T02:48:58.324292Z&quot;}"
papermill="{&quot;duration&quot;:1.865e-2,&quot;end_time&quot;:&quot;2024-03-08T02:48:58.326555&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-08T02:48:58.307905&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
