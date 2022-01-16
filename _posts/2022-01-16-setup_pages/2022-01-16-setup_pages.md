---
layout: post
title: "Jekyll のインストールから GitHub Pages での公開まで"
date: 2021-01-16
categories: 管理
---

Jekyll をインストールし、GitHub Pages で公開する作業のメモ書き

## 実行環境

| ソフト | バージョン |
| :-: | :-: |
| OS | Windows 11 Home |
| Ruby | 3.1.0p0 |
| Jekyll | 4.2.1 |

## 作業の流れ
1. Ruby をインストール
2. Jekyll と Bundler のインストール
3. Jekyll で新しいプロジェクトの作成、設定
4. GitHub でレポジトリを作成、設定
5. プラグインのインストール

## Ruby をインストール
<a href="https://jekyllrb.com/docs/installation/windows/" target="_blank">Jekyll on Windows - Jekyll</a> や <a href="http://jekyllrb-ja.github.io/docs/installation/windows/" target="_blank">Jekyll on Windows - Jekyll（日本語）</a> などに従って、作業を進める：
- <a href="https://rubyinstaller.org/downloads/" target="_blank">RubyInstaller のダウンロードページ</a> より **WITH DEVKIT** のインストーラをダウンロード
- インストーラを起動し、既定の設定のままでインストールを実行
- 終了後 `ridk install` のチェックを入れたままウィザードを閉じる
- 起動したプロンプトで指示に従い作業を完了させる
- `$ ruby -v` でバージョン情報が表示されること（＝インストール済）を確認

## Jekyll と Bundler のインストール
```
$ gem install jekyll bundler
```
完了後、インストール済みを確認：
```
$ jekyll -v
$ bundler -v
```

## Jekyll で新しいプロジェクトの作成、設定
### プロジェクトの作成・とりあえずビルド
`project_name` という名前のプロジェクトを作る例：
```
$ jekyll new project_name
$ cd project_name
$ jekyll serve
```
`$ jekyll serve` は `$ jekyll s` でも可。ローカルサーバー上にサイトが生成される。エラーが出なければ生成成功。  
<a href="http://127.0.0.1:4000/" target="_blank">http://127.0.0.1:4000/</a> にアクセス。終了時は、`Ctrl + C` をコマンドプロンプトに入力。

#### サイト生成時にエラーが出る場合
まだ何も変なことをしていないにも拘わらず、`$ jekyll serve` で以下のようなエラーが出ることがある：
```
                    ------------------------------------------------
      Jekyll 4.2.1   Please append `--trace` to the `serve` command
                     for any additional information or backtrace.
                    ------------------------------------------------
```
解決策は、<a href="https://github.com/jekyll/jekyll/issues/8523" target="_blank">Jekyll serve fails on Ruby 3.0</a> にあるように
```
$ bundle add webrick
```
を実行すればよい。これは、プロジェクト毎に一度実行すればOK。

また、ページ編集後にこのようなエラーが出る場合は、記述ミスも疑う。エラーの内容を読んで対応する。

## GitHub でレポジトリを作成、設定 
GitHubにレポジトリを作成する。
GitHub Pages の設定を行う。<a href="https://docs.github.com/en/pages/getting-started-with-github-pages/configuring-a-publishing-source-for-your-github-pages-site" target="_blank">Configuring a publishing source for your GitHub Pages site - GitHub Docs</a> の通り。

## プラグインのインストール
<a href="http://jekyllrb-ja.github.io/docs/plugins/installation/" target="_blank">プラグイン - Jekyll（日本語）</a> に従う。例えば、絵文字を表示するプラグイン `jemoji` をインストールする場合。  
まず、自身の環境（PC）にインストール：
```
$ gem install jemoji
```
これはプロジェクトごとに行う必要はないはず（要調査！）。

次に、プロジェクトに設定する。  
`_config.yml` に以下を追記：
```yaml
plugin:
  - jemoji
```
そして `Gemfile` に以下を追記：
```ruby
gem 'jemoji'
```
これで絵文字が使えるようになる :smile:

## メモ書きのメモ
ページ作成方法も書く
