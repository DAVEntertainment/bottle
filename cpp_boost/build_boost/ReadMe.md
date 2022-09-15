# Description
A script to build boost with b2 (provided by boost)

### build.py
Please make sure the environment of git is OK, which means:
- user is set, and available to access to github
- ssh private key is set, and available to access to github

Then simply run
```
python build.py
```

Wait and boost_x_xx_x folder will be generated alongside build_boost folder.
`x_xx_x` is the version of boost.
e.g. boost 1.79.0 will generate boost_1_79_0.

### boost_tuils.cmake
Provide some utils for using boost
