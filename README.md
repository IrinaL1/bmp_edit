# bmp_edit
bmp - dynamic lib => compiling:

gcc -c -fPIC source/bmp.c

gcc -shared -o bmp.so bmp.o

bmp_edit/lib: source - directory; bmp.o - object file; bmp.so - dynamic lib;

./lib/source : bmp.c - code file
