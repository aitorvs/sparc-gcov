CROSS_COMPILE = sparc-rtems-
CROSS_COMPILE = 
CC     = $(CROSS_COMPILE)gcc 

OBJS = interface.o if_serial.o analysis.o

%.o: %.c
	$(CC) -c $< -o $@

tracer: ${OBJS}
	$(CC) -o $@ ${OBJS}

clean:
	rm *.o tracer
