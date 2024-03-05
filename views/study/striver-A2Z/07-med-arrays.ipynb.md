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
    duration: 2.327428
    end_time: "2024-03-05T16:16:26.159457"
    environment_variables: {}
    input_path: study/striver-A2Z/07-med-arrays.ipynb
    output_path: study/striver-A2Z/07-med-arrays.ipynb
    parameters: {}
    start_time: "2024-03-05T16:16:23.832029"
    version: 2.4.0
---

<div id="21da8de7" class="cell markdown"
papermill="{&quot;duration&quot;:1.6269e-2,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.465085&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.448816&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UXDSeD9mN-k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="2f902cd9" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-05T16:16:25.482444Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-05T16:16:25.481824Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-05T16:16:25.514814Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-05T16:16:25.512995Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.4058e-2,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.517755&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.473697&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="1">

    (1, 3)

</div>

</div>

<div id="f0629198" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-05T16:16:25.526972Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-05T16:16:25.526482Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-05T16:16:25.539947Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-05T16:16:25.538177Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2545e-2,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.543677&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.521132&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="2">

    (1, 3)

</div>

</div>

<div id="e337b5a1" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-05T16:16:25.555882Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-05T16:16:25.555386Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-05T16:16:25.568549Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-05T16:16:25.566598Z&quot;}"
papermill="{&quot;duration&quot;:2.342e-2,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.571917&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.548497&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="3">

    True

</div>

</div>

<div id="5b551970" class="cell markdown"
papermill="{&quot;duration&quot;:5.638e-3,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.582787&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.577149&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=tp8JIuCXBaU&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="6a698467" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-05T16:16:25.596573Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-05T16:16:25.596079Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-05T16:16:25.610935Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-05T16:16:25.608655Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6475e-2,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.614722&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.588247&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="4">

    [0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2]

</div>

</div>

<div id="f50bbaee" class="cell markdown"
papermill="{&quot;duration&quot;:4.876e-3,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.624902&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.620026&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="5b07cd07" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-05T16:16:25.638135Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-05T16:16:25.636690Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-05T16:16:25.655393Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-05T16:16:25.653068Z&quot;}"
papermill="{&quot;duration&quot;:2.8379e-2,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.658300&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.629921&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="5">

    [0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2]

</div>

</div>

<div id="eee184d6" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-05T16:16:25.669561Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-05T16:16:25.669067Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-05T16:16:25.680187Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-05T16:16:25.678324Z&quot;}"
papermill="{&quot;duration&quot;:2.185e-2,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.683699&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.661849&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.509e-3,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.697201&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.689692&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="7d9408ac" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-05T16:16:25.712574Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-05T16:16:25.711949Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-05T16:16:25.723039Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-05T16:16:25.721334Z&quot;}"
lines_to_next_cell="2"
papermill="{&quot;duration&quot;:2.2731e-2,&quot;end_time&quot;:&quot;2024-03-05T16:16:25.725774&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-05T16:16:25.703043&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
