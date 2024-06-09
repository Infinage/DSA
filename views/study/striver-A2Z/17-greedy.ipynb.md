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
    duration: 1.533128
    end_time: "2024-06-09T03:36:12.931759"
    environment_variables: {}
    input_path: study/striver-A2Z/17-greedy.ipynb
    output_path: study/striver-A2Z/17-greedy.ipynb
    parameters: {}
    start_time: "2024-06-09T03:36:11.398631"
    version: 2.6.0
---

<div id="76cb4635" class="cell markdown"
papermill="{&quot;duration&quot;:3.873e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.530455&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.526582&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Useful imports

</div>

<div id="d45ec848" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.538205Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.537822Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.543254Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.542742Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0531e-2,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.544284&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.533753&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import heapq
import bisect
import collections
import itertools
import functools
import math
```

</div>

<div id="a2f52f24" class="cell markdown"
papermill="{&quot;duration&quot;:3.017e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.550498&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.547481&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Assign cookies: <https://leetcode.com/problems/assign-cookies/> Video
Link: <https://youtu.be/DIX2p7vb9co?si=-lYoEBkNX6G40Tpo>

</div>

<div id="8016e3c9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.557733Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.557385Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.562340Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.561890Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.797e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.563391&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.553594&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.082e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.569509&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.566427&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest job first CPU scheduling Video Link:
<https://youtu.be/3-QbX1iDbXs?si=oh3KUu3zLd08uDZ7>

</div>

<div id="1e00764f" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.577435Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.577060Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.581068Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.580621Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.756e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.582143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.573387&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.098e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.588554&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.585456&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lemonade change:
<https://leetcode.com/problems/lemonade-change/description/> Video link:
<https://youtu.be/n_tmibEhO6Q?si=bqyD-xTjBPIG9scO>

</div>

<div id="726bd349" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.595734Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.595308Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.600115Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.599695Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.49e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.601133&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.591643&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.097e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.607424&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.604327&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Jump game: <https://leetcode.com/problems/jump-game/> Video Link:
<https://youtu.be/tZAa_jJ3SwQ?si=PUeiia1qBXmvfk_C>

</div>

<div id="d487decb" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.614980Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.614573Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.618927Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.618446Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.404e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.619962&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.610558&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.627294Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.626846Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.631003Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.630512Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.908e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.632021&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.623113&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.639541Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.639098Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.643591Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.643104Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.33e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.644583&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.635253&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="7d2a5ae9" class="cell markdown"
papermill="{&quot;duration&quot;:3.048e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.650769&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.647721&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Jump Game - II: <https://leetcode.com/problems/jump-game-ii/> Video
Link: <https://youtu.be/7SBVnw7GSTk?si=UDZojaM70TuG0XgY>

</div>

<div id="bcdd786f" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.657894Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.657556Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.661845Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.661324Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.133e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.662953&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.653820&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def jump2Recursive(nums: list[int]) -> int:
    @functools.cache
    def backtrack(i: int) -> int:
        if i == N - 1:
            return 0
        else:
            min_ = N
            for jump in range(nums[i]):
                min_ = min(min_, backtrack(i + jump + 1))
            return 1 + min_

    N = len(nums)
    return backtrack(0)

# Testing the solution
assert jump2Recursive([2,3,1,1,4]) == 2
assert jump2Recursive([2,3,0,1,4]) == 2
```

</div>

<div id="7b38a2b6" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.670083Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.669793Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.674160Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.673648Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.19e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.675263&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.666073&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/jump-game-ii/submissions/1281812619/
def jump2Tab(nums: list[int]) -> int:
    # Time: O(N ** 2), Space: O(N)
    N = len(nums)
    dp: list[int] = [N if i < N - 1 else 0 for i in range(N)]
    for i in range(N - 2, -1, -1):
        for j in range(i + 1, min(N, i + 1 + nums[i])):
            dp[i] = min(dp[i], 1 + dp[j])

    return dp[0]

# Testing the solution
assert jump2Tab([2,3,1,1,4]) == 2
assert jump2Tab([2,3,0,1,4]) == 2
```

</div>

<div id="7336f2b2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.682478Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.682145Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.686396Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.685930Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.121e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.687471&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.678350&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/jump-game-ii/submissions/1281839417
def jump2Striver(nums: list[int]) -> int:
    """
    Instead of iterating through all indices that we can jump to,
    we keep track of the range.
    For each range
        - Figure out the maximum idx we can jump to
        - jumps = jumps + 1
    Iterate until we reach the last index, ans would be the value of jumps variable

    Time: O(N), Space: O(1)
    """
    N = len(nums)
    jumps = l = r = 0
    while r < N - 1:
        farthest = 0
        for i in range(l, r + 1):
            farthest = max(farthest, i + nums[i])
        l, r, jumps = r + 1, farthest, jumps + 1

    return jumps

# Testing the solution
assert jump2Striver([2,3,1,1,4]) == 2
assert jump2Striver([2,3,0,1,4]) == 2
```

</div>

<div id="52b5429b" class="cell markdown"
papermill="{&quot;duration&quot;:3.081e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.693682&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.690601&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Job sequencing Problem:
<https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1>
Video Link: <https://youtu.be/QbwltemZbRg?si=R93V-44Jyr37Il4L>

