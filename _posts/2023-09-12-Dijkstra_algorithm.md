---
layout: post
title: "ダイクストラ法"
date: 2023-10-30
categories: programming
---

## 記事の趣旨
ダイクストラ法の適切な実装をするのに時間が掛かったので、ここにまとめた。初級者の解説だが、ダイクストラ法の原理についても自分なりに説明した。幅優先探索（BFS）を知らない方はそちらを先に確認されたい。

## 問題設定

## 計算方法―ダイクストラ法
### 原理
幅優先探索（BFS）を改良し、頂点間の距離を考慮した探索を行う。参考にしたページ[^1]によると、ダイクストラ法は次のようにして探索を行う：

1. `queue` に始点と、始点からの距離（0）を push。始点からの最短距離を記録する配列 `dist` の始点を0にする。
2. `queue` が空になるまで、次をループ：
    - `queue` から、始点からの距離が一番短い頂点を取り出す
    - `dist` に記録された距離よりも取り出した頂点に記録された距離の方が大きいならば、その頂点に用はない。次の回のループへ
    - 取り出した頂点に隣接する頂点に対してそれぞれ、最短距離 `dist` が更新できる場合は、更新した上で `queue` にその頂点と始点からの距離情報を push。更新できない場合は何もしない

これで始点から各頂点への最短距離が求まるが求まる。その理由を考えてみる。

[^1]: [最短経路問題総特集！！！～BFSから拡張ダイクストラまで～](https://qiita.com/ageprocpp/items/cdf67e828e1b09316f6e#%E3%83%80%E3%82%A4%E3%82%AF%E3%82%B9%E3%83%88%E3%83%A9%E6%B3%95)

### priority_queue

### 実装例
C++ での実装。C++11 以降が必要。

```cpp
#include <bits/stdc++.h>
using namespace std;

template <class T> bool chmin(T &a, T b) { if (a > b) { a = b; return true; } return false; }

int main() {
    // 入力処理
    int m, n, r;
    cin >> m >> n >> r;
    // pair の中身は {頂点間の距離, 頂点}. que に合わせている
    vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>());
    for (int _; _ < m; ++_) {
        int s, t, d;
        cin >> s >> t >> d;
        // --s; --t;  // 1-index の場合
        g[s].push_back(make_pair(d, t));
        // g[t].push_back(make_pair(d, s));  // 無向グラフの場合
    }

    // ダイクストラ法
    vector<int> dist(n, INF);
    dist[r] = 0;
    // pair の中身は {始点からの距離, 頂点}. この順番にすることで、距離で昇順（greater<pair<int, int>>）になる
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
    que.push(make_pair(0, r));
    
    while (!que.empty()) {
        auto v = que.top();
        que.pop();
        if (dist[v.second] < v.first) continue;
        for (auto &nv : g[v.second]) {
            if (chmin(dist[nv.second], dist[v.second] + nv.first)) que.push(make_pair(dist[nv.second], nv.second));
        }
    }

    // 結果を出力するなど

    return 0;
}
```

