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
    duration: 1.657523
    end_time: "2024-06-07T18:28:52.609773"
    environment_variables: {}
    input_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    output_path: study/striver-A2Z/16-sliding-window-and-2-pointers.ipynb
    parameters: {}
    start_time: "2024-06-07T18:28:50.952250"
    version: 2.6.0
---

<div id="b6671da9" class="cell markdown"
papermill="{&quot;duration&quot;:4.677e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.096496&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.091819&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="8fe92d24" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.105868Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.105389Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.110917Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.110367Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1566e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.112104&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.100538&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.969e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.120100&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.116131&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.130196Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.129634Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.133645Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.133228Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0778e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.134737&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.123959&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.143797Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.143341Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.148839Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.148401Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1155e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.149868&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.138713&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.158639Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.158324Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.163510Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.162984Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0797e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.164599&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.153802&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.825e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.172277&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.168452&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum points you can obtain from cards Video link:
<https://youtu.be/pBWCOCS636U?si=MrB1rbR3ScPbJGyB>

</div>

<div id="d6a9257f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.181104Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.180755Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.185177Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.184669Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0207e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.186266&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.176059&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.794e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.194030&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.190236&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest substring without repeating characters Video Link:
<https://youtu.be/-zSxTJkcdAo?si=OCzXyY4AuXSZz-eS>

</div>

<div id="688e574f" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.202746Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.202383Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.206622Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.206175Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.854e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.207736&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.197882&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.874e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.215539&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.211665&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Max consecutive ones III:
<https://leetcode.com/problems/max-consecutive-ones-iii/> Video Link:
<https://youtu.be/3E4JBHSLpYk?si=63rPPAESHHuPbIas>

</div>

<div id="b81ea511" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.224034Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.223577Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.228902Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.228488Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0641e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.229906&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.219265&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.764e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.237558&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.233794&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Fruit into baskets: <https://leetcode.com/problems/fruit-into-baskets>
Video Link: <https://youtu.be/e3bs0uA1NhQ?si=6ii_zUURKMi_Wu4i> Striver
uses a different approach of counting by freq, they are of the same time
complexity

</div>

<div id="6d7b7c24" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.246151Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.245808Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.250410Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.250003Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0176e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.251473&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.241297&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.768e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.259049&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.255281&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest substring with k distinct characters:
<https://www.naukri.com/code360/problems/distinct-characters_2221410>
Video Link: <https://youtu.be/teM9ZsVRQyc?si=FMHKeYm3rvkCu0GG>

</div>

<div id="5116cf4c" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.267878Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.267470Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.271959Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.271520Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0025e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.273010&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.262985&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.864e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.280908&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.277044&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Number of substrings containing all 3 characters Video link:
<https://youtu.be/xtqN4qlgr8s?si=T_1Xp0aNnlf_pQzn>

</div>

<div id="23e9154b" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.289301Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.289109Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.293719Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.293288Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0064e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.294726&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.284662&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.303492Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.303023Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.306994Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.306568Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.453e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.308060&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.298607&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.065e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.316142&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.312077&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest repeating character replacement Video Link:
<https://youtu.be/_eNhaDCr6P0?si=bsYcEmV-N7yOOh1z>

</div>

<div id="91b23fa8" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.324746Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.324360Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.329186Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.328694Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0316e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.330262&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.319946&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.339002Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.338550Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.343747Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.343197Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0723e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.344849&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.334126&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.869e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.352567&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.348698&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Count binary arrays with sum:
<https://leetcode.com/problems/binary-subarrays-with-sum/> Video Link:
<https://youtu.be/XnMdNUkX6VM?si=Ln4lCZRl4UNUFHdm>

</div>

<div id="43e17995" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.361266Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.360822Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.365041Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.364500Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.684e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.366088&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.356404&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.374613Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.374292Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.378370Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.377877Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.567e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.379497&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.369930&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.388081Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.387756Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.392139Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.391659Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.841e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.393158&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.383317&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="76a28505" class="cell markdown"
papermill="{&quot;duration&quot;:3.797e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.400848&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.397051&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Count number of nice subarrays:
<https://leetcode.com/problems/count-number-of-nice-subarrays/> Video
Link: <https://youtu.be/j_QOv9OT9Og?si=bx1OWjbu3VXTIZhw>

</div>

<div id="b13204ae" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.409614Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.409181Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.413790Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.413368Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0097e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.414808&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.404711&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/count-number-of-nice-subarrays/submissions/1280053394
def numberOfSubarrays(nums: list[int], K: int) -> int:
    """
    Exact same logic as the previous question.
    Time: O(2N + 2N) ~ O(N), Space: O(1)
    """
    N = len(nums)
    def countSubArrays(k_: int) -> int:
        odd_count = count = i = j = 0
        while j < N:
            odd_count += nums[j] % 2
            while odd_count > k_:
                odd_count -= nums[i] % 2
                i += 1
            count += j - i + 1
            j += 1

        return count

    return countSubArrays(K) - (countSubArrays(K - 1) if K > 0 else 0)

