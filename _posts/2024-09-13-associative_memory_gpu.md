---
layout: post
title: "GPU を用いた連想記憶モデル（Hopfield network）の実装"
date: 2024-09-13
categories: physics
---

## 概要

[以前](https://skrbcr.github.io/blog/physics/associative_memory)、古典的なニューラルネットワーク「連想記憶モデル（Hopfield network）」の実装を紹介した。
今次、外付けGPU（Nvidia GeForce RTX 4060）を搭載したパソコンを導入したため、計算に GPU を使用する実装を行った。
CPU 実装より大幅に速く実行できることを確認し、前回は行わなかったいくつかの実験を行った。

## 実装

今回は Python を用いた。
GPU 計算には、[CuPy](https://cupy.dev/) を使用した。
これは Python のパッケージで、NumPy や SciPy の使用感で GPU 計算を利用することができる。

