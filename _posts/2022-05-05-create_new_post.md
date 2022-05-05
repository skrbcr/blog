---
layout: post
title: "Jekyll を用いて GitHub Pages に記事を投稿する"
date: 2022-05-05
categories: manage
---
[Jekyll のインストールから GitHub Pages での公開まで](https://skrbcr.github.io/blog/manage/setup_pages) のつづき。やはりメモ書きなので必要な情報は網羅されていません。

## 実行環境

| ソフト | バージョン |
| :-: | :-: |
| OS | Windows 11 Home |
| Ruby | 3.1.0p0 |
| Jekyll | 4.2.1 |
| GitHub Desktop | 3.0.0 |
| Visual Studio Code | 1.66.2 |

Visual Studio Code を使って記事を作成しています。なお、Ruby がアップデートされていないです。

## 作業の流れ
1. `_posts` フォルダ内にファイル作成
2. 記事の中身を書く
3. 変更を commit して push
4. 投稿完了

結局は [Posts - Jekyll](https://jekyllrb.com/docs/posts/) に従えばよい。

## 作業過程
まず、プロジェクト内の `_posts` フォルダに Markdown や HTML のファイルを作成する。ファイル名は `YYYY-MM-DD-title.md` つまり `2022-05-05-physics.md` のような形式にする。

記事の中身を書いていく。冒頭部には次のように書く。これにより、Jekyll がタイトルや投稿日などを自動的に設定してくれる：

```md
---
layout: post
title: "アヒルの観察"
date: 2022-05-05
categories: physics
---

（ここから記事の中身を書く）みなさんはアヒルが好きですか？　私は好きでも嫌いでもないです。
・・・・・・
・・・
```

ところで、記事中に画像などを挿入したい場合は、それらを `assets` フォルダ内に入れておくことで使えるようになる（こちらはファイル名の指定はない）。例として、このサイト `https://skrbcr.github.io/blog/` で記事を作成していて、画像 `awsome_photo.jpg` を使いたい場合。`assets` フォルダに `awsome_photo.jpg` を入れておけば、`https://skrbcr.github.io/blog/assets/awsome_photo.jpg/` で画像が利用できるようになる。つまり

```html
<img src="https://skrbcr.github.io/blog/assets/awsome_photo.jpg/">
```

と書けば、そこに画像が表示される。

記事が書けたら commit し、GitHub の Repository に push すれば投稿完了。

暫くすると反映されるので、実際の投稿を確認して終了。
