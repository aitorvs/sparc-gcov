rm *.gcno *.gcda *.info *.html *.png *.css

/opt/rtems-4.8/bin/sparc-rtems-gcc -qleon2 -c quicksort.c -ftest-coverage -fprofile-arcs

/opt/rtems-4.8/bin/sparc-rtems-gcc -qleon2 -o quicksort.cov quicksort.o -L ../../build -lgcov_rtems_leon2 -Xlinker --wrap -Xlinker Init

touch ttyS0

tsim-leon -fast_uart -uart2 ttyS0 quicksort.cov

../tracer/tracer ttyS0

lcov -g gcov --directory . --capture --output-file quicksort.info

genhtml quicksort.info
