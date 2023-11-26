---
layout: post
title: "連想記憶モデル（Hopfield network）の実装"
date: 2023-11-22
categories: physics
---

（一応 physics ジャンルの投稿です）

（細かい話に興味ない人は「原理」の節を飛ばしてください）

## 投稿の概要
連想記憶モデル（Hopfield model）は人工知能（AI）の一種で、情報の記憶、取り出しを行うことができる。以下で述べるように、不鮮明な入力から記憶した情報を思い出すことができる。本投稿は連想記憶モデルの原理について述べ、簡単な実験を行えるプログラムを紹介する。実験結果についても簡単に述べる。なお、"Statistical Physics of Spin Glasses and Information Processing An Introduction" by Hidetoshi Nishimori[^1] を参考文献としてお送りする。

[^1]: 電子版は[著者の先生のHP のページ](https://sites.google.com/view/nishimori/open_access_books)より無料DL できます

## 連想記憶モデルとは？
連想記憶モデル（Hopfield network）は情報の記憶・思い出しを行うニューラルネットワーク。例えば、1000枚の画像をこのネットワークに記憶させる。次に、1000枚の中から1枚を選び、それにノイズをのせた画像を用意する。そして、その画像をネットワークに入力すると、徐々に元の画像が再現される。この思い出しは常に成功するのではなく、条件を満たす必要がある。

<center>
<iframe width="560" height="315" src="https://www.youtube.com/embed/UE2mZNWXd-A?si=IULMuAeYakfd99YU" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>
<p>画像を思い出す様子</p>
</center>

連想記憶は脳が記憶したり思い出したりする仕組みを参考に構築されている。そのため、各記憶素子を「ニューロン」と呼ぶ。実際の脳のニューロンは発火したりしなかったりすることで情報を保持・伝達する。本モデルでもニューロンは発火・非発火により情報の保持・伝達を行う。

## 原理
### パターンの記憶

記憶するパターン数を $p$ とし、各ニューロンの記憶パターンを ${\xi_i^\mu}$ で表す。$\mu$ 番目の記憶パターンでは $i$ 個目のニューロンが $\xi_i^\mu$ の状態（発火・非発火）を表す：

$$\begin{equation}
    \xi_i^{\mu} = \begin{cases}
        1  & \text{：発火} \\
        -1 & \text{：非発火} \\
    \end{cases}
\end{equation}$$

ニューロン同士の相互作用として次の量$J_{ij}$を定義する。系は$J_{ij}$を計算することで $p$ 個のパターンがネットワークを記憶（埋め込み）する：

$$\begin{equation}
    J_{ij} = \frac{1}{N} \sum_{\mu = 1}^{p} \xi_i^\mu \xi_j^\mu
\end{equation}$$

$N$ はニューロンの個数。$J$ は $N\times N$ の行列。また、$J_{ii} = 0$ とする。

### ニューロン間のやりとり

ニューロン同士は情報のやり取りを行うことで記憶したものを思い出す。あるニューロンの状態は他のニューロンの状態により決まる。ニューロン $i$ がニューロン $j$ から受け取る信号の大きさを次のように決める：

$$\begin{equation}
    J_{ij}(S_j + 1) = \begin{cases}
        2J_{ij} & :~S_j = +1 \\
        0       & :~S_j = -1 \\
    \end{cases}
\end{equation}$$

こうすると良い理由は後述。すると、ニューロン $i$ に入ってくる信号の和 $h_i$ は

$$\begin{equation}
    h_i = \sum_{j = 1}^{N} J_{ij}(S_j + 1)
\end{equation}$$

ニューロン $i$ は入力の和があるしきい値 $\theta_i$ を超えるときに発火、そうでなければ非発火とする：

$$\begin{align}
    S_i(t + \Delta t) &= \mathrm{sgn}(h_i - \theta_i) \nonumber\\
                      &= \mathrm{sgn}\left(\sum_{j = 1}^{N} J_{ij}(S_j + 1) - \theta_i\right)
\end{align}$$

ここで $\mathrm{sgn}(\cdot)$ は符号関数。簡単のために、$\theta_i = J_{ij}$ として

$$\begin{equation}
    S_i(t + \Delta t) = \mathrm{sgn}\left(\sum_{j = 1}^{N} J_{ij}S_j(t)\right)
\end{equation}$$

### 思い出し
ここまで、ニューロンを使った記憶の方法・情報のやり取りの方法を説明した。この方法で本当に上手くいくのか？　上手くいくことを確認する。

思い出すとは、記憶したパターンに近いものを与えられたとき、元のパターンを復元できること。まずは、与えられるニューロンパターンが $\mu$ 番目パターンそのものの場合を考える。時刻 $t$ でニューロンたちが $\mu$ 番目のパターンそのものであるとき、時刻 $t + \Delta t$ では

$$\begin{align}
    S_i (t + \Delta t) &= \mathrm{sgn}\left(\sum_{j = 1}^{N} J_{ij}S_j(t)\right) \nonumber\\
                       &= \mathrm{sgn}\left(\sum_{j = 1}^{N} J_{ij}\xi_j^\mu\right) \nonumber\\
                       &= \mathrm{sgn}\left(\sum_{j = 1}^{N} \frac{1}{N}\sum_{\nu = 1}^p \xi_i^\nu \xi_j^\nu \xi_j^\mu\right) \nonumber\\
                       &= \mathrm{sgn}\left(\sum_{\nu = 1}^p \xi_i^\nu \frac{1}{N} \sum_{j = 1}^{N} \xi_j^\nu \xi_j^\mu\right)
\end{align}$$

ここで

$$\begin{equation}
    \frac{1}{N} \sum_{j = 1}^{N} \xi_j^\nu \xi_j^\mu
\end{equation}$$

は、$\mu = \nu$ のときは 1、$\mu \neq \nu$ のときは $N$ が十分大きければ 0 になりそう。なので、この部分はクロネッカーのデルタ $\delta_{\nu,\mu}$ になる。

$$\begin{align}
    S_i (t + \Delta t) &= \mathrm{sgn}\left(\sum_{\nu = 1}^p \xi_i^\nu \delta_{\nu,\mu}\right) \nonumber\\
                       &= \mathrm{sgn}(\xi_i^\mu) \nonumber\\
                       &= \xi_i^\mu 
\end{align}$$

確かに、時刻 $t + \Delta t$ でも系の状態はパターン $\mu$ のままであった。

次に、与えられるパターンがパターン $\mu$ から少しだけずれているときを考える。これは、系のエネルギーから定性的に説明できる。ニューロン $i$ に関して、入力信号 $h_i$ と状態 $S_i$ の積を考えると

$$\begin{align}
    -h_iS_i &= -\sum_j J_{ij}(S_j + 1) S_i \nonumber\\
            &= -\sum_j J_{ij}S_iS_j + const. \times S_i
\end{align}$$

全ての $i$ について和をとれば

$$\begin{equation}
    H = -\frac{1}{2}\sum_{i,j} J_{ij}S_iS_j
\end{equation}$$

ただし、定数部分は適当。この $H$ に関して次のことがわかる：

- $H$ は Ising model の Hamiltonian
- ひとつのニューロンに関して、入力信号と状態が等しいときエネルギーは小さく、異なるときエネルギーは大きくなる
- 系の状態がパターンの状態と等しいとき、エネルギーは極小（各ニューロン、入力 $h_i$ と状態 $S_i$ は等しくなっているので）

従って、系の状態がパターン $\mu$ から少し異なるとき、エネルギーが極小に落ち込むように、パターン $\mu$ に近づいていく。

以上により、連想記憶モデルは記憶と思い出しが行えることがわかった。

## 実装
[GitHub](https://github.com/skrbcr/toybox/tree/main/Hopfield_network) で公開している。

ここでは簡単に、記憶パートと思い出しパートを取り出して説明する。とはいえ、どちらも行列・ベクトルの計算をするだけで、それには [Boost C++ Library](https://www.boost.org/) の `boost::numeric::ublas` を用いた。

**記憶**

```cpp
#define sgn(x) (x >= 0 ? 1 : -1)  // 符号関数

std::mt19937 engine(12345);  // 乱数生成器

boost::numeric::ublas::matrix<double> J(n, n);  // J 行列
std::vector<boost::numeric::ublas::vector<int>> xi(p, ublas::vector<int>(n));  // p個のパターン ξ ベクトル

for (int mu = 0; mu < p; ++mu) {  // p個のパターンに対して
    for (int i = 0; i < n; ++i) {
        if (mu != 0) xi[mu](i) = sgn((int)engine());  // (p - 1)個のパターンをランダム生成
        for (int j = 0; j <= i; ++j) {  // 行列の下三角だけ埋める
            J(i, j) += xi[mu][i] * xi[mu][j];  // ξ_i^μ × ξ_j^μ
        }
    }
}
J /= (double)n;
for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) J(j, i) = J(i, j);  // 行列の上半分は下半分のコピー（J_ij = J_ji）
```

**思い出し**

```cpp
boost::numeric::ublas::vector<double> s(n), stemp(n);  // s: 入力（元画像にノイズがのったもの）; stemp: 計算の途中結果を一次保存

for (int t = 1; t < duration; ++t) {
    // sgn(J * s)
    stemp = ublas::prod(J, s);  
    for (int i = 0; i < n; ++i) s(i) = sgn(stemp(i));
}
```

## 結果
下の画像と、ランダム生成される $p - 1$ 枚の画像を記憶させる（サイズ：100 x 100）。

![記憶する画像]({{ 'assets/2023-11-01-associative_memory/github.png' | relative_url }} "記憶する画像")

思い出す画像は、この画像である。画像にノイズをのせてAI に与える。パターン数 $p$ と一致率 $r_n$（$1 - $(ノイズ比率)）を変えて思い出せるかどうかの実験を行った。

- $p = 100, n_r = 0.6$
<center><video controls src="{{ 'assets/2023-11-01-associative_memory/p100_n40.mp4' | relative_url }}" width="50%"></video></center>
あっという間に、完全に画像を復元できた。

- $p = 1000, n_r = 0.75$
<center><video controls src="{{ 'assets/2023-11-01-associative_memory/p1000_n25.mp4' | relative_url }}" width="50%"></video></center>
パターン数を増やすと、再現はできているものの若干のノイズが残る。

- $p = 1000, n_r = 0.65$
<center><video controls src="{{ 'assets/2023-11-01-associative_memory/p1000_n35.mp4' | relative_url }}" width="50%"></video></center>
同じくパターン数1000だが一致率を下げた。すると、再現できなくなった。

- $p = 3000, n_r = 0.95$
<center><video controls src="{{ 'assets/2023-11-01-associative_memory/p3000_n5.mp4' | relative_url }}" width="50%"></video></center>
パターン数を増やしていくと、高い一致率の画像を与えても再現できなくなった。ノイズは減るどころか増えている。

どれくらいのパターン数を埋め込めるのかは、数値計算で特定されている。パターン数 $p$ とニューロン数 $N$ の比率 $\alpha = p / N$ が 0.138 を超えると画像の再現ができなくなるらしい。一致率の方はどういう研究がされているのか、残念ながら知らないです。。

