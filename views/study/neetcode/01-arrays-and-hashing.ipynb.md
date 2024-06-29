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
    duration: 1.548759
    end_time: "2024-06-29T11:06:16.104338"
    environment_variables: {}
    input_path: study/neetcode/01-arrays-and-hashing.ipynb
    output_path: study/neetcode/01-arrays-and-hashing.ipynb
    parameters: {}
    start_time: "2024-06-29T11:06:14.555579"
    version: 2.6.0
---

<div id="3fdf69c6" class="cell markdown"
papermill="{&quot;duration&quot;:4.191e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.686199&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.682008&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Neccessary file imports

</div>

<div id="21971dda" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.694419Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.693960Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.699480Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.698974Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1117e-2,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.700812&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.689695&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import collections
import functools
import heapq
import bisect
import random
```

</div>

<div id="de28faf4" class="cell markdown"
papermill="{&quot;duration&quot;:3.2e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.707391&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.704191&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Contains duplicate

</div>

<div id="b1626aac" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.715773Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.715319Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.719333Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.718832Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.902e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.720502&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.710600&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/contains-duplicate/submissions/1301625329/
def containsDuplicate(nums: list[int]) -> bool:
    set_: set[int] = set()
    for n in nums:
        if n in set_:
            return True
        set_.add(n)
    return False

# Testing the solution
assert containsDuplicate([1,1,2,2,3,4]) == True
assert containsDuplicate([1,2,3,4,10]) == False
```

</div>

<div id="83540d6f" class="cell markdown"
papermill="{&quot;duration&quot;:3.197e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.727021&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.723824&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Valid Anagram

</div>

<div id="4877cbdf" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.734396Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.734123Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.738391Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.737966Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.125e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.739410&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.730285&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# 
# https://leetcode.com/problems/valid-anagram/submissions/1301649707/
def isAnagram(s1: str, s2: str) -> bool:
    N1, N2 = len(s1), len(s2)
    if N1 != N2:
        return False
    else:
        freq: list[int] = [0 for i in range(26)]
        for i in range(N1):
            freq[ord(s1[i]) - ord('a')] += 1
            freq[ord(s2[i]) - ord('a')] -= 1
        return not any(filter(lambda x: x != 0, freq))

# Testing the solution
assert isAnagram("anagram", "nagaram") == True
assert isAnagram("rat", "car") == False
```

</div>

<div id="df42a1f5" class="cell markdown"
papermill="{&quot;duration&quot;:3.196e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.745869&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.742673&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Concatenation of array

</div>

<div id="efbdfbb7" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.753341Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.752907Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.756598Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.756080Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.581e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.757664&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.749083&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/concatenation-of-array/submissions/1301720169/
def getConcatenation(nums: list[int]) -> list[int]:
    N = len(nums)
    result: list[int] = []
    for i in range(2 * N):
        result.append(nums[i % N])

    return result

# Testing the solution
assert getConcatenation([1,2]) == [1,2,1,2]
assert getConcatenation([1,2,3]) == [1,2,3,1,2,3]
```

</div>

<div id="2c5e7cdb" class="cell markdown"
papermill="{&quot;duration&quot;:3.216e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.764188&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.760972&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Replace elements with greater on the right side

</div>

<div id="c0f31c72" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.771909Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.771433Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.775185Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.774745Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.764e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.776204&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.767440&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/submissions/1301744473
def replaceElements(arr: list[int]) -> list[int]:
    N, max_ = len(arr), -1
    for i in range(N - 1, -1, -1):
        max_, arr[i] = max(max_, arr[i]), max_
    return arr

# Testing the solution
assert replaceElements([17,18,5,4,6,1]) == [18,6,6,6,1,-1]
assert replaceElements([400]) == [-1]
```

</div>

<div id="35f4ea99" class="cell markdown"
papermill="{&quot;duration&quot;:3.192e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.782650&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.779458&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Is Subsequence

</div>

<div id="c9569b8a" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.789993Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.789794Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.793627Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.793179Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.787e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.794645&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.785858&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/is-subsequence/submissions/1285008314/
def isSubsequence(s: str, t: str) -> bool:
    s_len, t_len, i, j = len(s), len(t), 0, 0
    while i < s_len and j < t_len:
        if s[i] == t[j]:
            i, j = i + 1, j + 1
        else:
            j += 1

    return i == s_len

# Testing the solution
assert isSubsequence("abc", "ahbgdc") == True
assert isSubsequence("axc", "ahbgdc") == False
```

</div>

<div id="0d9faf13" class="cell markdown"
papermill="{&quot;duration&quot;:3.256e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.801248&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.797992&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of Last word

