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
    duration: 1.508985
    end_time: "2024-03-13T04:05:01.468577"
    environment_variables: {}
    input_path: study/striver-A2Z/08-hard-arrays.ipynb
    output_path: study/striver-A2Z/08-hard-arrays.ipynb
    parameters: {}
    start_time: "2024-03-13T04:04:59.959592"
    version: 2.5.0
---

<div id="2e76de23" class="cell markdown"
papermill="{&quot;duration&quot;:3.853e-3,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.160674&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.156821&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="95dd0243" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.169206Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.168508Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.178422Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.177694Z&quot;}"
papermill="{&quot;duration&quot;:1.5822e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.180189&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.164367&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import random
import functools
import itertools
```

</div>

<div id="d47b5eaa" class="cell markdown"
papermill="{&quot;duration&quot;:2.957e-3,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.186188&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.183231&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=vwZj1K0e9U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=35>
Majority element, appearing \> floor(N / 3) times

</div>

<div id="e7bd2ff9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.193365Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.192853Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.199019Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.198215Z&quot;}"
papermill="{&quot;duration&quot;:1.1559e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.200707&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.189148&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force
arr: list[int] = [1, 1, 1, 3, 3, 2, 2, 2]
N = len(arr)
counter: dict[int, int] = dict()
for n in arr:
    counter[n] = counter.get(n, 0) + 1

for k, v, in counter.items():
    if v > math.floor(N / 3):
        print(k)
```

<div class="output stream stdout">

    1
    2

</div>

</div>

<div id="180dfe25" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.208563Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.207927Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.216189Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.215536Z&quot;}"
papermill="{&quot;duration&quot;:1.3859e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.217817&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.203958&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal solution
arr: list[int] = [1, 2, 1, 2, 1, 2, 3, 3]
N = len(arr)
cnt1, el1, cnt2, el2 = 0, None, 0, None
# Run Moore's voting algorithm
for i in range(N):
    if cnt1 == 0 and el2 != arr[i]:
        cnt1, el1 = 1, arr[i]
    elif cnt2 == 0 and el1 != arr[i]:
        cnt2, el2 = 1, arr[i]
    elif el1 == arr[i]:
        cnt1 += 1
    elif el2 == arr[i]:
        cnt2 += 1
    else:
        cnt1 -= 1
        cnt2 -= 1

# Verify if el1 and el2 are indeed the majority elements
cnt1 = cnt2 = 0
for i in range(N):
    if arr[i] == el1:
        cnt1 += 1
    elif arr[i] == el2:
        cnt2 += 1

if cnt1 > math.floor(N / 3):
    print(el1)
if cnt2 > math.floor(N / 3):
    print(el2)
```

<div class="output stream stdout">

    1
    2

</div>

</div>

<div id="133b6f15" class="cell markdown"
papermill="{&quot;duration&quot;:3.132e-3,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.224247&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.221115&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=DhFh8Kw7ymk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=36>
3Sum - Triplets that sum up to 0

</div>

<div id="c12350c0" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.231919Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.231401Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.237460Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.236631Z&quot;}"
papermill="{&quot;duration&quot;:1.1614e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.239042&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.227428&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force - O(N^3)
arr = [-1, 0, 1, 2, -1, -4]
N = len(arr)
for i in range(N - 2):
    for j in range(i + 1, N - 1):
        for k in range(j + 1, N):
            if arr[i] + arr[j] + arr[k] == 0:
                print(arr[i], arr[j], arr[k])
```

<div class="output stream stdout">

    -1 0 1
    -1 2 -1
    0 1 -1

</div>

</div>

<div id="d624981c" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.247210Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.246613Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.254375Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.253724Z&quot;}"
papermill="{&quot;duration&quot;:1.3623e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.256025&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.242402&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better - O(N^2), Space - O(N)
arr = [-1, 0, 1, 2, -1, -4]
N = len(arr)
indices: dict[int, list[int]] = dict()
for i, n in enumerate(arr):
    curr = indices.get(n, [])
    curr.append(i)
    indices[n] = curr

for i in range(N - 1):
    for j in range(i + 1, N - 2):
        curr = indices.get(0 - (arr[i] + arr[j]), [])
        k = -1
        while -k <= len(curr) and curr[k] > j:
            if arr[i] + arr[j] + arr[curr[k]] == 0:
                print(arr[i], arr[j], arr[curr[k]])
            k -= 1
