
#EXTRA_DIST = Makefile.mak

#INCLUDES = -I$(top_srcdir)/include

bin_PROGRAMS = genlab

genlab_SOURCES = genlab.cpp 

genlab_LDFLAGS = -pthread

genlab_LDADD = ../lib/etana/libEtAna.a ../lib/fsc/libFsc.a ../lib/engine/libHTSEngine.a ../lib/label/libEtLab.a

DISTCLEANFILES = *.log *.out *~

MAINTAINERCLEANFILES = Makefile.in
