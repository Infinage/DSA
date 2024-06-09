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
    duration: 1.785151
    end_time: "2024-06-09T12:52:35.240296"
    environment_variables: {}
    input_path: study/striver-A2Z/17-greedy.ipynb
    output_path: study/striver-A2Z/17-greedy.ipynb
    parameters: {}
    start_time: "2024-06-09T12:52:33.455145"
    version: 2.6.0
---

<div id="76cb4635" class="cell markdown"
papermill="{&quot;duration&quot;:5.146e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.600015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.594869&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Useful imports

</div>

<div id="d45ec848" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.610380Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.609953Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.615383Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.614945Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1948e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.616534&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.604586&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.324e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.625359&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.621035&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Assign cookies: <https://leetcode.com/problems/assign-cookies/> Video
Link: <https://youtu.be/DIX2p7vb9co?si=-lYoEBkNX6G40Tpo>

</div>

<div id="8016e3c9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.636225Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.635968Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.641212Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.640744Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1768e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.642328&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.630560&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.271e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.651107&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.646836&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest job first CPU scheduling Video Link:
<https://youtu.be/3-QbX1iDbXs?si=oh3KUu3zLd08uDZ7>

</div>

<div id="1e00764f" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.661256Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.660759Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.665218Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.664758Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0885e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.666329&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.655444&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.289e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.675183&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.670894&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lemonade change:
<https://leetcode.com/problems/lemonade-change/description/> Video link:
<https://youtu.be/n_tmibEhO6Q?si=bqyD-xTjBPIG9scO>

</div>

<div id="726bd349" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.685330Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.684838Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.689802Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.689349Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1343e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.690847&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.679504&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.307e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.699577&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.695270&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Jump game: <https://leetcode.com/problems/jump-game/> Video Link:
<https://youtu.be/tZAa_jJ3SwQ?si=PUeiia1qBXmvfk_C>

</div>

<div id="d487decb" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.709459Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.709010Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.713505Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.713059Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0786e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.714581&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.703795&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.724749Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.724321Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.728653Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.728191Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0652e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.729740&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.719088&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.739382Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.739189Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.743539Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.743094Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0611e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.744679&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.734068&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.172e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.753187&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.749015&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Jump Game - II: <https://leetcode.com/problems/jump-game-ii/> Video
Link: <https://youtu.be/7SBVnw7GSTk?si=UDZojaM70TuG0XgY>

</div>

<div id="bcdd786f" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.762955Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.762495Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.767001Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.766559Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0637e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.768086&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.757449&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.777962Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.777499Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.782115Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.781665Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0796e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.783211&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.772415&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.793215Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.792724Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.797129Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.796694Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0547e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.798185&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.787638&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.341e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.807054&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.802713&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Job sequencing Problem:
<https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1>
Video Link: <https://youtu.be/QbwltemZbRg?si=R93V-44Jyr37Il4L>

</div>

<div id="c804e410" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.817166Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.816657Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.823007Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.822580Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2789e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.824149&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.811360&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.341e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.833121&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.828780&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

N meetings in one room:
<https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1>
Video Link: <https://youtu.be/mKfhTotEguk?si=gTVT-RsSg0PR9RPP>

</div>

<div id="7fe0aed4" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.843049Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.842576Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.848049Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.847458Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1687e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.849117&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.837430&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.4e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.857885&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.853485&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Non overlapping intervals:
<https://leetcode.com/problems/non-overlapping-intervals/> Video Link:
<https://youtu.be/HDHQ8lAWakY?si=s1_2CwOoEBx5LSOQ>

</div>

<div id="7842ff87" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.867878Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.867309Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.873219Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.872747Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.212e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.874294&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.862174&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.424e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.883343&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.878919&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Insert intervals:
<https://leetcode.com/problems/insert-interval/description/> Video Link:
<https://youtu.be/xxRE-46OCC8?si=kKQ10RKueMFdlR-e>

</div>

