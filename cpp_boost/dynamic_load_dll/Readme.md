# Description
Demo of refering a shared library with boost

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
