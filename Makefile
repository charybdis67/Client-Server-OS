all:statclient	statserver
findtopk_mqueue:
	gcc	-g	-Wall	-o	statclient	statclien.c
findtopk_thread:
	gcc	-g	-Wall	-o	statserver	statserver.c
clean:	
	rm	-fr	statclient	statclient.o	*~	
	rm	-fr	statserver	statserver.o	*~
