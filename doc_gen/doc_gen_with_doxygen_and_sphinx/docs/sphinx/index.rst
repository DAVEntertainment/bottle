.. demo documentation master file, created by
   sphinx-quickstart on Sun Nov 21 00:45:39 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to demo's documentation!
================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

Content
==================

.. py:function:: enumerate(sequence[, start=0])

   Return an iterator that yields tuples of an index and an item of the
   *sequence*. (And so on.)

.. if python scripts path is included in conf.py,
   then we can easily gen its doc with following commands

.. autoclass:: build.Builder

.. autofunction:: build.main

Doxygen Specified Content
=================================

.. to involve doxygen doc, use breathe defined keywords to include pages gen by doxygen
   see more at https://breathe.readthedocs.io/en/latest/index.html

.. doxygenfunction:: add

.. doxygenclass:: Opera

.. doxygenclass:: Operator

Doxygen Page
=================================

.. in .build/docs/doxygen/xml, there must be a xml named ???page.xml
   in this case, indexpage.html
   see more at https://breathe.readthedocs.io/en/latest/page.html
.. doxygenpage:: index
    :project: demo

Doxygen Namespace
=================================

.. in .build/docs/doxygen/xml, there must be a xml named namespace???.xml
   in this case, namespacebuild.html
   see more at https://breathe.readthedocs.io/en/latest/namespace.html
.. doxygennamespace:: build
   :project: demo

Doxygen Index
=================================

.. doxygenindex::
   :project: demo
   :outline:
   :no-link:

