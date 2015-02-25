CROSS_COMPILER = /opt/rtems-4.8/bin/sparc-rtems-

CXX=$(CROSS_COMPILER)g++ $(CFLAGS)
CC=$(CROSS_COMPILER)gcc $(CFLAGS)

PROG 		= 	rtems_demo

TOPDIR		=	$(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)
OBJDIR		=	${TOPDIR}/obj
SRCDIR		=	${TOPDIR}/src
CPPSOURCES	=	${shell find ${SRCDIR} -name \*.cpp}
CSOURCES	=	${shell find  ${SRCDIR} -name \*.c}
SOURCES    = ${CPPSOURCES} ${CSOURCES}
OBJECTS		=	${shell for obj in ${CPPSOURCES:.cpp=.o} ${CSOURCES:.c=.o}; do echo ${OBJDIR}/`basename $$obj`;done}

VPATH      = ${shell for dir in `find ${SRCDIR} -type d | grep -v CVS`;do echo -n $$dir:;done}

CFLAGS		=	-O2 -fprofile-arcs -ftest-coverage
CFLAGS		=	-qleon2

FLAGS		=	-O2 
FLAGS		=	-O2 -fprofile-arcs -ftest-coverage

CXXFLAGS   	= 	-O2 
CXXFLAGS   	= 	-O2 -fno-rtti -fno-exceptions -fprofile-arcs -ftest-coverage
CPPFLAGS   	=
INCLUDE		=	

#implicit rules
${OBJDIR}/%.o: %.cpp
	${CXX} -c ${INCLUDE} ${CXXFLAGS} ${CPPFLAGS} ${FLAGS} $< -o $@

${OBJDIR}/%.o: %.c
	${CC} -c ${INCLUDE} ${CFLAGS} ${CPPFLAGS} ${FLAGS} $< -o $@

all: leon2fpv8

ifeq (.depend,${wildcard .depend})
include .depend
endif

${OBJECTS}: .depend

build: ${OBJECTS}
	$(CC)  ${OBJECTS} -o $(PROG) -L ../../build -lgcov_rtems_leon2 -Xlinker --wrap -Xlinker Init

leon2fpv8:
	make build

.depend: ${SOURCES} ${HFILES}
	@echo -n > .depend.tmp
	/usr/X11R6/bin/makedepend -f.depend.tmp -- ${CPPFLAGS} -- ${SOURCES}
	@sed -e "s@^[^:]*/@${OBJDIR}/@" < .depend.tmp > .depend

clean:
	@rm -f ${PROG} .depend
	@for dir in ${OBJDIR}; do \
		cd $$dir; rm *.*;	\
	done
	$(shell rm `find . -name *.png` *.png)
	$(shell rm `find . -name *.gcda`)
	$(shell rm `find . -name *.html`)
	$(shell rm `find . -name *.css`)

cleanObj:
	@for dir in ${OBJDIR}; do \
		cd $$dir; rm -f *.o;\
	done
