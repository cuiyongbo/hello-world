**********************
Ubuntu problem note 04
**********************

#. See the default system page size

    .. code-block:: sh

        getconf PAGESIZE
        4096

    .. note::

        Find more interesting features about :command:`getconf` by ``man getconf``,
        some examples::

                # display the maximum length of a filename in the /tmp directory
                getconf NAME_MAX /tmp
                255
                getconf CHAR_BIT
                8

#. username is not in the sudoers file.This incident will be reported

    * switch to root accout
    * add write permission: ``chmod u+w /etc/sudoers``
    * edit ``/etc/sudoers``: add ``username ALL=(ALL) ALL`` to ``/etc/sudoers``
    * retrive write permission: ``chmod u-w /etc/sudoers``

    .. note::

        这里说下你可以sudoers添加下面四行中任意一条::

            youuser            ALL=(ALL)                ALL
            %youuser           ALL=(ALL)                ALL
            youuser            ALL=(ALL)                NOPASSWD: ALL
            %youuser           ALL=(ALL)                NOPASSWD: ALL

        第一行:允许用户youuser执行sudo命令(需要输入密码).
        第二行:允许用户组youuser里面的用户执行sudo命令(需要输入密码).
        第三行:允许用户youuser执行sudo命令,并且在执行的时候不输入密码.
        第四行:允许用户组youuser里面的用户执行sudo命令,并且在执行的时候不输入密码.