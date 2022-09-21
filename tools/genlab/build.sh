#!/bin/sh
test -x configure || autoreconf -vif
./configure CC=/usr/bin/gcc CXX=/usr/bin/g++ CFLAGS="-g3 -gdwarf-2" CXXFLAGS="-g3 -gdwarf-2"
make
