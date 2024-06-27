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
    duration: 1.451176
    end_time: "2024-06-27T13:37:34.451532"
    environment_variables: {}
    input_path: study/neetcode/01-arrays-and-hashing.ipynb
    output_path: study/neetcode/01-arrays-and-hashing.ipynb
    parameters: {}
    start_time: "2024-06-27T13:37:33.000356"
    version: 2.6.0
---

<div id="3fdf69c6" class="cell markdown"
papermill="{&quot;duration&quot;:3.062e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.152785&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.149723&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Neccessary file imports

</div>

<div id="21971dda" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.158874Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.158534Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.163886Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.163469Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.793e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.165022&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.155229&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.303e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.169660&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.167357&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Contains duplicate

</div>

<div id="b1626aac" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.175263Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.174899Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.178581Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.178168Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.636e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.179614&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.171978&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.304e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.185038&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.182734&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Valid Anagram

</div>

<div id="4877cbdf" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.190642Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.190233Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.194498Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.194077Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.215e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.195558&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.187343&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.306e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.200285&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.197979&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Concatenation of array

</div>

<div id="efbdfbb7" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.205920Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.205558Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.209131Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.208706Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.558e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.210191&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.202633&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.359e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.215034&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.212675&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Replace elements with greater on the right side

</div>

<div id="c0f31c72" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.220804Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.220384Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.224127Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.223685Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.755e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.225195&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.217440&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.377e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.230009&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.227632&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Is Subsequence

</div>

<div id="c9569b8a" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.235849Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.235466Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.239231Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.238722Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.963e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.240329&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.232366&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.364e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.245172&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.242808&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of Last word

</div>

<div id="e0d87324" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.250886Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.250483Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.253864Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.253470Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.303e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.254852&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.247549&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.499e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.259894&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.257395&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Two sum

</div>

<div id="8d35c690" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.265830Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.265350Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.269882Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.269475Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.528e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.270896&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.262368&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.276760Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.276397Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.280527Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.280107Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.184e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.281559&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.273375&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.534e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.286559&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.284025&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Longest common prefix

</div>

<div id="39f57a0b" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.292391Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.292031Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.295892Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.295477Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.91e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.296957&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.289047&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.499e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.301954&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.299455&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Group Anagrams

</div>

<div id="fca19f3c" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.308670Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.308130Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.315509Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.315007Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2128e-2,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.316611&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.304483&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.656e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.321987&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.319331&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Pascals Triangle

</div>

<div id="8f42682b" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-27T13:37:34.328308Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-27T13:37:34.327993Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-27T13:37:34.332297Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-27T13:37:34.331867Z&quot;}"
papermill="{&quot;duration&quot;:8.659e-3,&quot;end_time&quot;:&quot;2024-06-27T13:37:34.333330&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-27T13:37:34.324671&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
