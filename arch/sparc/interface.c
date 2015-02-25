/*
 * =====================================================================================
 *
 *       Filename:  interface.c
 *
 *    Description:  This file implements the interface API to the embedded
 *    system
 *
 *        Version:  1.0
 *        Created:  04/04/08 17:28:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aitor Viana Sanchez (avs), aitor.viana.sanchez@esa.int
 *        Company:  European Space Agency (ESA-ESTEC)
 *
 * =====================================================================================
 */

#include "interface.h"

static int num_ifs = 0;

if_table_entry_s if_table[MAX_IF_DEVICES];


int if_register(struct if_operations *ops)
{
    int dev_id;

    if( num_ifs >= MAX_IF_DEVICES )
        return IF_ERR;

    int i = 0;
    while( if_table[i].valid == TRUE ) ++i;

    dev_id = i;

    if( ops->init() != IF_SUCCESS )
        return IF_ERR_DEV_INIT;

    if_table[i].valid = TRUE;
    if_table[i].ops = ops;


    num_ifs++;

    return dev_id;
}

int if_read(int dev_id, int nbytes, void *buffer)
{
    if( if_table[dev_id].valid == TRUE )
        return ( if_table[dev_id].ops->read(dev_id, nbytes, buffer) );
    else
        return IF_ERR_INVALID_DEVID;
}

int if_write(int dev_id, int nbytes, void *buffer)
{
    if( if_table[dev_id].valid == TRUE )
        return ( if_table[dev_id].ops->write(dev_id, nbytes, buffer) );
    else
        return IF_ERR_INVALID_DEVID;
}

int if_init(void)
{
    int i = 0;

    num_ifs = 0;

    for( i = 0; i < MAX_IF_DEVICES; ++i)
        if_table[i].valid = FALSE;

    return IF_SUCCESS;
}

int if_destroy(int dev_id)
{
    if( if_table[dev_id].valid == TRUE )
        return ( if_table[dev_id].ops->destroy(dev_id));
    else
        return IF_ERR_INVALID_DEVID;
}

