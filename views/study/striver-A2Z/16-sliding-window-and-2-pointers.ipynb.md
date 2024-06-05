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
    duration: 1.443706
    end_time: "2024-06-05T17:23:03.476713"
    environment_variables: {}
    input_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    output_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    parameters: {}
    start_time: "2024-06-05T17:23:02.033007"
    version: 2.6.0
---

<div id="b6671da9" class="cell markdown"
papermill="{&quot;duration&quot;:3.394e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.166525&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.163131&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="8fe92d24" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.173331Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.172903Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.178289Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.177843Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0043e-2,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.179390&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.169347&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.529e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.184575&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.182046&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.190553Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.190359Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.194181Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.193764Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.079e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.195201&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.187122&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.201470Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.200967Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.206443Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.205915Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.616e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.207468&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.197852&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.213562Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.213149Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.218222Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.217707Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.186e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.219221&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.210035&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.54e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.225144&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.222604&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum points you can obtain from cards Video link:
<https://youtu.be/pBWCOCS636U?si=MrB1rbR3ScPbJGyB>

</div>

<div id="d6a9257f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.231347Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.230925Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.235146Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.234711Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.544e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.236269&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.227725&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.557e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.241473&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.238916&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest substring without repeating characters Video Link:
<https://youtu.be/-zSxTJkcdAo?si=OCzXyY4AuXSZz-eS>

</div>

<div id="688e574f" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.247769Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.247300Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.251406Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.250958Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.32e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.252404&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.244084&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.655e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.257723&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.255068&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Max consecutive ones III:
<https://leetcode.com/problems/max-consecutive-ones-iii/> Video Link:
<https://youtu.be/3E4JBHSLpYk?si=63rPPAESHHuPbIas>

</div>

<div id="b81ea511" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.263911Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.263524Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.268819Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.268284Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.463e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.269822&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.260359&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.597e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.275207&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.272610&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Fruit into baskets: <https://leetcode.com/problems/fruit-into-baskets>
Video Link: <https://youtu.be/e3bs0uA1NhQ?si=6ii_zUURKMi_Wu4i> Striver
uses a different approach of counting by freq, they are of the same time
complexity

</div>

<div id="6d7b7c24" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.281150Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.280894Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.285664Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.285216Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.916e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.286702&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.277786&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.61e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.291939&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.289329&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest substring with k distinct characters:
<https://www.naukri.com/code360/problems/distinct-characters_2221410>
Video Link: <https://youtu.be/teM9ZsVRQyc?si=FMHKeYm3rvkCu0GG>

</div>

<div id="5116cf4c" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.298054Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.297719Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.302126Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.301621Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.468e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.303116&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.294648&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.552e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.308266&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.305714&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of substrings containing all 3 characters Video link:
<https://youtu.be/xtqN4qlgr8s?si=T_1Xp0aNnlf_pQzn>

</div>

<div id="23e9154b" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.314295Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.313892Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.318353Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.317848Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.574e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.319375&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.310801&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.325672Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.325245Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.329116Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.328668Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.064e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.330149&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.322085&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.615e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.335473&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.332858&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest repeating character replacement Video Link:
<https://youtu.be/_eNhaDCr6P0?si=bsYcEmV-N7yOOh1z>

</div>

<div id="91b23fa8" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.341740Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.341320Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.345911Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.345417Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.755e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.346888&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.338133&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-05T17:23:03.353018Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-05T17:23:03.352856Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-05T17:23:03.357589Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-05T17:23:03.357165Z&quot;}"
papermill="{&quot;duration&quot;:8.96e-3,&quot;end_time&quot;:&quot;2024-06-05T17:23:03.358646&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-05T17:23:03.349686&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
