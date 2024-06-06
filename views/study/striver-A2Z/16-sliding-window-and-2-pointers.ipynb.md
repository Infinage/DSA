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
    duration: 1.496647
    end_time: "2024-06-06T17:02:58.551806"
    environment_variables: {}
    input_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    output_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    parameters: {}
    start_time: "2024-06-06T17:02:57.055159"
    version: 2.6.0
---

<div id="b6671da9" class="cell markdown"
papermill="{&quot;duration&quot;:3.717e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.180649&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.176932&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="8fe92d24" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.188101Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.187875Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.192918Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.192491Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0108e-2,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.193988&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.183880&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.019e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.200132&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.197113&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.207277Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.206827Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.210670Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.210242Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.545e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.211720&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.203175&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.218710Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.218339Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.223536Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.222986Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.881e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.224575&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.214694&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.232403Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.232051Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.236995Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.236587Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.625e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.238015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.228390&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.045e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.244143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.241098&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum points you can obtain from cards Video link:
<https://youtu.be/pBWCOCS636U?si=MrB1rbR3ScPbJGyB>

</div>

<div id="d6a9257f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.251258Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.250781Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.254999Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.254582Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.936e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.256038&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.247102&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.981e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.262061&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.259080&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest substring without repeating characters Video Link:
<https://youtu.be/-zSxTJkcdAo?si=OCzXyY4AuXSZz-eS>

</div>

<div id="688e574f" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.269255Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.268936Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.272951Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.272502Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.9e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.273973&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.265073&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.028e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.280053&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.277025&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Max consecutive ones III:
<https://leetcode.com/problems/max-consecutive-ones-iii/> Video Link:
<https://youtu.be/3E4JBHSLpYk?si=63rPPAESHHuPbIas>

</div>

<div id="b81ea511" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.287205Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.286733Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.291997Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.291571Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.987e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.293035&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.283048&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.069e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.299261&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.296192&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Fruit into baskets: <https://leetcode.com/problems/fruit-into-baskets>
Video Link: <https://youtu.be/e3bs0uA1NhQ?si=6ii_zUURKMi_Wu4i> Striver
uses a different approach of counting by freq, they are of the same time
complexity

</div>

<div id="6d7b7c24" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.306257Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.305873Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.310592Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.310164Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.363e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.311640&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.302277&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/fruit-into-baskets/submissions/1277567029
def maxFruits(fruits: list[int]):
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
assert maxFruits([2,1,2]) == 3
assert maxFruits([0,1,2,2,2,2]) == 5
assert maxFruits([1,3,1,2,2,3,2]) == 4
```

</div>

<div id="ea13d95c" class="cell markdown"
papermill="{&quot;duration&quot;:3.001e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.317735&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.314734&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest substring with k distinct characters:
<https://www.naukri.com/code360/problems/distinct-characters_2221410>
Video Link: <https://youtu.be/teM9ZsVRQyc?si=FMHKeYm3rvkCu0GG>

</div>

<div id="5116cf4c" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.324878Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.324405Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.329134Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.328613Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.371e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.330155&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.320784&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def kDistinctChars(S: str, K: int):
    """
    Although it is possible to use the same code as above, finding the min index to shift right might take O(24) time.
    Better to use striver's implementation of the same problem.
    """

    N = len(S)
    max_ = i = 0
    freq: dict[str, int] = dict()
    for j in range(N):
        freq[S[j]] = freq.get(S[j], 0) + 1

        # Expand
        if len(freq) <= K:
            max_ = max(max_, j - i + 1)

        # Slide
        else:
            freq[S[i]] -= 1
            if freq[S[i]] == 0:
                freq.pop(S[i])
            i += 1

    return max_

# Testing the solution
assert kDistinctChars("abbbbbbc", 2) == 7
assert kDistinctChars("abcddefg", 3) == 4
```

</div>

<div id="34efbc74" class="cell markdown"
papermill="{&quot;duration&quot;:3.106e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.336348&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.333242&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of substrings containing all 3 characters Video link:
<https://youtu.be/xtqN4qlgr8s?si=T_1Xp0aNnlf_pQzn>

