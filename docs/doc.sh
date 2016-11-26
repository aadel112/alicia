#!/usr/bin/env bash

cat ../libAlicia.c | grep '^.\*'| perl libdoc.pl > libAlicia.md

pod2html ../Alicia.pm > Alicia.html

pandoc -f html -t markdown_github Alicia.html  > Alicia.md

cat Alicia.md | grep -v ^\s*\- > Alicia.md.tmp && mv Alicia.md.tmp Alicia.md

rm Alicia.html
