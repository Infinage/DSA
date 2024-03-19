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
    duration: 1.392662
    end_time: "2024-03-19T03:03:35.107341"
    environment_variables: {}
    input_path: study/striver-A2Z/09-binary-search.ipynb
    output_path: study/striver-A2Z/09-binary-search.ipynb
    parameters: {}
    start_time: "2024-03-19T03:03:33.714679"
    version: 2.5.0
---

<div id="db5bf785" class="cell markdown"
papermill="{&quot;duration&quot;:2.329e-3,&quot;end_time&quot;:&quot;2024-03-19T03:03:34.916437&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-19T03:03:34.914108&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Some useful imports

</div>

<div id="671e1a3f" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-19T03:03:34.921739Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-19T03:03:34.921267Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-19T03:03:34.934691Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-19T03:03:34.934020Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8098e-2,&quot;end_time&quot;:&quot;2024-03-19T03:03:34.936429&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-19T03:03:34.918331&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import random
import functools
import itertools
import tqdm
import pdb
```

</div>

<div id="8fc657ea" class="cell markdown"
papermill="{&quot;duration&quot;:1.636e-3,&quot;end_time&quot;:&quot;2024-03-19T03:03:34.939768&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-19T03:03:34.938132&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=MHf6awe89xw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=45>

</div>

<div id="1f233f2d" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-19T03:03:34.944206Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-19T03:03:34.943860Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-19T03:03:34.948247Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-19T03:03:34.947481Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.504e-3,&quot;end_time&quot;:&quot;2024-03-19T03:03:34.949898&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-19T03:03:34.941394&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Linear search
def lsearch(arr: list[int], target: int) -> int:
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    else:
        return -1
```

</div>

<div id="ea84f278" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-19T03:03:34.954681Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-19T03:03:34.954139Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-19T03:03:34.968738Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-19T03:03:34.967954Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8884e-2,&quot;end_time&quot;:&quot;2024-03-19T03:03:34.970567&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-19T03:03:34.951683&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Iterative solution
def bsearch_iter(arr: list[int], target: int) -> int:
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == target:
            return mid
        elif target > arr[mid]:
            low = mid + 1
        else:
            high = mid - 1
    else:
        return -1

# Test the algorithm
for i in tqdm.tqdm(range(100)):
    temp = random.sample(list(range(15, 30)), random.randint(1, 15))
    temp.sort()
    j = random.randint(0, 45)
    assert bsearch_iter(temp, j) == lsearch(temp, j), f"failed for {temp}, {j}"
```

<div class="output stream stderr">

      0%|          | 0/100 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 100/100 [00:00<00:00, 63772.30it/s]

</div>

<div class="output stream stderr">

</div>

</div>

<div id="e4e7cc25" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-19T03:03:34.976114Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-19T03:03:34.975480Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-19T03:03:34.987301Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-19T03:03:34.986529Z&quot;}"
papermill="{&quot;duration&quot;:1.6301e-2,&quot;end_time&quot;:&quot;2024-03-19T03:03:34.988921&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-19T03:03:34.972620&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Recursive solution
def bsearch_rec(arr: list[int], target: int) -> int:
    def backtrack(low: int, high: int) -> int:
        if low > high:
            return -1
        else:
            mid = (low + high) // 2
            if arr[mid] == target:
                return mid
            elif target < arr[mid]:
                return backtrack(low, mid - 1)
            else:
                return backtrack(mid + 1, high)

    return backtrack(0, len(arr) - 1)

for i in tqdm.tqdm(range(100)):
    temp = random.sample(list(range(15, 30)), random.randint(1, 15))
    temp.sort()
    j = random.randint(0, 45)
    assert bsearch_rec(temp, j) == lsearch(temp, j), f"failed for {temp}, {j}"
```

<div class="output stream stderr">

      0%|          | 0/100 [00:00<?, ?it/s]

</div>

<div class="output stream stderr">

    100%|██████████| 100/100 [00:00<00:00, 41892.77it/s]

</div>

<div class="output stream stderr">

</div>

</div>
