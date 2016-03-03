
#include "pcm.h"
#include "ops/cust.h"
#include "cm_fm.h"
#include "pin_errs.h"
#include "pinlog.h"
#include "pin_cust.h"
#include "ops/custom_opcode.h"

EXPORT_OP void
pcm_op_create_metafield(
		cm_nap_connection_t     *connp,
		int32                    opcode,
		int32                    flags,
		pin_flist_t             *in_flistp,
		pin_flist_t            **ret_flistpp,
		pin_errbuf_t            *ebufp);

void
fm_create_metafield_obj(
		pcm_context_t           *ctxp,
		int32                    flags,
		pin_flist_t             *in_flistp,
		pin_flist_t            **ret_flistpp,
		pin_errbuf_t            *ebufp) ;


/*******************************************************************
 * Main routine for the PCM_OP_CREATE_METAFIELD operation.
 *******************************************************************/
void
pcm_op_create_metafield(
		cm_nap_connection_t     *connp,
		int32                    opcode,
		int32                    flags,
		pin_flist_t             *in_flistp,
		pin_flist_t            **ret_flistpp,
		pin_errbuf_t            *ebufp)
{
	pcm_context_t           *ctxp = connp->dm_ctx;
	void				*vp =NULL;

	PIN_ERR_CLEAR_ERR(ebufp);

	/***********************************************************
	 * Insanity check.
	 ***********************************************************/
	if (opcode != PCM_OP_CREATE_METAFIELD) {
		pin_set_err(ebufp, PIN_ERRLOC_FM, PIN_ERRCLASS_SYSTEM_DETERMINATE, PIN_ERR_BAD_OPCODE, 0, 0, opcode);
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR, "pcm_op_create_metafield opcode error", ebufp);
		return;
	}

	/***********************************************************
	 * Debug: What we got.
	 ***********************************************************/
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "pcm_op_create_metafield input flist", in_flistp);

	/***********************************************************
	 * Do the actual op in a sub-function.
	 ***********************************************************/
	fm_create_metafield_obj(ctxp, flags, in_flistp, ret_flistpp, ebufp);

	/***********************************************************
	 * Error?
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) 
	{
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR, "pcm_op_create_metafield error", ebufp);
		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_ERROR, "pcm_op_create_metafield return flist", *ret_flistpp);
	} 
	else 
	{
		/***************************************************
		 * Debug: What we're sending back.
		 ***************************************************/
		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "pcm_op_create_metafield return flist", *ret_flistpp);
		vp = PIN_FLIST_FLD_GET(*ret_flistpp,PIN_FLD_POID,1,ebufp);

			if(PIN_POID_IS_NULL(vp)==0)
				PIN_ERR_LOG_POID(PIN_ERR_LEVEL_DEBUG, "metafield poid created is", vp);
	}
	return;
}

void
fm_create_metafield_obj(
		pcm_context_t           *ctxp,
		int32                    flags,
		pin_flist_t             *in_flistp,
		pin_flist_t            **ret_flistpp,
		pin_errbuf_t            *ebufp)

{
	void 		   *vp = NULL;
	int 		   count =0;
	int64        database  = pcm_get_current_db_no(ctxp);
	pin_flist_t   *i_flist = NULL;
	pin_flist_t   *sub_flistp = NULL;
	pin_flist_t   *r_flistp = NULL;

	if(PIN_ERRBUF_IS_ERR(ebufp))
		return;
	PIN_ERR_CLEAR_ERR(ebufp);

	*ret_flistpp = NULL;

	i_flist= PIN_FLIST_CREATE(ebufp);
	vp =  PIN_POID_CREATE(database, "/metafield", -1, ebufp);

	PIN_FLIST_FLD_SET(i_flist,PIN_FLD_POID,(void*)vp,ebufp);
	PCM_OP(ctxp,PCM_OP_READ_OBJ,0,i_flist,ret_flistpp,ebufp);

	sub_flistp = PIN_FLIST_ELEM_ADD(i_flist, PIN_FLD_ARGS, 1, ebufp);

	PIN_FLIST_FLD_SET(sub_flistp,PIN_FLD_NAME,NULL,ebufp);
	PIN_FLIST_FLD_SET(sub_flistp,PIN_FLD_TYPE,NULL,ebufp);
	PIN_FLIST_FLD_SET(sub_flistp,PIN_FLD_CLASS_NAME,NULL,ebufp);
	PIN_FLIST_FLD_SET(sub_flistp,PIN_FLD_DEFAULT_VALUE,NULL,ebufp);

	if (PIN_ERRBUF_IS_ERR(ebufp))
	{
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,"Error Occured while creating the input flist",ebufp);
		return;
	}

	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,"input flist for metafield obj ",i_flist);


	//Count FIELDS array 

	count = PIN_FLIST_ELEM_COUNT(i_flist,PIN_FLD_NAME,ebufp);

	if (count==0)
		return;
	if(count==1)
	{
		//Call pcm_op_create_obj 
		PCM_OP(ctxp,PCM_OP_CREATE_OBJ,0,i_flist,ret_flistpp,ebufp);

		if(PIN_ERRBUF_IS_ERR(ebufp))
				{
				PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,"Error Occured while calling PCM_OP_CREATE_OBJ",ebufp);
				return;
				}

				}
				else if (count >1)
				{
				//Call pcm_op_bulk_create_obj
				PCM_OP(ctxp,PCM_OP_BULK_CREATE_OBJ ,0,i_flist,ret_flistpp,ebufp);

				if(PIN_ERRBUF_IS_ERR(ebufp))
					{
					PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,"Error Occured while calling PCM_OP_BULK_CREATE_OBJ" ,ebufp);
					return;
					}
					}

					if(ret_flistpp)
					PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,"Output flist for metafield obj ",*ret_flistpp);

					return;

					}	


