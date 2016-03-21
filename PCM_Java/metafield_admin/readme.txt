readme
Obrm_metafield_admin Utility

	 This utility is written in PCM Java, it will be used to do the following operations.
		- Add or define a metafield  using PCM_OP_CREATE_METAFIELD opcode
 		- Update metafield definition using PCM_OP_GET_METAFIELD opcode
 		- Get the list of metafileds using PCM_OP_MODIFY_METAFIELD opcode

	 Executing the utility :
		1. Copy the metafield_admin directory .
		1. Check for env.unix file and set the absolute JAVA_HOME and jar file path. 
		2. Copy pcm_custom.jar file to directory and specify the path in env.unix file.
  		3. Compile the file, using command “make” 
		4. To run the utility, type “BMAU” 
				(or)
		java -classpath 	/home/pin12/opt/portal/7.4/jars/pcm.jar:/home/pin12/opt/portal/7.4/	jars/pcmext.jar:/home/pin12/opt/portal/7.4/jars/pcm_custom.jar: 	BrmMetafieldAdmin

	Command List of BMAU
	 login    - login using values in PortalUser.propertie
	 logout    - logout and close context
 	 create -name <NAME> -type <TYPE> -class_name <CLASS_NAME> -default_value <DEFAULT_VALUE>	
 	 modify -poid_id0 <POID_ID0> -name <NAME> -type <TYPE> -class_name <CLASS_NAME> -default_value <DEFAULT_VALUE>
 	 get -name <NAME> -type <TYPE> -class_name <CLASS_NAME>
 	 delete -name  -type -class_name -default_value
 	 q or quit                         - quit
 	 help             - displays this help

	Example to create a Metafield Object:
    		BMAU> login
		---------------------------------------------------------------
		Creating PCM context using configuration in Infranet.properties
		Context successfully created.
		current DB: 1
		user ID:    0.0.0.1 /service/admin_client 2 349
		BMAU> create -name new -class_name bmau -type 3 -default_value test
		Input Flist for PCM_OP_CREATE_OBJ:
		0 PIN_FLD_VALUES                   ARRAY [1] allocated 4, used 4
		1     PIN_FLD_NAME                   STR [0] "new"
		1     PIN_FLD_DEFAULT_VALUE          STR [0] "test"
		1     PIN_FLD_CLASS_NAME             STR [0] "bmau"
		1     PIN_FLD_TYPE                  ENUM [0] 3
		0 PIN_FLD_ACCOUNT_OBJ               POID [0] 0.0.0.1 /account -1 0
		0 PIN_FLD_POID                      POID [0] 0.0.0.1 /metafield -1 0

		Output Flist for PCM_OP_POL_CREATE_METAFIELD:
		0 PIN_FLD_POID                      POID [0] 0.0.0.1 /metafield 419634 0

		BMAU> logout
		PCM connection closed.
		BMAU> 

