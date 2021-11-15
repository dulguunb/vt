CC=g++
unit_test: Interpreter_Impl.hh Interpreter_Impl.cc Interpreter_Impl_Test.cc interpreter_impl.o gen.hh
	$(CC) -Wall -pthread -g Interpreter_Impl_Test.cc interpreter_impl.o -lgtest_main -lgtest -o unit_test
interpreter_impl.o: Interpreter_Impl.hh  Interpreter_Impl.cc
	$(CC) -g -c Interpreter_Impl.cc -o interpreter_impl.o
all: main.o interpreter_impl.o
	$(CC) -g main.cc interpreter_impl.o -o main.o
clean:
	rm -rf interpreter_impl.o main.o unit_test
