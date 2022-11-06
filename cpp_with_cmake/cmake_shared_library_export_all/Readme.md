# Description
Demos of generating shared library with cmake,
and the lib support find_package to link the generated library

Just run following command to run the demo
```batch
build_demo.cmd
```

Demo structure
```
lib_ref_demo (exe)
`-- demo.dll (shared)       - add del
    `-- sub.lib (static)    - sub
```


# How to check exported symbols
```batch
dumpbin /exports demo.dll
```
