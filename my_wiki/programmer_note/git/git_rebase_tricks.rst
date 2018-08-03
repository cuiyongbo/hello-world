*****************
Git rebase Tricks
*****************

**Usage:** Combine several commits into one

#. combine last 2 commits

   .. code-block:: sh
  
      $ git log -5 --oneline
      7d00a71 deleted python_indention_error.PNG
      b589a16 Added boolean functions
      d404925 Added iterator functions
      55d5b05 added help and dir
      a89a0e3 added int, long, float, complex
      
      $ git reset --soft HEAD^
      $ git commit -a --amend
      
      $ git log --oneline -5
      ded0055 Added boolean functions
      d404925 Added iterator functions
      55d5b05 added help and dir
      a89a0e3 added int, long, float, complex
      5fec164 Added type, isinstance

#. combine last n commits

   .. code-block:: sh

      $ git log --oneline -5
      ded0055 Added boolean functions
      d404925 Added iterator functions
      55d5b05 added help and dir
      a89a0e3 added int, long, float, complex
      5fec164 Added type, isinstance
      
      $ git rebase -i HEAD~4
      
      $ git log --oneline -5
      2bc541a added int, long, float, complex
      5fec164 Added type, isinstance
      00e1ffb added chr, ord, unichr, all, any
      0edff53 Added raillery, habit-forming, off-license
      ab4b8b8 Added extern c linkage
   
   .. code-block:: sh
      :caption: rebase options

      pick   a89a0e3 added int, long, float, complex     
      squash 55d5b05 added help and dir
      squash d404925 Added iterator functions
      squash ded0055 Added boolean functions
   
#. another method to combine last n commits

   .. code-block:: sh

      $ git log --oneline -5
      2bc541a added int, long, float, complex
      5fec164 Added type, isinstance
      00e1ffb added chr, ord, unichr, all, any
      0edff53 Added raillery, habit-forming, off-license
      ab4b8b8 Added extern c linkage
      
      $ git rebase -i 0edff53
      
      $ git log --oneline -5
      e4afdcd added chr, ord, unichr, all, any
      0edff53 Added raillery, habit-forming, off-license
      ab4b8b8 Added extern c linkage
      90a7dc6 Failed to refrain myself in weekends
      3639325 added clamp

   .. code-block:: sh
      :caption: rebase options

      pick   00e1ffb added chr, ord, unichr, all, any
      squash 5fec164 Added type, isinstance
      squash 2bc541a added int, long, float, complex

#. more examples
   
   .. code-block:: sh

      $ git log --oneline -5
      e4afdcd added chr, ord, unichr, all, any
      0edff53 Added raillery, habit-forming, off-license
      ab4b8b8 Added extern c linkage
      90a7dc6 Failed to refrain myself in weekends
      3639325 added clamp
      
      $ git rebase -i HEAD~4
      
      $ git log --oneline -5
      8442056 added chr, ord, unichr, all, any
      eb4ad04 Failed to refrain myself in weekends
      3639325 added clamp
      7583d4b added pansy
      a4ffedb Moved lethargy
      
      .. code-block:: sh
         :caption: rebase option
      
         pick   90a7dc6 Failed to refrain myself in weekends
         squash ab4b8b8 Added extern c linkage
         squash 0edff53 Added raillery, habit-forming, off-license
         pick   e4afdcd added chr, ord, unichr, all, any

   .. note::
   
      Important: If you've already pushed commits to remote server, 
      and then squash them locally, you will have to force the push to your branch.
      
      .. code-block:: sh
      
         $ git push origin branch-name --force
      
      Helpful hint: You can always edit your last commit message, 
      before pushing, by using:
      
      .. code-block:: sh
      
         $ git commit --amend

