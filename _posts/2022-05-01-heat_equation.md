---
layout: post
title: "熱拡散方程式を数値的に解く"
date: 2022-05-01
categories: physics
---

## 熱拡散方程式とは
（物理数学の授業で習っただけの知識なので、かなり浅いですが……）

熱の拡散の様子を表す微分方程式。熱分布の時間変化が空間的勾配を用いて表現される。あるいは、熱の空間的な分布（勾配）が時間変化によって表現される。そのため、式中に時間と空間の微分が現れる。この微分方程式は解析的に解くことが出来るが、ここでは数値的な解によるシミュレーションを行う。

### 基本の熱拡散方程式
外部からの熱の供給や吸収がなく単純に熱が拡がっていく場合。熱の拡散速度に関する定数 $\kappa$ を用いて以下の式で与えられる：

$$\begin{equation}
    \pdv{}{t} u(t, x) = \kappa\ppdv{2}{}{x}u(t, x)
\end{equation}$$

境界条件や初期条件を与えたり $\kappa$ の値を指定したりして解くことで、様々な条件下での熱の拡がりかたを求めることができる。

### 熱の湧き出しがある場合
ヒーターなどで常に一定の熱が供給されている場合を考える。点 $x$ における熱の供給率を $q(x)$ とおく。このとき

$$\begin{align}
    \pdv{u}{t} = q(x)
\end{align}$$

であるから、熱拡散方程式は次になる：

$$\begin{align}
    \pdv{}{t} u(t, x) = \kappa\ppdv{2}{}{x}u(t, x) + q(x)
\end{align}$$

## 微分方程式の数値解
### 熱の湧き出しなし
最初に述べた通り、微分方程式を数値的に解く。簡便な方法であるオイラー陽解法を採用する。  
オイラー法の通常の手順に従う。まず、次の近似式が成立することに注目する：

$$\begin{align}
    \pdv{}{x} u(t, x) \sim \frac{u(t, x + \Delta x) - u(t, x)}{\Delta x}
\end{align}$$

この近似を式 $(1)$ に適用する：

$$\begin{align}
    \frac{u(t + \Delta t, x) - u(t, x)}{\Delta t} &\sim \kappa\pdv{}{x}\frac{u'(t, x + \Delta x) - u'(t, x)}{\Delta x} \nonumber\\
    &\sim \kappa\frac{1}{\Delta x}\left(\frac{u(t, x + 2\Delta x) - u(t, x + \Delta x)}{\Delta x} - \frac{u(t, x + \Delta x) - u(t, x)}{\Delta x}\right) \nonumber\\
    &= \kappa\frac{u(t, x + 2\Delta x) - 2u(t, x + \Delta x) + u(t, x)}{\left(\Delta x\right)^2}
\end{align}$$

さらに、変形を行うと、必要な近似式が得られる：

$$\begin{align}
    u(t + \Delta t, x) = u(t, x) + \frac{\kappa\Delta t}{\left(\Delta x\right)^2}\big[u(t, x + 2\Delta x) - 2u(t, x + \Delta x) + u(t, x)\big]
\end{align}$$

この式を用いれば現在時刻の熱分布から、$\Delta t$ 経過後の熱分布が求まる。

### 熱の湧き出しあり
いまやったのと同じ近似を式 $(3)$ に適用すれば、近似式が得られる：

$$\begin{align}
    &u(t + \Delta t, x)\nonumber\\ =& u(t, x) + \frac{\kappa\Delta t}{\left(\Delta x\right)^2}\big[u(t, x + 2\Delta x) - 2u(t, x + \Delta x) + u(t, x)\big] + q(x)\Delta t
\end{align}$$

## シミュレーション
Pythonを用いてシミュレーションした。どの計算においても境界条件は、有限の区間を考え、区間の両端では常に熱は $0$ であるとした。結果は、横軸に $x$ 座標、縦軸に $u(t, x)$ をとったグラフで表し、時間変化をアニメーション（動画）で示す。

### 熱の湧き出しなし
2つの初期条件でシミュレートを行った。

#### 初期条件１
初期条件：

$$\begin{align}
    \begin{cases}
        u(x) = 4 \quad & for~ -2\le x \le 2 \\
        u(x) = 0 \quad & for~ x < -2,~2 < x
    \end{cases}
\end{align}$$

