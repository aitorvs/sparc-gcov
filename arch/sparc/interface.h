/*
 * =====================================================================================
 *
 *       Filename:  interface.h
 *
 *    Description:  This header file defines everything regarding the comm.
 *    interfaces.
 *
 *        Version:  1.0
 *        Created:  04/04/08 17:12:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aitor Viana Sanchez (avs), aitor.viana.sanchez@esa.int
 *        Company:  European Space Agency (ESA-ESTEC)
 *
 * =====================================================================================
 */

#ifndef _IF_H_
#define _IF_H_

#define MAX_IF_DEVICES  2

#define TRUE    1
#define FALSE   0

typedef enum _Result_T
{
    IF_SUCCESS = 0,

    IF_ERR_OPEN             = -1,
    IF_ERR_READ             = -2,
    IF_ERR_WRITE            = -3,
    IF_ERR_DEV_INIT         = -4,
    IF_ERR_INVALID_DEVID    = -5,
    IF_ERR_CLOSE            = -6,


    IF_NOT_IMPLEMENTED      = -100,
    IF_ERR                  = -101,

}Result_T;

typedef enum _devType_t
{
    TYPE_SERIAL = 0,
    TYPE_SPW,
}devType_t;

typedef enum _mode_T
{
    M_READ = 1,
    M_WRITE = 2,
    M_READWRITE = M_READ | M_WRITE,
}mode_T;

struct if_operations
{
    int (*read)(int dev_id, int nbytes, void *buffer);
    int (*write)(int dev_id, int nbytes, void *buffer);
    int (*init)(void);
    int (*destroy)(int dev_id);
};

typedef struct _if_table_entry
{
    struct if_operations *ops;
    unsigned int valid;
}if_table_entry_s;

extern if_table_entry_s if_table[MAX_IF_DEVICES];

int if_register(struct if_operations *ifops);
int if_read(int dev_id, int nbytes, void *buffer);
int if_write(int dev_id, int nbytes, void *buffer);
int if_init(void);

// These are all the possible operations
extern struct if_operations tty_operations;

#endif

