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
    duration: 1.887753
    end_time: "2024-03-16T14:33:42.517073"
    environment_variables: {}
    input_path: study/striver-A2Z/08-hard-arrays.ipynb
    output_path: study/striver-A2Z/08-hard-arrays.ipynb
    parameters: {}
    start_time: "2024-03-16T14:33:40.629320"
    version: 2.5.0
---

<div id="2e76de23" class="cell markdown"
papermill="{&quot;duration&quot;:7.192e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.795338&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.788146&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="95dd0243" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:41.809594Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:41.809292Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:41.819082Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:41.818455Z&quot;}"
papermill="{&quot;duration&quot;:1.9019e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.820791&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.801772&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.104e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.833093&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.826989&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=vwZj1K0e9U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=35>
Majority element, appearing \> floor(N / 3) times

</div>

<div id="e7bd2ff9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:41.846519Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:41.846032Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:41.851797Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:41.851000Z&quot;}"
papermill="{&quot;duration&quot;:1.4291e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.853450&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.839159&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:41.867382Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:41.866823Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:41.874899Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:41.874165Z&quot;}"
papermill="{&quot;duration&quot;:1.6752e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.876520&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.859768&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.344e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.889228&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.882884&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=DhFh8Kw7ymk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=36>
3Sum - Triplets that sum up to 0

</div>

<div id="c12350c0" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:41.903390Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:41.902808Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:41.908641Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:41.907842Z&quot;}"
papermill="{&quot;duration&quot;:1.4677e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.910209&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.895532&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:41.924949Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:41.924365Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:41.931888Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:41.931163Z&quot;}"
papermill="{&quot;duration&quot;:1.6629e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.933490&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.916861&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:41.948049Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:41.947495Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:41.953154Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:41.952426Z&quot;}"
papermill="{&quot;duration&quot;:1.4713e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.954708&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.939995&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:41.969650Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:41.969028Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:41.977459Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:41.976703Z&quot;}"
papermill="{&quot;duration&quot;:1.7468e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.979007&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.961539&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.923e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:41.992788&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.985865&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=eD95WRfh81c&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=37>
Four sum

</div>

<div id="1a37c603" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.007861Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.007249Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.013344Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.012616Z&quot;}"
papermill="{&quot;duration&quot;:1.5302e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.014895&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:41.999593&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.031271Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.030866Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.037184Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.036396Z&quot;}"
papermill="{&quot;duration&quot;:1.5796e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.038943&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.023147&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.055266Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.054779Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.061554Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.060764Z&quot;}"
papermill="{&quot;duration&quot;:1.62e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.063354&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.047154&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.398e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.079632&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.072234&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=eZr-6p0B7ME&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=38>
Number of subarrays with sum xor K

</div>

<div id="4e41d8af" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.095233Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.094568Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.104550Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.103862Z&quot;}"
papermill="{&quot;duration&quot;:1.9444e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.106140&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.086696&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.122751Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.122238Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.129307Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.128522Z&quot;}"
papermill="{&quot;duration&quot;:1.6625e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.130934&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.114309&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.07e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.146185&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.139115&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=IexN60k62jo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=39>
Merge overlapping intervals

</div>

<div id="dacfc2ea" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.162147Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.161449Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.170654Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.170022Z&quot;}"
papermill="{&quot;duration&quot;:1.891e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.172300&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.153390&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.222e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.186759&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.179537&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=n7uwj04E0I4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=41>
Merge two sorted arrays without extra space

</div>

<div id="2fd69784" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.202586Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.202051Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.210404Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.209702Z&quot;}"
papermill="{&quot;duration&quot;:1.8146e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.212110&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.193964&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.228315Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.227819Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.235508Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.234737Z&quot;}"
papermill="{&quot;duration&quot;:1.7557e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.237152&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.219595&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.253883Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.253289Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.263159Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.262461Z&quot;}"
papermill="{&quot;duration&quot;:1.9871e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.264802&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.244931&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="520fb0ad" class="cell markdown"
papermill="{&quot;duration&quot;:7.653e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.280096&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.272443&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2D0D8HE6uak&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=41>
Find the missing the repeating number

</div>