# Testing the solution
assert numberOfSubarrays([1,1,2,1,1], 3) == 2
assert numberOfSubarrays([2,4,6], 1) == 0
assert numberOfSubarrays([2,2,2,1,2,2,1,2,2,2], 2) == 16
```

</div>

<div id="b6b4a5ed" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.423807Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.423411Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.428035Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.427614Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0282e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.429093&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.418811&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/count-number-of-nice-subarrays/submissions/1280056713
def numberOfSubarraysStriver(nums: list[int], K: int) -> int:
    """
    [1,2,5,1,2,6,8], 3

    Apply a modulo 2 op on all numbers and it becomes: [1,0,1,1,0,0,0], 3
    """
    def countSubArrays(k_: int) -> int:
        count = sum_ = i = j = 0
        while j < N:
            sum_ += nums[j]
            while sum_ > k_:
                sum_ -= nums[i]
                i += 1
            count += j - i + 1
            j += 1

        return count

    N = len(nums)
    nums = list(map(lambda x: x % 2, nums))
    return countSubArrays(K) - (countSubArrays(K - 1) if K > 0 else 0)

# Testing the solution
assert numberOfSubarraysStriver([1,1,2,1,1], 3) == 2
assert numberOfSubarraysStriver([2,4,6], 1) == 0
assert numberOfSubarraysStriver([2,2,2,1,2,2,1,2,2,2], 2) == 16
```

</div>

<div id="19220f01" class="cell markdown"
papermill="{&quot;duration&quot;:3.846e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.438053&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.434207&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Subarrays with K different integers:
<https://leetcode.com/problems/subarrays-with-k-different-integers/description/>
Video Link: <https://youtu.be/7wYGbV_LsX4?si=m-cqYxni-iCnE80S>

</div>

<div id="3162b8cb" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.447071Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.446634Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.451618Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.451130Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0678e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.452660&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.441982&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/subarrays-with-k-different-integers/submissions/1280064513
def subarraysWithKDistinct(nums: list[int], K: int) -> int:
    """Time: O(N), Space: O(N)"""
    def countGoodSubArrays(k_: int) -> int:
        count = i = j = 0
        freq: dict[int, int] = dict()
        while j < N:
            freq[nums[j]] = freq.get(nums[j], 0) + 1
            while len(freq) > k_:
                freq[nums[i]] = freq[nums[i]] - 1
                if freq[nums[i]] == 0:
                    freq.pop(nums[i])
                i += 1
            count += j - i + 1
            j += 1

        return count

    N = len(nums)
    return countGoodSubArrays(K) - (countGoodSubArrays(K - 1) if K > 0 else 0)

# Testing the solution
assert subarraysWithKDistinct([1,2,1,2,3], 2) == 7
assert subarraysWithKDistinct([1,2,1,3,4], 3) == 3
```

</div>

<div id="43979531" class="cell markdown"
papermill="{&quot;duration&quot;:3.943e-3,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.460561&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.456618&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Minimum window substring:
<https://leetcode.com/problems/minimum-window-substring/> Video Link:
<https://youtu.be/WJaij9ffOIY?si=aCQufx9ALwI_84Z7>

</div>

<div id="76ff34c1" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.469395Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.469001Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.473875Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.473464Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0439e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.474909&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.464470&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minWindowBrute(s1: str, s2: str) -> str:
    # Time: O(N ** 2), Space: O(1)
    def included(freq: dict[str, int]) -> bool:
        for k, v in s2_freq.items():
            if k not in freq or v > freq[k]:
                return False
        return True

    N1, N2 = len(s1), len(s2)
    s2_freq = collections.Counter(s2)
    min_ = N1 + N2, ""
    for i in range(N1):
        s1_freq: dict[str, int] = dict()
        for j in range(i, N1):
            s1_freq[s1[j]] = s1_freq.get(s1[j], 0) + 1
            if min_[0] > j - i + 1 and included(s1_freq):
                min_ = j - i + 1, s1[i: j + 1]

    return min_[1]

# Testing the solution
assert minWindowBrute("ADOBECODEBANC", "ABC") == "BANC"
assert minWindowBrute("a", "a") == "a"
assert minWindowBrute("a", "aa") == ""
```

</div>

<div id="acd95ec3" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:28:52.483865Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:28:52.483445Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:28:52.489223Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:28:52.488689Z&quot;}"
papermill="{&quot;duration&quot;:1.1459e-2,&quot;end_time&quot;:&quot;2024-06-07T18:28:52.490376&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:28:52.478917&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/minimum-window-substring/submissions/1280827554
def minWindow(s1: str, s2: str) -> str:
    """
    Maintain a dictionary marking the frequencies.
    Values greater than 0 indicate that the window is invalid.
    Values lesser than 0 indicate that the window size can be shrunk
    Values equal to 0 is hypothetically possible, the perfect window
    """
    # Initialize values
    N1, N2 = len(s1), len(s2)
    window_char_match = i = j = 0
    start_idx, min_length = -1, N1 + N2

    # Compute the frequency of the second substring
    freq: dict[str, int] = {}
    for n in s2:
        freq[n] = freq.get(n, 0) + 1

    # If invalid, expand. If valid, try to shrink until it is no longer valid.
    # Slide with the size of the minimum window we had obtained
    while j < N1:
        if window_char_match < N2:
            freq[s1[j]] = freq.get(s1[j], 0) - 1
            if freq[s1[j]] >= 0:
                window_char_match += 1
        while window_char_match >= N2:
            if min_length > j - i + 1:
                min_length, start_idx = j - i + 1, i
            freq[s1[i]] = freq[s1[i]] + 1
            if freq[s1[i]] > 0:
                window_char_match -= 1
            i += 1

        # Long due to update, but for the sake of calc we update it at the end
        j += 1

    return s1[start_idx: start_idx + min_length] if start_idx >= 0 else ""

# Testing the solution
assert minWindow("ADOBECODEBANC", "ABC") == "BANC"
assert minWindow("a", "a") == "a"
assert minWindow("a", "aa") == ""
```

</div>
