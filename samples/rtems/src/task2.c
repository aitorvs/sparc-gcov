/*
 * =====================================================================================
 *
 *       Filename:  task1.c
 *
 *    Description:  This is the task one implementation
 *
 *        Version:  1.0
 *        Created:  07/04/08 16:21:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aitor Viana Sanchez (avs), aitor.viana.sanchez@esa.int
 *        Company:  European Space Agency (ESA-ESTEC)
 *
 * =====================================================================================
 */

#include <rtems.h>
#include <stdio.h>
#include <unistd.h>

extern rtems_event_set t2_finish_event;

rtems_task rtems_t2(rtems_task_argument ignored)
{
    int i;

    for(i = 0; i < 10; ++i)
    {
        rtems_time_of_day time;

        printf("I am task 2\n");

//        rtems_clock_get( RTEMS_CLOCK_GET_TOD, &time );
//        rtems_interval ticks_per_second;
//        ticks_per_second = rtems_clock_get( RTEMS_CLOCK_GET_TICKS_PER_SECOND, &ticks_per_second );
//        rtems_task_wake_after( 1 * 5 * ticks_per_second );
        rtems_task_wake_after( 1000 );

    }

    printf("Task 2 is gone\n");
    rtems_task_delete( RTEMS_SELF );
}