<div id="c09c42a9" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.893502Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.892987Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.899883Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.899403Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3296e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.900961&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.887665&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.35e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.909864&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.905514&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Minimum number of platforms required in a railway station:
<https://www.geeksforgeeks.org/problems/minimum-platforms-1587115620/1>
Video link: <https://youtu.be/AsGzwR_FWok?si=Nt5CMUPctV39JtSd>

</div>

<div id="35d5bae3" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.919944Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.919498Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.924620Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.924083Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1379e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.925682&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.914303&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.935913Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.935640Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.940366Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.939857Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1296e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.941501&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.930205&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.951732Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.951258Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.956271Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.955722Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1361e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.957424&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.946063&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="f8141934" class="cell markdown"
papermill="{&quot;duration&quot;:4.331e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.966348&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.962017&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Valid Parenthesis String:
<https://leetcode.com/problems/valid-parenthesis-string/> Video Link:
<https://youtu.be/cHT6sG_hUZI?si=7S_ZYJK-16nXDsLR>

</div>

<div id="27d2375c" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.976288Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.976024Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.981384Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.980822Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1857e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.982548&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.970691&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def checkValidStringBrute(s: str) -> bool:
    @functools.cache
    def backtrack(i: int, brackets: int) -> bool:
        if brackets < 0:
            return False
        elif i == N:
            return brackets == 0
        elif s[i] == "(":
            return backtrack(i + 1, brackets + 1)
        elif s[i] == ")":
            return backtrack(i + 1, brackets - 1)
        else:
            return backtrack(i + 1, brackets) or backtrack(i + 1, brackets - 1) or backtrack(i + 1, brackets + 1)

    N = len(s)
    return backtrack(0, 0)

# Testing the solution
for s, result in [
        ("()", True), ("(*)", True), ("(*))", True), ("(*()", True), (")*", False),
        ("(**", True), ("*", True), ("(**)()(((*))*))", True), ("(**(", False)
    ]:
    assert checkValidStringBrute(s) == result, f"failed for {s}"
```

</div>

<div id="d04d4889" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:34.992916Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:34.992461Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:34.998306Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:34.997860Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2227e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:34.999393&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:34.987166&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def checkValidStringBetter(s: str) -> bool:
    """
    Tabulating the backtracking approach to bring down log(N) portion of runtime

    Time: O(N ** 2), Space: O(N ** 2)
    """

    N = len(s)
    dp: list[list[bool]] = [[True if i == N and j == 0 else False for j in range(N + 1)] for i in range(N + 1)]
    for i in range(N - 1, -1, -1):
        for j in range(N - 1, -1, -1):
            if s[i] == "(":
                dp[i][j] = dp[i + 1][j + 1]
            elif s[i] == ")":
                dp[i][j] = dp[i + 1][j - 1]
            else:
                dp[i][j] = dp[i + 1][j] or dp[i + 1][j - 1] or dp[i + 1][j + 1]

    return dp[0][0]

# Testing the solution
for s, result in [
        ("()", True), ("(*)", True), ("(*))", True), ("(*()", True), (")*", False),
        ("(**", True), ("*", True), ("(**)()(((*))*))", True), ("(**(", False)
    ]:
    assert checkValidStringBetter(s) == result, f"failed for {s}"
```

</div>

<div id="0f4dbcad" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:35.009813Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:35.009333Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:35.014724Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:35.014212Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1625e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:35.015776&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:35.004151&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/valid-parenthesis-string/submissions/1282562888/
def checkValidStringSpaceOptimized(s: str) -> bool:
    """
    Time: O(N ** 2), Space: O(N)
    """
    N = len(s)
    dp: list[bool] = [True if j == 0 else False for j in range(N + 1)]
    for i in range(N - 1, -1, -1):
        prev_dp: list[bool] = list(dp)
        for j in range(N - 1, -1, -1):
            if s[i] == "(":
                dp[j] = prev_dp[j + 1]
            elif s[i] == ")":
                dp[j] = prev_dp[j - 1]
            else:
                dp[j] = prev_dp[j] or prev_dp[j - 1] or prev_dp[j + 1]

    return dp[0]

