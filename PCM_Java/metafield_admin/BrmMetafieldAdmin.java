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
import java.util.*;
import java.io.*;

import customfields.*;


	public class BrmMetafieldAdmin {
		private static boolean logout = true;
		private static long   fDatabaseNumber;
		static PortalContext ctx ;	
		static String s = "BMAU";
		static int i = 0;
		static PrintStream os = System.out;

		static void displayHelp(String string) throws EBufException{
		        if (string == null || string.equals("")) {
            			os.println("BMAU command list::");
            			os.println("");
            			os.println(" login    - login using values in PortalUser.properties");
            			os.println("");
            			os.println(" logout    - logout and close context");
            			os.println("");
            			os.println(" create -name <NAME> -type <TYPE> -class_name <CLASS_NAME> -default_value <DEFAULT_VALUE>");
            			os.println("");
            			os.println(" modify -poid_id0 <POID_ID0> -name <NAME> -type <TYPE> -class_name <CLASS_NAME> -default_value <DEFAULT_VALUE>");
            			os.println("");
            			os.println(" get -name <NAME> -type <TYPE> -class_name <CLASS_NAME>");
            			os.println("");
            			os.println(" delete -name  -type -class_name -default_value");
            			os.println("");
            			os.println(" q or quit                         - quit");
            			os.println("");
            			os.println(" h or ? or help             - displays this help");
            			os.println("");
        		}
    		}




		public static void main(String[] arrstring) throws IOException, EBufException, Exception{
			InputStreamReader inputStreamReader;
        		InputStreamReader inputStreamReader2;
        		boolean bl = false;

	        	if (arrstring.length > 0) {
        		    	inputStreamReader2 = new FileReader(arrstring[0]);
                 	} else {
                		bl = true;
                		inputStreamReader2 = new InputStreamReader(System.in);
                	}
        		LineNumberReader lineNumberReader = new LineNumberReader(inputStreamReader2);
        		long l = 1;
        		String string = null;

			while (((string = BrmMetafieldAdmin.getLine(lineNumberReader, bl)) != null) && !string.equals("quit") && !string.equals("q")) {


			try {
        	        	String string2;
        	        	String string3;
        	        	String string4;
        	        	String name = null;
        	        	int type = 0;
        	        	String class_name = null;
        	        	String default_value = null;
                		long l2;
                		int poid_id0 = 0;
                		string.trim();
                		StringTokenizer stringTokenizer = new StringTokenizer(string);

                		if (!stringTokenizer.hasMoreTokens() || (string2 = stringTokenizer.nextToken()).startsWith("#")) continue;

				if (string2.equals("login") || string2.equals("logout")){
                			fDatabaseNumber = BrmMetafieldAdmin.createContextUsingPropertiesFile(string);
					continue;
				} 

				if (string2.equals("create")){
					if (stringTokenizer.countTokens() < 2) {
            					System.err.println(" create -name <NAME> -type <TYPE> -class_name <CLASS_NAME> -default_value <DEFAULT_VALUE>");
                        			continue;
                    			}
					while (stringTokenizer.hasMoreTokens()){
						string3 = stringTokenizer.nextToken();

						if(string3.equals("-name") && name == null){
							name = stringTokenizer.nextToken();
						}

                                	        if(string3.equals("-type")){
							if (type == 0){
								string4 = stringTokenizer.nextToken();
                                        			type = Integer.parseInt(string4);
                                        		}
						}
                                        
						if(string3.equals("-class_name") && class_name == null){
                                        		class_name = stringTokenizer.nextToken();
                                        	}
	
        	                                if(string3.equals("-default_value") && default_value == null){
                                        		default_value = stringTokenizer.nextToken();
                                        	}
					}
					if (name == null || type == 0 || class_name == null){
						System.err.println(" create -name <NAME-Required> -type <TYPE-Required> -class_name <CLASS_NAME-Required> -default_value<DEFAULT_VALUE>");
						os.println("Required Field Missing");
					} else {
                                		BrmMetafieldAdmin.createMetafieldObj(name, type, class_name, default_value, fDatabaseNumber);
                                		continue;
					}
                        	}

				if (string2.equals("get")){

					if (stringTokenizer.countTokens() < 2) {
                                                System.err.println(" get -name <NAME> -type <TYPE> -class_name <CLASS_NAME> ");
                                                continue;
                                        }

					while (stringTokenizer.hasMoreTokens()){
                                        	string3 = stringTokenizer.nextToken();
                                         	
						if(string3.equals("-name") && name == null){
                                        		name = stringTokenizer.nextToken();
                                        	}
                                         	
						if(string3.equals("-type")){
                                                	if(type == 0) {
                                        			string4 = stringTokenizer.nextToken();
                                        			type = Integer.parseInt(string4);
                                        		}
                                        	}
	
        	                                if(string3.equals("-class_name") && class_name == null){
                                        		class_name = stringTokenizer.nextToken();
                                        	}
					}
					
                                	BrmMetafieldAdmin.getMetafieldObj(name, type, class_name, fDatabaseNumber);
                                	continue;
                        	}
		
				if (string2.equals("modify")){
					if (stringTokenizer.countTokens() < 2) {
                                        	System.err.println(" modify -poid_id0 -name -type  -class_name -default_value");
                                		continue;
                                	}
                        
					while (stringTokenizer.hasMoreTokens()){
                                        	string3 = stringTokenizer.nextToken();
						if(string3.equals("-poid_id0")){
					 		if (poid_id0 == 0){
                                        			string4 = stringTokenizer.nextToken();
								poid_id0 = Integer.parseInt(string4);
                                        		}
						}
	
                                         	if(string3.equals("-name") && name == null){
                                        		name = stringTokenizer.nextToken();
                                        	}
                                         	if(string3.equals("-type")){
							if(type == 0) {
								string4 = stringTokenizer.nextToken();
                                        			type = Integer.parseInt(string4);
							}
                                        	}

	                                        if(string3.equals("-class_name") && class_name == null){
                                        		class_name = stringTokenizer.nextToken();
                                        	}

	                                        if(string3.equals("-default_value") && default_value == null){
        		                                default_value = stringTokenizer.nextToken();
                                        	}
                                        }

                               		BrmMetafieldAdmin.modifyMetafieldObj(poid_id0, name, type, class_name, default_value, fDatabaseNumber);
                                	continue;
                        	}

				if (string2.equals("delete")){
                                	FList fList = BrmMetafieldAdmin.deleteMetafieldObj(string, fDatabaseNumber);
                                continue;
                        	}

				if (string2.equals("help")){
					BrmMetafieldAdmin.displayHelp(null);
					continue;
				} else {
                                	os.println("-- Invalid commmand: Type 'help' to display command set for BMAU ");
				}
			

			} catch (EBufException ebuf) {
				os.println("You weren't able to call the opcode.");
				os.println(" * Is the Infranet server CM up?");
				os.println("Here's the error:");
				os.println(ebuf);
			}
		}
                os.println("------Exiting the application------");

	}


	/***************************************************************
         * Create a PortalContext object with settings defined
         * in Infranet.properties file. There must be a valid
         * Infranet.properties file in the classpath.
         ***************************************************************/
        public static long createContextUsingPropertiesFile(String s) {
            try {

			switch(s){
                           case "login" :
				if (ctx != null) {
                        		System.err.println("Error: Logout first");
                    		} else {
                        		os.println("---------------------------------------------------------------");
                        		os.println("Creating PCM context using configuration in Infranet.properties");
                        		ctx = new PortalContext();
                        		ctx.connect();
					fDatabaseNumber = ctx.getCurrentDB();

                        		os.println("Context successfully created.");
                        		// print out some info about the connection
                        		os.println("current DB: " + fDatabaseNumber);
                        		os.println("user ID:    " + ctx.getUserID());
				}
                                break; //optional
                           case "logout" :
                        		// close the connection
                        		ctx.close(true);
					ctx = null;
                        		os.println("PCM connection closed.");
                                break; //optional
			}	
            } catch (EBufException ebufex) {
                        os.println("Your connection to the server failed.");
                        os.println(" * Do you have a correct Infranet.properties file in the classpath?");
                        os.println(" * Is the Infranet server CM up?");
                        os.println("Here's the error:");
                        os.println(ebufex);
            }
			return fDatabaseNumber;
}
	/*-------------------------------------------------------------------------------------
	calling create metafield obj function
	------------------------------------------------------------------------------------*/

	static void createMetafieldObj(String name, int type, String class_name, String default_value, long fDatabaseNumber) throws IOException, EBufException {
        	String string3;
		// create the flist
                FList flist = new FList();

		if (fDatabaseNumber != 0){
                	// add data to the flist
                	flist.set(FldPoid.getInst(), new Poid(fDatabaseNumber, -1, "/metafield"));
                	flist.set(FldAccountObj.getInst(), new Poid(fDatabaseNumber, -1, "/account"));

                	FList values = new FList();
                	values.set( FldName.getInst(), name );

			if ( default_value != null) {
                		values.set( PinFldDefaultValue.getInst(), default_value );
			}
                	values.set( PinFldClassName.getInst(), class_name );
                	values.set( FldType.getInst(), type );
                	// Add the name info to the plan flist
                	flist.setElement( FldValues.getInst(), 1, values );

                	os.println("Input Flist for PCM_OP_CREATE_OBJ:");
                        os.println(flist);
		 	FList outflist = ctx.opcode(CustomOp.CREATE_METAFIELD, flist);
               		os.println("Output Flist for PCM_OP_POL_CREATE_METAFIELD:");
                        os.println(outflist);
			} else {
                        	System.err.println(" login to connect the database");
               		}
		}

	/*-------------------------------------------------------------------------------------
	calling get metafield obj function
	------------------------------------------------------------------------------------*/

	static void getMetafieldObj(String name, int type, String class_name, long fDatabaseNumber) throws IOException, EBufException {
        	FList flist = new FList();

		if (fDatabaseNumber != 0){
                	// add data to the flist
                	flist.set(FldPoid.getInst(), new Poid(fDatabaseNumber, -1, "/metafield"));
                	flist.set(FldAccountObj.getInst(), new Poid(fDatabaseNumber, -1, "/account"));

			FList keys = new FList();
			if ( name != null) {
                		keys.set( FldName.getInst(), name );
                	}
                	if ( class_name != null) {
                		keys.set( PinFldClassName.getInst(), class_name );
                	}
                	if ( type != 0) {
                		keys.set( FldType.getInst(), type );
                	}
                	// Add the Fields to the plan flist
                	flist.setElement( PinFldKeys.getInst(), 1, keys );


                	os.println("Input Flist for PCM_OP_POL_GET_METAFIELD::");
                        os.println(flist);
                	// Call the opcode
                        FList outflist = ctx.opcode(CustomOp.GET_METAFIELD, flist);
                	os.println("Output Flist for PCM_OP_POL_GET_METAFIELD:");
                        os.println(outflist);

			} else {
				System.err.println(" login to connect the database");
			}	
	
    	}
	/*-------------------------------------------------------------------------------------
	calling modify  metafield obj function
	------------------------------------------------------------------------------------*/

	static void modifyMetafieldObj(int poid_id0, String name, int type, String class_name, String default_value, long l) throws IOException, EBufException {
 		// create the flist
                FList flist = new FList();
			if(fDatabaseNumber == 0)
			{
				os.println("login to connect to the respective database");
			} else {
		
                 		os.println("Connected with database number: " + fDatabaseNumber);
                		// add data to the flist
                		flist.set(FldPoid.getInst(), new Poid(fDatabaseNumber, poid_id0, "/metafield"));
                		flist.set(FldAccountObj.getInst(), new Poid(fDatabaseNumber, -1, "/account"));

                		FList field = new FList();
				if ( name != null) {
                		flist.set( FldName.getInst(), name );
				}
                		if ( default_value != null) {
                		flist.set( PinFldDefaultValue.getInst(), default_value );
                		}
				if ( class_name != null) {
                		flist.set( PinFldClassName.getInst(), class_name );
				}
				if ( type != 0) {
                		flist.set( FldType.getInst(), type );
				}
                		// Add the Fields to the plan flist
                		//flist.setElement( FldField.getInst(), 1, field );


                		os.println("Input Flist for PCM_OP_POL_MODIFY_METAFIELD::");
                        	os.println(flist);
				// Call the opcode
                        	FList outflist = ctx.opcode(CustomOp.MODIFY_METAFIELD, flist);
				os.println("Output Flist for PCM_OP_POL_MODIFY_METAFIELD:");
                        	os.println(outflist);
			}
    		}
/*-------------------------------------------------------------------------------------
calling delete metafield obj function
------------------------------------------------------------------------------------*/

static FList deleteMetafieldObj(String string, long l) throws IOException, EBufException {
        FList fList = null;
        os.println("delete");
        return fList;
    }

/*-----------------------------------------------------------------------------------*/
static String getLine(LineNumberReader lineNumberReader, boolean bl) throws IOException {
        if (bl) {
            os.print("BMAU> ");
        }
        return lineNumberReader.readLine();
    }

}
