**************
Makefile Demos
**************

.. code-block:: none
    :caption: Directory structure

    ./include:
    fastcgi.h fcgi_config.h fcgi_stdio.h fcgiapp.h
    fcgimisc.h fcgio.h fcgios.h
    
    ./libfcgi:
    cgi-fcgi.c fcgi_stdio.c fcgiapp.c fcgio.cpp os_unix.c

.. code-block:: none

    .PHONY: all clean
    
    HEADER_DIR = include
    APP_HEADERS = $(HEADER_DIR)/*.h
    SRC_DIR = libfcgi
    OBJS = cgi-fcgi.o fcgiapp.o fcgio.o fcgi_stdio.o os_unix.o
    
    CXX = g++
    CPPFLAGS += -I$(HEADER_DIR)
    CXXFLAGS += -pthread
    LIB_NAME = libfcgi.a
    
    all : $(LIB_NAME)
    
    cgi-fcgi.o : $(SRC_DIR)/cgi-fcgi.c $(APP_HEADERS)
       $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<
    
    fcgiapp.o : $(SRC_DIR)/fcgiapp.c $(APP_HEADERS)
       $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<
    
    fcgio.o : $(SRC_DIR)/fcgio.cpp $(APP_HEADERS)
       $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<
    
    fcgi_stdio.o : $(SRC_DIR)/fcgi_stdio.c $(APP_HEADERS)
       $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<
    
    os_unix.o : $(SRC_DIR)/os_unix.c $(APP_HEADERS)
       $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<
    
    libfcgi.a : $(OBJS)
       $(AR) $(ARFLAGS) $@ $^   
    
    clean:
       rm -rf *.o *.dSYM $(LIB_NAME)