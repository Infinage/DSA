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
    duration: 2.718481
    end_time: "2024-03-03T11:38:58.806710"
    environment_variables: {}
    input_path: 06-easy-arrays.ipynb
    output_path: 06-easy-arrays.ipynb
    parameters: {}
    start_time: "2024-03-03T11:38:56.088229"
    version: 2.4.0
---

<div id="53cdaecf" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.313770Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.313448Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.322415Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.321057Z&quot;}"
papermill="{&quot;duration&quot;:1.4667e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.324107&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.309440&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import functools
import itertools
```

</div>

<div id="cb8f677c" class="cell markdown"
papermill="{&quot;duration&quot;:2.046e-3,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.328426&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.326380&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=37E9ckMDdTk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=17>

</div>

<div id="adc79cbd" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.333744Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.333513Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.341623Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.340797Z&quot;}"
papermill="{&quot;duration&quot;:1.3404e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.343793&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.330389&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Largest element of an array
arr: list[int] = [1, 2, 3, 1, 2, 3, 4, 0, 3]
max_ = 0
for i in arr:
    if i > max_:
        max_ = i
max_
```

<div class="output execute_result" execution_count="2">

    4

</div>

</div>

<div id="40ba7146" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.350092Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.349864Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.356866Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.355985Z&quot;}"
papermill="{&quot;duration&quot;:1.2758e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.358688&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.345930&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Second largest element of an array - 2 passes
arr: list[int] = [1, 2, 3, 1, 2, 4, 4, 0, 3]
N = len(arr)

# Find the max index, this way if the Q requires that 2nd 
# largest be a diff number or simply a diff index
# we can accomodate both
max_, second_max_ = 0, 0
for i in range(N):
    if arr[i] > arr[max_]:
        max_ = i

# Variable to ensure that we return -1 if there is no 2nd largest
found = False
for i in range(N):
    if arr[i] > arr[second_max_] and arr[i] != arr[max_]:
        second_max_ = i
        found = True

arr[second_max_] if found else -1
```

<div class="output execute_result" execution_count="3">

    3

</div>

</div>

<div id="dc0c38ed" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.365135Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.364418Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.371845Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.371006Z&quot;}"
papermill="{&quot;duration&quot;:1.272e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.373758&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.361038&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Second largest  and secod largest of an array - 1 pass
arr: list[int] = [1, 2, 3, 1, 2, 4, 4, 2, 3]
N = len(arr)
max_, second_max_ = arr[0], -math.inf
min_, second_min_ = arr[0], math.inf
for i in arr:
    if i >= max_:
        max_ = i
    elif i > second_max_:
        second_max_ = i

    if i <= min_:
        min_ = i
    elif i < second_min_:
        second_min_ = i

second_max_, second_min_
```

<div class="output execute_result" execution_count="4">

    (3, 2)

</div>

</div>

<div id="436544e5" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.381016Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.380155Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.385590Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.384714Z&quot;}"
papermill="{&quot;duration&quot;:1.0929e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.387004&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.376075&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Check if the array is sorted
arr: list[int] = [1, 2, 3, 1, 2, 4, 4, 2, 3]
arr.sort()
for i in range(len(arr) - 1):
    if arr[i] > arr[i + 1]:
        print("False")
        break
else:
    print("True")
```

<div class="output stream stdout">

    True

</div>

</div>

<div id="104a4801" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.393785Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.392836Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.398241Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.397386Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0866e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.400155&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.389289&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Remove duplicates in place from a sorted array
arr: list[int | None] = [1, 1, 2, 2, 2, 3, 3, 4]

N = len(arr)
i, j = 0, 1

while j < N:
    if arr[i] != arr[j]:
        arr[i + 1] = arr[j]
        i += 1
    j += 1
i += 1

while i < N:
    arr[i] = None
    i += 1

print(arr)
```

<div class="output stream stdout">

    [1, 2, 3, 4, None, None, None, None]

</div>

</div>