$4$ や $2$ という数字に意味はない（適当なスケーリングがされているだけ）。この $t = 0$ での状態をグラフで表す。縦軸に熱の量 $u(x)$、横軸に位置座標 $x$ をとる。
<center><img src="/blog/assets/2022-05-01-heat_equation/湧き出しなし_初期条件1.svg" style="width: 70%;"></center>
グラフは、「高い部分＝熱い部分」と見なせばよいと思う。

では、時間を進めると熱がどのように拡散していくかをシミュレートする。式 $(7)$ において $\Delta t = dt = 0.001,~\Delta x = dx = 0.01$ として計算した結果が下の動画：
<center><video src="/blog/assets/2022-05-01-heat_equation/heat1_slow.mp4" controls style="width: 70%;"></video></center>
$u = 0$ と $u = 4$ の境界辺りから熱がゆっくりと拡がっていくのが分かる。

条件はそのままに、シミュレートの時間間隔を大きくしてする。$\Delta t = dt = 0.01,~\Delta x = dx = 0.05$ として計算した：
<center><video src="/blog/assets/2022-05-01-heat_equation/heat1.mp4" controls style="width: 70%;"></video></center>
矩形のグラフが丸みを帯びていく様子が見られる。

#### 初期条件2
初期条件：

$$\begin{align}
    \begin{cases}
        u(x) = x + 4  \quad & for~ -4\le x \le 0 \\
        u(x) = -x + 4 \quad & for~ 0\le x\le 4 \\
        u(x) = 0 \quad & for~ x < -4,~4 < x
    \end{cases}
\end{align}$$

<center><img src="/blog/assets/2022-05-01-heat_equation/湧き出しなし_初期条件2.svg" style="width: 70%;"></center>

上でやったのと同じように、$\Delta t = 0.01,~\Delta x = 0.05$ として（以下のシミュレーションでもこの数値を用いる）計算する：
<center><video src="/blog/assets/2022-05-01-heat_equation/heat2.mp4" controls style="width: 70%;"></video></center>
やはり、時間経過とともにグラフは丸みを帯びてゆく。

また、二つの初期条件において $t = 0$ でのグラフの形は異なるが、どちらも徐々にガウス関数に近い形に変形していくように見える。それには何か理由があるのか、それともただの思い違いなのかは知らない。

### 熱の湧き出しあり
点または区間から一定の熱が供給され続ける場合のシミュレーション。

#### 条件1
空間全体は最初熱を持たず、一点からの熱供給が絶えず行われている場合を考える。
<center><video src="/blog/assets/2022-05-01-heat_equation/heat3.mp4" controls style="width: 70%;"></video></center>
一点から鋭いピークが出現する。湧き出しがない時のような丸みを帯びたグラフへは変化しない。

#### 条件2
条件1と同じ設定で、熱の湧き出しを点ではなく区間（$2\le x\le 3$）とした。
<center><video src="/blog/assets/2022-05-01-heat_equation/heat4.mp4" controls style="width: 70%;"></video></center>
時間経過とともに山のピークがどんどん鋭くなるようだ。延々と続ければ、グラフの形は条件1にに限りなく近づいていくはず。

## 与太話
色々な初期条件・境界条件で試すと面白いはず。それと、拡散方程式に関して気になっていることもある。が、今回はここまでにしておく。

Python コード：

```python
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation

fig, ax = plt.subplots()

dx = 0.5    # 刻み幅（位置）
dt = 0.1    # 刻み幅（時間）
kappa = 0.05    # 拡散の定数
cons = (dt / dx) * (kappa / dx)

x = np.arange(-10, 10, dx)
u = np.zeros(x.size)

def update(n):
    if n != 0:
        for i in range(1, u.size - 1, 1):
            u[i] += (u[i+1] - 2 * u[i] + u[i-1]) * cons
            # 湧き出しがある場合
            #if 2 <= x[i] <= 3:
            #    u[i] += 0.01 * dt
    
    ax.cla()
    ax.set_ylim(bottom = -0.1, top = 5)
    ax.plot(x, u, 'r', label='$t = ' + '{:.2f}'.format(n * dt) + '$')
    ax.legend()
    ax.set_title('graph title')

def main():
    print(dt * kappa / (dx * dx))
    # 初期条件を設定
    #for i in range(u.size):
    #    if -4 <= x[i] <= 0:
    #        u[i] = x[i] + 4
    #    elif 0 <= x[i] <= 4:
    #        u[i] = -x[i] + 4

    # アニメーション作成
    ani = FuncAnimation(fig, update, frames=range(601), interval=100)
    ani.save(R"directory\heat_simulations.mp4", writer='ffmpeg')
    plt.show()

main()
```
