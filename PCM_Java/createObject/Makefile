######################################################################
# 
# Copyright (c) 2000, 2009, Oracle and/or its affiliates. All rights reserved. 
#  This material is the confidential property of Oracle Corporation. 
#  or its subsidiaries or licensors and may be used, reproduced, stored 
#  or transmitted only in accordance with a valid Oracle license or 
#  sublicense agreement.
#
######################################################################

include env.unix
include Make.include.unix

JAVA_PCM = CreateObject.java 
all:
	$(JAVAC) -classpath $(CLASSPATH) $(JAVA_PCM)

clean:
	rm -f *.class
