/*
 *
 *      Copyright (c) 2004 - 2007 Oracle. All rights reserved.
 *
 *      This material is the confidential property of Oracle Corporation or its
 *      licensors and may be used, reproduced, stored or transmitted only in
 *      accordance with a valid Oracle license or sublicense agreement.
 *
 */

#ifndef lint
static  char    Sccs_id[] = "@(#)%Portal Version: fm_price_calc_pol_config.c:RWSmod7.3.1Int:1:2007-Jun-28 05:35:28 %";
#endif

#include <stdio.h>	/* for FILE * in pcm.h */
#include "ops/newpri1.h"
#include "pcm.h"
#include "cm_fm.h"

#ifdef WIN32
__declspec(dllexport) void * fm_price_calc_pol_config_func();
#endif


/*******************************************************************
 *******************************************************************/
struct cm_fm_config fm_price_calc_pol_config[] = {
	/* opcode as a u_int, function name (as a string) */
	{ PCM_OP_POL_PRI_TEST,   "op_test_pri" },
	{ PCM_OP_GET_METAFIELD,  "op_get_meta_field"},
	{ 0,	(char *)0 }
};

#ifdef WIN32
void *
fm_price_calc_pol_config_func()
{
  return ((void *) (fm_price_calc_pol_config));
}
#endif
