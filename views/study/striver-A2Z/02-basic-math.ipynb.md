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
    duration: 1.614529
    end_time: "2024-02-28T01:59:56.573814"
    environment_variables: {}
    input_path: 02-basic-math.ipynb
    output_path: 02-basic-math.ipynb
    parameters: {}
    start_time: "2024-02-28T01:59:54.959285"
    version: 2.4.0
---

<div id="7a3eac84" class="cell markdown"
papermill="{&quot;duration&quot;:8.682e-3,&quot;end_time&quot;:&quot;2024-02-28T01:59:56.208809&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:56.200127&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=tNm_NNSB3_w&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=://www.youtube.com/watch?v=1xNbjMdbjug&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=6>

</div>

<div id="27c2f0df" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:56.228441Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:56.227578Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:56.252131Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:56.251075Z&quot;}"
papermill="{&quot;duration&quot;:3.7673e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:56.254689&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:56.217016&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Some necessary imports
import math
```

</div>

<div id="48b302bb" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:56.262987Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:56.262681Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:56.268306Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:56.267413Z&quot;}"
lines_to_next_cell="2"
papermill="{&quot;duration&quot;:1.2236e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:56.270384&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:56.258148&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:56.278691Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:56.278030Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:56.282822Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:56.281934Z&quot;}"
papermill="{&quot;duration&quot;:1.0632e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:56.284902&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:56.274270&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:56.292384Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:56.291823Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:56.296303Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:56.295558Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.465e-3,&quot;end_time&quot;:&quot;2024-02-28T01:59:56.298273&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:56.288808&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:56.306034Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:56.305301Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:56.310476Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:56.309743Z&quot;}"
papermill="{&quot;duration&quot;:1.0199e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:56.312466&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:56.302267&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:56.318156Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:56.317534Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:56.322601Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:56.321860Z&quot;}"
papermill="{&quot;duration&quot;:9.573e-3,&quot;end_time&quot;:&quot;2024-02-28T01:59:56.324083&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:56.314510&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:56.330425Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:56.329698Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:56.334794Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:56.333979Z&quot;}"
papermill="{&quot;duration&quot;:1.0285e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:56.336731&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:56.326446&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:56.343029Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:56.342792Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:56.347324Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:56.346547Z&quot;}"
papermill="{&quot;duration&quot;:9.611e-3,&quot;end_time&quot;:&quot;2024-02-28T01:59:56.349222&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:56.339611&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
