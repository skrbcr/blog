---
layout: post
title: "月の軌道"
date: 2022-08-29
categories: physics
---

## 調べること
月の軌道を、地球や太陽との万有引力を考えて計算する。以下、煩雑な記号が乱れ飛びます。[結果までジャンプ](#result)。

### 問題設定
座標系の原点に太陽があるとし、太陽は動かないとする（太陽は地球や月に比べて十分に重いのでこう近似できる）。地球や月は、互いの万有引力や太陽からの重力を受けて運動している。

必要ないくつかの物理量を以下の通りおく：
- 万有引力定数 $G = 6.6726\times 10^{-11}~\text{m}^3\text{kg}^{-1}\text{s}^{-2} = 8.647\times 10^{-13}~\text{km}^3\text{kg}^{-1}\text{h}^{-1}$
- 地球質量 $m = 5.97\times 10^{24}~\text{kg}$
- 太陽質量 $M = 1.99\times 10^{30}~\text{kg}$
- 月・地球質量比 $\mu = 0.0123002$
- 月・地球距離 $R_{\textrm{me}} = 3.84\times 10^{5}~\text{km}$
- 月周期 $T_{\text{moon}} = 27.3214~\text{day} = 655.7136~\text{h}$
- 太陽-月・地球距離 $R_{\text{es}} = 1.4959787\times 10^8~\text{km}$
- 地球周期 $T_{\text{earth}} = 365~\text{day} = 8760~\text{h}$

便宜上、単位を $\text{km},~\text{kg},~\text{h(=hour)}$ で統一した。

### 初期条件の設定

<center>
<img src="{{ 'assets/2022-08-29-moon_orbit/setup.svg' | relative_url }}" style="width: 70%">
<p>はじめ、月・地球・太陽はこのような配置で速度を持っているとする</p>
<hr class="separator">
</center>

最初、月・地球・太陽は上図の関係にあるとして、初期条件を次のように設定する：
- 月：位置 $(x,~y) = (0,~R_{\text{es}} - R_{\text{me}})$、速度 $(u,~v) = (0,~v_{\textrm{moon}})$
- 地球：位置 $(x,~y) = (0,~R_{\text{es}})$、速度 $(u,~v) = (0,~v_{\textrm{earth}})$
- 太陽：位置 $(x,~y) = (0,~0)$、速度 $(u,~v) = (0,~0)$

$v_{\textrm{moon}}$ と $v_{\textrm{earth}}$ を決める。まず、月・地球系の重心から各天体への距離は両者の質量比より分かるので、重心に対する両者の速さが分かる：

$$\begin{gather}
    v^{'}_{\textrm{moon}} = \frac{2\pi\frac{1/\mu}{1 + 1/\mu}R_{\text{me}}}{T_{\text{moon}}} \\
    v^{'}_{\textrm{earth}} = \frac{2\pi\frac{1}{1 + 1/\mu}R_{\text{me}}}{T_{\text{moon}}}
\end{gather}$$

<center>
<img src="{{ 'assets/2022-08-29-moon_orbit/condition.svg' | relative_url }}" style="width: 70%">
<p>重心からの各天体の距離は質量比より簡単に求まる。<br>両天体は重心周りに周期 $T_{\text{moon}}$ で回転することから、速さも求まる</p>
<hr class="separator">
</center>

つづいて、月・地球系の重心の速さも簡単に計算できる：

$$\begin{equation}
    v_{\text{moon and earth}} = \frac{2\pi R_{\text{es}}}{T_{\text{earth}}}
\end{equation}$$

以上より

$$\begin{align}
    v_{\textrm{moon}} = v_{\text{moon and earth}} - v^{'}_{\textrm{moon}} = \frac{2\pi R_{\text{es}}}{T_{\text{earth}}} - \frac{2\pi\frac{1/\mu}{1 + 1/\mu}R_{\text{me}}}{T_{\text{moon}}} \\
    v_{\textrm{earth}} = v_{\text{moon and earth}} + v^{'}_{\textrm{earth}} = \frac{2\pi R_{\text{es}}}{T_{\text{earth}}} + \frac{2\pi\frac{1}{1 + 1/\mu}R_{\text{me}}}{T_{\text{moon}}}
\end{align}$$

ごちゃごちゃとしているが、月と地球、それらの重心に対して円軌道の半径と周期から速さを求めただけである。

## 計算方法
### 解くべき式
月と地球に対して運動方程式を立てる。3体の間に働く万有引力を考えれば良い：

$$\begin{align}
    \text{Moon:}~& \mu m \ddot{x_\textrm{moon}} = - \frac{Gm\mu m}{((x_\textrm{moon} - x_\textrm{earth})^2 + (y_\textrm{moon} - y_\textrm{earth})^2){}^{3/2}}(x_\textrm{moon} - x_\textrm{earth}) - \frac{GM\mu m}{(x_\textrm{moon}{}^2 + y_\textrm{moon}{}^2)^{3/2}}x_\textrm{moon} \\
    & \mu m \ddot{y_\textrm{moon}} = - \frac{Gm\mu m}{((x_\textrm{moon} - x_\textrm{earth})^2 + (y_\textrm{moon} - y_\textrm{earth})^2){}^{3/2}}(y_\textrm{moon} - y_\textrm{earth}) - \frac{GM\mu m}{(x_\textrm{moon}{}^2 + y_\textrm{moon}{}^2)^{3/2}}y_\textrm{moon} \\
    \text{Earth:}~& m \ddot{x_\textrm{earth}} = - \frac{Gm\mu m}{((x_\textrm{moon} - x_\textrm{earth})^2 + (y_\textrm{moon} - y_\textrm{earth})^2){}^{3/2}}(x_\textrm{earth} - x_\textrm{moon}) - \frac{GMm}{(x_\textrm{earth}{}^2 + y_\textrm{earth}{}^2)^{3/2}}x_\textrm{earth} \\
    & m \ddot{y_\textrm{earth}} = - \frac{Gm\mu m}{((x_\textrm{moon} - x_\textrm{earth})^2 + (y_\textrm{moon} - y_\textrm{earth})^2){}^{3/2}}(y_\textrm{earth} - y_\textrm{moon}) - \frac{GMm}{(x_\textrm{earth}{}^2 + y_\textrm{earth}{}^2)^{3/2}}y_\textrm{earth}
\end{align}$$

天体間の距離は上で示した定数を用いてもよいかも知れない。

### プログラム
C++言語で計算を行い、Pythonでグラフアニメーションを作成した。

まず、C++。微分方程式の数値計算には Boost ライブラリの `boost/numeric/odeint.hpp` を用いた。簡単に数値解が計算でき非常に便利。使い方は解説ページ[^1]やドキュメント[^2]を参考にした。参考までに、実装の重要な部分を紹介。便利さが分かると思う。ソースコード全体は[こちら](https://github.com/skrbcr/blog/blob/main/docs/assets/2022-08-29-moon_orbit/main.cpp)。

[^1]: [C++で常微分方程式：boost::odeint入門 ― Qiita](https://qiita.com/hmito/items/483445ac0d42fb4428a5)：一通りのことが分かりやすく解説されている
[^2]: [Chapter 1. Boost.Numeric.Odeint（ドキュメント）](https://www.boost.org/doc/libs/1_80_0/libs/numeric/odeint/doc/html/index.html)：分量が膨大ですが公式ドキュメント

```cpp
class ThreeBody {
private:
    double M;       // 恒星質量
    double m1;      // 惑星質量
    double m2;      // 衛星質量

public:
    // 月と地球に対して、位置が2変数ずつ、速度も2変数ずつの計8変数が必要。
    using state = std::array<double, 8>;
    ThreeBody(double M, double m1, double m2) {
        this->M = M;
        this->m1 = m1;
        this->m2 = m2;
    }
    void operator()(const state& x, state& dx, double t) {
        double r_me = pow(x[0] - x[2], 2.) + pow(x[1] - x[3], 2.);
        double r_es = pow(x[0], 2.) + pow(x[1], 2.);
        double r_ms = pow(x[2], 2.) + pow(x[3], 2.);
        // 位置座標の微分＝速度 dx1 / dt = u1
        dx[0] = x[4];
        dx[1] = x[5];
        dx[2] = x[6];
        dx[3] = x[7];
        // 速度の微分＝加速度 運動方程式を実装
        dx[4] = - G * m2 / pow(r_me, 1.5) * (x[0] - x[2]) - G * M / pow(r_es, 1.5) * x[0];
        dx[5] = - G * m2 / pow(r_me, 1.5) * (x[1] - x[3]) - G * M / pow(r_es, 1.5) * x[1];
        dx[6] = - G * m1 / pow(r_me, 1.5) * (x[2] - x[0]) - G * M / pow(r_ms, 1.5) * x[2];
        dx[7] = - G * m1 / pow(r_me, 1.5) * (x[3] - x[1]) - G * M / pow(r_ms, 1.5) * x[3];
    }
};
```

計算ができれば、あとは Python でグラフにするだけ。ソースコードは[こちら](https://github.com/skrbcr/blog/blob/main/docs/assets/2022-08-29-moon_orbit/animation.py)。

## シミュレーション結果 {#result}
月が赤丸、地球が青丸、真ん中の黄色い丸が太陽。
<center>
    <video src="{{ '/assets/2022-08-29-moon_orbit/mes.mp4' | relative_url }}" controls style="width: 70%;"></video>
</center>

分かりにくいので、月の軌道を大袈裟にしてみると
<center>
    <video src="{{ '/assets/2022-08-29-moon_orbit/mes2.mp4' | relative_url }}" controls style="width: 70%;"></video>
</center>

月は地球の（ほぼ）円軌道を縫うようにして進むことが分かる。地球の周りを回っているから、下図のようにコイルのような環状の軌道を描くのかと思いきや、寧ろ地球と一緒に太陽の周りを回っている印象である。太陽から地球と月を観測したら共に太陽の周りを回っているかのように錯覚しそうだ。そうはいっても、もちろん月は主に地球の重力に捕われているのであって、太陽から受ける重力の方が小さい（およそ半分）。

<center>
<img src="{{ 'assets/2022-08-29-moon_orbit/orbit1.svg' | relative_url }}" style="width: 45%">
<img src="{{ 'assets/2022-08-29-moon_orbit/orbit2.svg' | relative_url }}" style="width: 45%">
<p>左のような軌道を描きそうだが、右の方が実際に近いことが分かった</p>
<hr class="separator">
</center>

地球を常に中心においたグラフのアニメーションも見ておく。やはり月は地球の周りを回っている。それは間違いないようだ。
<center>
    <video src="{{ '/assets/2022-08-29-moon_orbit/me.mp4' | relative_url }}" controls style="width: 70%;"></video>
</center>

## まとめなど
地球の周りを回転する月の、太陽から見た軌道を調べた。太陽から見た月は、地球に寄り添うようにして太陽の周りを回っているように見えることが分かった。