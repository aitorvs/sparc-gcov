/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/04/08 11:34:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aitor Viana Sanchez (avs), aitor.viana.sanchez@esa.int
 *        Company:  European Space Agency (ESA-ESTEC)
 *
 * =====================================================================================
 */

#include <stdio.h>

int main(void)
{
    int lista[] = { 12, 3, 7, 5, 10, 32, 67, 39, 25, 1};
    int i = 0;

    printf("Original list:");
    for (i = 0; i < 10; i++)
        printf(" %d", lista[i]);
    printf("\n");

    bubble(lista, 10);

    printf("Ordered list:");
    for (i = 0; i < 10; i++)
        printf(" %d", lista[i]);
    printf("\n");
}

