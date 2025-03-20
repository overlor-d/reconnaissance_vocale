FLAGS = -Wall -O2 -s -Wl,--strip-all -ffunction-sections -fdata-sections -flto
BIBLI = -lwinmm

all :
	gcc -o mon_programme.exe ./src/audioCapture.c ${FLAGS} ${BIBLI}