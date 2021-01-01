DIR_BIN := bin
DIR_SRC := src
DIR_LIB := lib
DIR_OBJ := obj

LIB_OBJS := $(patsubst ${DIR_LIB}/%.c,${DIR_OBJ}/%.o,$(wildcard ${DIR_LIB}/*.c))
BINS := $(patsubst ${DIR_SRC}/%.c,${DIR_BIN}/%,$(wildcard ${DIR_SRC}/*))

FLAGS := -g -Wall --pedantic -lpthread -ldl -I${DIR_LIB}

all: ${BINS}

${DIR_BIN}/% : ${DIR_SRC}/%.c ${LIB_OBJS} | ${DIR_BIN}
	gcc $^ -o $@ ${FLAGS}

${DIR_OBJ}/%.o : ${DIR_LIB}/%.c | ${DIR_OBJ}
	gcc -c $^ -o $@

${DIR_BIN} ${DIR_OBJ}:
	mkdir -p $@

.PRECIOUS: ${LIB_OBJS}
