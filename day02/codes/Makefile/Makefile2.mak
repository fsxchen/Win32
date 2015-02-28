CPP=cl.exe
CPP_FLAG="/c"
LINK32=link.exe
LINK_LIB=user32.lib

ALL: HelloWorld.exe
	$(CPP) $(CPP_FLAG) HelloWorld.c
	$(LINK32) $(LINK_LIB) HelloWorld.obj /out:HelloWorld.exe

CLEAN:
	echo deleting ...
	del *.obj
	del *.exe

INSTALL:

