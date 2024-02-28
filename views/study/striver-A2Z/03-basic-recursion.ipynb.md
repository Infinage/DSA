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
    version: 3.11.5
  nbformat: 4
  nbformat_minor: 5
  papermill:
    default_parameters: {}
    duration: 1.699773
    end_time: "2024-02-28T02:00:02.967318"
    environment_variables: {}
    input_path: 03-basic-recursion.ipynb
    output_path: 03-basic-recursion.ipynb
    parameters: {}
    start_time: "2024-02-28T02:00:01.267545"
    version: 2.4.0
---

<div id="f9f971fa" class="cell markdown"
papermill="{&quot;duration&quot;:8.317e-3,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.541390&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.533073&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=un6PLygfXrA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=8>

</div>

<div id="61aab27d" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.559259Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.558455Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.590438Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.588988Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.5777e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.594859&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.549082&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q1 - Print name, N times
def q1(name: str, N: int) -> None:
    if N == 0:
        return
    print(name)
    q1(name, N - 1)

q1("DSA", 5)
```

<div class="output stream stdout">

    DSA
    DSA
    DSA
    DSA
    DSA

</div>

</div>

<div id="f258baaf" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.604799Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.604431Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.610093Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.609301Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2693e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.612311&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.599618&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q2 - Print 1 - N
def q2(n: int, i: int = 1) -> None:
    if i > n:
        return
    else:
        print (i)
        q2(n, i + 1)

q2(5, 1)
```

<div class="output stream stdout">

    1
    2
    3
    4
    5

</div>

</div>

<div id="3667c0a6" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.622326Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.622072Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.626686Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.625922Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1795e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.628624&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.616829&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q3 - Print N - 1
def q3(n: int) -> None:
    if n == 0:
        return
    else:
        print(n)
        q3(n - 1)

q3(5)
```

<div class="output stream stdout">

    5
    4
    3
    2
    1

</div>

</div>

<div id="8768c1b1" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.637971Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.637727Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.642293Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.641570Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1031e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.644194&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.633163&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q4 - Print 1 - N by backtracking
def q4(n: int) -> None:
    if n == 0:
        return
    else:
        q4(n - 1)
        print (n)

q4(5)
```

<div class="output stream stdout">

    1
    2
    3
    4
    5

</div>

</div>

<div id="de4297f4" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.652793Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.652470Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.658113Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.657317Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1022e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.660046&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.649024&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q5 - Print N - 1 by backtracking
def q5(n: int, i: int = 1) -> None:
    if i > n:
        return
    else:
        q5(n, i + 1)
        print (i)

q5(5)
```

<div class="output stream stdout">

    5
    4
    3
    2
    1

</div>

</div>

<div id="c929e8e2" class="cell markdown"
papermill="{&quot;duration&quot;:2.789e-3,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.667446&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.664657&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=69ZCDFy-OUo&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=9>

</div>

<div id="f4694fdd" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.673800Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.673179Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.679955Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.679027Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2981e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.682785&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.669804&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q6 - Sum of first N numbers (modifided: of an array)
def q6_1(arr: list[int], n: int) -> int:
    "Time - O(N), Space - O(N^2)"
    if not arr or n == 0:
        return 0
    return arr[0] + q6_1(arr[1:], n - 1)

def q6_2(arr: list[int], n: int) -> int:
    "Time - O(N), Space - O(N)"
    arr_length = len(arr)
    def backtrack(i: int = 0):
        if i >= arr_length or i == n:
            return 0
        else:
            return arr[i] + backtrack(i + 1)
    return backtrack()

print(q6_1([1, 2, 3, 4], 2))
print(q6_2([1, 2, 3, 4], 2))
```

<div class="output stream stdout">

    3
    3

</div>

</div>

<div id="2ca73cfc" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.691035Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.690385Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.697981Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.697171Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.297e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.699912&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.686942&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q7 - Factorial of N
def q7(n: int) -> int:
    "Time - O(N), Space - O(N)"
    if n == 0:
        return 1
    else:
        return n * q7(n - 1)

q7(10)
```

<div class="output execute_result" execution_count="7">

    3628800

</div>

</div>

<div id="e1001c60" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.709184Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.708858Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.716230Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.715417Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3653e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.717856&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.704203&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q8 - Reverse an array
def q8_1(arr: list[int]) -> list[int]:
    "Time - O(N), Space - O(N^N)"
    if not arr:
        return []
    else:
        return q8_1(arr[1:]) + [arr[0]]

def q8_2(arr: list[int]) -> list[int]:
    "Time - O(N), Space - O(N)"
    N = len(arr)
    result: list[int] = []

    def backtrack(i: int = 0) -> None:
        if i == N:
            return
        backtrack(i + 1)
        result.append(arr[i])

    backtrack()
    return result

def q8_3(arr: list[int]) -> list[int]:
    "Time - O(N), Space - O(1) auxilary"
    def backtrack(left: int, right: int) -> None:
        if left > right:
            return
        backtrack(left + 1, right - 1)
        arr[left], arr[right] = arr[right], arr[left]

    backtrack(0, len(arr) - 1)
    return arr

print(q8_1([1, 2, 3]))
print(q8_2([1, 2, 3]))
print(q8_3([1, 2, 3]))
```

<div class="output stream stdout">

    [3, 2, 1]
    [3, 2, 1]
    [3, 2, 1]

</div>

</div>

<div id="8c445058" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.724488Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.724100Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.730361Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.729599Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1301e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.731893&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.720592&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q9 - Check if palindrome
def q9(s: str) -> bool:
    length = len(s)
    def backtrack(left: int, right: int) -> bool:
        if left > right:
            return True
        return s[left] == s[right] and backtrack(left + 1, right - 1)
    return backtrack(0, length - 1)

q9("racecar")
```

<div class="output execute_result" execution_count="9">

    True

</div>

</div>

<div id="e8beb5da" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T02:00:02.738710Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T02:00:02.738466Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T02:00:02.744499Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T02:00:02.743760Z&quot;}"
papermill="{&quot;duration&quot;:1.1316e-2,&quot;end_time&quot;:&quot;2024-02-28T02:00:02.746002&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T02:00:02.734686&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q10 - Fibonacci
def q10(n: int) -> int:
    """
    Time - O(2^N), Space - O(2^N).
    Every call branches 2 times. Nearly O(2^N) not exactly since each call f(n) = f(n-1) + f(n-2)
    If it had branched into: f(n) = f(n-1) + f(n-1) then it would be perfectly O(2^N)
    """
    if n <= 1:
        return 1
    return q10(n - 1) + q10(n - 2)

[q10(i) for i in range(10)]
```

<div class="output execute_result" execution_count="10">

    [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]

</div>

</div>
