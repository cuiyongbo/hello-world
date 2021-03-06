**************
pip usage note
**************

**DESCRIPTION**

	.. code-block:: sh

		pip <command> [options]
		pip3 <command> [options]

	pip is a Python package installer, recommended for installing Python packages which are not 
	available in the Debian archive. It can work with version control repositories, logs output 
	extensively, and prevents partial installs by downloading all requirements before starting 
	installation.

	On Debian, pip is the command to use when installing packages for Python 2, while pip3 is the  
	command to use when installing packages for Python 3.

**COMMANDS**

		The command comes before any options.  
		The following commands are recognized::

			help        Show help for commands.
			install     Install packages.
			uninstall   Uninstall packages.
			freeze      Output installed packages in requirements format.
			list        List installed packages.
			show        Show information about installed packages.
			search      Search PyPI for packages.
			wheel       Build wheels from your requirements.

#. Check python and pip version
	
	.. code-block:: sh

		$ pip -V
		pip 18.1 from /usr/local/lib/python2.7/dist-packages/pip (python 2.7)
		$ pip --version
		pip 18.1 from /usr/local/lib/python2.7/dist-packages/pip (python 2.7)
		$ python -V
		Python 2.7.12
		$ python --version
		Python 2.7.12

#. List installed packages
	
	* Invoke python interpreter, and run ``help("modules")``.
	* Run ``pip list`` or ``pip freeze``.
	
	.. code-block:: sh

		$ pip list
		Package            Version
		------------------ -------
		adium-theme-ubuntu 0.3.4  
		pip                18.1   
		setuptools         20.7.0 
		unity-lens-photos  1.0    
		virtualenv         16.1.0 
		wheel              0.29.0 
		$ pip freeze
		adium-theme-ubuntu==0.3.4
		unity-lens-photos==1.0
		virtualenv==16.1.0

#. Permission denied while ``pip install ***``
	
	Using the `--user` option: ``pip install --user sphinx``.

#. Pip to view package dependency

    .. code-block:: sh

        $ pip3 show -h
        
        Usage:   
          pip3 show [options] <package> ...
        
        Description:
          Show information about one or more installed packages.
        
        $ pip3 show sphinx
        Name: Sphinx
        Version: 3.1.0
        Summary: Python documentation generator
        Home-page: http://sphinx-doc.org/
        Author: Georg Brandl
        Author-email: georg@python.org
        License: BSD
        Location: /usr/local/lib/python3.7/site-packages
        Requires: sphinxcontrib-htmlhelp, Jinja2, docutils, sphinxcontrib-jsmath, setuptools, babel, imagesize, sphinxcontrib-applehelp, snowballstemmer, requests, sphinxcontrib-devhelp, packaging, Pygments, sphinxcontrib-qthelp, sphinxcontrib-serializinghtml, alabaster
        Required-by: 
        
        $ pip3 show numpy
        Name: numpy
        Version: 1.18.5
        Summary: NumPy is the fundamental package for array computing with Python.
        Home-page: https://www.numpy.org
        Author: Travis E. Oliphant et al.
        Author-email: None
        License: BSD
        Location: /usr/local/lib/python3.7/site-packages
        Requires: 
        Required-by: tensorboard, scipy, opt-einsum, matplotlib, Keras-Preprocessing, h5py