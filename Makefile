FLAGS = -Wall -O2 -s -Wl,--strip-all -ffunction-sections -fdata-sections -flto
BIBLI = -lwinmm

NAME_OUTPUT = prog

NAME_OUTPUT_C = prog_capture
NAME_OUTPUT_M = prog_manipulation

SRC_C = ./src/AudioCapture.c
SRC_M = ./src/AudioManipulation.c

all :
	gcc -o ${NAME_OUTPUT}.exe ${SRC_M} ${FLAGS} ${BIBLI}

capture :
	gcc -o ${NAME_OUTPUT_C}.exe ${SRC_C} ${FLAGS} ${BIBLI}

manipulation :
	gcc -o ${NAME_OUTPUT_M}.exe ${SRC_M} ${FLAGS} ${BIBLI}

clean :
	del ${NAME_OUTPUT}.exe