<div id="6d1febea" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.407005Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.406776Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.411556Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.410710Z&quot;}"
papermill="{&quot;duration&quot;:1.0523e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.413025&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.402502&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Left rotate array by one place
def left_rotate_inplace(arr_: list[int]):
    j, N = arr_[0], len(arr_)
    for i in range(0, N - 1):
        arr_[i] = arr_[i + 1]
    arr_[-1] = j

arr: list[int] = [1, 2, 3, 4, 5]
left_rotate_inplace(arr)
print(arr)
```

<div class="output stream stdout">

    [2, 3, 4, 5, 1]

</div>

</div>

<div id="dbc08a71" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.419241Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.419013Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.424479Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.423396Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0853e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.426288&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.415435&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Left rotate array by K places (in place)
# Time - O(KN), Space - O(1)
arr: list[int] = [1, 2, 3, 4, 5]
k = 4

N = len(arr)
k = k % N
for i in range(k):
    left_rotate_inplace(arr)

print(arr)
```

<div class="output stream stdout">

    [5, 1, 2, 3, 4]

</div>

</div>

<div id="d12886b4" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.433179Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.432647Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.439613Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.438699Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2388e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.441270&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.428882&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Left rotate array by K places 
# Time - O(N), Space - O(N)
def left_rotate_(arr_: list[int], k: int):
    N = len(arr)
    k = k % N

    result: list[int] = []
    for i in range(k, N):
        result.append(arr[i])
    for i in range(k):
        result.append(arr[i])

    return result

left_rotate_([1, 2, 3, 4, 5], 4)
```

<div class="output execute_result" execution_count="9">

    [4, 5, 1, 2, 3]

</div>

</div>

<div id="72166199" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.448304Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.448077Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.454012Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.453175Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2195e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.455996&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.443801&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Left rotate array in O(N) with O(1) space
def left_rotate(arr_: list[int], k: int):
    def reverse(start: int, end: int):
        while start < end:
            arr_[start], arr_[end] = arr_[end], arr_[start]
            start, end = start + 1, end - 1

    N = len(arr_)
    k = k % N

    reverse(0, k - 1)
    reverse(k, N - 1)
    reverse(0, N - 1)

arr: list[int] = [1, 2, 3, 4, 5]
left_rotate(arr, 2)
print(arr)
```

<div class="output stream stdout">

    [3, 4, 5, 1, 2]

</div>

</div>

<div id="fe8102bb" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.463193Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.462964Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.468396Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.467542Z&quot;}"
papermill="{&quot;duration&quot;:1.1347e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.469909&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.458562&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Right rotate array in O(N) with O(1) space
def right_rotate(arr_: list[int], k: int):
    def reverse(start: int, end: int):
        while start < end:
            arr_[start], arr_[end] = arr_[end], arr_[start]
            start, end = start + 1, end - 1

    N = len(arr_)
    k = k % N

    reverse(0, N - 1)
    reverse(0, k - 1)
    reverse(k, N - 1)

arr: list[int] = [1, 2, 3, 4, 5]
right_rotate(arr, 3)
print(arr)
```

<div class="output stream stdout">

    [3, 4, 5, 1, 2]

</div>

</div>

<div id="f1d2c590" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.477315Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.476826Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.482782Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.481908Z&quot;}"
papermill="{&quot;duration&quot;:1.165e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.484302&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.472652&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Move zeros to end of the array
arr: list[int] = [0, 0, 1, 0, 8, 3, 0, 2, 5, 3, 0]
N = len(arr)
i, j = 0, 1
while j < N:
    if arr[i] != 0:
        i += 1
    elif arr[i] == 0 and arr[j] != 0:
        arr[i], arr[j] = arr[j], arr[i]
        i += 1
    j += 1

print (arr)
```

<div class="output stream stdout">

    [1, 8, 3, 2, 5, 3, 0, 0, 0, 0, 0]

</div>

</div>

<div id="9f438462" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.492113Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.491466Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.497963Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.496879Z&quot;}"
papermill="{&quot;duration&quot;:1.2518e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.499540&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.487022&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Linear search
arr: list[int] = [1, 2, 1, 3, 5, 4, 3]
j = 9
for i in range(len(arr)):
    if arr[i] == j:
        break
