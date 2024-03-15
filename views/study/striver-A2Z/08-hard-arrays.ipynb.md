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
    duration: 1.711504
    end_time: "2024-03-15T02:24:18.267522"
    environment_variables: {}
    input_path: study/striver-A2Z/08-hard-arrays.ipynb
    output_path: study/striver-A2Z/08-hard-arrays.ipynb
    parameters: {}
    start_time: "2024-03-15T02:24:16.556018"
    version: 2.5.0
---

<div id="2e76de23" class="cell markdown"
papermill="{&quot;duration&quot;:5.894e-3,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.717850&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.711956&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="95dd0243" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.730099Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.729482Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.738925Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.738318Z&quot;}"
papermill="{&quot;duration&quot;:1.7314e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.740567&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.723253&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import random
import functools
import itertools
import pdb
```

</div>

<div id="d47b5eaa" class="cell markdown"
papermill="{&quot;duration&quot;:5.113e-3,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.750895&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.745782&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=vwZj1K0e9U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=35>
Majority element, appearing \> floor(N / 3) times

</div>

<div id="e7bd2ff9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.762576Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.761980Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.768176Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.767340Z&quot;}"
papermill="{&quot;duration&quot;:1.3679e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.769740&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.756061&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.781586Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.781033Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.789018Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.788373Z&quot;}"
papermill="{&quot;duration&quot;:1.5479e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.790543&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.775064&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.242e-3,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.801152&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.795910&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=DhFh8Kw7ymk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=36>
3Sum - Triplets that sum up to 0

</div>

<div id="c12350c0" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.813088Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.812485Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.818592Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.817777Z&quot;}"
papermill="{&quot;duration&quot;:1.3928e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.820306&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.806378&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.832653Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.832336Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.839822Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.839075Z&quot;}"
papermill="{&quot;duration&quot;:1.5617e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.841460&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.825843&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.853873Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.853644Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.859717Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.858874Z&quot;}"
papermill="{&quot;duration&quot;:1.4188e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.861359&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.847171&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.873855Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.873295Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.882356Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.881703Z&quot;}"
papermill="{&quot;duration&quot;:1.7094e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.884014&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.866920&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.554e-3,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.895277&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.889723&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=eD95WRfh81c&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=37>
Four sum

</div>

<div id="1a37c603" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.908079Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.907424Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.913478Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.912737Z&quot;}"
papermill="{&quot;duration&quot;:1.4143e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.915094&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.900951&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.929308Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.928723Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.935075Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.934443Z&quot;}"
papermill="{&quot;duration&quot;:1.4565e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.936767&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.922202&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.951175Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.950602Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.957544Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.956863Z&quot;}"
papermill="{&quot;duration&quot;:1.513e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.959141&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.944011&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="af7c5ce6" class="cell markdown"
papermill="{&quot;duration&quot;:5.92e-3,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.972271&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.966351&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=eZr-6p0B7ME&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=38>
Number of subarrays with sum xor K

</div>

<div id="4e41d8af" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:17.985060Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:17.984806Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:17.993918Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:17.993175Z&quot;}"
papermill="{&quot;duration&quot;:1.7459e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:17.995557&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:17.978098&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force - O(N^2)
arr = [4, 2, 2, 6, 4]
K = 6
N, count = len(arr), 0
for i in range(N):
    sum_ = 0
    for j in range(i, N):
        sum_ = sum_ ^ arr[j]
        if sum_ == K:
            count += 1

count
```

<div class="output execute_result" execution_count="11">

    4

</div>

</div>

<div id="b0399a91" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:18.009986Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:18.009375Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:18.016430Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:18.015670Z&quot;}"
papermill="{&quot;duration&quot;:1.5596e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:18.018182&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:18.002586&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal: Using prefix sum
# Time: O(N), Space: O(N)
arr = [4, 2, 2, 6, 4]
K = 6
N, count = len(arr), 0
dict_: dict[int, int] = {0: 1}
sum_ = 0
for i in range(N):
    sum_ = sum_ ^ arr[i]
    if K ^ sum_ in dict_:
        count += dict_[K ^ sum_]
    dict_[sum_] = dict_.get(sum_, 0) + 1

