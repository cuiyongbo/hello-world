******************
Install Tensorflow
******************

System requirements::

   Ubuntu 16.04 or later (64-bit)
   macOS 10.12.6 (Sierra) or later (64-bit) (no GPU support)


#. Install the Python development environment on your system (Assume Python 2.7)
   
   Check if your Python environment is already configured::

      python --version
      pip --version
      virtualenv --version

   If these packages are already installed, skip to the next step.
   Otherwise, install Python, the pip package manager, 
   and Virtualenv::

      sudo apt update
      sudo apt install python-dev python-pip
      sudo pip install -U virtualenv  # system-wide install

#. Create a virtual environment (recommended)
   
   Python virtual environments are used to isolate package installation from the system.
   Create a new virtual environment by choosing a Python interpreter and 
   making a ``./venv`` directory to hold it::

      virtualenv --system-site-packages -p python2.7 ./venv

   Activate the virtual environment using a shell-specific 
   command::

      source ./venv/bin/activate  # sh, bash, ksh, or zsh

   When virtualenv is active, your shell prompt is prefixed with (venv).

   Install packages within a virtual environment without affecting 
   the host system setup. Start by upgrading pip::

      pip install --upgrade pip
      pip list  # show packages installed within the virtual environment

   And to exit virtualenv later::

      deactivate  # don't exit until you're done using TensorFlow

#. Install the TensorFlow pip package

   Choose one of the following TensorFlow packages to 
   install from PyPI::

      pip install --upgrade tensorflow

   Verify the install::

      python -c "import tensorflow as tf; tf.enable_eager_execution(); \
                     print(tf.reduce_sum(tf.random_normal([1000, 1000])))"

   .. code-block:: py
      :caption: More examples

      import tensorflow as tf
      mnist = tf.keras.datasets.mnist
      
      (x_train, y_train),(x_test, y_test) = mnist.load_data()
      x_train, x_test = x_train / 255.0, x_test / 255.0
      
      model = tf.keras.models.Sequential([
        tf.keras.layers.Flatten(),
        tf.keras.layers.Dense(512, activation=tf.nn.relu),
        tf.keras.layers.Dropout(0.2),
        tf.keras.layers.Dense(10, activation=tf.nn.softmax)
      ])
      model.compile(optimizer='adam',
                    loss='sparse_categorical_crossentropy',
                    metrics=['accuracy'])
      
      model.fit(x_train, y_train, epochs=5)
      model.evaluate(x_test, y_test)

.. rubric:: Footnotes

.. [#] `Install tensorflow <https://www.tensorflow.org/install/pip>`_