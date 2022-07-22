---
layout: post
title: "円筒まわりの定常流"
date: 2022-07-22
categories: physics
---

## 調べること
流体力学の講義で複素速度ポテンシャルを学習した。具体例として、一様流のなかに円筒を置いた場合の流れを計算した。そこで、コンピュータで流れを計算・描画してみることにした。コード（Python）は[こちら](https://github.com/skrbcr/blog/blob/main/assets/2022-07-22-cylinder_flow/cylinder.py)。

内容の薄い記事だが、作りかけで放置状態だったのでとりあえず文章をまとめて公開することにした。

## 一様流中に置かれた円筒周りの流れ
二次元平面上に一様な流れを考える。流れ（左図）や各点での流体の速度（右図。左図よりも2倍拡大してあることに注意）を図示すると、下図のようになる：
<center><img src="/blog/assets/2022-07-22-cylinder_flow/uniform_flow_stream.svg" style="width: 50%"><img src="/blog/assets/2022-07-22-cylinder_flow/uniform_flow_quiver.svg" style="width: 50%"></center>
この一様流の中に、中身の詰まった円を入れてみる。あるいは、円筒を置いてみる。流れは直感通り、次のようになる：
<center><img src="/blog/assets/2022-07-22-cylinder_flow/norm_stream.svg" style="width: 50%"><img src="/blog/assets/2022-07-22-cylinder_flow/norm_quiver.svg" style="width: 50%"></center>
左の図からは、流体が円筒（円）を避けるようにして流れていることがわかる。右の図からは、円筒表面では流速が $0$ になる淀み点 $(-1, 0), (1, 0)$ と一様流の速さ（例えば $(2.0, 2.0)$ あたり）よりも大きくなる点 $(0, -1), (0, 1)$ があることがわかる。

## 循環を加える
前節の流れに下図のような渦糸（循環）を加えてみる。
<center><img src="/blog/assets/2022-07-22-cylinder_flow/rot_stream.svg" style="width: 50%"><img src="/blog/assets/2022-07-22-cylinder_flow/rot_quiver.svg" style="width: 50%"></center>
このとき、流れの様子は、循環の大きさにより変化する。

### 循環が小さい場合
<center><img src="/blog/assets/2022-07-22-cylinder_flow/rot_weak_stream.svg" style="width: 50%"><img src="/blog/assets/2022-07-22-cylinder_flow/rot_weak_quiver.svg" style="width: 50%"></center>
循環流と一様流の向きが同じとなる上側では流速が速くなり、下側では遅くなる。ここまでは直感的な結果が得られている。

### 循環が特別な大きさの場合
<center><img src="/blog/assets/2022-07-22-cylinder_flow/rot_med_stream.svg" style="width: 50%"><img src="/blog/assets/2022-07-22-cylinder_flow/rot_med_quiver.svg" style="width: 50%"></center>
循環の流速を上げていくと、やがて円筒下部に特徴的な流れが出現する。左側の流れと右側の流れがぶつかり合う点ができる。具体的な循環の大きさは、流速を $U$、円筒の半径を $a$ とすると $\Gamma = 4\pi Ua$。

### 循環が大きい場合
<center><img src="/blog/assets/2022-07-22-cylinder_flow/rot_strong_stream.svg" style="width: 50%"><img src="/blog/assets/2022-07-22-cylinder_flow/rot_strong_quiver.svg" style="width: 50%"></center>
さらに循環の流速を上げると円筒下部の淀み点は円筒から離れた位置に移動する。直感的には分かりずらい流れが発生している。
