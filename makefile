OBJ = main.o screen.o sound.o
APPNAME = sound.out
$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm  
%.o : %.c
	gcc -c -o $@ $<

clean :
	rm $(APPNAME) $(OBJ)

tar : 
	tar cf sound.tar *.c *.h makefile
	