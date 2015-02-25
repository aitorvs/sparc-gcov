rm *.gcno *.gcda *.info *.html *.png *.css ttyS0

/opt/rtems-4.8/bin/sparc-rtems-gcc -qleon2 -c bubble.c -ftest-coverage -fprofile-arcs

/opt/rtems-4.8/bin/sparc-rtems-gcc -qleon2 -o bubble.cov bubble.o -L ../../build -lgcov_rtems_leon2 -Xlinker --wrap -Xlinker Init

touch ttyS0

tsim-leon -fast_uart -uart2 ttyS0 bubble.cov

../tracer/tracer ttyS0

lcov -g gcov --directory . --capture --output-file bubble.info

genhtml bubble.info
