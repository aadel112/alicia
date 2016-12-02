UNAME := $(shell uname)

NM=libSeries
OF=$(NM).o

ifeq ($(UNAME), Linux)
TARGET = $(NM).so
else
TARGET = $(NM).dll
endif

$(TARGET): $(OF)
	gcc -O3 -o $@  $^  -shared
		# '-o $@'    => output file => $@ = libhello.so or hello.dll
		# '   $^'    => no options => Link all depended files => $^ = hello.o
		# '-shared'  => generate shared library

$(OF): $(NM).c
	gcc -O3 -o $@  -c $<  -fPIC
		# '-o $@' => output file => $@ = the target file (main.o)
		# '-c $<' => compile the first depended file (main.cpp)
		# '-fPIC' => Position-Independent Code (required for shared lib)

clean:
	rm -f *.o *.so *.dll *.exe
