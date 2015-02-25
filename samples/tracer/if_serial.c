/*
 * =====================================================================================
 *
 *       Filename:  if_serial.c
 *
 *    Description:  This file implements the serial interface for the gcov host
 *    analizer
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

#include "interface.h"
#include "if_serial.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define TTY_DEVICE  "ttyS0"
static int file = -1;

struct if_operations tty_operations = {
    if_serial_read,
    if_serial_write,
    if_serial_init,
    if_serial_destroy,
};

int if_serial_init(void)
{
    if( file >= 0 )
        return IF_ERR_DEV_INIT;

    if( (file = open(TTY_DEVICE, O_RDONLY)) < 0 )
        return IF_ERR_OPEN;

    return IF_SUCCESS;
}

int if_serial_read(int dev_id, int nbytes, void  *buffer)
{
    if( file < 0 )
        return IF_ERR_INVALID_DEVID;

    return ( read(file, buffer, nbytes) );
}

int if_serial_write(int dev_id, int nbytes, void  *buffer)
{
    if( file < 0 )
        return IF_ERR_INVALID_DEVID;

    return ( write(file, buffer, nbytes) );
}

int if_serial_destroy(int dev_id)
{
    if( file ) return IF_ERR_CLOSE;
    close(file);
    file = -1;

    return IF_SUCCESS;
}

