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
    duration: 1.551354
    end_time: "2024-02-29T03:17:21.451642"
    environment_variables: {}
    input_path: 04-basic-hashing.ipynb
    output_path: 04-basic-hashing.ipynb
    parameters: {}
    start_time: "2024-02-29T03:17:19.900288"
    version: 2.4.0
---

<div id="624ef24f" class="cell markdown"
papermill="{&quot;duration&quot;:9.238e-3,&quot;end_time&quot;:&quot;2024-02-29T03:17:21.149501&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:21.140263&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Video Link: <https://www.youtube.com/watch?v=KEs5UyBJ39g&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=12>

</div>

<div id="c053fc4c" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-29T03:17:21.170818Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-29T03:17:21.169903Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-29T03:17:21.189670Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-29T03:17:21.188527Z&quot;}"
papermill="{&quot;duration&quot;:3.1429e-2,&quot;end_time&quot;:&quot;2024-02-29T03:17:21.191553&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:21.160124&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Necessary imports
import math
```

</div>

<div id="cd24a3f4" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-29T03:17:21.196256Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-29T03:17:21.195438Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-29T03:17:21.200905Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-29T03:17:21.200141Z&quot;}"
papermill="{&quot;duration&quot;:9.646e-3,&quot;end_time&quot;:&quot;2024-02-29T03:17:21.202656&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:21.193010&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Count the numbers in an arrray
arr: list[int] = [1, 2, 3, 3, 1, 2, 2, 12]
queries: list[int] = [1, 12, 2]
hm: dict[int, int] = dict()
for ch in arr:
    hm[ch] = hm.get(ch, 0) + 1
for ch in queries:
    print(hm[ch])
```

<div class="output stream stdout">

    2
    1
    3

</div>

</div>

<div id="d92c2ebb" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-29T03:17:21.206943Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-29T03:17:21.206531Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-29T03:17:21.212931Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-29T03:17:21.212164Z&quot;}"
papermill="{&quot;duration&quot;:1.0682e-2,&quot;end_time&quot;:&quot;2024-02-29T03:17:21.214796&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:21.204114&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Count characters
temp = "abcasdadbadasdasd"
queries: list[str] = ['a', 's']
hs: list[int] = [0] * 26
for ch in temp:
    curr = ord('a') - ord(ch)
    hs[curr] = hs[curr] + 1
for ch in queries:
    curr = ord('a') - ord(ch)
    print (hs[curr])
```

<div class="output stream stdout">

    6
    3

</div>

</div>

<div id="985369fd" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-29T03:17:21.221694Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-29T03:17:21.220996Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-29T03:17:21.226991Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-29T03:17:21.226256Z&quot;}"
papermill="{&quot;duration&quot;:1.1382e-2,&quot;end_time&quot;:&quot;2024-02-29T03:17:21.228897&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:21.217515&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Highest and lowest frequency element
arr: list[int] = [10,5,10,15,10,5]
hm: dict[int, int] = dict()
for ch in arr:
    hm[ch] = hm.get(ch, 0) + 1
max_ = None, -math.inf
min_ = None, math.inf
for ch, freq in hm.items():
    if freq > max_[1]:
        max_ = ch, freq
    if freq < min_[1]:
        min_ = ch, freq
print(max_[0], min_[0])
```

<div class="output stream stdout">

    10 15

</div>

</div>
