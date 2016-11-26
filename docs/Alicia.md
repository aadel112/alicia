-   [NAME](#NAME)
-   [SYNOPSIS](#SYNOPSIS)
-   [DESCRIPTION](#DESCRIPTION)
    -   [METHODS](#METHODS)
-   [LICENSE](#LICENSE)
-   [AUTHOR](#AUTHOR)

NAME
====

**Alicia** - SQL As a high speed, all-purpose programming language

SYNOPSIS
========

DESCRIPTION
===========

METHODS
-------

`new`  
Returns a new Alicia object, initializes the symbol table, called \_ST, creates its statements, indexes it; sets up an SQLite database as the memory-store. This is optimal for many reasons.

`main`  
Called by the CLI, initializes a new Alicia object, parses, and executes the Alicia script or stdin.

`parse_and_execute_statements`  
parses the very limited set of Alicia specific instructions, and executes them as appropriate

`set`  
is called by the execution if the instruction "SET('something', 'value'). You can nest these, such as SET('five', GET('three') + 2). This is pretty highly optimized, as it's very limited. These values are all stored in the symbol\_table (\_ST).

`get`  
is called by the execution if the instruction GET('something') is used. These can be nested, for example, GET(GET('value references something in \_ST'))

`drop`  
Drops a table

`truncate`  
Truncates a table

`exec`  
executes any sql that isn't in the limited instruction set

`read`  
reads a delimited file into a table, where the fields will be all text, and will be named like f0, f1, f2, etc.

`write`  
writes a table to a delimited file.

LICENSE
=======

MIT License

Copyright (c) 2016 Aaron Adel

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

AUTHOR
======

Aaron Adel -<http://aadel112.com>, -<https://github.com/aadel112>
