###################################################
# with GLEW:
#	make GLEW='true'
#
# without GLEW (i.e. with glext.h)
#	make
#
# to CLEAN:
#	make clean
##################################################

# VARIABLE DEFINITIONS
# --------------------
CC = g++
LIB_FILENAME = 
LIBS_DIR = -L.
INC =
MACROS =
OPTS = -g -std=c++11
OBJS = XMLHandler.o JSONHandler.o Object3D.o GameManager.o GameState.o GameStateManager.o Keyboard.o InputManager.o SystemLog.o Window.o gl_core_4_2.o 

# TARGETS
# -------
all: $(OBJS)
	ar cvr $(LIB_FILENAME) $(OBJS)

%.o : %.cpp 
	$(CC) -c $< $(OPTS) $(MACROS) $(INC)

doc : 
	doxygen

clean:
	rm $(OBJS) *~ $(LIB_FILENAME) 

cleandoc:
	rm -rf html; rm -rf latex

cleanobj:
	rm *.obj

cleanall: cleandoc cleanobj clean 
