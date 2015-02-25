/*
 * =====================================================================================
 *
 *       Filename:  if_serial.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/08 08:46:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aitor Viana Sanchez (avs), aitor.viana.sanchez@esa.int
 *        Company:  European Space Agency (ESA-ESTEC)
 *
 * =====================================================================================
 */


#ifndef _IF_SERIAL_H_
#define _IF_SERIAL_H_

int if_serial_init(void);
int if_serial_read(int dev_id, int nbytes, void  *buffer);
int if_serial_write(int dev_id, int nbytes, void  *buffer);
int if_serial_close(void);
int if_serial_destroy(int dev_id);

#endif

