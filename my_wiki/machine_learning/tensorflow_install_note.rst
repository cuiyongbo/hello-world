******************
Install Tensorflow
******************

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

#. Supress tensorflow warnings

   .. code-block:: py

      # in scripts

      import os
      import tensorflow as tf
      os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

      # 0 = all messages are logged (default behavior)
      # 1 = INFO messages are not printed
      # 2 = INFO and WARNING messages are not printed
      # 3 = INFO, WARNING, and ERROR messages are not printed

   .. code-block:: sh

      # add environment variable
      export TF_CPP_MIN_LOG_LEVEL=2

.. rubric:: Footnotes

.. [#] `Install tensorflow <https://www.tensorflow.org/install/pip>`_
.. [#] `Tensorflow ZH Community <http://www.tensorfly.cn/tfdoc/get_started/introduction.html>`_