</div>

<div id="e0d87324" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.808749Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.808286Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.811975Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.811516Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.608e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.813019&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.804411&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/length-of-last-word/submissions/1301765924
def lengthOfLastWord(s: str) -> int:
    i, length = len(s) - 1, 0
    while i >= 0:
        if s[i] != ' ':
            length += 1
        elif length > 0:
            break
        i -= 1

    return length

# Testing the solution
assert lengthOfLastWord("abc") == 3
assert lengthOfLastWord("abc   ") == 3
assert lengthOfLastWord("abc   abcd ") == 4
```

</div>

<div id="5ff5abc6" class="cell markdown"
papermill="{&quot;duration&quot;:3.206e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.819453&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.816247&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Two sum

</div>

<div id="8d35c690" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.826845Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.826508Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.831178Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.830647Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.621e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.832308&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.822687&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def twoSumBetter(nums: list[int], target: int) -> tuple[int, int]:
    N = len(nums)

    # Store all the indices
    indices: collections.defaultdict[int, list[int]] = collections.defaultdict(list)
    for i in range(N):
        indices[nums[i]].append(i)

    # For each idx1, check if we another idx2 who total equals target
    for i in range(N):
        n = nums[i]
        if target - n in indices:
            for idx in indices[target - n]:
                if idx != i:
                    return i, idx

    return -1, -1

# Testing the solution
assert twoSumBetter([3,3,4], 6) == (0,1)
assert twoSumBetter([3,2,4], 6) == (1,2)
assert twoSumBetter([2,7,11,15], 13) == (0,2)
```

</div>

<div id="b1788ccd" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.839752Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.839356Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.843515Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.843078Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.973e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.844559&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.835586&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def twoSum(nums: list[int], target: int) -> tuple[int, int]:
    "One pass solution from Neetcode"
    indices: dict[int, int] = dict()
    for i in range(len(nums)):
        if target - nums[i] in indices:
            return indices[target - nums[i]], i
        indices[nums[i]] = i

    return -1, -1

# Testing the solution
assert twoSum([3,3,4], 6) == (0,1)
assert twoSum([3,2,4], 6) == (1,2)
assert twoSum([2,7,11,15], 13) == (0,2)
```

</div>

<div id="863712d9" class="cell markdown"
papermill="{&quot;duration&quot;:3.275e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.851061&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.847786&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest common prefix

</div>

<div id="39f57a0b" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.858451Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.858071Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.861871Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.861359Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.603e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.862887&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.854284&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/longest-common-prefix/submissions/1301965071
def longestCommonPrefix(strs: list[str]) -> str:
    prefix: str = strs[0]
    for string in strs[1:]:
        i = 0
        while i < len(prefix) and i < len(string) and prefix[i] == string[i]:
            i += 1
        prefix = prefix[:i]

    return prefix

# Testing the solution
assert longestCommonPrefix(["flow", "flower", "flight"]) == "fl"
assert longestCommonPrefix(["dog", "car"]) == ""
assert longestCommonPrefix(["dog"]) == "dog"
```

</div>

<div id="2f683cba" class="cell markdown"
papermill="{&quot;duration&quot;:3.469e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.869609&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.866140&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Group Anagrams

</div>

<div id="fca19f3c" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.877023Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.876628Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.883776Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.883283Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2137e-2,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.884942&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.872805&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/group-anagrams/submissions/1301981761
def groupAnagrams(strs: list[str]) -> list[list[str]]:
    # Time: O(N x avg_str_length)
    anagrams: collections.defaultdict[str, list[str]] = collections.defaultdict(list)
    for string in strs:
        freq: list[int] = [0 for _ in range(26)]
        for ch in string:
            freq[ord(ch) - ord('a')] += 1

        freq_key: str = ','.join(map(str, freq))
        anagrams[freq_key].append(string)

    return list(anagrams.values())

# Testing the solution
groupAnagrams(["eat","tea","tan","ate","nat","bat", ""])
```

<div class="output execute_result" execution_count="11">

    [['eat', 'tea', 'ate'], ['tan', 'nat'], ['bat'], ['']]

</div>

</div>

<div id="08810553" class="cell markdown"
papermill="{&quot;duration&quot;:3.381e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.891671&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.888290&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Pascals Triangle

</div>

<div id="8f42682b" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.899199Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.898829Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.902991Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.902487Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.027e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.904015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.894988&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/pascals-triangle/submissions/1302000166
def generatePascalsTriangle(N: int) -> list[list[int]]:
    result: list[list[int]] = [[1]]
    for i in range(1, N):
        layer: list[int] = []
        for j in range(i + 1):
            layer.append((result[-1][j] if j < i else 0) + (result[-1][j - 1] if j - 1 >= 0 else 0))
        result.append(layer)

    return result

# Testing the solution
assert generatePascalsTriangle(5) == [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
```

