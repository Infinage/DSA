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
    duration: 1.342778
    end_time: "2024-06-04T15:59:41.313332"
    environment_variables: {}
    input_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    output_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    parameters: {}
    start_time: "2024-06-04T15:59:39.970554"
    version: 2.6.0
---

<div id="b6671da9" class="cell markdown"
papermill="{&quot;duration&quot;:2.78e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.093858&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.091078&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="8fe92d24" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T15:59:41.099298Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T15:59:41.098901Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T15:59:41.104166Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T15:59:41.103659Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.09e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.105235&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.096145&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.452e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.109737&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.107285&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T15:59:41.115000Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T15:59:41.114597Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T15:59:41.118290Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T15:59:41.117858Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.497e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.119349&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.111852&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T15:59:41.124566Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T15:59:41.124139Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T15:59:41.129585Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T15:59:41.129150Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.133e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.130648&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.121515&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T15:59:41.135405Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T15:59:41.134983Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T15:59:41.140086Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T15:59:41.139676Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.609e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.141122&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.132513&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.804e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.144896&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.143092&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum points you can obtain from cards Video link:
<https://youtu.be/pBWCOCS636U?si=MrB1rbR3ScPbJGyB>

</div>

<div id="d6a9257f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T15:59:41.149672Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T15:59:41.149203Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T15:59:41.153392Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T15:59:41.152864Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.612e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.154380&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.146768&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.913e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.158121&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.156208&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest substring without repeating characters Video Link:
<https://youtu.be/-zSxTJkcdAo?si=OCzXyY4AuXSZz-eS>

</div>

<div id="688e574f" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T15:59:41.163597Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T15:59:41.163173Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T15:59:41.167223Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T15:59:41.166794Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.491e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.168244&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.160753&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="50bdca9c" class="cell markdown"
papermill="{&quot;duration&quot;:1.809e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.171945&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.170136&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Max consecutive ones III:
<https://leetcode.com/problems/max-consecutive-ones-iii/> Video Link:
<https://youtu.be/3E4JBHSLpYk?si=63rPPAESHHuPbIas>

</div>

<div id="b81ea511" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T15:59:41.176449Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T15:59:41.176183Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T15:59:41.181223Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T15:59:41.180817Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.492e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.182308&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.173816&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/max-consecutive-ones-iii/submissions/1277492942/
def longestOnes(nums: list[int], K: int) -> int:
    """
    Expand if zero_count <= k
    Else slide

    We can optimize this code a little more if we kept track of the first 0 within our window.
    Once zero_count > K, we can directly slide first_zero - i steps.
    """
    N, zero_count = len(nums), 1 if nums[0] == 0 else 0
    max_: int = 0
    i = j = 0
    while j < N:

        # Expand
        if zero_count <= K:
            max_ = max(max_, j - i + 1)
            j += 1
            if j < N and nums[j] == 0:
                zero_count += 1

        # Slide
        else:
            if nums[i] == 0:
                zero_count -= 1
            if j + 1 < N and nums[j + 1] == 0:
                zero_count += 1
            i, j = i + 1, j + 1

    return max_

# Testing the solution
assert longestOnes([1,1,1,0,0,0,1,1,1,1,0], 2) == 6
assert longestOnes([0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], 3) == 10
assert longestOnes([0,0,0,0], 3) == 3
```

</div>

<div id="ee79e853" class="cell markdown"
papermill="{&quot;duration&quot;:1.845e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.186081&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.184236&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Fruit into baskets: <https://leetcode.com/problems/fruit-into-baskets>
Video Link: <https://youtu.be/e3bs0uA1NhQ?si=6ii_zUURKMi_Wu4i> Striver
uses a different approach of counting by freq, they are of the same time
complexity

</div>

<div id="6d7b7c24" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-04T15:59:41.190679Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-04T15:59:41.190293Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-04T15:59:41.194997Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-04T15:59:41.194576Z&quot;}"
papermill="{&quot;duration&quot;:8.105e-3,&quot;end_time&quot;:&quot;2024-06-04T15:59:41.196023&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-04T15:59:41.187918&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/fruit-into-baskets/submissions/1277567029
def sumSubarrayMins(fruits: list[int]):
    # Time: O(N), Space: O(1)
    N = len(fruits)
    indices: dict[int, int] = dict()
    max_length = i = 0
    for j in range(N):
        indices[fruits[j]] = j
        if len(indices) < 3:
            max_length = max(max_length, j - i + 1)
        else:
            min_pair = (-1, N)

            # At most 3 items
            for k, v in indices.items():
                if v < min_pair[1]:
                    min_pair = (k, v)

            indices.pop(min_pair[0])
            i = min_pair[1] + 1

    return max_length

# Testing the solution
assert sumSubarrayMins([2,1,2]) == 3
assert sumSubarrayMins([0,1,2,2,2,2]) == 5
assert sumSubarrayMins([1,3,1,2,2,3,2]) == 4
```

</div>
