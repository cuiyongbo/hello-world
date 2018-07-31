**************************************
Batch remove Kugou music quality flags
**************************************

.. code-block:: py
   
   #!/usr/bin/env python
   #coding: utf-8

   import os

   def remove_quality_flags(name, flags):
      root_suffix_tuple = os.path.splitext(name)
      if root_suffix_tuple[0].endswith(flags):
         new_name = root_suffix_tuple[0][:len(root_suffix_tuple[0])-3] + root_suffix_tuple[1]
         os.rename(name, new_name)

   if __name__ == "__main__":
      interested_flags = ("_HQ", "_MQ", "_SQ")
      files = os.listdir(".")
      for name in files:
         remove_quality_flags(name, interested_flags)
