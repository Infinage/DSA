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
    duration: 1.283251
    end_time: "2024-06-07T18:56:02.906852"
    environment_variables: {}
    input_path: study/striver-A2Z/17-greedy.ipynb
    output_path: study/striver-A2Z/17-greedy.ipynb
    parameters: {}
    start_time: "2024-06-07T18:56:01.623601"
    version: 2.6.0
---

<div id="a2f52f24" class="cell markdown"
papermill="{&quot;duration&quot;:1.33e-3,&quot;end_time&quot;:&quot;2024-06-07T18:56:02.779278&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:56:02.777948&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Assign cookies: <https://leetcode.com/problems/assign-cookies/> Video
Link: <https://youtu.be/DIX2p7vb9co?si=-lYoEBkNX6G40Tpo>

</div>

<div id="8016e3c9" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-07T18:56:02.782890Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-07T18:56:02.782497Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-07T18:56:02.790046Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-07T18:56:02.789640Z&quot;}"
papermill="{&quot;duration&quot;:1.1029e-2,&quot;end_time&quot;:&quot;2024-06-07T18:56:02.791161&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-07T18:56:02.780132&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
