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
    duration: 5.50673
    end_time: "2024-03-04T02:35:00.923394"
    environment_variables: {}
    input_path: 06-easy-arrays.ipynb
    output_path: 06-easy-arrays.ipynb
    parameters: {}
    start_time: "2024-03-04T02:34:55.416664"
    version: 2.4.0
---

<div id="53cdaecf" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.334305Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.333029Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.353351Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.351233Z&quot;}"
papermill="{&quot;duration&quot;:4.0618e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.357886&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.317268&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import functools
import itertools
```

</div>

<div id="cb8f677c" class="cell markdown"
papermill="{&quot;duration&quot;:1.1231e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.377880&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.366649&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=37E9ckMDdTk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=17>

</div>

<div id="adc79cbd" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.398754Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.397664Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.415406Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.413086Z&quot;}"
papermill="{&quot;duration&quot;:3.1426e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.418983&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.387557&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.438247Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.436894Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.454884Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.451818Z&quot;}"
papermill="{&quot;duration&quot;:3.3267e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.459967&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.426700&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.482912Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.481677Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.500222Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.497403Z&quot;}"
papermill="{&quot;duration&quot;:3.5523e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.504397&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.468874&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.525985Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.524595Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.538714Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.536174Z&quot;}"
papermill="{&quot;duration&quot;:2.9228e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.542584&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.513356&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.564458Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.563244Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.579030Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.576429Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1818e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.583143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.551325&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.609562Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.608349Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.622895Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.619914Z&quot;}"
papermill="{&quot;duration&quot;:3.4366e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.627083&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.592717&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.649334Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.648041Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.661839Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.659520Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9284e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.665867&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.636583&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.752682Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.751464Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.770011Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.767654Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.8476e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.774121&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.675645&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.800905Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.799703Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.817038Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.814788Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6846e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.821047&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.784201&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.844048Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.842839Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.858559Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.855647Z&quot;}"
papermill="{&quot;duration&quot;:3.1755e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.862245&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.830490&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.885480Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.884290Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.899581Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.897165Z&quot;}"
papermill="{&quot;duration&quot;:3.1192e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.903926&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.872734&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:34:59.930177Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:34:59.929575Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:34:59.946889Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:34:59.944180Z&quot;}"
papermill="{&quot;duration&quot;:3.7555e-2,&quot;end_time&quot;:&quot;2024-03-04T02:34:59.951260&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.913705&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:00.008079Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:00.006565Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:00.034138Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:00.031448Z&quot;}"
papermill="{&quot;duration&quot;:8.7025e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.048139&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:34:59.961114&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:00.094883Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:00.094314Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:00.108550Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:00.105719Z&quot;}"
papermill="{&quot;duration&quot;:3.6911e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.113031&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.076120&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3385e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.136663&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.123278&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=bYWLJb3vCWY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=19>

</div>

<div id="00a0dac6" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:00.160734Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:00.159517Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:00.174703Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:00.171492Z&quot;}"
papermill="{&quot;duration&quot;:3.2209e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.178952&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.146743&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:00.203987Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:00.202662Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:00.220888Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:00.218659Z&quot;}"
papermill="{&quot;duration&quot;:3.646e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.225797&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.189337&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:00.253235Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:00.251820Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:00.270814Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:00.267437Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.8199e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.274604&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.236405&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="3c2b7f3b" class="cell markdown"
papermill="{&quot;duration&quot;:9.923e-3,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.294709&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.284786&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=frf7qxiN2qU&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=20>

</div>

<div id="4e9fa5a5" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:00.319300Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:00.318237Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:00.333242Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:00.331232Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1784e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.336737&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.304953&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Longest subarray with sum K - brute force
def lcs_brute(arr_: list[int], k: int) -> int:
    "Return max length subarray with sum = k, O(N^3)"
    N = len(arr_)
    max_ = 0
    for i in range(N):
        for j in range(i, N):
            sub_ = arr_[i: j + 1]
            if sum(sub_) == k:
                max_ = max(max_, j - i + 1)
    return max_

lcs_brute([1, 2, 3, 1, 1, 1, 1, 4, 2, 3], 4)
```

<div class="output execute_result" execution_count="19">

    4

</div>

</div>

<div id="d34b31c4" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:00.361644Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:00.360427Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:00.378565Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:00.376026Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.6721e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.382586&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.345865&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Longest subarray with sum K - Brute optimized
def lcs_brute_optimized(arr_: list[int], k: int) -> int:
    "Time - O(N ^ 2)"
    N = len(arr_)
    max_ = 0
    for i in range(N):
        length = sum_ = 0
        for j in range(i, N):
            sum_ += arr_[j]
            length += 1
            if sum_ == k:
                max_ = max(max_, length)

    return max_

lcs_brute_optimized([1, 2, 3, 1, 1, 1, 1, 4, 2, 3], 4)
```

<div class="output execute_result" execution_count="20">

    4

</div>

</div>

<div id="9b1594f5" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:00.407997Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:00.406657Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:00.425947Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:00.423403Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.7263e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.430281&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.393018&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Longest subarray with sum K - Better
# This is the OPTIMAL when there are +ve, -ve and 0s
def lcs_better(arr_: list[int], k: int) -> int:
    "Time - O(N), Space - O(N)"
    N = len(arr_)
    hashmap = dict()
    max_ = sum_ = 0
    for i in range(N):
        sum_ += arr_[i]

        # Since we want the longest sum, we do not update 
        # the hashmap when a more recent index is found
        # Timestamp: 21.53
        if sum_ not in hashmap:
            hashmap[sum_] = i

        if sum_ == k:
            max_ = max(max_, i + 1)
        if sum_ - k in hashmap:
            max_ = max(max_, i - hashmap[sum_ - k])
    return max_

lcs_better([1, 2, 3, 1, 1, 1, 1, 4, 2, 3], 5)
```

<div class="output execute_result" execution_count="21">

    3

</div>

</div>

<div id="7c4a918e" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:00.455974Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:00.454762Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:00.474110Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:00.471708Z&quot;}"
papermill="{&quot;duration&quot;:3.7861e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:00.478793&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:00.440932&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Longest subarray with sum K - Optimal
# If arrays had only +ve and 0s we can do better
def lcs_optimial_only_positives(arr_: list[int], k: int) -> int:
    "Two pointer approach, Time - O(N), Space - O(1)"
    N = len(arr_)
    i, j = 0, -1
    sum_ = max_ = 0
    while j < N - 1:
        if sum_ <= k or i == j:
            j += 1
            sum_ += arr_[j]
        else:
            sum_ -= arr_[i]
            i += 1
        if sum_ == k:
            max_ = max(max_, j - i + 1)

    return max_

lcs_optimial_only_positives([1, 2, 3, 1, 1, 1, 1, 4, 2, 3], 5)
```

<div class="output execute_result" execution_count="22">

    3

</div>

</div>
