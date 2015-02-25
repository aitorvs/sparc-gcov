/*
 * =====================================================================================
 *
 *       Filename:  delay.c
 *
 *    Description:  This function implements the delay function
 *
 *        Version:  1.0
 *        Created:  07/04/08 16:27:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aitor Viana Sanchez (avs), aitor.viana.sanchez@esa.int
 *        Company:  European Space Agency (ESA-ESTEC)
 *
 * =====================================================================================
 */


#include <time.h>

int milli_delay (int milli_seconds)
{
	struct timespec tm ;
	
	/* compute the second part */
	tm.tv_sec  = (time_t) (milli_seconds / 1000) ;
	/* take the residue and and convert to nano seconds */
	tm.tv_nsec = (milli_seconds % 1000) * 1000000 ;
	
	if( nanosleep(&tm, NULL) == 0)
		return(0) ;
	else
		return(-1) ;
}