i if arr[i] == j else -1
```

<div class="output execute_result" execution_count="13">

    -1

</div>

</div>

<div id="952ed4de" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.507303Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.506584Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.513610Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.512774Z&quot;}"
papermill="{&quot;duration&quot;:1.2916e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.515309&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.502393&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Union of two sorted arrays - same order without repetitions
# Time complexity - O(N1 + N2)
arr1: list[int] = [1, 1, 2, 3, 4, 5]
arr2: list[int] = [2, 3, 4, 4, 5, 6]

N1, N2 = len(arr1), len(arr2)
arr: list[int] = []

i, j = 0, 0
while i < N1 or j < N2:
    if j >= N2 or (i < N1 and arr1[i] < arr2[j]):
        if not arr or arr[-1] < arr1[i]:
            arr.append(arr1[i])
        i += 1
    else:
        if not arr or arr[-1] < arr2[j]:
            arr.append(arr2[j])
        j += 1

print(arr)
```

<div class="output stream stdout">

    [1, 2, 3, 4, 5, 6]

</div>

</div>

<div id="e6368fd9" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.522374Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.522148Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.528053Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.527228Z&quot;}"
papermill="{&quot;duration&quot;:1.1799e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.529963&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.518164&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Intersection of two sorted arrays
# Time complexity - O(min(N1, N2))
arr1: list[int] = [1, 1, 2, 3, 4, 5]
arr2: list[int] = [2, 3, 4, 4, 5, 6]

N1, N2 = len(arr1), len(arr2)
arr: list[int] = []

i = j = 0
while i < N1 and j < N2:
    if arr1[i] == arr2[j]:
        arr.append(arr1[i])
        i += 1
        j += 1
    elif arr1[i] < arr2[j]:
        i += 1
    else:
        j += 1

assert arr == [2, 3, 4, 5]
```

</div>

<div id="1038c86e" class="cell markdown"
papermill="{&quot;duration&quot;:2.993e-3,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.536077&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.533084&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=bYWLJb3vCWY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=19>

</div>

<div id="00a0dac6" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.543349Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.543119Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.549465Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.548619Z&quot;}"
papermill="{&quot;duration&quot;:1.1926e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.550846&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.538920&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Find missing number
arr: list[int] = [1, 2, 4, 5]
N = 5

# Approach 1
print(((N * (N + 1)) / 2) - sum(arr))

# Approach 2, this is better since with approach 1 we sum up all the 
# numbers which could potentially be larger compared to this approach 
# where the number would be of utmost size the max element of the array
N1 = functools.reduce(lambda x, y: x ^ y, range(1, N + 1), 0)
for i in arr:
    N1 = N1 ^ i
print(N1)
```

<div class="output stream stdout">

    3.0
    3

</div>

</div>

<div id="11c5af8a" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.558323Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.558095Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.564866Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.564009Z&quot;}"
papermill="{&quot;duration&quot;:1.2637e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.566324&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.553687&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Maximum consequitive ones
arr: list[int] = [1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1]
result: int = 0
count = 0
for i in arr + [0]:
    if i == 1:
        count += 1
    else:
        result = max(result, count)
        count = 0
result
```

<div class="output execute_result" execution_count="17">

    4

</div>

</div>

<div id="ea545fc5" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-03T11:38:58.574476Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-03T11:38:58.574248Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-03T11:38:58.580143Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-03T11:38:58.579301Z&quot;}"
papermill="{&quot;duration&quot;:1.284e-2,&quot;end_time&quot;:&quot;2024-03-03T11:38:58.582112&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-03T11:38:58.569272&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Find element that occurs once when every other element occurs twice
arr: list[int] = [1, 1, 2, 3, 3, 4, 4]
result: int = functools.reduce(lambda x, y: x ^ y, arr)
result
```

<div class="output execute_result" execution_count="18">

    2

</div>

</div>