</div>

<div id="23e9154b" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.343198Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.342999Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.347722Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.347244Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.324e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.348708&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.339384&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/submissions/1277998565
def numberOfSubstrings(S: str) -> int:
    """
    Increase J until we find a valid sequence, everything to the right is also valid
    Try shrinking left (increasing i) to see if it is valid, if it is everything to the right is also valid

    Time: O(2N), Space: O(3)
    """
    N = len(S)
    freq: dict[str, int] = {S[0]: 1}
    count = i = j = 0
    while j < N:
        if len(freq) == 3:
            count += N - j
            freq[S[i]] -= 1
            if freq[S[i]] == 0:
                freq.pop(S[i])
            i += 1
        else:
            j += 1
            if j < N:
                freq[S[j]] = freq.get(S[j], 0) + 1

    return count

# Testing the solution
assert numberOfSubstrings("abcabc") == 10
assert numberOfSubstrings("aaacb") == 3
assert numberOfSubstrings("abc") == 1
```

</div>

<div id="f3d190d8" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.355783Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.355309Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.359635Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.359085Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.991e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.360755&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.351764&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/submissions/1278006815
def numberOfSubstringsStriver(S: str) -> int:
    """
    At every index we keep track of the last seen index for each character a, b, c -> last_seen
    Find the minimial window uptil which the window was valid - min(last_seen.values()) -> i
    Every substring to the left of our minimal window would have still been valid: count += i + 1

    Time: O(N), Space: O(3)
    """
    N, count = len(S), 0
    last_seen: dict[str, int] = {"a": -1, "b": -1, "c": -1}
    for i in range(N):
        last_seen[S[i]] = i
        count += min(last_seen.values()) + 1

    return count

# Testing the solution
assert numberOfSubstringsStriver("abcabc") == 10
assert numberOfSubstringsStriver("aaacb") == 3
assert numberOfSubstringsStriver("abc") == 1
```

</div>

<div id="52f58033" class="cell markdown"
papermill="{&quot;duration&quot;:3.01e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.366920&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.363910&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest repeating character replacement Video Link:
<https://youtu.be/_eNhaDCr6P0?si=bsYcEmV-N7yOOh1z>

</div>

<div id="91b23fa8" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.373890Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.373564Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.378142Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.377632Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.184e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.379133&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.369949&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/longest-repeating-character-replacement/submissions/1278607910
def characterReplacement(S: str, K: int) -> int:
    """
    Logic: Given a string 'AAABBC', minimum conversions required would be length - maxfreq
    """
    N, max_length = len(S), 0
    freq: list[int] = [0 for i in range(26)]

    i = j = 0
    while j < N:

        # Expand
        if (j - i + 1) - max(freq) <= K:
            max_length = max(max_length, j - i + 1)

        # Slide
        else:
            freq[ord(S[i]) - ord('A')] -= 1
            i += 1

        j += 1
        if j < N:
            freq[ord(S[j]) - ord('A')] += 1

    return max_length

# Testing the solution
assert characterReplacement("ABAB", 2) == 4
assert characterReplacement("AABABBA", 1) == 4
```

</div>

<div id="35170d83" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.386193Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.385821Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.390776Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.390368Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.733e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.391903&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.382170&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/longest-repeating-character-replacement/submissions/1278630543
def characterReplacementStriver(S: str, K: int) -> int:
    """
    Max freq variable keeps track of the maximum frequency.

    We increase it each time we increment j.
    We can rescan during the times we decrement i, however since we are trying to find
    a length that is larger than the current largest, we can skip rescanning during the decrement portion.

    5 (length) - 3 (max_freq) <= 2 (K) => VALID

    We are trying to find length - 6, 7, 8, ..
    max_freq if decreased would tend to make the window invalid

    6 (length) - 2 (max_freq) > 4 (K) => INVALID
    """
    N, max_length = len(S), 0
    freq: list[int] = [0 for i in range(26)]
    freq[ord(S[0]) - ord('A')] += 1
    max_freq = 1

    i = j = 0
    while j < N:

        # Expand
        if (j - i + 1) - max_freq <= K:
            max_length = max(max_length, j - i + 1)

        # Slide
        else:
            freq[ord(S[i]) - ord('A')] -= 1
            i += 1

        j += 1
        if j < N:
            freq[ord(S[j]) - ord('A')] += 1
            max_freq = max(max_freq, freq[ord(S[j]) - ord('A')])

    return max_length

# Testing the solution
assert characterReplacementStriver("ABAB", 2) == 4
assert characterReplacementStriver("AABABBA", 1) == 4
```

