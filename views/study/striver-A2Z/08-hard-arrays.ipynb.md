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
    duration: 2.212012
    end_time: "2024-03-18T03:05:18.608928"
    environment_variables: {}
    input_path: study/striver-A2Z/08-hard-arrays.ipynb
    output_path: study/striver-A2Z/08-hard-arrays.ipynb
    parameters: {}
    start_time: "2024-03-18T03:05:16.396916"
    version: 2.5.0
---

<div id="2e76de23" class="cell markdown"
papermill="{&quot;duration&quot;:8.668e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.558168&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.549500&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="95dd0243" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.575766Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.575228Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.584982Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.584365Z&quot;}"
papermill="{&quot;duration&quot;:2.0437e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.586688&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.566251&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.758e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.602368&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.594610&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=vwZj1K0e9U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=35>
Majority element, appearing \> floor(N / 3) times

</div>

<div id="e7bd2ff9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.619397Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.618800Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.624497Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.623765Z&quot;}"
papermill="{&quot;duration&quot;:1.5975e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.626203&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.610228&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.643510Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.642895Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.650853Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.650094Z&quot;}"
papermill="{&quot;duration&quot;:1.828e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.652437&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.634157&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.891e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.668396&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.660505&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=DhFh8Kw7ymk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=36>
3Sum - Triplets that sum up to 0

</div>

<div id="c12350c0" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.686401Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.685816Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.691333Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.690612Z&quot;}"
papermill="{&quot;duration&quot;:1.6292e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.693100&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.676808&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.710593Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.710013Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.717392Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.716668Z&quot;}"
papermill="{&quot;duration&quot;:1.7844e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.719049&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.701205&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.736752Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.736157Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.742332Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.741588Z&quot;}"
papermill="{&quot;duration&quot;:1.6779e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.743974&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.727195&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.762137Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.761516Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.770106Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.769406Z&quot;}"
papermill="{&quot;duration&quot;:1.9344e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.771732&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.752388&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.41e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.789023&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.780613&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=eD95WRfh81c&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=37>
Four sum

</div>

<div id="1a37c603" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.807266Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.806643Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.813325Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.812684Z&quot;}"
papermill="{&quot;duration&quot;:1.765e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.815002&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.797352&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.834348Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.833893Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.840563Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.839719Z&quot;}"
papermill="{&quot;duration&quot;:1.7485e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.842140&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.824655&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.860554Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.859951Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.866854Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.866097Z&quot;}"
papermill="{&quot;duration&quot;:1.7748e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.868520&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.850772&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.448e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.885421&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.876973&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=eZr-6p0B7ME&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=38>
Number of subarrays with sum xor K

</div>

<div id="4e41d8af" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.903572Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.903335Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.912900Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.912101Z&quot;}"
papermill="{&quot;duration&quot;:2.0422e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.914486&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.894064&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.933299Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.932707Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.939799Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.939029Z&quot;}"
papermill="{&quot;duration&quot;:1.8214e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.941472&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.923258&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.687e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.959059&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.950372&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=IexN60k62jo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=39>
Merge overlapping intervals

</div>

<div id="dacfc2ea" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:17.977807Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:17.977298Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:17.985657Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:17.984938Z&quot;}"
papermill="{&quot;duration&quot;:1.949e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:17.987313&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.967823&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.964e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.005321&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:17.996357&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=n7uwj04E0I4&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=41>
Merge two sorted arrays without extra space

</div>

<div id="2fd69784" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.024563Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.023871Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.032288Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.031561Z&quot;}"
papermill="{&quot;duration&quot;:1.9808e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.033988&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.014180&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.053372Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.052818Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.060087Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.059325Z&quot;}"
papermill="{&quot;duration&quot;:1.8638e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.061718&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.043080&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.081563Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.080940Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.091264Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.090528Z&quot;}"
papermill="{&quot;duration&quot;:2.1838e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.092890&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.071052&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.222e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.111689&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.102467&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2D0D8HE6uak&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=41>
Find the missing the repeating number

</div>

<div id="0e488ecb" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.131132Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.130895Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.137857Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.137076Z&quot;}"
papermill="{&quot;duration&quot;:1.856e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.139502&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.120942&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.489e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.158442&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.148953&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.178577Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.177985Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.185674Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.184989Z&quot;}"
papermill="{&quot;duration&quot;:1.9544e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.187395&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.167851&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.465e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.206565&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.197100&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.227170Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.226573Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.237033Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.236349Z&quot;}"
papermill="{&quot;duration&quot;:2.2456e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.238677&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.216221&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="56ac4d0b" class="cell markdown"
papermill="{&quot;duration&quot;:9.508e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.257824&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.248316&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=AseUmwVNaoY&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=42>
Count Inversions in an array

</div>

<div id="7a103651" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.278263Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.277734Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.283991Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.283227Z&quot;}"
papermill="{&quot;duration&quot;:1.8171e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.285603&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.267432&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force, Time - O(N^2), Space - O(1)
arr = [5, 3, 2, 4, 1]
N = len(arr)

count = 0
for i in range(N - 1):
    for j in range(i, N):
        if arr[i] > arr[j]:
            count += 1

