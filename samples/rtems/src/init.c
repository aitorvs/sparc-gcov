/*
 * =====================================================================================
 *
 *       Filename:  init.c
 *
 *    Description:  This file is the implements the main function of RTEMS
 *    exmaple.
 *
 *        Version:  1.0
 *        Created:  07/04/08 15:56:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aitor Viana Sanchez (avs), aitor.viana.sanchez@esa.int
 *        Company:  European Space Agency (ESA-ESTEC)
 *
 * =====================================================================================
 */

/*-----------------------------------------------------------------------------
 *  RTEMS configuration
 *-----------------------------------------------------------------------------*/
#include <rtems.h>

/*  Forward declaration */
rtems_task Init(rtems_task_argument ignored);

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK 1000
#define CONFIGURE_MAXIMUM_TASKS     10

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
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
        (rtems_task_entry)__wrap_Init,
        CONFIGURE_INIT_TASK_INITIAL_MODES,
        CONFIGURE_INIT_TASK_ARGUMENTS,
    }
};
#define CONFIGURE_INIT_TASK_TABLE Initialization_tasks

#define CONFIGURE_INIT_TASK_TABLE_SIZE  \
    sizeof(CONFIGURE_INIT_TASK_TABLE) / sizeof(rtems_initialization_tasks_table)

#define CONFIGURE_INIT
#if (__GNUC__ > 3)
    #include <rtems/confdefs.h>
#else
    #include <confdefs.h>
#endif
/*-----------------------------------------------------------------------------
 *  RTEMS Configuration END
 *-----------------------------------------------------------------------------*/


#include <stdio.h>

rtems_id Task_id[2];
rtems_name Task_name[2];
rtems_id init_task_id = 0;

rtems_task rtems_t1(rtems_task_argument ignored);
rtems_task rtems_t2(rtems_task_argument ignored);


rtems_event_set t1_finish_event = RTEMS_EVENT_0;
rtems_event_set t2_finish_event = RTEMS_EVENT_1;

static void show_rtems_configuration(void)
{
    printf("%s: Entry point 0x%x\n", __func__, (int)Initialization_tasks[0].entry_point);
}

rtems_task Init(rtems_task_argument ignored)
{
    rtems_status_code status;
    rtems_id task_id = 0;
    rtems_task_argument argument = (rtems_task_argument)&init_task_id;
    rtems_event_set *rcv_event = &t1_finish_event;

    show_rtems_configuration();

    Task_name[0] = rtems_build_name( 'T', 'A', '1', ' ' );
    Task_name[1] = rtems_build_name( 'T', 'A', '2', ' ' );

    status = rtems_task_create( Task_name[0], 
                                2, 
                                1024 * 2, 
                                RTEMS_DEFAULT_MODES, 
                                RTEMS_DEFAULT_ATTRIBUTES, 
                                &Task_id[0]);

    status = rtems_task_create( Task_name[1], 
                                1, 
                                1024 * 2, 
                                RTEMS_DEFAULT_MODES, 
                                RTEMS_DEFAULT_ATTRIBUTES, 
                                &Task_id[1]);

    status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &init_task_id );

    status = rtems_task_start( Task_id[0], rtems_t1, argument );
    status = rtems_task_start( Task_id[1], rtems_t2, argument );


//    status = rtems_event_receive( t1_finish_event, RTEMS_WAIT | RTEMS_EVENT_ANY, RTEMS_NO_TIMEOUT, rcv_event );
//    printf("rtems_task_delete\n");
//    status = rtems_task_delete( RTEMS_SELF );

    return 0;
}


