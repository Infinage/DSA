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
    duration: 1.940143
    end_time: "2024-03-07T02:38:01.235468"
    environment_variables: {}
    input_path: study/striver-A2Z/07-med-arrays.ipynb
    output_path: study/striver-A2Z/07-med-arrays.ipynb
    parameters: {}
    start_time: "2024-03-07T02:37:59.295325"
    version: 2.4.0
---

<div id="1fbe5a89" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.467562Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.466806Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.476913Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.476116Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0217e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.478771&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.458554&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Neccessary imports
import functools
import math
import random
```

</div>

<div id="21da8de7" class="cell markdown"
papermill="{&quot;duration&quot;:5.834e-3,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.490848&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.485014&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UXDSeD9mN-k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="2f902cd9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.504311Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.503500Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.514774Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.514023Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0057e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.516645&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.496588&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.530213Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.529794Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.538352Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.537464Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7191e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.539959&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.522768&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.553765Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.553275Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.561378Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.560552Z&quot;}"
papermill="{&quot;duration&quot;:1.6884e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.563018&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.546134&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.133e-3,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.575530&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.569397&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=tp8JIuCXBaU&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="6a698467" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.590418Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.589589Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.598190Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.597434Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7611e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.599805&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.582194&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.447e-3,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.612805&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.606358&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.627148Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.626491Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.635932Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.635144Z&quot;}"
papermill="{&quot;duration&quot;:1.8732e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.637753&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.619021&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.652604Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.651948Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.658008Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.657258Z&quot;}"
papermill="{&quot;duration&quot;:1.5137e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.659593&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.644456&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.547e-3,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.672705&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.666158&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.687549Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.687029Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.694021Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.693218Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6393e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.695654&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.679261&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.56e-3,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.708955&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.702395&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AHZpyENo7k4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=24>

</div>

<div id="39a84ac4" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.724308Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.723602Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.731700Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.730946Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7576e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.733334&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.715758&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.748462Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.747943Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.756506Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.755696Z&quot;}"
papermill="{&quot;duration&quot;:1.8138e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.758288&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.740150&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.773886Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.773367Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.776999Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.776222Z&quot;}"
papermill="{&quot;duration&quot;:1.3365e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.778713&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.765348&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]" title="[markdowm]">

``` python
# Video Link: https://youtu.be/excAOvwF_Wk?si=gMRidcVfigxolP0g
# Best time to buy and sell stocks
```

</div>

<div id="d0ab96d2" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.794387Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.793847Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.801053Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.800202Z&quot;}"
papermill="{&quot;duration&quot;:1.6992e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.802747&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.785755&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.818913Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.818302Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.825679Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.824840Z&quot;}"
papermill="{&quot;duration&quot;:1.723e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.827464&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.810234&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.281e-3,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.842236&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.834955&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/h4aBagy4Uok?si=kTZx4kZSvEfrdO7o> Rearrange
elements by sign

</div>

<div id="31f5ec38" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.858668Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.857951Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.866504Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.865723Z&quot;}"
papermill="{&quot;duration&quot;:1.8676e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.868195&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.849519&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.885247Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.884616Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.893138Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.892271Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8844e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.894755&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.875911&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.629e-3,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.910289&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.902660&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=JDOXKqF60RQ&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=27>
Next Permutation

</div>

<div id="19358d4f" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.927601Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.926888Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.936018Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.935261Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9675e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.937706&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.918031&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:00.955837Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:00.955219Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:00.965695Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:00.964906Z&quot;}"
papermill="{&quot;duration&quot;:2.1398e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.967454&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.946056&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.071e-3,&quot;end_time&quot;:&quot;2024-03-07T02:38:00.983771&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.975700&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/cHrH9CQ8pmY?si=Vl3mYSwTY727JgHV> Leaders
of an array

</div>

<div id="0416042b" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-07T02:38:01.001826Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-07T02:38:01.001074Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-07T02:38:01.008682Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-07T02:38:01.008007Z&quot;}"
papermill="{&quot;duration&quot;:1.8489e-2,&quot;end_time&quot;:&quot;2024-03-07T02:38:01.010360&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-07T02:38:00.991871&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
