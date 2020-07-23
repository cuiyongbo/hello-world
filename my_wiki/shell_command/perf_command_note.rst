Perf Command Note
=================

NAME: perf - Performance analysis tools for Linux

SYNOPSIS: ``perf [--version] [--help] COMMAND [ARGS]``

DESCRIPTION
       
    Performance counters for Linux are a new kernel-based subsystem that provide a framework 
    for all things performance analysis. It covers hardware level (CPU/PMU, Performance Monitoring Unit) 
    features and software features (software counters, tracepoints) as well.

SEE ALSO

    perf-stat(1), perf-top(1), perf-record(1), perf-report(1), perf-list(1)

Example

.. code-block:: sh

    # to generate flame graph
    $ perf record -F 200 -p pid_to_sample -- sleep 600
    $ ./perf script -i perf.data &> perf.unfold
    $ perl FlameGraph/stackcollapse-perf.pl perf.unfold &> perf.folded
    $ perl FlameGraph/flamegraph.pl perf.folded >perf.svg

