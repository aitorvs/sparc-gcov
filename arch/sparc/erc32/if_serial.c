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


struct if_operations tty_operations = {
    if_serial_read,
    if_serial_write,
    if_serial_init,
    if_serial_destroy,
};

int if_serial_init(void)
{
    return IF_NOT_IMPLEMENTED;
}

int if_serial_read(int dev_id, int nbytes, void  *buffer)
{
    return IF_NOT_IMPLEMENTED;
}

int if_serial_write(int dev_id, int nbytes, void  *buffer)
{
    return IF_NOT_IMPLEMENTED;
}

int if_serial_destroy(int dev_id)
{
    return IF_NOT_IMPLEMENTED;
}

