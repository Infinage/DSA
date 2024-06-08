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
    duration: 1.328723
    end_time: "2024-06-08T04:19:32.159220"
    environment_variables: {}
    input_path: study/striver-A2Z/17-greedy.ipynb
    output_path: study/striver-A2Z/17-greedy.ipynb
    parameters: {}
    start_time: "2024-06-08T04:19:30.830497"
    version: 2.6.0
---

<div id="76cb4635" class="cell markdown"
papermill="{&quot;duration&quot;:2.054e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:31.962554&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:31.960500&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Useful imports

</div>

<div id="d45ec848" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T04:19:31.967343Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T04:19:31.966871Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T04:19:31.972259Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T04:19:31.971809Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.928e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:31.973340&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:31.964412&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import heapq
import bisect
import collections
import itertools
import functools
```

</div>

<div id="a2f52f24" class="cell markdown"
papermill="{&quot;duration&quot;:1.525e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:31.976408&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:31.974883&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Assign cookies: <https://leetcode.com/problems/assign-cookies/> Video
Link: <https://youtu.be/DIX2p7vb9co?si=-lYoEBkNX6G40Tpo>

</div>

<div id="8016e3c9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T04:19:31.980430Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T04:19:31.980003Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T04:19:31.984922Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T04:19:31.984406Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.128e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:31.986041&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:31.977913&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/assign-cookies/submissions/1280845661
def findContentChildren(g: list[int], s: list[int]) -> int:
    """
    For each child we assign cookies that only require as much to satisfy their greed.
    For a child with greed of 3, we assign the minimum cookie left to satisfy condition: s[k] >= 3
    """
    # Sort in ASC order since we need to find the max
    # number of content children possible
    g.sort()
    s.sort()

    # Have pointers for greed and cookies arrary
    g_length, s_length = len(g), len(s)
    content_children = g_idx = s_idx = 0

    # Iterate until either of the arrays are exhausted
    while g_idx < g_length and s_idx < s_length:
        if s[s_idx] >= g[g_idx]:
            content_children, s_idx, g_idx = content_children + 1, s_idx + 1, g_idx + 1
        else:
            s_idx += 1

    return content_children

# Testing the solution
assert findContentChildren([1,2,3], [1,1,1]) == 1
assert findContentChildren([1,2], [1,2,3]) == 2
assert findContentChildren([1,2,3], [1,2]) == 2
```

</div>

<div id="f911a310" class="cell markdown"
papermill="{&quot;duration&quot;:1.508e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:31.989193&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:31.987685&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest job first CPU scheduling Video Link:
<https://youtu.be/3-QbX1iDbXs?si=oh3KUu3zLd08uDZ7>

</div>

<div id="1e00764f" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T04:19:31.993213Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T04:19:31.992875Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T04:19:31.996821Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T04:19:31.996299Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.161e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:31.997874&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:31.990713&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def SJF(bt: list[int]) -> float:
    """Time: O(N), Space: O(N)"""

    # Heapify to convert into a min heap
    heapq.heapify(bt)

    N = len(bt)
    curr_time = total_time = 0
    while bt:
        runtime = heapq.heappop(bt)
        total_time += curr_time
        curr_time += runtime

    avg_wait = total_time // N
    return avg_wait

# Testing the solution
assert SJF([4,3,7,1,2]) == 4
assert SJF([1,2,3,4]) == 2
```

</div>

<div id="e8d91515" class="cell markdown"
papermill="{&quot;duration&quot;:1.584e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:32.001024&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:31.999440&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lemonade change:
<https://leetcode.com/problems/lemonade-change/description/> Video link:
<https://youtu.be/n_tmibEhO6Q?si=bqyD-xTjBPIG9scO>

</div>

<div id="726bd349" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T04:19:32.005303Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T04:19:32.004908Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T04:19:32.009433Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T04:19:32.009011Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.892e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:32.010535&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:32.002643&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/lemonade-change/submissions/1281069969
def lemonadeChange(bills: list[int]) -> bool:
    change5 = change10 = 0
    for bill in bills:
        if bill == 5:
            change5 += 1
        elif bill == 10:
            change10 += 1
            change5 -= 1
        else:
            # Try to change with 10 if available
            if change10 > 0:
                change5, change10 = change5 - 1, change10 - 1
            # Else we can change with 5
            else:
                change5 -= 3

        # Reason this is added here and not at the end: [10,5]
        if change5 < 0 or change10 < 0:
            return False

    else:
        return True

# Testing the solution
assert lemonadeChange([5,5,10,10,20]) == False
assert lemonadeChange([10,5]) == False
assert lemonadeChange([5,10,20]) == False
assert lemonadeChange([5,5,5,20]) == True
```

</div>

<div id="bf923f2c" class="cell markdown"
papermill="{&quot;duration&quot;:1.556e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:32.013742&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:32.012186&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Jump game: <https://leetcode.com/problems/jump-game/> Video Link:
<https://youtu.be/tZAa_jJ3SwQ?si=PUeiia1qBXmvfk_C>

</div>

<div id="d487decb" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T04:19:32.017926Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T04:19:32.017552Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T04:19:32.021846Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T04:19:32.021386Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.623e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:32.022918&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:32.015295&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def canJumpBrute(nums: list[int]) -> bool:
    N = len(nums)
    good_indices: collections.deque = collections.deque([N - 1])
    for i in range(N - 2, -1, -1):
        for good_idx in good_indices:
            if i + nums[i] >= good_idx:
                good_indices.appendleft(i)
                break

    return good_indices[0] == 0

# Testing the solution
assert canJumpBrute([2,3,1,1,4]) == True
assert canJumpBrute([3,2,1,0,4]) == False
assert canJumpBrute([2,0,2,0,0]) == True
```

</div>

<div id="4b59da66" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T04:19:32.028111Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T04:19:32.027749Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T04:19:32.032213Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T04:19:32.031764Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.862e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:32.033247&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:32.025385&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/jump-game/submissions/1281092917
def canJump(nums: list[int]) -> bool:
    """
    We can notice that if the latest good index was reachable, then every other good index beyond would
    have been reachable as well.

    On the contrary if the latest good index (nearest to current) was not reachable, then no index beyond would be reachable.

    Time: O(N), Space: O(1)
    """
    N = len(nums)
    good_idx: int = N - 1
    for i in range(N - 2, -1, -1):
        if i + nums[i] >= good_idx:
            good_idx = i

    return good_idx == 0

# Testing the solution
assert canJump([2,3,1,1,4]) == True
assert canJump([3,2,1,0,4]) == False
assert canJump([2,0,2,0,0]) == True
```

</div>

<div id="da43a335" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T04:19:32.037544Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T04:19:32.037113Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T04:19:32.041304Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T04:19:32.040867Z&quot;}"
papermill="{&quot;duration&quot;:7.419e-3,&quot;end_time&quot;:&quot;2024-06-08T04:19:32.042351&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T04:19:32.034932&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/jump-game/submissions/1281113037
def canJumpStriver(nums: list[int]) -> bool:
    """
    If there were no 0's we would always be able to reach the destination.
    In other cases it may or may not be possible.

    Time: O(N), Space: O(1)
    """
    N, max_idx = len(nums), 0
    for i in range(N):
        if i <= max_idx:
            max_idx = max(max_idx, nums[i] + i)
        else:
            return False

    return True

# Testing the solution
assert canJumpStriver([2,3,1,1,4]) == True
assert canJumpStriver([3,2,1,0,4]) == False
assert canJumpStriver([2,0,2,0,0]) == True
```

</div>