<div id="0e488ecb" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.296833Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.296140Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.303307Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.302621Z&quot;}"
papermill="{&quot;duration&quot;:1.733e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.305020&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.287690&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute Force, Space - O(n), Time - O(1)
arr = [4, 3, 6, 2, 1, 1]
N = len(arr)

set_: set[int] = set()
sum_ = 0
for i in arr:
    if i not in set_:
        sum_ += i
        set_.add(i)
    else:
        j = i

# Repeat, Missing
j, ((N * (N + 1)) / 2) - sum_
```

<div class="output execute_result" execution_count="17">

    (1, 5.0)

</div>

</div>

<div id="9fcff761" class="cell markdown"
papermill="{&quot;duration&quot;:7.832e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.320862&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.313030&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Mathematical approach:

      First Equation:
      sum_of_array_elements - sum_of_N_natural_numbers = repeat - missing

      Second Equation:
      sum_of_squares_of_array_elements - sum_of_squares_of_N_Natural_numbers = (repeat^2 - missing^2)
      => (repeat - missing)(repeat + missing)

      => repeat = ((eq2 / eq1) + eq1) / 2
      => missing = repeat - eq1

</div>

<div id="79447097" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.337878Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.337362Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.344723Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.343917Z&quot;}"
papermill="{&quot;duration&quot;:1.7652e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.346371&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.328719&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal - 1
arr = [4, 3, 6, 2, 1, 1]
N = len(arr)

expected_sum, expected_sum_of_squares = 0, 0
for i in range(1, N + 1):
    expected_sum += i
    expected_sum_of_squares += i * i

sum_, sum_of_squares = 0, 0
for i in arr:
    sum_ += i
    sum_of_squares += i * i

eq1 = sum_ - expected_sum
eq2 = sum_of_squares - expected_sum_of_squares

repeat = ((eq2 / eq1) + eq1) / 2
repeat, repeat - eq1
```

<div class="output execute_result" execution_count="18">

    (1.0, 5.0)

</div>

</div>

<div id="558572e0" class="cell markdown"
papermill="{&quot;duration&quot;:8.16e-3,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.362739&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.354579&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

XOR method

1.  XOR all nums and xor with numbers from 1 to N, result = repeat ^
    missing
2.  Find right most differentiating bit from prev result
3.  Iterate through 1 to N and all elements in arr, XORing them and
    group them based on the differenting bit
4.  Since the repeat, missing comes up odd number of times - one of the
    group result would be repeat and the other missing
5.  Iterate through array and verify which is which

</div>

<div id="3e5b861f" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-16T14:33:42.380682Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-16T14:33:42.380069Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-16T14:33:42.390473Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-16T14:33:42.389718Z&quot;}"
papermill="{&quot;duration&quot;:2.1259e-2,&quot;end_time&quot;:&quot;2024-03-16T14:33:42.392059&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-16T14:33:42.370800&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
arr = [4, 3, 6, 2, 1, 1]
N = len(arr)

xr = 0
for i in arr:
    xr ^= i
for i in range(1, N + 1):
    xr ^= i

# This can be replaced by using the left shift / right shift operators
xr_bin = bin(xr)[2:]
diff_bit_pos = len(xr_bin) - xr_bin.rfind('1')

diff_bit_0, diff_bit_1 = 0, 0
for i in arr:
    curr = bin(i)
    if len(curr) < diff_bit_pos or curr[-diff_bit_pos] == '0':
        diff_bit_0 ^= i
    else:
        diff_bit_1 ^= i
for i in range(1, N + 1):
    curr = bin(i)
    if len(curr) < diff_bit_pos or curr[-diff_bit_pos] == '0':
        diff_bit_0 ^= i
    else:
        diff_bit_1 ^= i

for i in arr:
    if i == diff_bit_0:
        missing = diff_bit_1
        repeat = diff_bit_0
        break
    elif i == diff_bit_1:
        missing = diff_bit_0
        repeat = diff_bit_1
        break

repeat, missing
```

<div class="output execute_result" execution_count="19">

    (1, 5)

</div>

</div>