</div>

<div id="c804e410" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.700925Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.700584Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.706502Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.705986Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0826e-2,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.707637&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.696811&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def jobScheduling(jobs: list[tuple[int, int, int]], N: int) -> tuple[int, int]:
    """
    Start with the jobs with highest profit, try to push the start time as close as possible to the deadline
    being super lazy about it.

    Time: O(N log N) + O(N x max deadline)
    Space: O(N)

    We can optimize the inner loop (deadline -> 0) further with the use of DSU (Disjoint set union)
    """
    jobs_start: set[int] = set()
    jobs_sorted: list[tuple[int, int]] = sorted(map(lambda x: (x[2], x[1]), jobs), reverse=True)
    job_count = total_profit = 0
    for profit, deadline in jobs_sorted:
        for start in range(deadline - 1, -1, -1):
            if start not in jobs_start:
                jobs_start.add(start)
                job_count, total_profit = job_count + 1, total_profit + profit
                break

    return job_count, total_profit

# Testing the solution
assert jobScheduling([(1,2,100),(2,1,19),(3,2,27),(4,1,25),(5,1,15)], 5) == (2, 127)
assert jobScheduling([(1,4,20),(2,1,10),(3,1,40),(4,1,30)], 5) == (2, 60)
assert jobScheduling([(1,4,50),(2,1,50)], 2) == (2, 100)
assert jobScheduling([(1,4,60),(2,1,50)], 2) == (2, 110)
```

</div>

<div id="2835d225" class="cell markdown"
papermill="{&quot;duration&quot;:3.083e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.713878&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.710795&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

N meetings in one room:
<https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1>
Video Link: <https://youtu.be/mKfhTotEguk?si=gTVT-RsSg0PR9RPP>

</div>

<div id="7fe0aed4" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.721161Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.720744Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.725971Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.725529Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.003e-2,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.727031&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.717001&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def maximumMeetings(N: int, start: list[int], end: list[int]) -> int:
    """
    Sort based on end time, we need to find meetings that finish sooner.
    Simply iterate through the sorted meeting in order and check if it is possible to host the meeting

    - It works because the earliest-ending meeting can't possibly cause more conflicts than any other choice
    - It leaves the largest amount of un-interrupted time remaining for other intervals to be chosen from

    Time: O(N log N)
    Space: O(N)
    """

    # Sort meeting based on the end time
    meetings: list[tuple[int, int, int]] = [(start[i], end[i], i) for i in range(N)]
    meetings.sort(key=lambda x: x[1])

    order: list[int] = []
    meeting_count = free_at = 0
    for stime, etime, idx in meetings:
        if stime > free_at:
            order.append(idx)
            meeting_count, free_at = meeting_count + 1, etime

    # If needed, to return the order in which the meetings could be conducted,
    # we can make use of the `meeting_count` variable

    return meeting_count

# Testing the solution
assert maximumMeetings(6, [1,3,0,5,8,5], [2,4,6,7,9,9]) == 4
assert maximumMeetings(3, [1,4,6], [5,6,10]) == 2
```

</div>

<div id="68f75f03" class="cell markdown"
papermill="{&quot;duration&quot;:3.177e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.733353&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.730176&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Non overlapping intervals:
<https://leetcode.com/problems/non-overlapping-intervals/> Video Link:
<https://youtu.be/HDHQ8lAWakY?si=s1_2CwOoEBx5LSOQ>

</div>

<div id="7842ff87" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.740732Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.740348Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.745905Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.745460Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.04e-2,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.746972&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.736572&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/non-overlapping-intervals/submissions/1282204448
def eraseOverlapIntervals(intervals: list[list[int]]) -> int:
    # Sort intervals based on start time
    intervals.sort(key=lambda x: (x[1], x[0]))

    print(intervals)

    curr_time, skip = intervals[0][0], 0
    for stime, etime in intervals:
        if curr_time <= stime:
            curr_time = etime
        else:
            skip += 1

    return skip

