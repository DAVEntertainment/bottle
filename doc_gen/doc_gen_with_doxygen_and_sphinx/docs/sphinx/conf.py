# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.

import os
import sys

repoRoot = os.path.abspath(os.path.join(__file__, '..', '..', '..'))

# @@@ if build.py and builder.py cannot be imported,
# @@@ then the doc for them will not be included
scriptsRoot = os.path.abspath(os.path.join(repoRoot, 'scripts'))
sys.path.insert(0, scriptsRoot)

# -- Project information -----------------------------------------------------
project = 'demo'
copyright = '2022, dav'
author = 'dav'

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [ # @@@
    'breathe',
    'sphinx.ext.autodoc',
    'sphinx.ext.imgmath',
    'sphinx.ext.todo',
]

# Breathe Configuration
breathe_default_project = 'demo' # @@@
breathe_projects = {
    'demo': os.path.join(repoRoot, '.build/doxygen/xml')  # @@@ add demo root
}
