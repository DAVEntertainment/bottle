# Description
Demo of libraries dependencies
```
    nested_lib_deps
     /         \
    |           |
shared_a      shared_b
    |           |
static(v1)    static(v2)
```
Intended to prove that shared library `a` and shared library `b` can link to same library with different versions.

Call stack
```
             nested_lib_deps (main)
           /                      \
          |                        |
shared_a (show_a)           shared_b (show_b)
          |                         |
static(v1) (check(v1))    static(v2) (check(v2))
```


# Setup boost
Just run following command to setup boost for demo
```
python ../build_boost/build.py --static
```

# How to
Just run following command to run the demo
```batch
build_demo.cmd
```

# Tips
### Check exported symbols
```
dumpbin /EXPORTS /SYMBOLS demod.dll
```
