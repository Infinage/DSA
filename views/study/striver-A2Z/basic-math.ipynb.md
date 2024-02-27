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
    duration: 2.080938
    end_time: "2024-02-27T03:01:45.189263"
    environment_variables: {}
    input_path: basic-math.ipynb
    output_path: basic-math.ipynb
    parameters: {}
    start_time: "2024-02-27T03:01:43.108325"
    version: 2.4.0
---

<div id="7a3eac84" class="cell markdown"
papermill="{&quot;duration&quot;:5.821e-3,&quot;end_time&quot;:&quot;2024-02-27T03:01:44.556207&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-27T03:01:44.550386&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=tNm_NNSB3_w&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=://www.youtube.com/watch?v=1xNbjMdbjug&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=6>

</div>

<div id="27c2f0df" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-27T03:01:44.570558Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-27T03:01:44.569679Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-27T03:01:44.594624Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-27T03:01:44.591066Z&quot;}"
papermill="{&quot;duration&quot;:3.7002e-2,&quot;end_time&quot;:&quot;2024-02-27T03:01:44.598834&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-27T03:01:44.561832&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Some necessary imports
import math
```

</div>

<div id="48b302bb" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-27T03:01:44.624360Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-27T03:01:44.622310Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-27T03:01:44.643886Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-27T03:01:44.641476Z&quot;}"
lines_to_next_cell="2"
papermill="{&quot;duration&quot;:4.3409e-2,&quot;end_time&quot;:&quot;2024-02-27T03:01:44.647294&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-27T03:01:44.603885&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q1 - Count digits
N = N_ = 123213121231231231221323

# Counting digits in O(log10(N))
# Log10(N) because everytime N is divided by 10

# LogM(N) if N is divided by M everytime
count = 0
while N_ > 0:
    N_ = N_ // 10
    count += 1
print(count)

# Count digits in O(1)
print(int(math.log10(N) + 1))
```

<div class="output stream stdout">

    24
    24

</div>

</div>

<div id="228219f8" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-27T03:01:44.655418Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-27T03:01:44.654672Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-27T03:01:44.662241Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-27T03:01:44.660544Z&quot;}"
papermill="{&quot;duration&quot;:1.4812e-2,&quot;end_time&quot;:&quot;2024-02-27T03:01:44.665190&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-27T03:01:44.650378&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q2 - Reverse a number
N = 1230
rev = 0
while N > 0:
    rev = (rev * 10) + (N % 10)
    N //= 10
print(rev)
```

<div class="output stream stdout">

    321

</div>

</div>

<div id="50d26615" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-27T03:01:44.673875Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-27T03:01:44.672946Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-27T03:01:44.680976Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-27T03:01:44.679116Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.58e-2,&quot;end_time&quot;:&quot;2024-02-27T03:01:44.683884&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-27T03:01:44.668084&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q3 - Palindrome
N_ = N = 10201
rev = 0
while N_ > 0:
    rev = (rev * 10) + (N_ % 10)
    N_ //= 10
print(rev == N)
```

<div class="output stream stdout">

    True

</div>

</div>

<div id="7939a9d7" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-27T03:01:44.692009Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-27T03:01:44.691610Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-27T03:01:44.702612Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-27T03:01:44.700614Z&quot;}"
papermill="{&quot;duration&quot;:1.884e-2,&quot;end_time&quot;:&quot;2024-02-27T03:01:44.705246&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-27T03:01:44.686406&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q4 - GCD
def gcd(a: int, b: int) -> int:
    "O(log(min(a, b))"
    while a > 0 and b > 0:
        max_, min_ = max(a, b), min(a, b)
        a, b = max_ % min_, min_
    return max(a, b)
print(gcd(52, 24))
```

<div class="output stream stdout">

    4

</div>

</div>

<div id="a1ad42ba" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-27T03:01:44.714477Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-27T03:01:44.713143Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-27T03:01:44.721347Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-27T03:01:44.719559Z&quot;}"
papermill="{&quot;duration&quot;:1.6255e-2,&quot;end_time&quot;:&quot;2024-02-27T03:01:44.724137&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-27T03:01:44.707882&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q5 - Armstrong Numbers
N_ = N = 371
acc = 0
while N_ > 0:
    acc += (N_ % 10) ** 3
    N_ //= 10
print(acc == N)
```

<div class="output stream stdout">

    True

</div>

</div>

<div id="f64a952c" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-27T03:01:44.733727Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-27T03:01:44.732893Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-27T03:01:44.740850Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-27T03:01:44.739323Z&quot;}"
papermill="{&quot;duration&quot;:1.5358e-2,&quot;end_time&quot;:&quot;2024-02-27T03:01:44.743236&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-27T03:01:44.727878&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q6 - Print all divisors
# O(sqrt(N) x log(sqrt(N)))
N = 36
i = 1
result = set()
while i*i <= N:
    if N % i == 0:
        result.add(i)
        result.add(N // i)
    i += 1
print(sorted(result))
```

<div class="output stream stdout">

    [1, 2, 3, 4, 6, 9, 12, 18, 36]

</div>

</div>

<div id="fb3d2c16" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-27T03:01:44.752215Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-27T03:01:44.751811Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-27T03:01:44.759199Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-27T03:01:44.757383Z&quot;}"
papermill="{&quot;duration&quot;:1.5464e-2,&quot;end_time&quot;:&quot;2024-02-27T03:01:44.761574&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-27T03:01:44.746110&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Q7 - Prime
N = 13
i = 2
while i * i <= N:
    if N % i == 0:
        print("False")
        break
    i += 1
else:
    print("True")
```

<div class="output stream stdout">

    True

</div>

</div>