# Testing the solution
for s, result in [
        ("()", True), ("(*)", True), ("(*))", True), ("(*()", True), (")*", False),
        ("(**", True), ("*", True), ("(**)()(((*))*))", True), ("(**(", False)
    ]:
    assert checkValidStringSpaceOptimized(s) == result, f"failed for {s}"
```

</div>

<div id="08fd566b" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:35.026337Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:35.026086Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:35.030889Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:35.030352Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1579e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:35.031954&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:35.020375&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/valid-parenthesis-string/submissions/1282590335
def checkValidString(s: str) -> bool:
    """
    We still try out all possibilties, instead of carrying a count of brackets we carry
    a range.

    Time: O(N), Space: O(1)
    """
    low = high = 0
    for ch in s:
        if ch == "(":
            low, high = low + 1, high + 1
        elif ch == ")":
            low, high = low - 1, high - 1
        else:
            low, high = low - 1, high + 1

        if low < 0:
            low = 0
        if high < 0:
            return False

    return low == 0

# Testing the solution
for s, result in [
        ("()", True), ("(*)", True), ("(*))", True), ("(*()", True), (")*", False),
        ("(**", True), ("*", True), ("(**)()(((*))*))", True), ("(**(", False)
    ]:
    assert checkValidString(s) == result, f"failed for {s}"
```

</div>

<div id="79e48339" class="cell markdown"
papermill="{&quot;duration&quot;:4.548e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:35.041288&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:35.036740&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Fractional Knapsack:
<https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1>
Video Link: <https://youtu.be/1ibsQrnuEEg?si=nTPVv4QkGEXUTndS>

</div>

<div id="df6e8d1f" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:35.051545Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:35.051188Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:35.056416Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:35.055855Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1733e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:35.057535&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:35.045802&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def fractionalknapsack(capacity: int, values: list[float], weights: list[int], N: int) -> float:
    """
    Time: O(N log N), Space: O(N)
    """
    # We use the unit rate to pick the best possible item to pick
    rates: list[tuple[float, int]] = []
    for i in range(N):
        rates.append((values[i] / weights[i], weights[i]))
    rates.sort(reverse=True)

    # Greedily fill in as much as possible
    total = 0.
    idx = 0
    while idx < N:
        units = min(capacity, rates[idx][1])
        total += rates[idx][0] * units
        capacity -= units
        idx += 1
        if capacity == 0:
            break

    return total

