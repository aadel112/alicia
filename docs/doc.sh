#!/usr/bin/env bash

cat ../libAlicia.c | grep '^.\*'| perl libdoc.pl > libAlicia.md
