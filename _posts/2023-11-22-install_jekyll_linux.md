---
layout: post
title: "Jekyll のインストール（WSL・Linux の場合）"
date: 2023-11-26
categories: manage
---

[以前の記事](https://skrbcr.github.io/blog/manage/setup_pages)の Linux 版です。

## 実行環境

| ソフト | バージョン |
| :-: | :-: |
| OS | Windows 11 Home 23H2 |
| WSL | 2.0.9.0 |
| Linux | Arch Linux |
| Ruby | 3.0.6p216 |
| Jekyll | 4.2.2 |

## 作業の流れ
1. Ruby と Bundler をインストール
2. Jekyll のインストール

## Ruby と Bundler をインストール
まずは Ruby。各OS 毎のインストールコマンドが [docs](https://jekyllrb.com/docs/installation/other-linux/) に掲載されている。
```bash
$ sudo pacman -S ruby base-devel
```

次に Bundler。
```bash
$ gem install bundler
```

そして環境変数の設定。[docs](https://jekyllrb.com/docs/installation/ubuntu/) に従う。私は fish を使用しているので `config.fish` に以下を追記する。

```bash
set -gx PATH $PATH $HOME/.local/share/gem/ruby/3.0.0/bin
set -gx GEM_HOME $HOME/gems
```

## Jekyll のインストール
```bash
$ gem install jekyll
```

最後にインストールされたことを確認：
```bash
$ bundle --version
$ jekyll --version
```

以下、プロジェクトの作成からは [Windowsのとき](https://skrbcr.github.io/blog/manage/setup_pages#jekyll-で新しいプロジェクトの作成設定)と同じ。

