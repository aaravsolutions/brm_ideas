
#include "pcm.h"
#include "ops/cust.h"
#include "cm_fm.h"
#include "pin_errs.h"
#include "pinlog.h"
#include "pin_cust.h"
#include "ops/custom_opcode.h"

EXPORT_OP void
op_create_metafield(
		cm_nap_connection_t     *connp,
		int32                    opcode,
		int32                    flags,
		pin_flist_t             *in_flistp,
		pin_flist_t            **ret_flistpp,
		pin_errbuf_t            *ebufp);

void
fm_cust_pol_create_metafield_obj(
		pcm_context_t           *ctxp,
		int32                    flags,
		pin_flist_t             *in_flistp,
		pin_flist_t            **ret_flistpp,
		pin_errbuf_t            *ebufp) ;


/*******************************************************************
 * Main routine for the PCM_OP_CREATE_METAFIELD operation.
 *******************************************************************/
void
op_create_metafield(
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
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR, "op_create_metafield opcode error", ebufp);
		return;
	}

	/***********************************************************
	 * Debug: What we got.
	 ***********************************************************/
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "op_create_metafield input flist", in_flistp);

	/***********************************************************
	 * Do the actual op in a sub-function.
	 ***********************************************************/
	fm_cust_pol_create_metafield_obj(ctxp, flags, in_flistp, ret_flistpp, ebufp);

	/***********************************************************
	 * Error?
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) 
	{
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR, "op_create_metafield error", ebufp);
		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_ERROR, "op_create_metafield return flist", *ret_flistpp);
	} 
	else 
	{
		/***************************************************
		 * Debug: What we're sending back.
		 ***************************************************/
		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "op_create_metafield return flist", *ret_flistpp);
		vp = PIN_FLIST_FLD_GET(*ret_flistpp,PIN_FLD_POID,1,ebufp);

		if(PIN_POID_IS_NULL(vp)==0)
			PIN_ERR_LOG_POID(PIN_ERR_LEVEL_DEBUG, "metafield poid created is", vp);
	}
	return;
}
//  INPUT FLIST FOR CREATING THE BULK/ONE OBJECT
//  
//  0 PIN_FLD_POID           POID [0] 0.0.0.1 /metafield -1 0
//  0 PIN_FLD_VALUES          ARRAY [1] allocated 20, used 3
//  1     PIN_FLD_NAME            STR [0] "DUMMY_NAME"
//  1     PIN_FLD_TYPE           ENUM [0] 1
//  1     PIN_FLD_CLASS_NAME      STR [0] "DUMMY_CLASS"
//  1 PIN_FLD_ACCOUNT_OBJ    POID [0]  0.0.0.1 /account -1
//  0 PIN_FLD_VALUES          ARRAY [2] allocated 20, used 3
//  1     PIN_FLD_NAME            STR [0] "DUMMY_NAME2"
//  1     PIN_FLD_TYPE           ENUM [0] 1
//  1     PIN_FLD_CLASS_NAME      STR [0] "DUMMY_CLASS2"
//  1 PIN_FLD_ACCOUNT_OBJ    POID [0]  0.0.0.1 /account -1
//  0 PIN_FLD_VALUES          ARRAY [3] allocated 20, used 3
//  1     PIN_FLD_NAME            STR [0] "DUMMY_NAME3"
//  1     PIN_FLD_TYPE           ENUM [0] 1
//  1     PIN_FLD_CLASS_NAME      STR [0] "DUMMY_CLASS3"     
//  1 PIN_FLD_ACCOUNT_OBJ    POID [0]  0.0.0.1 /account -1 
//    
//  

void
fm_cust_pol_create_metafield_obj(
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
	char 	      *program_name = NULL;
	char 	      *class_name= NULL;
	char 	      *default_value= NULL;
	int 	       fld_type=0;

	if(PIN_ERRBUF_IS_ERR(ebufp))
		return;
	PIN_ERR_CLEAR_ERR(ebufp);

	*ret_flistpp = NULL;

	//Count FIELDS array 
	count = PIN_FLIST_ELEM_COUNT(in_flistp,PIN_FLD_VALUES,ebufp);


	if (count==0)
		return;

	if(count==1)
	{

		i_flist= PIN_FLIST_CREATE(ebufp);
		vp = PIN_FLIST_FLD_GET(in_flistp,PIN_FLD_POID,1,ebufp);
		PIN_FLIST_FLD_SET(i_flist,PIN_FLD_POID,(void*)vp,ebufp);

		sub_flistp = PIN_FLIST_ELEM_GET(in_flistp, PIN_FLD_VALUES,PIN_ELEMID_ANY, 1, ebufp);
		program_name = PIN_FLIST_FLD_GET(sub_flistp,PIN_FLD_NAME,1,ebufp);
		PIN_FLIST_FLD_SET(i_flist,PIN_FLD_NAME,program_name,ebufp);

		fld_type =*(int*) PIN_FLIST_FLD_GET(sub_flistp,PIN_FLD_TYPE,1,ebufp);
		PIN_FLIST_FLD_SET(i_flist,PIN_FLD_TYPE,&fld_type,ebufp);

		class_name=PIN_FLIST_FLD_GET(sub_flistp,PIN_FLD_CLASS_NAME,1,ebufp);
		PIN_FLIST_FLD_SET(i_flist,PIN_FLD_CLASS_NAME,class_name,ebufp);

		default_value=PIN_FLIST_FLD_GET(sub_flistp,PIN_FLD_DEFAULT_VALUE,1,ebufp);
		if(default_value)
			PIN_FLIST_FLD_SET(i_flist,PIN_FLD_DEFAULT_VALUE,default_value,ebufp);

		if (PIN_ERRBUF_IS_ERR(ebufp))
		{
			PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,"Error Occured while creating the input flist",ebufp);
			return;
		}

		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,"input flist for metafield obj ",i_flist);


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
		PCM_OP(ctxp,PCM_OP_BULK_CREATE_OBJ ,0,in_flistp,ret_flistpp,ebufp);

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


