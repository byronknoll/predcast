OBJS = build/brain.o build/memory.o
CC = g++
CFLAGS = -Wall -c -O3
LFLAGS = -Wall -O3
#CFLAGS = -Wall -c -ggdb
#LFLAGS = -Wall -ggdb

all : simple-predictor complex-predictor rmse

rmse : src/rmse.cpp
	$(CC) $(LFLAGS) src/rmse.cpp -o rmse

simple-predictor : $(OBJS) src/simple-predictor.cpp
	$(CC) $(LFLAGS) $(OBJS) src/simple-predictor.cpp -o simple-predictor

complex-predictor : $(OBJS) src/complex-predictor.cpp
	$(CC) $(LFLAGS) $(OBJS) src/complex-predictor.cpp -o complex-predictor

build/brain.o : src/brain.cpp src/brain.h src/memory.h
	$(CC) $(CFLAGS) src/brain.cpp -o build/brain.o

build/memory.o : src/memory.h src/memory.cpp
	$(CC) $(CFLAGS) src/memory.cpp -o build/memory.o

clean:
	rm -f -r build/* simple-predictor complex-predictor rmse