```

<div class="output stream stdout">

    -1 0 1
    -1 2 -1
    0 1 -1

</div>

</div>

<div id="c8d6774b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.264435Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.263888Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.269561Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.268784Z&quot;}"
papermill="{&quot;duration&quot;:1.1742e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.271339&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.259597&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better (Much Neater) solution - O(N^2), Space - O(N)
arr = [-1, 0, 1, 2, -1, -4]
N = len(arr)
for i in range(N - 1):
    set_: set[int] = set()
    for j in range(i + 1, N):
        k = -(arr[i] + arr[j])
        if k in set_:
            print(arr[i], arr[j], k)
        set_.add(arr[j])
```

<div class="output stream stdout">

    -1 1 0
    -1 -1 2
    0 -1 1

</div>

</div>

<div id="f832a851" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.280499Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.279899Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.288579Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.287838Z&quot;}"
papermill="{&quot;duration&quot;:1.5037e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.290137&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.275100&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal - O(N^2), Space - O(1)
# Code below returns only distinct triplets.
# If non distinct are allowed, simply inc, inc, dec - i, j, k by 1 instead of the while loop below
arr = [-1, 0, 1, 2, -1, -4]
N = len(arr)

arr.sort()
i = 0
while i < N - 2:
    j, k = i + 1, N - 1
    while j < k:
        curr_sum = arr[i] + arr[j] + arr[k]
        if curr_sum == 0:
            print(arr[i], arr[j], arr[k])
            j_, k_ = j, k
            while j_ < k_ and arr[j_] == arr[j] and arr[k_] == arr[k]:
                j_, k_ = j_ + 1, k_ - 1
            j, k = j_, k_

        elif curr_sum < 0:
            j_ = j
            while j_ < k and arr[j_] == arr[j]:
                j_ += 1
            j = j_

        else:
            k_ = k
            while k_ > j and arr[k_] == arr[k]:
                k_ -= 1
            k = k_

    i_ = i
    while i_ < N and arr[i_] == arr[i]:
        i_ += 1
    i = i_
```

<div class="output stream stdout">

    -1 -1 2
    -1 0 1

</div>

</div>

<div id="472fd6df" class="cell markdown"
papermill="{&quot;duration&quot;:3.784e-3,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.297784&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.294000&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=eD95WRfh81c&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=37>
Four sum

</div>

<div id="1a37c603" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.306861Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.306234Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.312266Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.311504Z&quot;}"
papermill="{&quot;duration&quot;:1.23e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.313815&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.301515&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force - O(N^4)
arr = [1, 0, -1, 0, -2, 2]
N = len(arr)
for i in range(N - 3):
    for j in range(i + 1, N - 2):
        for k in range(j + 1, N - 1):
            for l in range(k + 1, N):
                if (arr[i] + arr[j] + arr[k] + arr[l]) == 0:
                    print(arr[i], arr[j], arr[k], arr[l])
```

<div class="output stream stdout">

    1 0 -1 0
    1 -1 -2 2
    0 0 -2 2

</div>

</div>

<div id="013df8c7" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.323071Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.322482Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.328684Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.327960Z&quot;}"
papermill="{&quot;duration&quot;:1.2339e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.330223&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.317884&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better - O(N^3), Space - O(1)
arr = [1, 0, -1, 0, -2, 2]
N = len(arr)
for i in range(N - 2):
    for j in range(i + 1, N - 1):
        set_: set[int] = set()
        for k in range(j + 1, N):
                curr_sum = arr[i] + arr[j] + arr[k]
                if -curr_sum in set_:
                    print(arr[i], arr[j], arr[k], -curr_sum)
                set_.add(arr[k])
```

<div class="output stream stdout">

    1 0 0 -1
    1 -1 2 -2
    0 0 2 -2

</div>

</div>

<div id="2f4988ff" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-13T04:05:01.339683Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-13T04:05:01.339135Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-13T04:05:01.346019Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-13T04:05:01.345283Z&quot;}"
papermill="{&quot;duration&quot;:1.3385e-2,&quot;end_time&quot;:&quot;2024-03-13T04:05:01.347701&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-13T04:05:01.334316&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal - O(N^3), Space - O(1)
# As noted above, this would print all quartets including non distinct ones
# If only distinct ones are required, inc, dec variables until a different value is found
arr = [1, 0, -1, 0, -2, 2]
N = len(arr)
arr.sort()
for i in range(N - 3):
    for j in range(i + 1, N - 2):
        k, l = j + 1, N - 1
        while k < l:
            curr = arr[i], arr[j], arr[k], arr[l]
            if sum(curr) == 0:
                print(', '.join(map(str, curr)))
                k += 1
                l -= 1
            elif sum(curr) < 0:
                k += 1
            else:
                l -= 1
```

<div class="output stream stdout">

    -2, -1, 1, 2
    -2, 0, 0, 2
    -1, 0, 0, 1

</div>

</div>
