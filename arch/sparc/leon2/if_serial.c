/*
 * =====================================================================================
 *
 *       Filename:  if_serial.c
 *
 *    Description:  This file implementst the serial interface in the leon2
 *    architecture.
 *
 *        Version:  1.0
 *        Created:  04/04/08 17:14:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aitor Viana Sanchez (avs), aitor.viana.sanchez@esa.int
 *        Company:  European Space Agency (ESA-ESTEC)
 *
 * =====================================================================================
 */

#include "../interface.h"
#include "if_serial.h"

#include <stdio.h>

static unsigned int *REGMAP = (unsigned int*)0x80000000;
#define LEON2_UART_THE  (1 << 2)        // Ready to load the data

struct if_operations tty_operations = {
    if_serial_read,
    if_serial_write,
    if_serial_init,
    if_serial_destroy,
};

int if_serial_init(void)
{
    return IF_SUCCESS;
}

int if_serial_read(int dev_id, int nbytes, void  *buffer)
{
    dev_id = dev_id;
    nbytes = nbytes;
    buffer = buffer;
    return IF_NOT_IMPLEMENTED;
}

int if_serial_write(int dev_id, int nbytes, void  *buffer)
{
    dev_id = dev_id;
    volatile unsigned int uart_status;
    unsigned char *buf = (unsigned char *)buffer;


    while(!(uart_status = REGMAP[0x84 / 4]) & LEON2_UART_THE);
    int i = 0;
    for(i = 0; i < nbytes; ++i)
    {
        REGMAP[0x80 / 4] = buf[i];
        // Wait for the correct transmission
        while(!(uart_status = REGMAP[0x84 / 4]) & LEON2_UART_THE);
    }

    // return the number of byes read
    return i;
}

int if_serial_destroy(int dev_id)
{
    dev_id = dev_id;
    return IF_SUCCESS;
}

