/*
 * =====================================================================================
 *
 *       Filename:  analisys.c
 *
 *    Description:  This file implements everything needed to retrieve the gcov
 *    information from the embedded sysrtem
 *
 *        Version:  1.0
 *        Created:  04/04/08 17:04:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aitor Viana Sanchez (avs), aitor.viana.sanchez@esa.int
 *        Company:  European Space Agency (ESA-ESTEC)
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "interface.h"

#define INTERFACE   "ttyS0"
#define MAXFILENAME 100

typedef struct _to_send
{
    char filename[MAXFILENAME];
    unsigned int nbytes;
}header_T;

static header_T header_s;

static void usage(char *av)
{
    printf("\n\n========================================================================\n");
    printf("The application the file where the gcov information for all the files is stored\n");
    printf("\tUsage: %s <file>\n", av);
    printf("========================================================================\n");


    exit(1);
}

int main(int ac, char *av[])
{
    int dev_id;
    unsigned char *buffer = (unsigned char *)&header_s;
    FILE *file = NULL;

    if( ac < 2 ) usage(av[0]);

    if_init();
    if( (dev_id = if_register(&tty_operations)) < 0 )
    {
        printf("(%d) - Error getting the device identifer\n", dev_id);
        exit(1);
    }

    for(;;)
    {
        char *aux;
        int nbytes = 0, br;

        // read the header to create the file
        if( (br = if_read( dev_id, sizeof(header_T), (void *)buffer )) != sizeof(header_T) )
        {
            printf("%s: error reading\n");
            break;
        }
        if( (file = fopen(header_s.filename, "a")) == NULL )
        {
            printf("%s: error opening the %s file\n", __func__, header_s.filename);
            break;
        }
        nbytes = ntohl(header_s.nbytes);

        if( (aux = (char *)malloc(nbytes + 1)) == NULL )
        {
            printf("%s: error, not enough memory %d\n", __func__, nbytes);
            fclose(file);
            break;
        }

        // readint the gcov information to place it in the gcda file.
        int i = 0;
        for( i = 0; i < nbytes; ++i)
        {
            if( if_read( dev_id, 1, (void*)(aux + i) ) != 1 )
            {
                printf("%s: error reading\n");
                fclose(file);
                break;
            }
        }

        for( i = 0; i < nbytes; ++i)
            fwrite(aux + i, 1, 1, file);


        free(aux);
        fclose(file);
        printf("file %s done\n", header_s.filename);
    }

    printf("done\n");

    return 0;
}

