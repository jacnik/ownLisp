Lisp interpreter project build from scratch in C <br />
[this project is following this amazing online book](http://www.buildyourownlisp.com/contents)

## Notes to self:

* compiling with links to a file in a ./external directory: <br />
```console
cc -std=c99 -Wall lispy.c ./external/mpc.c -ledit -lm -o lispy 
```
-lm -> link to the maths library  
-ledit -> link to the editline library  
./external/mpc.c -> link to the mpc.c file in the ./external directory  

* compiling a c file with cc and C99 standard:<br />
```console
cc -std=c99 -Wall prompt.c -o prompt
```

* compiling with linking to 'editline' library: <br />
```console
cc -std=c99 -Wall prompt.c -ledit -o prompt
```

* [gdb tutorial](http://web.archive.org/web/20140910051410/http://www.dirac.org/linux/gdb/)<br />

* installing editline library for ubuntu: <br />
```console
sudo apt-get install libedit-dev
```

* [mpc repository](https://github.com/orangeduck/mpc) <br />