count
```

<div class="output execute_result" execution_count="12">

    4

</div>

</div>

<div id="4fb45d7f" class="cell markdown"
papermill="{&quot;duration&quot;:6.051e-3,&quot;end_time&quot;:&quot;2024-03-15T02:24:18.032184&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:18.026133&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=IexN60k62jo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=39>
Merge overlapping intervals

</div>

<div id="dacfc2ea" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:18.045536Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:18.045025Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:18.053316Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:18.052589Z&quot;}"
papermill="{&quot;duration&quot;:1.6879e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:18.055088&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:18.038209&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal force - O(N log N) + O(N)
arr: list[tuple[int, int]] = [(1, 3), (2, 6), (8, 9), (9, 11), (8, 10), (2, 4), (15, 18), (16, 17)]
arr.sort(key=lambda x: x[0])
result: list[tuple[int, int]] = []
for i, j in arr:
    while len(result) > 0 and result[-1][1] >= i:
        prev = result.pop()
        i = min(prev[0], i)
        j = max(prev[1], j)
    result.append((i, j))

result
```

<div class="output execute_result" execution_count="13">

    [(1, 6), (8, 11), (15, 18)]

</div>

</div>

<div id="10c671b2" class="cell markdown"
papermill="{&quot;duration&quot;:6.369e-3,&quot;end_time&quot;:&quot;2024-03-15T02:24:18.069721&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:18.063352&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=n7uwj04E0I4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=41>
Merge two sorted arrays without extra space

</div>

<div id="2fd69784" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:18.085001Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:18.084403Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:18.093088Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:18.092401Z&quot;}"
papermill="{&quot;duration&quot;:1.7503e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:18.094731&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:18.077228&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force, extra O(M) space
arr1 = [1, 3, 5, 7]
arr2 = [0, 2, 6, 8, 9]
N1, N2 = len(arr1), len(arr2)

# Allocate extra space
for i in range(N2):
    arr1.append(None)

# Merge arrays
i, j, k = N1 - 1, N2 - 1, N1 + N2 - 1
while i >= 0 or j >= 0:
    if j < 0 or (i >= 0 and arr1[i] >= arr2[j]):
        arr1[k] = arr1[i]
        k, i = k - 1, i - 1
    else:
        arr1[k] = arr2[j]
        k, j = k - 1, j - 1

arr1
```

<div class="output execute_result" execution_count="14">

    [0, 1, 2, 3, 5, 6, 7, 8, 9]

</div>

</div>

<div id="f72f3592" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:18.110302Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:18.109694Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:18.116998Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:18.116237Z&quot;}"
papermill="{&quot;duration&quot;:1.6261e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:18.118651&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:18.102390&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal 1
arr1 = [1, 3, 5, 7]
arr2 = [0, 2, 6, 8, 9]
N1, N2 = len(arr1), len(arr2)

# Merge arrays
i, j = N1 - 1, 0
while arr1[i] > arr2[j]:
    arr1[i], arr2[j] = arr2[j], arr1[i]
    i, j = i - 1, j + 1

arr1.sort()
arr2.sort()
arr1 + arr2
```

<div class="output execute_result" execution_count="15">

    [0, 1, 2, 3, 5, 6, 7, 8, 9]

</div>

</div>

<div id="f567f80c" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-15T02:24:18.133330Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-15T02:24:18.132992Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-15T02:24:18.142670Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-15T02:24:18.141909Z&quot;}"
papermill="{&quot;duration&quot;:1.9004e-2,&quot;end_time&quot;:&quot;2024-03-15T02:24:18.144412&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-15T02:24:18.125408&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal 2, shell sort
arr1 = [1, 3, 5, 7, 10]
arr2 = [0, 2, 6, 8, 9]
N1, N2 = len(arr1), len(arr2)

gap = math.ceil((N1 + N2) / 2)
while gap > 0:
    left, right = 0, gap
    while right < N1 + N2:
        # arr1, arr2
        if left < N1 and right >= N1:
            l, r = left, right - N1
            a1, a2 = arr1, arr2
        # arr1, arr1
        elif right < N1:
            l, r = left, right
            a1, a2 = arr1, arr1
        # arr2, arr2
        else:
            l, r = left - N1, right - N1
            a1, a2 = arr2, arr2

        if a1[l] > a2[r]:
            a1[l], a2[r] = a2[r], a1[l]
        left, right = left + 1, right + 1

    if gap == 1:
        break
    gap = math.ceil(gap / 2)

arr1 + arr2
```

<div class="output execute_result" execution_count="16">

    [0, 1, 2, 3, 5, 6, 7, 8, 9, 10]

</div>

</div>
