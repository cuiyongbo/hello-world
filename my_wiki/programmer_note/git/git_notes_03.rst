*************
Git Tricks 03
*************

Command line instructions

#. Git global setup

   .. code-block:: sh
   
      git config --global user.name "cuiyb"
      git config --global user.email "cuiyb@mapbar.com"

#. Create a new repository
      
   .. code-block:: sh

      git clone git@gitlab.mapbar.com:cuiyb/past-ti-fetcher.git
      cd past-ti-fetcher
      touch README.md
      git add README.md
      git commit -m "add README"
      git push -u origin master

#. Existing folder

   .. code-block:: sh

      cd existing_folder
      git init
      git remote add origin git@gitlab.mapbar.com:cuiyb/past-ti-fetcher.git
      git add .
      git commit -m "Initial commit"
      git push -u origin master

#. Existing Git repository

   .. code-block:: sh

      cd existing_repo
      git remote rename origin old-origin
      git remote add origin git@gitlab.mapbar.com:cuiyb/past-ti-fetcher.git
      git push -u origin --all
      git push -u origin --tags


#. Existing local repository
   
   .. code-block:: sh

      $ git remote set-url --add origin git@gitlab.mapbar.com:cuiyb/past-ti-fetcher.git
      $ git push -u origin master