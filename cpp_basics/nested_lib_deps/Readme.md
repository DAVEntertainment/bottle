# Description
Demo of libraries dependencies
```
    nested_lib_deps
     /         \
    |           |
shared_a      shared_b
    |           |
static(v0)    static(v1)
```
Intended to prove that shared library `a` and shared library `b` can link to same library with different versions.

Call stack
```
             nested_lib_deps (main)
           /                      \
          |                        |
shared_a (show_a)           shared_b (show_b)
          |                         |
static(v0) (check(v0))    static(v1) (check(v1))
```


# How to
Just run following command to run the demo
```batch
build.cmd
```

# Tips
### Check exported symbols
```
dumpbin /EXPORTS /SYMBOLS shared_a.dll
```
