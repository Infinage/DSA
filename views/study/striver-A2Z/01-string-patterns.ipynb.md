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
    duration: 2.307645
    end_time: "2024-02-28T01:59:46.965605"
    environment_variables: {}
    input_path: 01-string-patterns.ipynb
    output_path: 01-string-patterns.ipynb
    parameters: {}
    start_time: "2024-02-28T01:59:44.657960"
    version: 2.4.0
---

<div id="d50974a9" class="cell markdown"
papermill="{&quot;duration&quot;:2.2669e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.308004&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.285335&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=tNm_NNSB3_w&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=4>

</div>

<div id="5c29f379" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.334871Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.334348Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.343204Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.342335Z&quot;}"
papermill="{&quot;duration&quot;:2.1696e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.345327&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.323631&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 1
N = 7
for i in range(N):
    for j in range(N):
        print ("*", end=" ")
    print()
```

<div class="output stream stdout">

    * * * * * * * 
    * * * * * * * 
    * * * * * * * 
    * * * * * * * 
    * * * * * * * 
    * * * * * * * 
    * * * * * * * 

</div>

</div>

<div id="73698c67" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.362252Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.361659Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.366283Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.365387Z&quot;}"
papermill="{&quot;duration&quot;:1.4304e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.368252&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.353948&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 2
N = 7
for i in range(N):
    for j in range(i + 1):
        print ("*", end=" ")
    print()
```

<div class="output stream stdout">

    * 
    * * 
    * * * 
    * * * * 
    * * * * * 
    * * * * * * 
    * * * * * * * 

</div>

</div>

<div id="7ea9a66d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.379996Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.379319Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.385627Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.384275Z&quot;}"
papermill="{&quot;duration&quot;:1.6085e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.390303&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.374218&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 3
N = 7
for i in range(N):
    for j in range(1, i + 2):
        print (j, end=" ")
    print()
```

<div class="output stream stdout">

    1 
    1 2 
    1 2 3 
    1 2 3 4 
    1 2 3 4 5 
    1 2 3 4 5 6 
    1 2 3 4 5 6 7 

</div>

</div>

<div id="3d16bd53" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.400254Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.399329Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.404177Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.403452Z&quot;}"
papermill="{&quot;duration&quot;:1.1576e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.405992&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.394416&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 4
N = 7
for i in range(1, N + 1):
    for j in range(1, i + 1):
        print(i, end=" ")
    print()
```

<div class="output stream stdout">

    1 
    2 2 
    3 3 3 
    4 4 4 4 
    5 5 5 5 5 
    6 6 6 6 6 6 
    7 7 7 7 7 7 7 

</div>

</div>

<div id="cdb9bcd3" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.415204Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.414951Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.419632Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.418845Z&quot;}"
papermill="{&quot;duration&quot;:1.1506e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.421531&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.410025&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 5
N = 7
for i in range(N):
    for j in range(N - i):
        print ("*", end=" ")
    print()
```

<div class="output stream stdout">

    * * * * * * * 
    * * * * * * 
    * * * * * 
    * * * * 
    * * * 
    * * 
    * 

</div>

</div>

<div id="6c3168cd" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.434815Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.434515Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.439933Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.439045Z&quot;}"
papermill="{&quot;duration&quot;:1.3977e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.441840&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.427863&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 6
N = 7
for i in range(N):
    for j in range(1, N - i + 1):
        print (j, end=" ")
    print()
```

<div class="output stream stdout">

    1 2 3 4 5 6 7 
    1 2 3 4 5 6 
    1 2 3 4 5 
    1 2 3 4 
    1 2 3 
    1 2 
    1 

</div>

</div>

<div id="554c463b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.453019Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.452760Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.458868Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.457777Z&quot;}"
papermill="{&quot;duration&quot;:1.3322e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.461121&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.447799&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 7
N = 7
for i in range(1, N + 1):
    for j in range(N - i):
        print("", end=" ")
    for j in range((2 * i) - 1):
        print("*", end="")
    for j in range(N - i):
        print("", end=" ")
    print()
```

<div class="output stream stdout">

          *      
         ***     
        *****    
       *******   
      *********  
     *********** 
    *************

</div>

</div>

<div id="378ca824" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.473425Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.472990Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.478454Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.477678Z&quot;}"
papermill="{&quot;duration&quot;:1.197e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.480019&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.468049&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 8
N = 7
for i in range(N, 0, -1):
    for j in range(N - i):
        print("", end=" ")
    for j in range((2 * i) - 1):
        print("*", end="")
    for j in range(N - i):
        print("", end=" ")
    print()
```

<div class="output stream stdout">

    *************
     *********** 
      *********  
       *******   
        *****    
         ***     
          *      

</div>

</div>

