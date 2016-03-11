/************************************************************************
 * Copyright (c) 2000, 2009, Oracle and/or its affiliates. 
 * All rights reserved. 
 *  This material is the confidential property of Oracle Corporation. 
 *  or its subsidiaries or licensors and may be used, reproduced, stored 
 *  or transmitted only in accordance with a valid Oracle license or 
 *  sublicense agreement.
 ************************************************************************/

import com.portal.pcm.*;
import com.portal.pcm.fields.*;

public class CreateObject {
	private static boolean logout = true;
	private static long   fDatabaseNumber;


	public static void main(String[] args) {

		try {



			// Create PCM connext necessary for connecting to the server. 
	 		// A valid Infranet.properties file should be in the classpath.
	 		// See context examples for additional information.
            		PortalContext ctx = new PortalContext();
			ctx.connect();
			fDatabaseNumber = ctx.getCurrentDB();

			// Get the input flist
			FList inflist = createFList(fDatabaseNumber);
			System.out.println("Connected with database number: " + fDatabaseNumber);

			// Print input flist
			System.out.println("Input flist to PCM_OP_CREATE_OBJ");
			System.out.println(inflist);

			// Call the opcode
			FList outflist = ctx.opcode(PortalOp.CREATE_OBJ, inflist);

			// Close PCM connection
			ctx.close(logout);

			// Print the return flist
			System.out.println("Output flist of PCM_OP_CREATE_OBJ:");
			outflist.dump(); // this is an alternate way to print out an flist

			System.out.println("Success!");

		} catch (EBufException ebuf) {
			System.out.println("You weren't able to call the PCM_OP_CREATE_OBJECT opcode.");
			System.out.println(" * Is the Infranet server CM up?");
			System.out.println("Here's the error:");
			System.out.println(ebuf);
		}
	}

	/*******************************************************************
	 * Create and return a input  FList of the form for PCM_OP_CREATE_OBJ:
	 * 		0 PIN_FLD_POID                      POID [0] 0.0.0.1 /my_test -1 8
	 *		0 PIN_FLD_ACCOUNT_OBJ               POID [0] 0.0.0.1 /account -1 0
	 *		0 PIN_FLD_NAMEINFO                  ARRAY [0] allocated 5, used 5
	 *		1 PIN_FLD_NAME                       STR [0] "PIN Service Object"
	 *******************************************************************/
	public static FList createFList(long fDatabaseNumber) throws EBufException {
		// create the flist
		FList flist = new FList();
		 System.out.println("Connected with database number: " + fDatabaseNumber);

		// add data to the flist
		flist.set(FldPoid.getInst(), new Poid(fDatabaseNumber, -1, "/my_test"));
		flist.set(FldAccountObj.getInst(), new Poid(fDatabaseNumber, -1, "/account"));
		
		FList nameInfo = new FList();
                nameInfo.set( FldName.getInst(), "archana" );
		// Add the name info to the plan flist
                flist.setElement( FldNameinfo.getInst(), 1, nameInfo );


		System.out.println("Prepare Input Flist for PCM_OP_CREATE_OBJ:");
                        System.out.println(flist);

		return flist;
	}
}
