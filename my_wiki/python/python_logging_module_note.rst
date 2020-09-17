Python loggin module note
=========================

Log levels::

    DEBUG
    INFO
    WARNING (by default)
    ERROR
    CRITICAL

Log functions::

    logging.debug
    logging.info
    logging.warning
    logging.error
    logging.critial

.. code-block:: py

    #!/usr/bin/env python3
    #coding: utf-8

    import logging
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("-l", "--log-level", type=str, default = 'debug',
            choices=['debug', 'info', 'warning', 'error', 'critial'], 
            help = "set log level")
    args = parser.parse_args()

    # print(args)

    loglevel = args.log_level
    numeric_level = getattr(logging, loglevel.upper(), logging.DEBUG)
    if not isinstance(numeric_level, int):
        raise ValueError("Invalid loglevel: %s" % loglevel)

    logging.basicConfig(filename='notebook.log', filemode='w', level=numeric_level)

    logging.debug("debug log")
    logging.info("info log")
    logging.warning("warning log")
    logging.error("error log")
    logging.critical("critial log")