</div>

<div id="44029b82" class="cell markdown"
papermill="{&quot;duration&quot;:4.123e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.911787&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.907664&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Remove element

</div>

<div id="8fb28845" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.920061Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.919883Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.924436Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.923974Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.886e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.925503&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.915617&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/remove-element/submissions/1303667206/
def removeElement(nums: list[int], val: int) -> int:
    N, i, j = len(nums), 0, 0
    while j < N:
        if nums[j] != val:
            nums[i] = nums[j]
            i += 1
        j += 1

    print(nums[:i])
    return i

# Testing the solution
assert removeElement([3,2,2,3], 3) == 2
assert removeElement([0,1,2,2,3,0,4,2], 2) == 5
```

<div class="output stream stdout">

    [2, 2]
    [0, 1, 3, 0, 4]

</div>

</div>

<div id="ac4870d5" class="cell markdown"
papermill="{&quot;duration&quot;:3.394e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.932276&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.928882&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Unique Email Addresses

</div>

<div id="d0a3c36e" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.939932Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.939559Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.944629Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.944179Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0057e-2,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.945682&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.935625&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/unique-email-addresses/submissions/1303683218/
def numUniqueEmails(emails: list[str]) -> int:
    email_set: set[str] = set()
    for email in emails:
        email_rep: list[str] = []
        domain, i = False, 0
        while i < len(email):
            if email[i] not in ('+', '.', '@'):
                email_rep.append(email[i])
            elif email[i] == '.':
                if domain:
                    email_rep.append(email[i])
            elif email[i] == '+':
                if domain:
                    email_rep.append(email[i])
                else:
                    while email[i + 1] != '@':
                        i += 1
            else:
                email_rep.append(email[i])
                domain = True
            i += 1
        email_set.add(''.join(email_rep))

    return len(email_set)

# Testing the solution
assert numUniqueEmails(["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]) == 2
assert numUniqueEmails(["a@leetcode.com","b@leetcode.com","c@leetcode.com"]) == 3
```

</div>

<div id="2102af06" class="cell markdown"
papermill="{&quot;duration&quot;:3.397e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.952498&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.949101&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Isomorphic Strings

</div>

<div id="75db0d24" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.960344Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.959909Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.964823Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.964307Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.953e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.965927&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.955974&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def isIsomorphic(s1: str, s2: str) -> bool:
    mapping: dict[str, str] = dict()
    rev_mapping: dict[str, str] = dict()
    for i in range(len(s1)):
        if s1[i] not in mapping and s2[i] not in rev_mapping:
            mapping[s1[i]] = s2[i]
            rev_mapping[s2[i]] = s1[i]
        elif s1[i] in mapping and s2[i] in rev_mapping:
            if not mapping[s1[i]] == s2[i] or not rev_mapping[s2[i]] == s1[i]:
                return False
        else:
            return False

    return True

# Testing the solution
assert isIsomorphic("egg", "add") == True
assert isIsomorphic("abc", "baa") == False
assert isIsomorphic("aabb", "baba") == False
assert isIsomorphic("paper", "title") == True
```

</div>

<div id="4b0b1937" class="cell markdown"
papermill="{&quot;duration&quot;:3.508e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.972959&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.969451&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Can place flowers

</div>

<div id="124d8f5e" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-29T11:06:15.980956Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-29T11:06:15.980436Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-29T11:06:15.984530Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-29T11:06:15.984106Z&quot;}"
papermill="{&quot;duration&quot;:9.218e-3,&quot;end_time&quot;:&quot;2024-06-29T11:06:15.985601&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-29T11:06:15.976383&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/can-place-flowers/submissions/1303795340
def canPlaceFlowers(flowerbed: list[int], n_flowers: int) -> bool:
    N = len(flowerbed)
    for i in range(N):
        left, mid, right = flowerbed[i - 1] if i - 1 >= 0 else 0, flowerbed[i], flowerbed[i + 1] if i + 1 < N else 0
        if left == mid == right:
            flowerbed[i], n_flowers = 1, n_flowers - 1

    return n_flowers <= 0

# Testing the solution
assert canPlaceFlowers([1,0,0,0,1], 1) == True
assert canPlaceFlowers([1,0,0,0,1], 2) == False
```

</div>
