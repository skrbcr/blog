---
layout: post
title: "KaTeXの導入・使用"
date: 2022-03-08
categories: manage
---

## $\KaTeX$ について
$\KaTeX$（<a href="https://katex.org/" target="_blank">公式サイト</a>）は、HTML 文書上で（$\approx$ Web ページで）数式を綺麗に高速で表示させるための Java Script ライブラリである。$\LaTeX$ の Web 版のようなもの。

## $\KaTeX$ の導入
### 基本の導入方法
まず、ページ上で $\KaTeX$ を使えるようにする。基本的には、公式ドキュメントの <a href="https://katex.org/docs/browser.html" target="_balnk">Installation/Browser</a> に従って作業すればよい。HTML 文書の `<head>` タグ内に以下を記述する：
```html
<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.15.2/dist/katex.min.css" integrity="sha384-MlJdn/WNKDGXveldHDdyRP1R4CTHr3FeuDNfhsLPYrq2t0UBkUdK2jyTnXPEK1NQ" crossorigin="anonymous">
<script defer src="https://cdn.jsdelivr.net/npm/katex@0.15.2/dist/katex.min.js" integrity="sha384-VQ8d8WVFw0yHhCk5E8I86oOhv48xLpnDZx5T9GogA/Y84DcCKWXDmSDfn13bzFZY" crossorigin="anonymous"></script>
<script defer src="https://cdn.jsdelivr.net/npm/katex@0.15.2/dist/contrib/auto-render.min.js" integrity="sha384-+XBljXPPiv+OzfbB3cVmLHf4hdUFHlWNZN5spNQ7rmHTXpd7WvJum6fIACpNNfIR" crossorigin="anonymous"></script>
```
これにより、$\KaTeX$ の機能を使えるようになる。

### Jekyll で使用する場合
Jekyll は初期設定で、$'$ を $’$ に変換してしまう。数式では $f'(x)$ のように $'$ を使うので、 `_config.yml` に次を記述する：
```yaml
kramdown:
  smart_quotes: ["apos", "apos", "quot", "quot"]
```
詳細やこれで上手くいく理由は <a href="https://stackoverflow.com/questions/25596792/how-do-i-turn-off-smart-quotes-in-jekyll" target="_blank">How do I turn off smart quotes in Jekyll?</a> や <a href="https://github.com/KaTeX/KaTeX/issues/967" target="_blank">Render smart quotes in math as regular quotes</a> を参照。

### カスタマイズ
$\KaTeX$ はマクロなどをカスタマイズできる。`<head>` タグ内に続けて次のように書けばよい：
```html
<script>
    document.addEventListener("DOMContentLoaded", function() {
        renderMathInElement(document.body, {
            // 以下、カスタマイズ内容を記述

            // 「$（数式）$」でインライン表示、などの設定
            delimiters: [
                {left: '$$', right: '$$', display: true},       // デイスプレイ表示
                {left: '$', right: '$', display: false},        // インライン表示
                {left: '\\(', right: '\\)', display: false},    // デイスプレイ表示
                {left: '\\[', right: '\\]', display: true}      // インライン表示
            ],
            // マクロの定義
            macros: {
                "\\arsinh": "\\text{ar}\\!\\sinh",      // \arcsin{#1}
                "\\dd": "\\,d",                         // \dd{#1}
                "\\dv": "\\frac{d #1}{d #2}",           // \dv{#1}{#2}
            },
            // エラー発生時に Console Window にエラーメッセージを表示するか
            throwOnError : false,       // しない
        });
    });
</script>
```
バックスラッシュ あるいは 円マーク `\` は エスケープする（`\\` と記述する）ことに注意。

マクロの設定は若干分かりずらいが、例えば `\dv` であれば、上の通り設定しておけば `\dv{y}{x}` は $\\dv{y}{x}$ と表示される。

## $\KaTeX$ の使用
$\LaTeX$ のように使用すればよい。ただし、いくつかの相違点はあるので注意が必要。例えば、`$` や `$$` 記号による数式の括りは上のように自分で設定する必要がある。使用できる関数は、公式ドキュメントの <a href="https://katex.org/docs/supported.html" target="_blank">Supported Function</a> を参照。

また、`equation` などの環境が用意されているが、`$$, $$` や `\\[, \\]` で囲って使用する。そうしないと、数式として認識されない。
```html
Schrödinger 方程式：

$$\begin{equation}
    i\hbar\frac{\partial}{\partial t}\psi(\vec{x}, t) = \hat{H}\psi(\vec{x}, t)
\end{equation}$$
```

Schrödinger 方程式：

$$\begin{equation}
    i\hbar\frac{\partial}{\partial t}\psi(\vec{x}, t) = \hat{H}\psi(\vec{x}, t)
\end{equation}$$
