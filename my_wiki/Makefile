# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line.
#SPHINXOPTS    = -W
#SPHINXOPTS    = --keep-going
SPHINXOPTS    =
#SPHINXBUILD   = python -msphinx
SPHINXBUILD   = sphinx-build
SPHINXPROJ    = MyWiki
SOURCEDIR     = .
BUILDDIR      = ../_build

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# workaround because sphinx does not completely clean up (#11139)
clean:
	@$(SPHINXBUILD) -M clean "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	rm -rf "$(SOURCEDIR)/_build"
	rm -rf "$(SOURCEDIR)/api/_as_gen"
	rm -rf "$(SOURCEDIR)/gallery"
	rm -rf "$(SOURCEDIR)/tutorials"
	rm -rf "$(SOURCEDIR)/savefig"
	rm -rf "$(SOURCEDIR)/sphinxext/__pycache__"

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
