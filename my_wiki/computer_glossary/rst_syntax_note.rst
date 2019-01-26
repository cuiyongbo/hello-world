**********************
reStructure Syntax FAQ
**********************

#. Preserve line breaks while generating docs using Sphinx

    Line blocks are a way of preserving line breaks.
   
    | These lines are
    | broken exactly like in
    | the source file.
   
#. Suppress WARNING: document isn't included in any toctree

    Add ``:orphan:`` directive before the titile.

#. Suppress WARNING: unknown option
   
    Add ``suppress_warnings`` build configure to :file:`conf.py`::

        suppress_warnings = [
           "ref.option"
        ]

#. Exclude certain file(s) from building
   
    Add file or file patterns to *exclude_patterns* in :file:`conf.py`.

#. Write Makefile for documentation
   
    Basically, Use python and sphinx, and set sphinx options::

        # Minimal makefile for Sphinx documentation

        # You can set these variables from the command line.
        #SPHINXOPTS    = -W # treat warnings as errors
        #SPHINXOPTS    = --keep-going # ignore error
        SPHINXBUILD   = python -msphinx
        SPHINXPROJ    = MyWiki
        SOURCEDIR     = .
        BUILDDIR      = build
        
        # Put it first so that "make" without argument is like "make help".
        help:
            @$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
        
        .PHONY: help Makefile
        
        # workaround because sphinx does not completely clean up (#11139)
        clean:
            @$(SPHINXBUILD) -M clean "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
            rm -rf "$(SOURCEDIR)/build"
            rm -rf "$(SOURCEDIR)/api/_as_gen"
            rm -rf "$(SOURCEDIR)/gallery"
            rm -rf "$(SOURCEDIR)/tutorials"
            rm -rf "$(SOURCEDIR)/savefig"
            rm -rf "$(SOURCEDIR)/sphinxext/__pycache__"
        
        # Catch-all target: route all unknown targets to Sphinx using the new
        # "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
        %: Makefile
            @$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
