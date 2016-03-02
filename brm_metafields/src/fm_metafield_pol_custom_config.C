/*******************************************************************
 *
 *
* Copyright (c) 2007, 2011, Oracle and/or its affiliates. All rights reserved. 
 * 
 *      This material is the confidential property of Oracle Corporation
 *      or its licensors and may be used, reproduced, stored or transmitted
 *      only in accordance with a valid Oracle license or sublicense agreement.
 *
 *******************************************************************/

#ifndef lint
static  char Sccs_Id[] = "@(#)$Id: fm_metafield_pol_custom_config.c /cgbubrm_main.rwsmod/1 2011/07/26 04:22:50 dbangalo Exp $";
#endif

#include <stdio.h>			/* for FILE * in pcm.h */
#include "ops/cust.h"
#include "pcm.h"
#include "cm_fm.h"
#include "ops/custom_opcode.h"

PIN_EXPORT void * fm_metafield_pol_custom_config_func();

/*******************************************************************
 *******************************************************************/

struct cm_fm_config fm_metafield_pol_custom_config[]={
	/* opcode as a u_int, function name (as a string) */

        /*****************************************************************************
         * If you want to customize any of the op-codes commented below, you need to *
         * uncomment it.
         *****************************************************************************/

	{ PCM_OP_CREATE_METAFIELD,		"op_create_metafield"},
	{ 0,	(char *)0 }
};

void *
fm_metafield_pol_custom_config_func()
{
  return ((void *) (fm_metafield_pol_custom_config));
}

