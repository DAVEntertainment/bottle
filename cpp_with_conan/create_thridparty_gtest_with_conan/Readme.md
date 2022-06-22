# Description
This is the official Conan gtest recipe
From [Conan Center Index](https://github.com/conan-io/conan-center-index)
Here is the link: [GTest Recipe](https://github.com/conan-io/conan-center-index/tree/master/recipes/gtest)

# How to build
Run the command below to build gtest demo
```bash
conan create . gtest/1.11.0@demo/testing
```

# How to upload
Run the command below to upload gtest library
```bash
conan upload gtest/1.11.0@demo/testing --all -r=conancenter
```

# Notes
conanfile.py        - recipe
conan_file_dict.log - log for a ConanFile instance

# Related links
[Conan Center Index](https://github.com/conan-io/conan-center-index)
[Recipes](https://github.com/conan-io/conan-center-index/tree/master/recipes)

# Demo for local built package references
Here, we clone demo *build_with_gtest_static* as use_gtest_cache_demo to prove the usage of a local built conan package.

Run following command to install gtest for demo build_with_gtest_static
```
conan install use_gtest_cache_demo -if build --build=missing
```
When installing package, there will be logs
```
conanfile.txt: Installing package
Requirements
    gtest/1.11.0@demo/testing from local cache - Cache
Packages
    gtest/1.11.0@demo/testing:3fb49604f9c2f729b85ba3115852006824e72cab - Build
```
Keyword `from local cache - Cache` proves gtest is used from local cache

# TODO
- [ ] gtest/1.11.0@demo/testing do not generate FindGTest.cmake, which makes `build_use_demo.cmd` not able to build demo

