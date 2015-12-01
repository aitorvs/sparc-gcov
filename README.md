# sparc-gcov

GCOV is an open source tool that can be used together with GCC to test code coverage in applications. 

The tool is widely spread, used and maintained and this project ported it to SPARC architecture, in particular to the processors used for space applications (ERC32/LEON2-3)

The usage does not deviate a lot from the normal usage of GCOV.


## Usage guidelines

### Library compilation

The compilation of the library is pretty simple.

```
cd <path-to-gcov/sparc-gcov
make
```

Those to lines will compile the library and leave in the directory ```build``` a series of static libraries dubbed libgcov_rtems_leon[2/3].a that will need to be linked with the application under test


### Application Configuration

The application to be tested for coverage should first be configured. For that the following should be defined

```c
#define CONFIGURE_HAS_OWN_INIT_TASK_TABLE

#define CONFIGURE_INIT_TASK_NAME            rtems_build_name( 'U', 'I', '1', ' ' )
#define CONFIGURE_INIT_TASK_STACK_SIZE      RTEMS_MINIMUM_STACK_SIZE
#define CONFIGURE_INIT_TASK_PRIORITY        1
#define CONFIGURE_INIT_TASK_ATTRIBUTES      RTEMS_DEFAULT_ATTRIBUTES
#define CONFIGURE_INIT_TASK_INITIAL_MODES   RTEMS_PREEMPT
#define CONFIGURE_INIT_TASK_ARGUMENTS       0

extern void __wrap_Init(void *ignored);

rtems_initialization_tasks_table Initialization_tasks[] = {
    {
        CONFIGURE_INIT_TASK_NAME,
        CONFIGURE_INIT_TASK_STACK_SIZE,
        CONFIGURE_INIT_TASK_PRIORITY,
        CONFIGURE_INIT_TASK_ATTRIBUTES,
        __wrap_Init,
        CONFIGURE_INIT_TASK_INITIAL_MODES,
        CONFIGURE_INIT_TASK_ARGUMENTS,
    }
};
#define CONFIGURE_INIT_TASK_TABLE Initialization_tasks

#define CONFIGURE_INIT_TASK_TABLE_SIZE  \
    sizeof(CONFIGURE_INIT_TASK_TABLE) / sizeof(rtems_initialization_tasks_table)
```


All code above might be put either inside the C source file or header file.

The function ```__wrap_Init``` is a wrapper function to RTEMS Init function. It is already defined inside os/rtems/ wrapper.c

## Compilation and Linking process

The compilation process is generic as for any other application. Needless to say, the cross-compiler for SPARC shall be used.
The following flags should be added:

- ```-ftest-coverage```
- ```-fprofile-arcs```

The application under test shall be linked with one of the libraries generated during the compilation of the GCOV module (step above)

The application shall wrap the ```Init``` function of RTEMS, for that ```--wrap``` shall be used.

### Application execution and coverage trace

The appliation under test will be executed normally, the only difference is upon exit, it will dump all the coverage traces to the serial port (or to a file if using a simulator like TSIM).

When testing an application in a real embedded environment, the application output can be received/saved using a tool like ```minicom```.

```
$> minicom -C coverageOutput.txt
```

The output trace can be intepreted using other tools like ```LCOV```.



You should be now ready to test coverage.


