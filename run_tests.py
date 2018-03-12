from __future__ import absolute_import, division, print_function

from libtbx.test_utils.pytest import discover

tst_list = [
  "$D/annlib_adaptbx/sample.py",
  "$D/annlib_adaptbx/self_match.py",
] + discover()