<div id="df22abe8" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.489803Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.489546Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.496520Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.495687Z&quot;}"
papermill="{&quot;duration&quot;:1.3907e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.498107&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.484200&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 9
N = 7
for i in range(1, 2 * N + 1):
    if i <= N:
        for j in range(N - i):
            print ("", end=" ")
        for j in range(i * 2 - 1):
            print ("*", end="")
        for j in range(N - i):
            print ("", end=" ")
    else:
        i_ = (2 * N) - i + 1
        for j in range(N - i_):
            print ("", end=" ")
        for j in range(i_ * 2 - 1):
            print ("*", end="")
        for j in range(N - i_):
            print ("", end=" ")
    print()
```

<div class="output stream stdout">

          *      
         ***     
        *****    
       *******   
      *********  
     *********** 
    *************
    *************
     *********** 
      *********  
       *******   
        *****    
         ***     
          *      

</div>

</div>

<div id="74011d5f" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.507913Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.507573Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.512887Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.512136Z&quot;}"
papermill="{&quot;duration&quot;:1.2043e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.514341&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.502298&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 10
N = 7
result = []
for i in range(1, N + 1):
    row = []
    for j in range(i):
        row.append("*")
    result.append(" ".join(row))
result = result + result[-2::-1]
print("\n".join(result))
```

<div class="output stream stdout">

    *
    * *
    * * *
    * * * *
    * * * * *
    * * * * * *
    * * * * * * *
    * * * * * *
    * * * * *
    * * * *
    * * *
    * *
    *

</div>

</div>

<div id="13b266fb" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.524186Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.523943Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.528898Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.528158Z&quot;}"
papermill="{&quot;duration&quot;:1.1747e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.530365&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.518618&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 11
N = 7
for i in range(1, N + 1):
    for j in range(1, i + 1):
        if i % 2 == 0:
            print (1 if j % 2 == 0 else 0, end=" ")
        else:
            print (0 if j % 2 == 0 else 1, end=" ")
    print()
```

<div class="output stream stdout">

    1 
    0 1 
    1 0 1 
    0 1 0 1 
    1 0 1 0 1 
    0 1 0 1 0 1 
    1 0 1 0 1 0 1 

</div>

</div>

<div id="e65cda14" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.540890Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.540458Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.545850Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.544923Z&quot;}"
papermill="{&quot;duration&quot;:1.285e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.547899&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.535049&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 12
N = 7
for i in range(1, N + 1):
    for j in range(1, i + 1):
        print (j, end="")
    for j in range((N - i) * 2):
        print ("", end=" ")
    for j in range(i, 0, -1):
        print (j, end="")
    print()
```

<div class="output stream stdout">

    1            1
    12          21
    123        321
    1234      4321
    12345    54321
    123456  654321
    12345677654321

</div>

</div>

<div id="a8369219" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.562367Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.562031Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.568642Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.567228Z&quot;}"
papermill="{&quot;duration&quot;:1.6608e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.573070&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.556462&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 13
N = 7
rowCount, curr = 1, 1
while rowCount <= N:
    for i in range(curr, curr + rowCount):
        print (i, end=" ")
    print()
    rowCount += 1
    curr = i + 1
```

<div class="output stream stdout">

    1 
    2 3 
    4 5 6 
    7 8 9 10 
    11 12 13 14 15 
    16 17 18 19 20 21 
    22 23 24 25 26 27 28 

</div>

</div>

<div id="0ae579b2" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.583277Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.583009Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.587936Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.587207Z&quot;}"
papermill="{&quot;duration&quot;:1.194e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.589544&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.577604&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 14
N = 7
for i in range(1, N + 1):
    for j in range(ord("A"), ord("A") + i):
        print (chr(j), end=" ")
    print()
```

<div class="output stream stdout">

    A 
    A B 
    A B C 
    A B C D 
    A B C D E 
    A B C D E F 
    A B C D E F G 

</div>

</div>

<div id="c93c8fe8" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.599873Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.599541Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.604656Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.603873Z&quot;}"
papermill="{&quot;duration&quot;:1.2089e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.606143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.594054&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 15
N = 7
for i in range(N):
    for j in range(N - i):
        print(chr(ord("A") + j), end=" ")
    print()
```

<div class="output stream stdout">

    A B C D E F G 
    A B C D E F 
    A B C D E 
    A B C D 
    A B C 
    A B 
    A 

</div>

</div>

<div id="f3424ddb" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.616314Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.616103Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.620349Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.619590Z&quot;}"
papermill="{&quot;duration&quot;:1.1646e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.622263&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.610617&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 16
N = 7
for i in range(N):
    for j in range(i + 1):
        print(chr(ord("A") + i), end="")
    print()
```

<div class="output stream stdout">

    A
    BB
    CCC
    DDDD
    EEEEE
    FFFFFF
    GGGGGGG

</div>

</div>

<div id="5c35d73e" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.634535Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.634227Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.640660Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.639627Z&quot;}"
papermill="{&quot;duration&quot;:1.3976e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.642489&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.628513&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 17
N = 7
for i in range(1, N + 1):
    for j in range(N - i):
        print ("", end=" ")

    curr = 0
    for j in range(i * 2 - 1):
        print (chr(ord("A") + curr), end="")
        if j < i - 1:
            curr += 1
        else:
            curr -= 1

    for j in range(N - i):
        print ("", end=" ")
    print()
