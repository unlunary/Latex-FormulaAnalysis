> 可优化：
>
> 1. 叶子结点替换步骤：叶子结点处，除了六个常量符号，皆被替换为X。**<u>可保留数字。</u>**
> 2. 生成子树组合索引步骤：各子树组合的结果实际上相同，可去除同质化结果。
>
> 未完成：
>
> 1. ~~公式合法性检测~~ **已完成大小括号匹配**



### 测试范围

##### 未测：

- [x] COT, SEC, CSC（三角函数，补充样例即可）

- [x] ~~DEGREE~~, （不在解析范围内）

- [x] DIVIDE, （同理MULTIPLY）

- [x] NOT,AND, OR, XOR, IFF （可用离散课本中习题）

##### 已测：

FRAC, SQRT, MINUS, NEGSIGN, SIN, COS, TAN,ADD, MULTIPLY, POWER,IMPLY



---



### 测试样例结果

#### （1）可判断括号优先级示例：

```latex
{(4+((\alpha+2)+3))}\times{3}+{(4+((1+\beta)+3))}
```

- tree to string:7510606060252607400606060

- print tree's index:+(5){\beta}{X}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}

- indexes:

  - t1+t2+t3+t4+t5: +(5){\beta}{X}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t1+t2+t3+t4: +(4){\beta}{X}{X}{X}
  - t1+t2+t3+t5: +(4){\beta}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t1+t2+t3: +(3){\beta}{X}{X}
  - t1+t2+t4+t5: +(4){\beta}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t1+t2+t4: +(3){\beta}{X}{X}
  - t1+t2+t5: +(3){\beta}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t1+t2: +(2){\beta}{X}
  - t1+t3+t4+t5: +(4){\beta}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t1+t3+t4: +(3){\beta}{X}{X}
  - t1+t3+t5: +(3){\beta}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t1+t3: +(2){\beta}{X}
  - t1+t4+t5: +(3){\beta}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t1+t4: +(2){\beta}{X}
  - t1+t5: +(2){\beta}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t2+t3+t4+t5: +(4){X}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t2+t3+t4: +(3){X}{X}{X}
  - t2+t3+t5: +(3){X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t2+t3: +(2){X}{X}
  - t2+t4+t5: +(3){X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t2+t4: +(2){X}{X}
  - t2+t5: +(2){X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t3+t4+t5: +(3){X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t3+t4: +(2){X}{X}
  - t3+t5: +(2){X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
  - t4+t5: +(2){X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}

  

#### （2）示例2：

```latex
{\frac{{\alpha}\times{\frac{2}{3}}}{2+3}}+{\frac{(\alpha+\beta)+\pi}{2+3}}
```

- tree to string:7216216272252737260600016200104060606060

- print tree's index:+(2){\frac(2){+(2){X}{X}}{\times(2){\alpha}{\frac(2){X}{X}}}}{\frac(2){+(3){\alpha}{\beta}{\pi}}{+(2){X}{X}}}

- indexes:
  - t1+t2: +(2){\frac(2){+(2){X}{X}}{\times(2){\alpha}{\frac(2){X}{X}}}}{\frac(2){+(3){\alpha}{\beta}{\pi}}{+(2){X}{X}}}



#### （3）

```latex
\sin{(\alpha-\beta)}\implies{{\sin{\alpha}}\times{\cos{\beta}}-{{\cos{\alpha}\times{\sin{\beta}}}}}
```

- tree to string:1722118282242242001010121110121110000010


- print tree's index:\implies(2){\sin(1){-(2){\alpha}{\beta}}}{-(2){\times(2){\cos(1){\beta}}{\sin(1){\alpha}}}{\times(2){\cos(1){\alpha}}{\sin(1){\beta}}}}
- indexes:
  \implies(2){\sin(1){-(2){\alpha}{\beta}}}{-(2){\times(2){\cos(1){\beta}}{\sin(1){\alpha}}}{\times(2){\cos(1){\alpha}}{\sin(1){\beta}}}}



#### （4）

```latex
{((-4)-((\alpha+(-2))+3))}\times{(-3)}+{(4+(((-1)+\beta)-3))}
```

- tree to string: 7360822627260608210606073006060

- print tree's index:+(3){X}{-(2){+(2){\beta}{X}}{X}}{\times(2){X}{-(2){X}{+(3){\alpha}{X}{X}}}}

- indexes:
  - t1+t2+t3: +(3){X}{-(2){+(2){\beta}{X}}{X}}{\times(2){X}{-(2){X}{+(3){\alpha}{X}{X}}}}
  - t1+t2: +(2){X}{-(2){+(2){\beta}{X}}{X}}
  - t1+t3: +(2){X}{\times(2){X}{-(2){X}{+(3){\alpha}{X}{X}}}}
  - t2+t3: +(2){-(2){+(2){\beta}{X}}{X}}{\times(2){X}{-(2){X}{+(3){\alpha}{X}{X}}}}



#### （5）

```latex
{\tan{(\alpha-\beta)}}\implies{\frac{{\tan{\alpha}}-{\tan{\beta}}}{{1}+{{\tan{\alpha}}\times{\tan{\beta}}}}}
```

- tree to string:19225117282827200102512516026200102512510010

- print tree's index:\implies(2){\tan(1){-(2){\alpha}{\beta}}}{\frac(2){-(2){\tan(1){\alpha}}{\tan(1){\beta}}}{+(2){X}{\times(2){\tan(1){\alpha}}{\tan(1){\beta}}}}}
- indexes:
  \implies(2){\tan(1){-(2){\alpha}{\beta}}}{\frac(2){-(2){\tan(1){\alpha}}{\tan(1){\beta}}}{+(2){X}{\times(2){\tan(1){\alp
  ha}}{\tan(1){\beta}}}}}



#### （6）

```latex
\frac{{\alpha}\times{(\beta+\pi)}}{2+3}
```

- tree to string:17226272007260601040

- print tree's index:\frac(2){\times(2){\alpha}{+(2){\beta}{\pi}}}{+(2){X}{X}}

- indexes:
  \frac(2){\times(2){\alpha}{+(2){\beta}{\pi}}}{+(2){X}{X}}



#### （7）

```latex
{\frac{{\alpha}\times{({\sqrt[3]{2}}+{5})}}{2+3}}+{\frac{(\alpha+\beta)+\pi}{2+3}}
```

- tree to string:72172172262727372007260600010406060602426060

- print tree's index:+(2){\frac(2){\times(2){\alpha}{+(2){X}{\sqrt(2){X}{X}}}}{+(2){X}{X}}}{\frac(2){+(3){\alpha}{\beta}{\pi}}{+(2){X}{X}}}
- indexes:
  t1+t2: +(2){\frac(2){\times(2){\alpha}{+(2){X}{\sqrt(2){X}{X}}}}{+(2){X}{X}}}{\frac(2){+(3){\alpha}{\beta}{\pi}}{+(2){X}{X}}}



#### （8）

```latex
\frac{\sin{(x+y)}}{2+3}
```

- tree to string:172231727260606060

- print tree's index:\frac(2){\sin(1){+(2){X}{X}}}{+(2){X}{X}}

- indexes:
  \frac(2){\sin(1){+(2){X}{X}}}{+(2){X}{X}}



#### （9）

```latex
1 + {(\\frac{1}{1-{x}^{2}})}^{3}
```

- tree to string:7260272172606082602726060

- print tree's index:+(2){X}{^(2){\frac(2){X}{-(2){X}{^(2){X}{X}}}}{X}}

- indexes:
  - t1+t2: +(2){X}{^(2){\frac(2){X}{-(2){X}{^(2){X}{X}}}}{X}}

#### （10）

```latex
\cot{(\alpha-\beta)}\implies{{\sec{\alpha}}\times{\csc{\beta}}-{{\cos{\alpha}\times{\sin{\beta}}}}}
```

- tree to string:1921318282262262001014122112123110000010
- print tree's index:\implies(2){\cot(1){-(2){\alpha}{\beta}}}{-(2){\times(2){\csc(1){\beta}}{\sec(1){\alpha}}}{\times(2){
  \cos(1){\alpha}}{\sin(1){\beta}}}}
- indexes:
  \implies(2){\cot(1){-(2){\alpha}{\beta}}}{-(2){\times(2){\csc(1){\beta}}{\sec(1){\alpha}}}{\times(2){\cos(1){\alpha}}{\s
  in(1){\beta}}}}

#### （11）

```latex
\frac{{\alpha}\divide{(\beta+\pi)}}{2+3}
```

- tree to string:17216272007260601040
- print tree's index:\frac(2){\div(2){\alpha}{+(2){\beta}{\pi}}}{+(2){X}{X}}
- indexes:
  \frac(2){\div(2){\alpha}{+(2){\beta}{\pi}}}{+(2){X}{X}}

#### （12）

```latex
{A}\cup{({A}\cap{B})}\iff{A}
```

- tree to string:18260152601026060
- print tree's index:\iff(2){X}{\cup(2){X}{\cap(2){X}{X}}}
- indexes:
  t1+t2: \iff(2){X}{\cup(2){X}{\cap(2){X}{X}}}

#### （13）
```latex
\neg{{A}\cap{B}}\iff{{\neg{A}}\cup{\neg{B}}}
```

- tree to string:19220115210220120160606060
- print tree's index:\implies(2){\neg(1){\cap(2){X}{X}}}{\cup(2){\neg(1){X}}{\neg(1){X}}}
- indexes:
  \implies(2){\neg(1){\cap(2){X}{X}}}{\cup(2){\neg(1){X}}{\neg(1){X}}}

#### （14）

```latex
{{P}\implies{Q}}\iff{{\neg{P}}\implies{\neg{Q}}}
```

- tree to string:18219219260602012016060
- print tree's index:\iff(2){\implies(2){X}{X}}{\implies(2){\neg(1){X}}{\neg(1){X}}}
- indexes:
  t1+t2: \iff(2){\implies(2){X}{X}}{\implies(2){\neg(1){X}}{\neg(1){X}}}


#### （15）
```latex
{A}\oplus{({A}\cap{B})}\implies{A}
```

- tree to string:19221260601026060
- print tree's index:\implies(2){\oplus(2){X}{\cap(2){X}{X}}}{X}
- indexes:
  \implies(2){\oplus(2){X}{\cap(2){X}{X}}}{X}