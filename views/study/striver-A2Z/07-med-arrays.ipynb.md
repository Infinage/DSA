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
    version: 3.10.13
  nbformat: 4
  nbformat_minor: 5
  papermill:
    default_parameters: {}
    duration: 2.621512
    end_time: "2024-03-04T02:35:11.908650"
    environment_variables: {}
    input_path: 07-med-arrays.ipynb
    output_path: 07-med-arrays.ipynb
    parameters: {}
    start_time: "2024-03-04T02:35:09.287138"
    version: 2.4.0
---

<div id="21da8de7" class="cell markdown"
papermill="{&quot;duration&quot;:5.0e-3,&quot;end_time&quot;:&quot;2024-03-04T02:35:11.356930&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:11.351930&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=UXDSeD9mN-k&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=22>

</div>

<div id="2f902cd9" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:11.373846Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:11.372079Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:11.405259Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:11.402954Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.7274e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:11.409684&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:11.362410&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Two Sum - Brute Force
def two_sum_brute(arr_: list[int], target: int) -> tuple[int, int]:
    "Time complexity - O(N^2)"
    N = len(arr_)
    for i in range(N - 1):
        for j in range(i + 1, N):
            if arr_[i] + arr_[j] == target:
                return i, j
    else:
        return -1, -1

two_sum_brute([2, 6, 5, 8, 11], 14)
```

<div class="output execute_result" execution_count="1">

    (1, 3)

</div>

</div>

<div id="f0629198" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:11.418274Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:11.416980Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:11.434027Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:11.431901Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7035e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:11.438819&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:11.411784&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Two sum - better
def two_sum_better(arr_: list[int], target: int) -> tuple[int, int]:
    "Time compelexity - O(N), Space - O(N)"
    N = len(arr_)
    dict_: dict[int, int] = {}
    for i in range(N):
        if target - arr_[i] in dict_:
            result = i, dict_[target - arr_[i]]
            return min(result), max(result)
        dict_[arr_[i]] = i
    return -1, -1

two_sum_better([2, 6, 5, 8, 11], 14)
```

<div class="output execute_result" execution_count="2">

    (1, 3)

</div>

</div>

<div id="e337b5a1" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-04T02:35:11.449106Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-04T02:35:11.447930Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-04T02:35:11.466100Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-04T02:35:11.463757Z&quot;}"
papermill="{&quot;duration&quot;:2.8776e-2,&quot;end_time&quot;:&quot;2024-03-04T02:35:11.470369&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-04T02:35:11.441593&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Two sum - Optimal
def two_sum_optimal(arr_: list[int], target: int) -> bool:
    "Time - O(N log N), Space - O(1)"
    arr_.sort()
    N = len(arr_)
    i, j = 0, N - 1
    while i < j and j < N:
        sum_ = arr_[i] + arr_[j]
        if sum_ == target:
            return True
        elif sum_ < target:
            i += 1
        else:
            j -= 1
    return False

two_sum_optimal([2, 6, 5, 8, 11], 14)
```

<div class="output execute_result" execution_count="3">

    True

</div>

</div>
