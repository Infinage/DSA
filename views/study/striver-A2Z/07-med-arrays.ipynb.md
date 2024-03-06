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
    duration: 2.999048
    end_time: "2024-03-06T13:45:10.146856"
    environment_variables: {}
    input_path: study/striver-A2Z/07-med-arrays.ipynb
    output_path: study/striver-A2Z/07-med-arrays.ipynb
    parameters: {}
    start_time: "2024-03-06T13:45:07.147808"
    version: 2.4.0
---

<div id="1fbe5a89" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.659555Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.658177Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.666459Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.665667Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.494e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.668449&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.653509&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Neccessary imports
import functools
import math
import random
```

</div>

<div id="21da8de7" class="cell markdown"
papermill="{&quot;duration&quot;:2.524e-3,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.673745&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.671221&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UXDSeD9mN-k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="2f902cd9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.681093Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.680699Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.689450Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.688603Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.506e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.691334&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.676274&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.697524Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.697300Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.704878Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.704031Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2889e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.706603&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.693714&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.712620Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.712390Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.720270Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.719409Z&quot;}"
papermill="{&quot;duration&quot;:1.3206e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.722218&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.709012&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.561e-3,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.727425&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.724864&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=tp8JIuCXBaU&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="6a698467" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.734305Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.733602Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.741560Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.740608Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3087e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.742955&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.729868&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.861e-3,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.748438&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.745577&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.755628Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.754924Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.763226Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.762377Z&quot;}"
papermill="{&quot;duration&quot;:1.422e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.765214&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.750994&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.772265Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.771808Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.777141Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.775974Z&quot;}"
papermill="{&quot;duration&quot;:1.112e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.778903&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.767783&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.715e-3,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.784558&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.781843&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.791066Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.790832Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.797382Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.796330Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2212e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.799380&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.787168&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.562e-3,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.804712&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.802150&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AHZpyENo7k4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=24>

</div>

<div id="39a84ac4" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.813447Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.812552Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.819456Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.818583Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3412e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.821443&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.808031&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.829863Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.828847Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.836541Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.835665Z&quot;}"
papermill="{&quot;duration&quot;:1.4219e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.838460&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.824241&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.845905Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.845353Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.849192Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.848009Z&quot;}"
papermill="{&quot;duration&quot;:9.188e-3,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.850502&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.841314&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]" title="[markdowm]">

``` python
# Video Link: https://youtu.be/excAOvwF_Wk?si=gMRidcVfigxolP0g
# Best time to buy and sell stocks
```

</div>

<div id="d0ab96d2" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.858762Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.857850Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.863851Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.863057Z&quot;}"
papermill="{&quot;duration&quot;:1.2413e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.865794&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.853381&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.873407Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.873024Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.880285Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.879434Z&quot;}"
papermill="{&quot;duration&quot;:1.3301e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.882060&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.868759&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.05e-3,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.888219&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.885169&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/h4aBagy4Uok?si=kTZx4kZSvEfrdO7o> Rearrange
elements by sign

</div>

<div id="31f5ec38" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.896764Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.895839Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.904225Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.903372Z&quot;}"
papermill="{&quot;duration&quot;:1.4436e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.905945&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.891509&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-06T13:45:09.914604Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-06T13:45:09.913802Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-06T13:45:09.921256Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-06T13:45:09.920404Z&quot;}"
papermill="{&quot;duration&quot;:1.3919e-2,&quot;end_time&quot;:&quot;2024-03-06T13:45:09.922986&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-06T13:45:09.909067&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
