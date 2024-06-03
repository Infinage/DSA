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
    version: 3.11.9
  nbformat: 4
  nbformat_minor: 5
  papermill:
    default_parameters: {}
    duration: 1.315501
    end_time: "2024-06-03T16:49:40.938938"
    environment_variables: {}
    input_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    output_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    parameters: {}
    start_time: "2024-06-03T16:49:39.623437"
    version: 2.6.0
---

<div id="b6671da9" class="cell markdown"
papermill="{&quot;duration&quot;:1.713e-3,&quot;end_time&quot;:&quot;2024-06-03T16:49:40.787303&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-03T16:49:40.785590&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="8fe92d24" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-03T16:49:40.790885Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-03T16:49:40.790354Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-03T16:49:40.795585Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-03T16:49:40.795186Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.256e-3,&quot;end_time&quot;:&quot;2024-06-03T16:49:40.796711&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-03T16:49:40.788455&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import bisect
import collections
import itertools
import functools
```

</div>

<div id="d85c2eae" class="cell markdown"
papermill="{&quot;duration&quot;:8.97e-4,&quot;end_time&quot;:&quot;2024-06-03T16:49:40.798576&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-03T16:49:40.797679&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Sliding window and 2 pointers

Video Link: <https://youtu.be/9kdHxplyl5I?si=YRjMqeBd1hIsB-Pt> Types of
problems:

1.  Constant window
2.  Longest subarray with condition
    - Expand happens for the right side of the window
    - Shrink happens for the left side of the window
3.  No of subarrays with condition
4.  Shortest / minimum window with condition

</div>

<div id="6ef36636" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-03T16:49:40.801545Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-03T16:49:40.801121Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-03T16:49:40.805243Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-03T16:49:40.804751Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.762e-3,&quot;end_time&quot;:&quot;2024-06-03T16:49:40.806304&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-03T16:49:40.799542&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Category 1: Maximum sum subarray of k elements
def maxSumSubarray(arr: list[int], K: int) -> int:
    # Time: O(N), Space: O(1)
    N = len(arr)
    max_ = sum_ = sum(arr[:K])
    for j in range(K, N):
        i = j - K
        sum_  = sum_ - arr[i] + arr[j]
        max_ = max(max_, sum_)

    return max_

# Testing the solution
assert maxSumSubarray([-1,2,3,3,4,5,-1], 4) == 15
```

</div>

<div id="814183d5" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-03T16:49:40.809031Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-03T16:49:40.808858Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-03T16:49:40.813883Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-03T16:49:40.813454Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.658e-3,&quot;end_time&quot;:&quot;2024-06-03T16:49:40.814922&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-03T16:49:40.807264&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Category 2: Longest subarray with sum <= K
def longestSubarrayBetter(arr: list[int], K: int):
    N = len(arr)
    max_, sum_, i, j = 0, float(arr[0]), 0, 0
    while j < N and i < N:

        # Expand
        if sum_ <= K:
            max_ = max(max_, j - i + 1)
            sum_, j = sum_ + (arr[j + 1] if j + 1 < N else math.inf), j + 1

        # Shrink
        else:
            sum_, i = sum_ - arr[i], i + 1
            if i > j and i < N:
                sum_, j = arr[i], i

    return max_

# Testing the solution
assert longestSubarrayBetter([2,5,1,7,10], 14) == 3
assert longestSubarrayBetter([2,5,1,7,10], 1) == 1
assert longestSubarrayBetter([2,5,1,7,10], 0) == 0
assert longestSubarrayBetter([7,10,0], 0) == 1
```

</div>

<div id="171f3929" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-03T16:49:40.817600Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-03T16:49:40.817439Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-03T16:49:40.821926Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-03T16:49:40.821401Z&quot;}"
papermill="{&quot;duration&quot;:7.012e-3,&quot;end_time&quot;:&quot;2024-06-03T16:49:40.822914&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-03T16:49:40.815902&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def longestSubarrayOptimal(arr: list[int], K: int):
    N = len(arr)
    max_ = sum_ = i = j = 0
    while j < N:
        sum_ = sum_ + arr[j]
        if sum_ > K:
            sum_, i = sum_ - arr[i], i + 1
        else:
            max_ = max(max_, j - i + 1)
        j += 1

    return max_

# Testing the solution
assert longestSubarrayOptimal([2,5,1,7,10], 14) == 3
assert longestSubarrayOptimal([2,5,1,7,10], 1) == 1
assert longestSubarrayOptimal([2,5,1,7,10], 0) == 0
assert longestSubarrayOptimal([7,10,0], 0) == 1
```

</div>
