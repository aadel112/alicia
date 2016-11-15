* the basic idea is to have a C++ framework that can work with sqlite to store all data in a database
* there would then be maybe a python script or something I'm thinking that would read a SQL file and translated into C++ and compile it.
* features that should be back in include:
    - basic ability to store variables do arithmetic
        - input and output
        - output would definitely be through select
        - input would likely have to be done through custom syntax
    - ability to construct functions with SQL syntax
        - sqlite only supports on insert ignore triggers in place of functions
        - this should actually be fine as the python or whatever scripted translate ANSI SQL functions to triggers
    - Json support
        - is really cool I dreaded pythonesque, it's Name Escapes me but it's probably what I'll end up using
    - web framework support
        - I'd like this symbol table to contain something similar to PHP post good session Etc variables

=================================================
other details
=================================================
* this is an sqlite database stored in memory
* it should be able to support threads
* if the roads aren't used it should use fsync off
* if they are it should use an asynchronous read uncommitted model

* for SQL functions in language constructs like for loops yielding stuff like that will be written in SQL and loaded on Startup

* the Alicia class Handel's databases C++ interaction
* the python script will handle the extended SQL, converting it to Alicia, compiling it if needed, and running it

* implementation on the conversion is still entirely decided. I may just keep it in C++ in the alicia Class

* development is completely test-driven
