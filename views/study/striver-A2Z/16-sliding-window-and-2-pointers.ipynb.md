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
    duration: 1.322759
    end_time: "2024-06-04T13:57:02.518653"
    environment_variables: {}
    input_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    output_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    parameters: {}
    start_time: "2024-06-04T13:57:01.195894"
    version: 2.6.0
---

<div id="b6671da9" class="cell markdown"
papermill="{&quot;duration&quot;:2.331e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.335369&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.333038&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="8fe92d24" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T13:57:02.340395Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T13:57:02.339927Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T13:57:02.345329Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T13:57:02.344807Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.101e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.346417&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.337316&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.683e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.349738&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.348055&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Sliding window and 2 pointers

Video Link: <https://youtu.be/9kdHxplyl5I?si=YRjMqeBd1hIsB-Pt> Types of
problems:

1.  Constant window
2.  Longest subarray with condition
    - Expand happens for the right side of the window
    - Shrink happens for the left side of the window
3.  No of subarrays with condition
    - For eg: Num of subarrays with sum equals K =\> No of subarrays
      with sum \<= K - No of subarrays with sum \<= K - 1
4.  Shortest / minimum window with condition
    - Find a valid window, shrink until window remains valid

</div>

<div id="6ef36636" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T13:57:02.353887Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T13:57:02.353561Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T13:57:02.357295Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T13:57:02.356793Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.992e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.358356&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.351364&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T13:57:02.362659Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T13:57:02.362290Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T13:57:02.367531Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T13:57:02.367071Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.578e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.368607&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.360029&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Category 2: Longest subarray with sum <= K
def longestSubarrayBetter(arr: list[int], K: int):
    """
    If valid, we try to expand
    Else we try to shrink
    This is the valid solution if we are especially asked to find and print the subarray

    Time: O(2N), Space: O(1)
    """
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T13:57:02.372997Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T13:57:02.372512Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T13:57:02.377723Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T13:57:02.377323Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.53e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.378763&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.370233&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def longestSubarrayOptimal(arr: list[int], K: int):
    """
    The code is the same as above with 1 optimization.
    Since we are asked to find just the length, we don't have to shrink the array beyond the max length already obtained.
    Shrink until we have reached the max window size and then slide it forward.

    Time: O(N), Space: O(1)
    """
    N = len(arr)
    max_, sum_, i, j = 0, float(arr[0]), 0, 0
    while j < N and i < N:

        # Expand
        if sum_ <= K:
            max_ = max(max_, j - i + 1)
            sum_, j = sum_ + (arr[j + 1] if j + 1 < N else math.inf), j + 1

        # Slide
        else:
            sum_, i, j = sum_ - arr[i] + (arr[j + 1] if j + 1 < N else math.inf), i + 1, j + 1

    return max_

# Testing the solution
assert longestSubarrayOptimal([2,5,1,7,10], 14) == 3
assert longestSubarrayOptimal([2,5,1,7,10], 1) == 1
assert longestSubarrayOptimal([2,5,1,7,10], 0) == 0
assert longestSubarrayOptimal([7,10,0], 0) == 1
```

</div>

<div id="cf69814c" class="cell markdown"
papermill="{&quot;duration&quot;:1.529e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.381989&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.380460&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum points you can obtain from cards Video link:
<https://youtu.be/pBWCOCS636U?si=MrB1rbR3ScPbJGyB>

</div>

<div id="d6a9257f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T13:57:02.385781Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T13:57:02.385385Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T13:57:02.389502Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T13:57:02.389079Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.208e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.390596&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.383388&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/submissions/1276966170
def maxScore(cardPoints: list[int], K: int) -> int:
    N: int = len(cardPoints)
    max_ = sum_ = sum(cardPoints[-K:])
    for i in range(K):
        sum_ = sum_ - cardPoints[N + i - K] + cardPoints[i]
        max_ = max(max_, sum_)

    return max_

# Testing the solution
assert maxScore([1,2,3,4,5,6,1], 3) == 12
assert maxScore([1,2,3,4,5,6,1], 2) == 7
assert maxScore([2,2,2], 2) == 4
assert maxScore([9,7,7,9,7,7,9], 7) == 55
```

</div>

<div id="0d36216d" class="cell markdown"
papermill="{&quot;duration&quot;:1.423e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.393497&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.392074&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest substring without repeating characters Video Link:
<https://youtu.be/-zSxTJkcdAo?si=OCzXyY4AuXSZz-eS>

</div>

<div id="688e574f" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T13:57:02.397401Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T13:57:02.397004Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T13:57:02.401056Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T13:57:02.400589Z&quot;}"
lines_to_next_cell="2"
papermill="{&quot;duration&quot;:7.199e-3,&quot;end_time&quot;:&quot;2024-06-04T13:57:02.402103&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T13:57:02.394904&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/1277421731
def lengthOfLongestSubstring(s: str) -> int:
    N, max_, i = len(s), 0, 0
    indices: dict[str, int] = {}
    for j in range(N):
        idx, indices[s[j]] = indices.get(s[j], -1), j
        if idx < i:
            max_ = max(max_, j - i + 1)
        else:
            i = idx + 1

    return max_

# Testing the solution
assert lengthOfLongestSubstring("abcabcbb") == 3
assert lengthOfLongestSubstring("pwwkew") == 3
assert lengthOfLongestSubstring("aaqasdcdaq") == 5
```

</div>
