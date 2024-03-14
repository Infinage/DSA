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
    duration: 1.652101
    end_time: "2024-03-14T16:34:35.218280"
    environment_variables: {}
    input_path: study/striver-A2Z/08-hard-arrays.ipynb
    output_path: study/striver-A2Z/08-hard-arrays.ipynb
    parameters: {}
    start_time: "2024-03-14T16:34:33.566179"
    version: 2.5.0
---

<div id="2e76de23" class="cell markdown"
papermill="{&quot;duration&quot;:4.777e-3,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.726099&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.721322&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="95dd0243" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.736529Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.735816Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.745974Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.745332Z&quot;}"
papermill="{&quot;duration&quot;:1.7263e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.747728&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.730465&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.94e-3,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.756030&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.752090&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=vwZj1K0e9U8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=35>
Majority element, appearing \> floor(N / 3) times

</div>

<div id="e7bd2ff9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.765714Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.764987Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.771070Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.770297Z&quot;}"
papermill="{&quot;duration&quot;:1.2733e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.772799&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.760066&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.782300Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.781716Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.789671Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.788911Z&quot;}"
papermill="{&quot;duration&quot;:1.4443e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.791354&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.776911&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.061e-3,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.799657&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.795596&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=DhFh8Kw7ymk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=36>
3Sum - Triplets that sum up to 0

</div>

<div id="c12350c0" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.809398Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.808797Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.814419Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.813684Z&quot;}"
papermill="{&quot;duration&quot;:1.2338e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.816109&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.803771&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.826216Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.825623Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.833137Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.832407Z&quot;}"
papermill="{&quot;duration&quot;:1.4389e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.834845&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.820456&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.845697Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.845051Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.851003Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.850266Z&quot;}"
papermill="{&quot;duration&quot;:1.303e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.852701&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.839671&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.863302Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.862667Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.871262Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.870610Z&quot;}"
papermill="{&quot;duration&quot;:1.5615e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.872951&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.857336&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.448e-3,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.881922&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.877474&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=eD95WRfh81c&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=37>
Four sum

</div>

<div id="1a37c603" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.892533Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.891837Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.898244Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.897492Z&quot;}"
papermill="{&quot;duration&quot;:1.3384e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.899891&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.886507&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.911528Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.910930Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.917233Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.916460Z&quot;}"
papermill="{&quot;duration&quot;:1.3059e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.918819&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.905760&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.931670Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.931020Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.937833Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.937062Z&quot;}"
papermill="{&quot;duration&quot;:1.4025e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.939527&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.925502&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.709e-3,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.951024&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.946315&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=eZr-6p0B7ME&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=38>
Number of subarrays with sum xor K

</div>

<div id="4e41d8af" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.962434Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.961978Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.972274Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.971581Z&quot;}"
papermill="{&quot;duration&quot;:1.7566e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.973870&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.956304&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-14T16:34:34.986988Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-14T16:34:34.986394Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-14T16:34:34.993593Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-14T16:34:34.992855Z&quot;}"
papermill="{&quot;duration&quot;:1.4531e-2,&quot;end_time&quot;:&quot;2024-03-14T16:34:34.995183&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-14T16:34:34.980652&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