```

<div class="output stream stdout">

          A      
         ABA     
        ABCBA    
       ABCDCBA   
      ABCDEDCBA  
     ABCDEFEDCBA 
    ABCDEFGFEDCBA

</div>

</div>

<div id="a59d7343" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.656625Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.656374Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.661040Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.660252Z&quot;}"
papermill="{&quot;duration&quot;:1.2147e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.662839&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.650692&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 18
N = 7
for i in range(N):
    for j in range(N - i - 1, N):
        print (chr(ord("A") + j), end=" ")
    print()
```

<div class="output stream stdout">

    G 
    F G 
    E F G 
    D E F G 
    C D E F G 
    B C D E F G 
    A B C D E F G 

</div>

</div>

<div id="060aa997" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.673721Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.673151Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.679360Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.678521Z&quot;}"
papermill="{&quot;duration&quot;:1.443e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.681968&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.667538&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 19
N = 7
for i in range(2 * N):
    if i < N:
        i_ = i
    else:
        i_ = (2 * N) - i - 1

    for j in range(N - i_):
        print("*", end="")
    for j in range(i_ * 2):
        print(" ", end="")
    for j in range(N - i_):
        print("*", end="")
    print()
```

<div class="output stream stdout">

    **************
    ******  ******
    *****    *****
    ****      ****
    ***        ***
    **          **
    *            *
    *            *
    **          **
    ***        ***
    ****      ****
    *****    *****
    ******  ******
    **************

</div>

</div>

<div id="ae396acb" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.695672Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.695416Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.701621Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.700856Z&quot;}"
papermill="{&quot;duration&quot;:1.3448e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.703187&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.689739&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 20
N = 7
for i in range(1, 2 * N):
    if i <= N:
        i_ = i
    else:
        i_ = (2 * N) - i 

    for j in range(i_):
        print("*", end="")
    for j in range(2 * (N - i_)):
        print (" ", end="")
    for j in range(i_):
        print("*", end="")
    print()
```

<div class="output stream stdout">

    *            *
    **          **
    ***        ***
    ****      ****
    *****    *****
    ******  ******
    **************
    ******  ******
    *****    *****
    ****      ****
    ***        ***
    **          **
    *            *

</div>

</div>

<div id="f6cec386" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.715456Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.714813Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.720555Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.719734Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3404e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.721927&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.708523&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 21
N = 7
for i in range(N):
    if i == 0 or i == N - 1:
        for j in range(N):
            print ("*", end="")
    else:
        print ("*", end="")
        for j in range(N - 2):
            print(" ", end="")
        print ("*", end="")
    print()
```

<div class="output stream stdout">

    *******
    *     *
    *     *
    *     *
    *     *
    *     *
    *******

</div>

</div>

<div id="5c65598f" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-28T01:59:46.733191Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-28T01:59:46.732504Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-28T01:59:46.739870Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-28T01:59:46.739126Z&quot;}"
papermill="{&quot;duration&quot;:1.4685e-2,&quot;end_time&quot;:&quot;2024-02-28T01:59:46.741410&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-28T01:59:46.726725&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 22
def pattern22(N: int):
    """
    0 - [[]]
    1 - [[1]]
    2 - [[2,2,2],[2,1,2],[2,2,2]]
    3 - [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
    """

    def backtrack(n: int) -> list[list[str]]:
        if n == 1:
            return [['1'.zfill(max_char_length)]]
        else:
            prev = backtrack(n - 1)
            curr, length = str(n).zfill(max_char_length), 2 * n - 1
            curr_row = [curr for _ in range(length)]
            next_: list[list[str]] = []

            next_.append(curr_row)
            pad_length = (length - len(prev[0])) // 2
            for row in prev:
                next_.append([curr for _ in range(pad_length)] + row + [curr for _ in range(pad_length)])
            next_.append(curr_row)

            return next_

    max_char_length = len(str(N))
    result = backtrack(N)
    for row in result:
        print(" ".join(row))
    print()

# Testing the function
pattern22(7)
```

<div class="output stream stdout">

    7 7 7 7 7 7 7 7 7 7 7 7 7
    7 6 6 6 6 6 6 6 6 6 6 6 7
    7 6 5 5 5 5 5 5 5 5 5 6 7
    7 6 5 4 4 4 4 4 4 4 5 6 7
    7 6 5 4 3 3 3 3 3 4 5 6 7
    7 6 5 4 3 2 2 2 3 4 5 6 7
    7 6 5 4 3 2 1 2 3 4 5 6 7
    7 6 5 4 3 2 2 2 3 4 5 6 7
    7 6 5 4 3 3 3 3 3 4 5 6 7
    7 6 5 4 4 4 4 4 4 4 5 6 7
    7 6 5 5 5 5 5 5 5 5 5 6 7
    7 6 6 6 6 6 6 6 6 6 6 6 7
    7 7 7 7 7 7 7 7 7 7 7 7 7

</div>

</div>
