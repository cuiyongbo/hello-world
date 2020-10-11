C++ Object Model
================

.. note:: Refer to *Inside the C++ object model, section 1.1* for further information.

The C++ object model is derived from the simple object model by optimizing
for space and access time:

* Nonstatic data members are allocated directly within each class object.
* Static data members are stored outside the individual class object.
* Static and nonstatic function members are also hosited outside the class object.
* Virtual fucntions are supported in 2 steps:
    * A table of pointers to virtual fucntions is generated for each class (aka virtual table).
    * A single pointer to the virtual table is inserted to each class object (aka ``vptr``).

.. note:: 

    The setting, resetting, and not setting of ``vptr`` is handled automaticaly through code generated
    within each class constructor, destructor, and copy assignment operator. the ``type_info`` object associated
    with each class in support of :abbr:`RTTI (Runtime Type Identification)` is also addressed within
    the virtual table, usually with the table's first slot.