count
```

<div class="output execute_result" execution_count="20">

    8

</div>

</div>

<div id="a56fd8e3" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.306609Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.306018Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.316248Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.315638Z&quot;}"
papermill="{&quot;duration&quot;:2.2485e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.317958&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.295473&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal, Time - O(N Log N), Space - O(N)
def countInversionPairs(arr: list[int]) -> int:
    """
    1. Sort the array using merge sort
    2. While merging, count the inversion pairs using O(m + n) algorithm
    """

    def mergeSort_(low: int, high: int) -> int:
        if low >= high:
            return 0
        else:
            mid = (low + high + 1) // 2
            left_count = mergeSort_(low, mid - 1)
            right_count = mergeSort_(mid, high)
            temp: list[int] = []
            count = 0
            i, j = low, mid
            while i < mid or j <= high:
                if (j > high) or (i < mid and arr[i] <= arr[j]):
                    temp.append(arr[i])
                    i += 1
                else:
                    temp.append(arr[j])
                    j += 1

                    # Each time we add from right, it means that all elements on the left are greater
                    # Increase count by len of elements on the left
                    count += mid - i

            # Copy from temp array to actual array
            arr[low: high + 1] = temp

            return count + left_count + right_count

    count = mergeSort_(0, len(arr) - 1)
    return count

assert countInversionPairs([5, 3, 2, 4, 1]) == 8
assert countInversionPairs([4, 3, 2, 1]) == 6
assert countInversionPairs([1, 20, 6, 4, 5]) == 5
assert countInversionPairs([15, 28, 11, 20, 14, 7, 14, 2, 15, 4, 22, 19, 17, 1, 26, 6, 20, 2, 6]) == 96
```

</div>

<div id="58d05c9c" class="cell markdown"
papermill="{&quot;duration&quot;:9.895e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.337942&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.328047&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=0e4bZaP3MDI&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=43>

</div>

<div id="95da4636" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.358880Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.358297Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.365036Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.364374Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8975e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.366715&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.347740&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force, Time - O(N^2), Space - O(1)
arr = [40, 25, 19, 12, 9, 6, 2]
N = len(arr)

count = 0
for i in range(N):
    for j in range(i + 1, N):
        if arr[i] > 2 * arr[j]:
            count += 1

count
```

<div class="output execute_result" execution_count="22">

    15

</div>

</div>

<div id="90b8bcd9" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.388059Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.387824Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.398770Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.397996Z&quot;}"
papermill="{&quot;duration&quot;:2.3472e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.400396&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.376924&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal, Time - O(N log N)
def countReversePairs(arr: list[int]) -> int:
    def merge_sort_(low: int, high: int) -> int:
        if low >= high:
            return 0
        else:
            mid = (low + high + 1) // 2
            left_count = merge_sort_(low, mid - 1)
            right_count = merge_sort_(mid, high)
            count = 0

            # Merge the arrays into a temp array
            temp: list[int] = []
            i, j = low, mid
            k = low # keep track of idx on left starting with arr[k] > 2 * arr[j]
            while i < mid or j <= high:
                if j > high or (i < mid and arr[i] <= arr[j]):
                   temp.append(arr[i])
                   i += 1
                else:
                    temp.append(arr[j])
                    j += 1

                    # Count the pairs
                    while k < mid and arr[k] <= 2 * arr[j - 1]:
                        k += 1

                    count += mid - k

            # Copy elements from temp into arr
            arr[low: high + 1] = temp

            return left_count + right_count + count

    count = merge_sort_(0, len(arr) - 1)
    return count

countReversePairs([40, 25, 19, 12, 9, 6, 2])
```

<div class="output execute_result" execution_count="23">

    15

</div>

</div>

<div id="1cdfb391" class="cell markdown"
papermill="{&quot;duration&quot;:1.0017e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.420712&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.410695&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=hnswaLJvr6g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>
Maximum product subarray

</div>

<div id="fbf22ac2" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.442586Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.442055Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.448759Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.447979Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9468e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.450512&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.431044&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Brute force, Time - O(N^2), Space - O(1)
arr = [2, 3, -2, 4]
N = len(arr)

max_ = -math.inf
for i in range(N):
    prod = 1
    for j in range(i, N):
        prod *= arr[j]
        if prod > max_:
            max_ = prod

max_
```

<div class="output execute_result" execution_count="24">

    6

</div>

</div>

<div id="114f1f9b" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:18.472696Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:18.472183Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:18.480185Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:18.479423Z&quot;}"
papermill="{&quot;duration&quot;:2.0879e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:18.481858&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:18.460979&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal
# When all +ve is simply prod of all nums
# When array contains negatives, result would need to exclude a single negative (either product of prefix or suffix)
# When array contains 0, we treat it as a demarcation point
class Solution:
    def maxProduct(self, nums: list[int]) -> int:
        N = len(nums)

        prefix, suffix, max_ = 1, 1, -math.inf
        for i in range(N):
            j = N - i - 1

            prefix *= nums[i]
            suffix *= nums[j]

            max_ = max(max_, prefix, suffix)

            if prefix == 0:
                prefix = 1

            if suffix == 0:
                suffix = 1

        return int(max_)

Solution().maxProduct([2, 3, -2, 0, 4])
```

<div class="output execute_result" execution_count="25">

    6

</div>

</div>
