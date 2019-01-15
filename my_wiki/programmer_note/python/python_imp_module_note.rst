**********************
Python imp module note
**********************

.. function:: find_module(name, [path]) -> (file, filename, (suffix, mode, type))
   
   Search for a module.  If path is omitted or None, search for a
   built-in, frozen or special module and continue search in sys.path.
   The module name cannot contain '.'; to search for a submodule of a
   package, pass the submodule name and the package's __path__.

.. function:: load_module(name, file, filename, (suffix, mode, type)) -> module
    
    Load a module, given information returned by find_module().
    The module name must include the full package name, if any.


.. function:: imp.load_compiled(name, pathname[, file])

    Load and initialize a module implemented as a byte-compiled code file 
    and return its module object. If the module was already initialized, 
    it will be initialized again. The name argument is used to create or 
    access a module object. The pathname argument points to the byte-compiled 
    code file. The file argument is the byte-compiled code file, open for reading 
    in binary mode, from the beginning. It must currently be a real file object, 
    not a user-defined class emulating a file.

.. function:: imp.load_source(name, pathname[, file])

    Similar to ``load_compiled()``, but load from a Python source file instead.

.. code-block:: py

    import imp
    import sys
    
    def __import__(name, globals=None, locals=None, fromlist=None):
        # Fast path: see if the module has already been imported.
        try:
            return sys.modules[name]
        except KeyError:
            pass
    
        # If any of the following calls raises an exception,
        # there's a problem we can't handle -- let the caller handle it.
    
        fp, pathname, description = imp.find_module(name)
    
        try:
            return imp.load_module(name, fp, pathname, description)
        finally:
            # Since we may exit via an exception, close fp explicitly.
            if fp:
                fp.close()  