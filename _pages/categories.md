---
layout: page
title: カテゴリー
permalink: /categoris/
---

<ul>
  {%- for page in site.pages -%}
  {%- if page.layout == 'category' -%}
    <li>
      <a href="{{ page.url | absolute_url }}">{{ page.title }}</a>
    </li>
  {%- endif -%}
  {%- endfor -%}
</ul>    
