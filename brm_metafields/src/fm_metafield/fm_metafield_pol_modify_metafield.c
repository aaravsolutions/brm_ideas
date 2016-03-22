/* continuus file information --- %full_filespec: fm_metafield_pol_modify_metafield.c~5:csrc:1 % */

#ifndef lint
static  char    Sccs_id[] = "@(#)%Portal Version: fm_metafield_pol_modify_metafield.c:ServerIDCVelocityInt:1:2006-Sep-06 16:46:27 %";
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



#define FILE_SOURCE_ID  "fm_metafield_pol_modify_metafield.c (1.7)"
 
EXPORT_OP void
op_modify_meta_field(
        cm_nap_connection_t     *connp,
        u_int                   opcode,
        u_int                   flags,
        pin_flist_t             *in_flistp,
        pin_flist_t             **ret_flistp,
        pin_errbuf_t            *ebufp);


static void
fm_modify_meta_field(
        pcm_context_t           *ctxp,
        pin_flist_t             *in_flistp,
        pin_flist_t             **out_flistpp,
        pin_errbuf_t            *ebufp);


/*******************************************************************
 * Main routine for the PCM_OP_MODIFY_METAFIELD operation.
 *******************************************************************/
void
op_modify_meta_field(
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
        if (opcode != PCM_OP_MODIFY_METAFIELD) {
                pin_set_err(ebufp, PIN_ERRLOC_FM,
                        PIN_ERRCLASS_SYSTEM_DETERMINATE,
                        PIN_ERR_BAD_OPCODE, 0, 0, opcode);
                PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
                        "op_modify_meta_field opcode error", ebufp);
                return;
        }

		/*  Debug - What we got */
		
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
		"op_modify_meta_field", in_flistp);


	/***********************************************************
         * Call main function 
         ***********************************************************/
        fm_modify_meta_field(ctxp, in_flistp, &r_flistp, ebufp);
        
        if (PIN_ERR_IS_ERR(ebufp)) {
                /***************************************************
                 * Log Error Buuffer and return.
                 ***************************************************/
                PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
                        "op_modify_meta_field", ebufp);
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
                        "op_modify_meta_field return flist", r_flistp);
        }

		
  /*** Print Output What We Got ***/
        PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,"fm_modify_meta_field", r_flistp);

	
		return;
		}
		



static void
fm_modify_meta_field(
	pcm_context_t           *ctxp,
        pin_flist_t             *in_flistp,
        pin_flist_t             **out_flistpp,
        pin_errbuf_t            *ebufp)
{
        pin_flist_t     *flistp = NULL; 
        int32           status = 0;
        int64           database = 0;
        int32           sflags = 256;
        int32           result = PIN_BOOLEAN_FALSE;
        pin_decimal_t   *zero_decimal =  pin_decimal("0.0", ebufp);
	pin_flist_t	*r_flistp = NULL;

        if (PIN_ERR_IS_ERR(ebufp)) {
                return;
        }
        PIN_ERR_CLEAR_ERR(ebufp);


         PCM_OP(ctxp, PCM_OP_WRITE_FLDS, 0, in_flistp, out_flistpp, ebufp);

	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "op_modify_meta_field search flistp", in_flistp);  


 
  }
