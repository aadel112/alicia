#!/usr/bin/env bash

cat ../libAlicia.c | grep '^.\*'| perl libdoc.pl > libAlicia.md

pod2html ../Alicia.pm > Alicia.html

pandoc -f html -t markdown_github Alicia.html  > Alicia.md

cat Alicia.md | grep -v ^\s*\- | grep -v '#METHOD'> Alicia.md.tmp && mv Alicia.md.tmp Alicia.md

rm Alicia.html

n=$((`cat -n Alicia.md | grep METHODS | awk -F' ' '{print $1}'`))

INS_PERF=$(( $n$n - 1 ))
WC=$((`cat Alicia.md | wc -l`))
REST=$(( $WC - $n + 1 ))

exec > README.md

cat Alicia.md | head -$INS_PREF
cat perf.md 
cat libAlicia.md
cat Alicia.md | tail -$REST

