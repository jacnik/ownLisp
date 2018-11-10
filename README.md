Lisp interpreter project build from scratch in C <br />
[this project is following this amazing online book](http://www.buildyourownlisp.com/contents)

## Notes to self:

* compiling with linkes to a file in a ./external directory: <br />
cc -std=c99 -Wall prompt.c ./external/mpc.c -ledit -lm -o parsing   
- -lm -> link to the maths library
- -ledit -> link to the editline library
- ./external/mpc.c -> link to the mpc.c file in the ./external directory

* compiling a c file with cc and C99 standard:<br />
cc -std=c99 -Wall prompt.c -o prompt

* compiling with linking to 'editline' library: <br />
cc -std=c99 -Wall prompt.c -ledit -o prompt

* [gdb tutorial](http://web.archive.org/web/20140910051410/http://www.dirac.org/linux/gdb/)<br />

* installing editline library for ubuntu: <br />
sudo apt-get install libedit-dev

* [mpc repository](https://github.com/orangeduck/mpc) <br />


