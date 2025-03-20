FLAGS = -Wall -O2 -s -Wl,--strip-all -ffunction-sections -fdata-sections -flto
BIBLI = -lwinmm

NAME_OUTPUT = mon_programme

all :
	gcc -o ${NAME_OUTPUT}.exe ./src/audioCapture.c ${FLAGS} ${BIBLI}

clean :
	del ${NAME_OUTPUT}.exe