# Testing the solution
assert eraseOverlapIntervals([[1,2],[2,3],[3,4],[1,3]]) == 1
assert eraseOverlapIntervals([[1,2],[1,2],[1,2]]) == 2
assert eraseOverlapIntervals([[1,2],[2,3]]) == 0
assert eraseOverlapIntervals([[-10,20],[8,12],[3,4],[5,6],[10,12],[15,20]]) == 2
```

<div class="output stream stdout">

    [[1, 2], [1, 3], [2, 3], [3, 4]]
    [[1, 2], [1, 2], [1, 2]]
    [[1, 2], [2, 3]]
    [[3, 4], [5, 6], [8, 12], [10, 12], [-10, 20], [15, 20]]

</div>

</div>

<div id="f4ede58d" class="cell markdown"
papermill="{&quot;duration&quot;:3.171e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.753388&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.750217&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Insert intervals:
<https://leetcode.com/problems/insert-interval/description/> Video Link:
<https://youtu.be/xxRE-46OCC8?si=kKQ10RKueMFdlR-e>

</div>

<div id="c09c42a9" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.760766Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.760438Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.767065Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.766602Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1472e-2,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.768076&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.756604&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/insert-interval/submissions/1282223708/
def insertIntervals(intervals: list[list[int]], newInterval: list[int]) -> list[list[int]]:
    # Time: O(N), Space: O(N)
    N = len(intervals)

    # Insert intervals here post merge
    merged: list[list[int]] = []

    # Travel until we are at a pos to insert newInterval
    i = 0
    while i < N and intervals[i][0] < newInterval[0]:
        merged.append(intervals[i])
        i += 1

    # Insert the new interval or merge it with prev interval
    if merged and merged[-1][1] >= newInterval[0]:
        merged[-1] = [merged[-1][0], max(merged[-1][1], newInterval[1])]
    else:
        merged.append(newInterval)

    # Continue merging and then inserting until all intervals are done
    while i < N:
        if merged[-1][1] >= intervals[i][0]:
            merged[-1] = [merged[-1][0], max(merged[-1][1], intervals[i][1])]
        else:
            merged.append(intervals[i])
        i += 1

    return merged

# Testing the solution
assert insertIntervals([[1,3],[6,9]], [2,5]) == [[1,5],[6,9]]
assert insertIntervals([[1,2],[3,5],[6,7],[8,10],[12,16]], [3,8]) == [[1,2],[3,10],[12,16]]
assert insertIntervals([[1,2],[3,5],[6,7],[8,10],[12,16]], [11,11]) == [[1,2],[3,5],[6,7],[8,10],[11,11],[12,16]]
```

</div>

<div id="c948b4ef" class="cell markdown"
papermill="{&quot;duration&quot;:3.166e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.774491&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.771325&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Minimum number of platforms required in a railway station:
<https://www.geeksforgeeks.org/problems/minimum-platforms-1587115620/1>
Video link: <https://youtu.be/AsGzwR_FWok?si=Nt5CMUPctV39JtSd>

</div>

<div id="35d5bae3" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.781909Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.781593Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.786369Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.785936Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.664e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.787412&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.777748&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimumPlatformBrute1(N: int, arr: list[int], dep: list[int]) -> int:
    # Time: O(N x 2400) + O(2400), Space: O(2400)
    platform: list[int] = [0 for i in range(2400)]
    for stime, etime in zip(arr, dep):
        for i in range(stime, etime + 1):
            platform[i] += 1

    return max(platform)

# Testing the soltution
assert minimumPlatformBrute1(3, [900, 1100, 1235], [1000, 1200, 1240]) == 1
assert minimumPlatformBrute1(3, [900, 930, 1015], [1000, 1030, 1100]) == 2
assert minimumPlatformBrute1(3, [900, 930, 1000], [1000, 1030, 1100]) == 3
```

</div>

<div id="d0510feb" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.794712Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.794512Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.799207Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.798760Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.584e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.800231&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.790647&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimumPlatformBrute2(N: int, arr: list[int], dep: list[int]) -> int:
    max_overlap = 0
    for i in range(N):
        overlap, istart, iend = 0, arr[i], dep[i]
        for j in range(i + 1, N):
            jstart, jend = arr[j], dep[j]
            if jstart <= iend:
                overlap += 1
        max_overlap = max(max_overlap, overlap)

    return max_overlap + 1

# Testing the soltution
assert minimumPlatformBrute2(3, [900, 1100, 1235], [1000, 1200, 1240]) == 1
assert minimumPlatformBrute2(3, [900, 930, 1015], [1000, 1030, 1100]) == 2
assert minimumPlatformBrute2(3, [900, 930, 1000], [1000, 1030, 1100]) == 3
```

</div>

<div id="8f9a4262" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T03:36:12.807767Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T03:36:12.807433Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T03:36:12.812180Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T03:36:12.811753Z&quot;}"
papermill="{&quot;duration&quot;:9.656e-3,&quot;end_time&quot;:&quot;2024-06-09T03:36:12.813186&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T03:36:12.803530&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def minimumPlatform(N: int, arr: list[int], dep: list[int]) -> int:
    """
    Brilliant logic from Striver:
        Stand and observe the station as the time passes by

    Time: O(N log N), Space: O(1)
    """
    # Sort the events based on time, imagine an observer standing by and watching the events unfolding
    arr.sort()
    dep.sort()

    # Count the overlaps
    max_overlap = overlap = arr_idx = dep_idx = 0
    while arr_idx < N or dep_idx < N:
        if dep_idx >= N or (arr_idx < N and arr[arr_idx] <= dep[dep_idx]):
            overlap, arr_idx = overlap + 1, arr_idx + 1
        else:
            overlap, dep_idx = overlap - 1, dep_idx + 1
        max_overlap = max(max_overlap, overlap)

    return max_overlap

# Testing the soltution
assert minimumPlatform(3, [900, 1100, 1235], [1000, 1200, 1240]) == 1
assert minimumPlatform(3, [900, 930, 1015], [1000, 1030, 1100]) == 2
assert minimumPlatform(3, [900, 930, 1000], [1000, 1030, 1100]) == 3
```

</div>
