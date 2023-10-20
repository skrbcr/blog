---
layout: post
title: "積分公式"
date: 2022-01-28
update: 2023-10-20
categories: math
---

## 不定積分

$$\begin{equation}
    \int \frac{1}{a^2 + x^2} \dd x = \frac{1}{a}\arctan\frac{x}{a}
\end{equation}$$

$$\begin{equation}
    \int \frac{1}{a^2 - x^2} \dd x = \frac{1}{a}\artanh\frac{x}{a}
\end{equation}$$

$$\begin{equation}
    \int \frac{1}{\sqrt{a^2 - x^2}} \dd x = \arcsin\frac{x}{a}
\end{equation}$$

$$\begin{equation}
    \int \frac{1}{\sqrt{x^2 + a}} \dd x = \log\left| x + \sqrt{x^2 + a}\right|
\end{equation}$$

### $\tan{\frac{x}{2}} = t$ の置換積分
$x$ から $t$ へ $\tan{\frac{x}{2}} = t$ の置換。次のように変換される：

$$\begin{align}
    \dd x = \frac{2}{1 + t^2} \dd t
\end{align}$$

$$\begin{align}
    \sin x = \frac{2t}{1 + t^2}, \quad\cos x = \frac{1 - t^2}{1 + t^2}, \quad\tan x = \frac{2t}{1 - t^2}
\end{align}$$

## 定積分
### Gauss関数

$$\begin{gather}
    \int_{-\infty}^{\infty} e^{-ax^2} \dd x = \sqrt{\frac{\pi}{a}} \\
    \int_{-\infty}^{\infty} x^2 e^{-ax^2} \dd x = \frac{1}{2}\sqrt{\frac{\pi}{a^3}} \\
    \int_{-\infty}^{\infty} x^4 e^{-ax^2} \dd x = \frac{3}{4}\sqrt{\frac{\pi}{a^5}}
\end{gather}$$

複素平面上で積分経路を虚軸方向にずらした場合：

$$\begin{align}
    \int_{-\infty}^{\infty} e^{-a(x + ib)^2} \dd x = \sqrt{\frac{\pi}{a}}
\end{align}$$

### 三角関数

$$\begin{align}
    \int_{0}^{\frac{\pi}{2}} \sin^{n}x\dd x = \int_{0}^{\frac{\pi}{2}} \cos^{n}x\dd x =
    \begin{cases}
        \dfrac{(n-1)!!}{n!!}\dfrac{\pi}{2} \\\\
        \dfrac{(n-1)!!}{n!!}
    \end{cases}
\end{align}$$
