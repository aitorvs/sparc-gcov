/**
 *  \file   quicksort.c
 *  \brief  This file implements the quicksort algorithm for RTEMS
 *
 *  Detailed description starts here.
 *
 *  \author  Aitor Viana Sanchez (avs), Aitor.Viana.Sanchez@esa.int
 *
 *  \internal
 *    Created:  12/03/09
 *   Revision:  $Id: quicksort.c 1.4 12/03/09 avs Exp $
 *   Compiler:  gcc/g++
 *    Company:  European Space Agency (ESA-ESTEC)
 *  Copyright:  Copyright (c) 2009, Aitor Viana Sanchez
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
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
        __wrap_Init,
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
#include <stdlib.h>


void quicksort(int lista[], int inf, int sup)
{
    int izq, der, mitad, x;

    izq = inf;
    der = sup;

    mitad = lista[(izq + der)/2];

    do
    {
        while (lista[izq] < mitad && izq < sup) izq++;
        while (mitad < lista[der] && der > inf) der--;
        if (izq <= der)
        {
            x = lista[izq];
            lista[izq] = lista[der];
            lista[der] = x;
            izq++; der--;
        }
    } while (izq <= der);
    if (inf < der) quicksort(lista, inf, der);
    if (izq < sup) quicksort(lista, izq, sup);
}

rtems_task Init(rtems_task_argument ignored)
{
    int lista[] = { 12, 3, 7, 5, 10, 32, 67, 39, 25, 1};
    int i = 0;

    printf("Original list:");
    for (i = 0; i < 10; i++)
        printf(" %d", lista[i]);
    printf("\n");

    quicksort(lista, 0, 9);

    printf("Ordered list:");
    for (i = 0; i < 10; i++)
        printf(" %d", lista[i]);
    printf("\n");
}
