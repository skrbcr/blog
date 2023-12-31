---
layout: post
title: "rbenv を用いて Ruby をインストール"
date: 2023-12-30
update: 2023-12-31
categories: programming
---

Ruby の最新版が必要になり調べていたところ、Ruby 環境を管理する rbenv を知ったのでインストールした。

## 実行環境

| ソフト | バージョン |
| :-: | :-: |
| OS | Windows 11 Home 23H2 22631.2861 |
| WSL | 2.0.9.0 |
| Linux | Arch Linux |
| rbenv | 1.2.0 |
| Ruby | 3.3.0 |

## 作業の流れ

1. rbenv のインストール
2. Ruby のインストール
3. プロジェクトのセットアップ

## rbenv のインストール
[GitHub の README](https://github.com/rbenv/rbenv) に従う。自分は Arch Linux を使っているので以下の通り

### AUR パッケージから rbenv をダウンロード・インストール
[AUR のサイト](https://aur.archlinux.org/packages/rbenv) で Git の URL を入手。上の方の `Git Clone URL` がそれ。クローンする：
```bash
$ git clone https://aur.archlinux.org/rbenv.git
```

インストール：
```bash
$ cd rbenv
$ makepkg -sirc
```

参考文献：[Arch User Repository](https://wiki.archlinux.jp/index.php/Arch_User_Repository)

### rbenv の初期作業
次のコマンドを実行して表示される指示に従う：
```bash
$ rbenv init
```

### ruby-build のインストール
rbenv のプラグインである ruby-build もインストールする。

まずは [Suggested build environment](https://github.com/rbenv/ruby-build/wiki#suggested-build-environment) にある requirement を満たしておく。そしてインストール：
```bash
$ git clone https://github.com/rbenv/ruby-build.git "$(rbenv root)"/plugins/ruby-build
```

## Ruby のインストール
### Ruby
ruby-build をインストールすることで `rbenv install` が使えるようになる。

安定版のリストを確認：
```bash
$ rbenv install -l
```

ヴァージョンを選んでインストール（例えば 3.3.0）：
```bash
$ rbenv install 3.3.0
```

使用する Ruby のヴァージョンを選択しておく。
```bash
$ rbenv local 3.3.0  # プロジェクトのディレクトリで実行すると、そのプロジェクトにのみ適用
# もしくは
$ rbenv global 3.3.0  # デフォルトを設定
```

### Bundler
パッケージ管理を行う Bundler をインストールする：
```bash
$ rbenv exec gem install bundler
$ rbenv exec bundle --version
```

## プロジェクトのセットアップ

システムに Bundler がインストールされていない場合は `bundle` コマンドに `rbenv exec` を付ける必要はないらしい。

```bash
$ rbenv exec bundle init
# システムに Bundler がインストールされて「いない」場合は下でも可：
$ bundle init
```

Gemfile が生成されるので、必要なパッケージを書いてインストール。まずはインストール場所を指定しておく（一度だけ実行すればよい）：

```bash
# gem はこのプロジェクトのみにインストール。vendor/bundle ディレクトリが生成される
$ rbenv exec bundle config set path 'vendor/bundle'
```

gem をインストールする：
```bash
$ rbenv exec bundle install
```

ネットでは `rbenv exec bundle install --path=vendor/bundle` コマンドが紹介されていた。しかし、これを実行すると上の通りに改めよと警告される。将来的に `--path` フラグは使えなくなるようだ。

## rbenv のアップデート
rbenv のアップデート方法についてもまとめる。

- rbenv 自体は rbenv の レポジトリを pull し、再度インストールすればよい：
```bash
$ cd /path/to/rbenv
$ git pull
$ makepkg -sirc
```
- ruby-build：
```bash
$ git clone https://github.com/rbenv/ruby-build.git "$(rbenv root)"/plugins/ruby-build
```