</div>

<div id="98ae4a30" class="cell markdown"
papermill="{&quot;duration&quot;:3.021e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.397990&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.394969&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Count binary arrays with sum:
<https://leetcode.com/problems/binary-subarrays-with-sum/> Video Link:
<https://youtu.be/XnMdNUkX6VM?si=Ln4lCZRl4UNUFHdm>

</div>

<div id="43e17995" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.405203Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.404803Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.408806Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.408293Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.646e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.409813&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.401167&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def numSubarraysWithSumBrute(nums: list[int], goal: int) -> int:
    N, count = len(nums), 0
    for i in range(N):
        sum_ = 0
        for j in range(i, N):
            sum_ += nums[j]
            if sum_ == goal:
                count += 1
            elif sum_ > goal:
                break
    return count

# Testing the solution
assert numSubarraysWithSumBrute([1,0,1,0,1], 2) == 4
assert numSubarraysWithSumBrute([0,0,0,0,0], 0) == 15
```

</div>

<div id="9cc52060" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.416991Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.416649Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.420736Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.420232Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.744e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.421725&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.412981&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/submissions/detail/1279702194/
def numSubarraysWithSumBetter(nums: list[int], goal: int) -> int:
    """
    A better solution using prefix sum - count arrays with sum equals K

    1. For each n in arr, increment prefix_sum += n
    2. If target - prefix_sum had existed in hashmap, increase count by the number of times target - pf occured.
    3. Increment prefix_sum in hashmap by 1

    Time: O(N), Space: O(N)
    """
    # Store count of times that 'x' has occured
    hm: dict[int, int] = {0: 1}
    count = prefix_sum = 0

    for n in nums:
        prefix_sum += n
        count += hm.get(prefix_sum - goal, 0)
        hm[prefix_sum] = hm.get(prefix_sum, 0) + 1

    return count

# Testing the solution
assert numSubarraysWithSumBetter([1,0,1,0,1], 2) == 4
assert numSubarraysWithSumBetter([0,0,0,0,0], 0) == 15
```

</div>

<div id="1d2c7d1f" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-06T17:02:58.428782Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-06T17:02:58.428416Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-06T17:02:58.432786Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-06T17:02:58.432291Z&quot;}"
papermill="{&quot;duration&quot;:9.039e-3,&quot;end_time&quot;:&quot;2024-06-06T17:02:58.433828&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-06T17:02:58.424789&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/submissions/detail/1279747938
def numSubarraysWithSumOptimal(nums: list[int], goal: int) -> int:
    """
    When checking for sum equivalent to goal, we wouldn't know whether to shrink or to expand
    Hence we modify the problem to find the count of subarrays <= goal
    """
    def countSubArraysLTE(K: int) -> int:
        count = sum_ = i = j = 0
        while j < N:
            sum_ += nums[j]
            while i < N and sum_ > K:
                sum_ -= nums[i]
                i += 1
            count += j - i + 1
            j += 1

        return count

    N = len(nums)
    return countSubArraysLTE(goal) - (countSubArraysLTE(goal - 1) if goal > 0 else 0)

# Testing the solution
assert numSubarraysWithSumOptimal([1,0,1,0,1], 2) == 4
assert numSubarraysWithSumOptimal([0,0,0,0,0], 0) == 15
```

</div>