# Testing the solution
assert fractionalknapsack(50, [60,100,120], [10,20,30], 3) == 240.
assert fractionalknapsack(50, [60,100], [10,20], 2) == 160.
```

</div>

<div id="13750c04" class="cell markdown"
papermill="{&quot;duration&quot;:4.521e-3,&quot;end_time&quot;:&quot;2024-06-09T12:52:35.066701&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:35.062180&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Candy: <https://leetcode.com/problems/candy/> Video link:
<https://youtu.be/IIqVFvKE6RY?si=tMFSEL4aw1g2VSc5>

</div>

<div id="8bee261e" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:35.076904Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:35.076666Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:35.083371Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:35.082829Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.334e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:35.084494&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:35.071154&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def candy(ratings: list[int]) -> int:
    """
    Start with kids having lowest ratings. Assign them 1 candy and try to move left/right.

    If neighbouring kid has a higher rating, we need to give them atleast 1 candy more than what current kid has.
    If neighbouring kid has a lower rating, we could assign them the lowest possible as long as they are isolated* (check if they are untouched previously)

    Time: O(N log N), Space: O(N)
    """
    N, min_rating = len(ratings), min(ratings)
    candies: list[int] = [-1 for i in range(N)]
    heap: list[tuple[int, int]] = []
    for i in range(N):
        if ratings[i] == min_rating:
            heap.append((1, i))

    while heap:
        count, idx = heapq.heappop(heap)
        candies[idx] = count

        if idx - 1 >= 0:
            # Neighbour has better rating and lower number of candies, update ->
            if ratings[idx - 1] > ratings[idx] and candies[idx - 1] <= candies[idx]:
                heapq.heappush(heap, (count + 1, idx - 1))

            # Try to sneakily assign the lowest possible candy, if they are isolated (untouched previously)
            elif candies[idx - 1] == -1:
                heapq.heappush(heap, (1, idx - 1))

        if idx + 1 < N:
            # Neighbour has better rating and lower number of candies, update ->
            if ratings[idx + 1] > ratings[idx] and candies[idx + 1] <= candies[idx]:
                heapq.heappush(heap, (count + 1, idx + 1))

            # Try to sneakily assign the lowest possible candy, if they are isolated (untouched previously)
            elif candies[idx + 1] == -1:
                heapq.heappush(heap, (1, idx + 1))

    return sum(candies)

# Testing the solution
assert candy([1,0,2]) == 5
assert candy([1,2,2]) == 4
assert candy([3,2,1]) == 6
assert candy([1,3,4,5,2]) == 11
```

</div>

<div id="6955d618" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:35.095225Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:35.094780Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:35.100304Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:35.099751Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2521e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:35.101846&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:35.089325&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/candy/submissions/1282748617
def candyStriverBrute(ratings: list[int]) -> int:
    # Time: O(N), Space: O(N)
    N = len(ratings)

    # Solve worrying only about the left neighbours
    left: list[int] = []
    for i in range(N):
        if i == 0 or ratings[i] <= ratings[i - 1]:
            left.append(1)
        else:
            left.append(left[-1] + 1)

    # Solve worrying only about the right neighbours
    right: list[int] = []
    for i in range(N - 1, -1, -1):
        if i == N - 1 or ratings[i] <= ratings[i + 1]:
            right.append(1)
        else:
            right.append(right[-1] + 1)
    right.reverse()

    # The candies assigned must satisfy both left and right, hence max
    total = 0
    for i in range(N):
        total += max(left[i], right[i])
    return total

# Testing the solution
assert candyStriverBrute([1,0,2]) == 5
assert candyStriverBrute([1,2,2]) == 4
assert candyStriverBrute([3,2,1]) == 6
assert candyStriverBrute([1,3,4,5,2]) == 11
```

</div>

<div id="cf809a5f" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-09T12:52:35.114547Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-09T12:52:35.114008Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-09T12:52:35.119300Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-09T12:52:35.118757Z&quot;}"
papermill="{&quot;duration&quot;:1.2005e-2,&quot;end_time&quot;:&quot;2024-06-09T12:52:35.120481&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-09T12:52:35.108476&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/candy/submissions/1282800027/
def candyStriver(ratings: list[int]) -> int:
    """
    Won't be able to think this solution on our own, need some prior insights
    Visualize ratings in terms of slope - peaks and troughs

    Code shamelessly copied from Striver's logic :O
    """
    N = len(ratings)
    total = i = 1
    while i < N:
        if i == 0 or ratings[i] == ratings[i - 1]:
            total, i = total + 1, i + 1
        else:
            peak = 1
            while i < N and ratings[i] > ratings[i - 1]:
                peak += 1
                total, i = total + peak, i + 1

            down = 1
            while i < N and ratings[i] < ratings[i - 1]:
                total += down
                down, i = down + 1, i + 1

            if down > peak:
                total += down - peak

    return total

# Testing the solution
assert candyStriver([1,0,2]) == 5
assert candyStriver([1,2,2]) == 4
assert candyStriver([3,2,1]) == 6
assert candyStriver([1,3,4,5,2]) == 11
```

</div>
