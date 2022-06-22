# Demo

# Description

This is a project demo for documentation generation

# Tips

This can be specified by `USE_MDFILE_AS_MAINPAGE`, so that it will be used as the main page

# How-gen setup environment for this demo
### setup for doxygen
1. install doxygen
2. add doxygen/bin to path

### Setup for sphinx
1. setup virtualenv, init with requirements.txt (for sphinx)

# How-to gen doc with this demo?
1. run doxygen-cmd.cmd (in repo root)
2. run sphinx-cmd.cmd (in repo root), from the virtualenv just created

Be careful to run shpinx-cmd after doxygen-cmd, sphinx will include docs gen by doxygen

U can get demo doc:
- doxygen in <root>/.build/doxygen/html/index.html
- sphinx in <root>/.build/sphinx/index.html

# TODO:
- [x] Generate with doxygen
- [x] Add main page for doxygen output
- [x] Fix doxygen output empty
- [x] Find sphinx-build.exe with finx_package
- [x] Build doc with sphinx and doxygen
- [ ] Fix sphinx output empty
