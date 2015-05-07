CC:= g++
OPTS:= -fpic -g -Wall -std=c++11
INC:= -Iinclude
OBJDIR:= build
OUTFILESDIR:= files
OBJS:= \
	DataGenerator.o	\
	Family.o \
	Evaluator.o	\
	Chromosome.o \
	Population.o \
	PMXOp.o \
	OXOp.o \
	CXOp.o \
	Globals.o \
	Logger.o \
	main.o
TARGET:= main

vpath %.cpp src
vpath %.hpp include

.PHONY: all clean 

all: ${OBJDIR}/${TARGET}

${OBJDIR}/${TARGET}: ${OBJS}
	@echo --building executable--
	@echo $^
	cd ${OBJDIR} && ${CC} ${INC} -o ${TARGET} $^

%.o: %.cpp | ${OBJDIR}
	${CC} ${INC} ${OPTS} -o ${OBJDIR}/$@ -c $<

${OBJDIR}:
	@echo --making objdir-- 
	mkdir -p ${OBJDIR}
	mkdir -p ${OUTFILESDIR}

clean:
	-cd ${OBJDIR} && rm -rf ${OBJS}
	-cd ${OBJDIR} && rm -rf ${TARGET}
	-rm -rf ${OBJDIR}
	-rm -rf ${OUTFILESDIR}
