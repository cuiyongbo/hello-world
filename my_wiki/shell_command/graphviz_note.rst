Graphviz Note
=============

Graphviz is a package of open-source tools initiated by AT&T Labs Research 
for drawing graphs specified in DOT language scripts. 

Installation: ``sudo apt install graphviz``

#. Format: "png" not recognized. Use one of:

You need register plugins first, run ``sudo dot -c``.

#. Examples

.. code-block:: sh

    $ echo '
    digraph jobrill {
      graph [label="JobRill DAG (machine generated)"]
      // node name pattern: m_id-m_name
      "0-A"->"1-B"
      "0-A"->"2-C"
      "1-B"->"3-D"
      "2-C"->"3-D"
      "3-D"
    } ' > rill.dot && dot -Tpng rill.dot -o rill.png

    $ echo '
    digraph jobrill {
      graph [label="JobRill DAG (machine generated)"]
      // node name pattern: m_id-m_name
      "0-InputJob"->"1-OutputJob"
      "1-OutputJob"
    } ' > rill.dot && dot -Tpng rill.dot -o rill.png
