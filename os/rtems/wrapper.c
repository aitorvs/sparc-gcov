/*
 * ==================================================================
 *    This file has been automatically generated, do not modified
 * ==================================================================
 */

#include <stdio.h>
#include <rtems.h>

extern int dev_id;
extern int gcov_exit(void);
extern int gcov_if_init(void);
extern void __real_Init(void *ignored);

//void __wrap_Init(void *ignored)

#define real_function   __real_Init
#define DELAY_IN_MS     20000

void __wrap_Init(void *ignored)
{

    printf("%s: Coverage initialized\n", __func__);
    gcov_if_init();
    /*	call the real funcion	*/
    real_function(ignored);

    /*  send out the coeverage info. after several seconds  */
    printf("%s: Sending the gcov info. after %d ms\n", __func__, DELAY_IN_MS);
    rtems_task_wake_after( DELAY_IN_MS );
    gcov_exit();

    /*  Delete the RTEMS init task  */
    printf("rtems_task_delete\n");
    rtems_task_delete( RTEMS_SELF );

}


