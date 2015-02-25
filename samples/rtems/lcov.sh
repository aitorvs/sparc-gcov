rm *.gcno *.gcda *.info *.html *.png *.css

touch ttyS0

tsim-leon -fast_uart -uart2 ttyS0 rtems_demo

./tracer ttyS0

lcov -g gcov --directory . --capture --output-file rtems_demo.info

genhtml rtems_demo.info
