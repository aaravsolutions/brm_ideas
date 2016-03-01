/* continuus file information --- %full_filespec: fm_price_calc_pol_product.c~5:csrc:1 % */
/*******************************************************************
 *
 *  @(#) %full_filespec: fm_bill_make_invoice.c~5:csrc:1 %
 *
 *      Copyright (c) 1999 - 2006  Oracle. All rights reserved.
 *
 *      This material is the confidential property of Oracle Corporation
 *      or its subsidiaries or licensors and may be used, reproduced, stored
 *      or transmitted only in accordance with a valid Oracle license or
 *      sublicense agreement.
 *
 *******************************************************************/

/******************************************************************
 ******************************************************************
 **
 ** This policy opcode can be used to perform validations over and
 ** above those which will be performed by fm_price
 **
 ** By default it just passes 
 **
 ******************************************************************
 ******************************************************************/

#ifndef lint
static  char    Sccs_id[] = "@(#)%Portal Version: fm_get_metafield.c:ServerIDCVelocityInt:1:2006-Sep-06 16:46:27 %";
#endif

/************************************************************************
 * This policy determines whether or not the specified deal
 * object is valid and may be safely introduced into the db.
 *
 * XXX NOOP - STUBBED PROTOTYPE ONLY - ALWAYS PASSES XXX
 ************************************************************************/
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "pcm.h"
#include "ops/newpri1.h"
#include "cm_fm.h"
#include "pin_errs.h"
#include "pin_cust.h"
#include "pinlog.h"



#define FILE_SOURCE_ID  "fm_get_metafield.c (1.7)"
 
EXPORT_OP void
op_get_meta_field(
        cm_nap_connection_t     *connp,
        u_int                   opcode,
        u_int                   flags,
        pin_flist_t             *in_flistp,
        pin_flist_t             **ret_flistp,
        pin_errbuf_t            *ebufp);


static void
fm_get_meta_field(
        pcm_context_t           *ctxp,
        pin_flist_t             *in_flistp,
        pin_flist_t             **out_flistpp,
        pin_errbuf_t            *ebufp);


/*******************************************************************
 * Main routine for the PCM_OP_GET_METAFIELD operation.
 *******************************************************************/
void
op_get_meta_field(
        cm_nap_connection_t	*connp,
	u_int			opcode,
        u_int			flags,
        pin_flist_t		*in_flistp,
        pin_flist_t             **ret_flistp,
        pin_errbuf_t		*ebufp)
		
		{
        pcm_context_t           *ctxp = connp->dm_ctx;
        pin_flist_t             *r_flistp = NULL;


        if (PIN_ERR_IS_ERR(ebufp))
                return;
        PIN_ERR_CLEAR_ERR(ebufp);
        /***********************************************************
         * Insanity check.
         ***********************************************************/
        if (opcode != PCM_OP_GET_METAFIELD) {
                pin_set_err(ebufp, PIN_ERRLOC_FM,
                        PIN_ERRCLASS_SYSTEM_DETERMINATE,
                        PIN_ERR_BAD_OPCODE, 0, 0, opcode);
                PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
                        "op_get_meta_field opcode error", ebufp);
                return;
        }

		/*  Debug - What we got */
		
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
		"op_get_meta_field", in_flistp);


	/***********************************************************
         * Call main function 
         ***********************************************************/
        fm_get_meta_field(ctxp, in_flistp, &r_flistp, ebufp);
        
        if (PIN_ERR_IS_ERR(ebufp)) {
                /***************************************************
                 * Log Error Buuffer and return.
                 ***************************************************/
                PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
                        "op_get_meta_field", ebufp);
                PIN_FLIST_DESTROY_EX(&r_flistp, NULL);
                *ret_flistp = NULL;

        }
        else
        {

		*ret_flistp = PIN_FLIST_COPY(r_flistp, ebufp);
                /***************************************************
                 * Debug: What we're sending back.
                 ***************************************************/
                PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
                        "op_get_meta_field return flist", r_flistp);
        }

		
  /*** Print Output What We Got ***/
        PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,"fm_get_meta_field", r_flistp);

	
		return;
		}
		



static void
fm_get_meta_field(
	pcm_context_t           *ctxp,
        pin_flist_t             *in_flistp,
        pin_flist_t             **out_flistpp,
        pin_errbuf_t            *ebufp)
{
        pin_flist_t     *items_flistp = NULL;
        pin_flist_t     *flistp = NULL; 
        poid_t          *s_pdp = NULL; 
        poid_t          *bi_pdp = NULL; 
        int32           status = 0;
        int64           database = 0;
        int32           sflags = 256;
        int32           result = PIN_BOOLEAN_FALSE;
        void            *vp = NULL;
        pin_decimal_t   *zero_decimal =  pin_decimal("0.0", ebufp);
	pin_flist_t	*r_flistp = NULL;

        if (PIN_ERR_IS_ERR(ebufp)) {
                return;
        }
        PIN_ERR_CLEAR_ERR(ebufp);

       bi_pdp = PIN_FLIST_FLD_GET(in_flistp, PIN_FLD_POID, 0, ebufp );
 
			   
			


 /*********************************************************
         * Create the search flist to search in the item objects
         *********************************************************/
        items_flistp = PIN_FLIST_CREATE(ebufp);
        database = PIN_POID_GET_DB(bi_pdp);
        s_pdp = PIN_POID_CREATE(database, "/search", -1, ebufp);
        PIN_FLIST_FLD_PUT(items_flistp, PIN_FLD_POID, (void *)s_pdp, ebufp);
        PIN_FLIST_FLD_SET(items_flistp, PIN_FLD_TEMPLATE,
         (void *) "select X  from /metafield where  F1 = V1 ", ebufp);
        PIN_FLIST_FLD_SET(items_flistp, PIN_FLD_FLAGS, (void *)&sflags, ebufp);

        /*********************************************************
         * Add the search arguments.
         *********************************************************/

        flistp = PIN_FLIST_ELEM_ADD(items_flistp, PIN_FLD_ARGS, 1, ebufp);
        PIN_FLIST_FLD_SET(flistp, PIN_FLD_CLASS_NAME, (void *)"ASSOGSM", ebufp);

      
        /*********************************************************
         * Add the result array for the search.
         *********************************************************/

        flistp = PIN_FLIST_ELEM_ADD(items_flistp, PIN_FLD_RESULTS, 0, ebufp);
        PIN_FLIST_FLD_SET(flistp, PIN_FLD_TYPE,(void *)NULL, ebufp);
        
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "op_get_meta_field search flistp", items_flistp);  

	 PCM_OP(ctxp, PCM_OP_SEARCH, 0, items_flistp, *out_flistpp, ebufp);

	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "op_get_meta_field search flistp", *out_flistpp);     
 
  }
