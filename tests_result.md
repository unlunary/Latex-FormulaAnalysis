> 可优化：
>
> 1. 叶子结点替换步骤：叶子结点处，除了六个常量符号，皆被替换为X。**<u>可保留数字。</u>**
> 2. 生成子树组合索引步骤：各子树组合的结果实际上相同，可去除同质化结果。

### 测试样例结果

#### （1）可判断括号优先级示例：

```latex
{(4+((\alpha+2)+3))}\times{3}+{(4+((1+\beta)+3))}
```

- 图示：

   <img src="D:\u_typoraImages\image-20221216180511811.png" alt="image-20221216180511811" style="zoom: 33%;" />

> tree to string:
>
> 7510606060252607400606060
>
> print tree's index:+(5){\beta}{X}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
>
> indexes:
>
> t1+t2+t3+t4+t5: +(5){\beta}{X}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t1+t2+t3+t4: +(4){\beta}{X}{X}{X}
> t1+t2+t3+t5: +(4){\beta}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t1+t2+t3: +(3){\beta}{X}{X}
> t1+t2+t4+t5: +(4){\beta}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t1+t2+t4: +(3){\beta}{X}{X}
> t1+t2+t5: +(3){\beta}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t1+t2: +(2){\beta}{X}
> t1+t3+t4+t5: +(4){\beta}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t1+t3+t4: +(3){\beta}{X}{X}
> t1+t3+t5: +(3){\beta}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t1+t3: +(2){\beta}{X}
> t1+t4+t5: +(3){\beta}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t1+t4: +(2){\beta}{X}
> t1+t5: +(2){\beta}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t2+t3+t4+t5: +(4){X}{X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t2+t3+t4: +(3){X}{X}{X}
> t2+t3+t5: +(3){X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t2+t3: +(2){X}{X}
> t2+t4+t5: +(3){X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t2+t4: +(2){X}{X}
> t2+t5: +(2){X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t3+t4+t5: +(3){X}{X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t3+t4: +(2){X}{X}
> t3+t5: +(2){X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}
> t4+t5: +(2){X}{\times(2){X}{+(4){\alpha}{X}{X}{X}}}

---



#### （2）示例2：

```latex
\frac{(\alpha+\beta)+\pi}{2+3}
```

