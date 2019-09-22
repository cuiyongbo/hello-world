********************
Matplotlib Tricks 01
********************

#. diplay an existing picture

    .. code-block:: py

        img_path = 'path/to/pic.png'
        img = plt.imread(img_path)
        plt.imshow(img)
        plt.show()
