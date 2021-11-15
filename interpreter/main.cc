#include "Interpreter_Impl.hh"
#include "gen.hh"
#include <iostream>
#include <chrono>

int main(int argc,char *argv[]){
 // • scenarios 1 and 2: size 10000, seed 1, probabilities 0/1/0/0/0 (for opcodes 1/2/3/4/5) and 1/1/1/0/0 
 // • scenarios 3, 4, 5: size 10000, seed 1-3, probabilities 1/9/1/5/5 
 // • scenarios 6, 7, 8: size 50000, seed 1-3, probabilities 1/9/1/5/5 
  if(argc <= 1){
    std::cout<< "usage: ./main.o <scenario no>" << std::endl;
  }
  bool selected[10] = {false,false,false,false,false,false,false,false,false,false};
  for(int i=0;i<argc;i++){
    int index = argv[i][0] - '0';
    selected[index] = true;
  }
  // Start of Scenario 1
  int size=0;
  int seed=0;
  int prob[5];
  int A = 0;
  int L= 0;
  int *rA = &A;
  int *rL = &L;
  if(selected[1]){
    size = 10000;
    seed = 1;
    prob[0] = 0;
    prob[1] = 1;
    prob[2] = 0;
    prob[3] = 0;
    prob[4] = 0;
    A = 0;
    L = 0;
  }
  if (selected[2]){
    size = 10000;
    seed = 1;
    prob[0] = 1;
    prob[1] = 1;
    prob[2] = 1;
    prob[3] = 0;
    prob[4] = 0;
    A = 0;
    L = 0;
  }

  if (selected[3]){
    size = 10000;
    seed = 1;
    prob[0] = 1;
    prob[1] = 9;
    prob[2] = 1;
    prob[3] = 5;
    prob[4] = 5;
    A = 0;
    L = 0;
  }

  if (selected[4]){
    size = 10000;
    seed = 2;
    prob[0] = 1;
    prob[1] = 9;
    prob[2] = 1;
    prob[3] = 5;
    prob[4] = 5;
    A = 0;
    L = 0;
  }

  if (selected[5]){
    size = 10000;
    seed = 3;
    prob[0] = 1;
    prob[1] = 9;
    prob[2] = 1;
    prob[3] = 5;
    prob[4] = 5;
    A = 0;
    L = 0;
  }

  if (selected[6]){
    size = 50000;
    seed = 1;
    prob[0] = 1;
    prob[1] = 9;
    prob[2] = 1;
    prob[3] = 5;
    prob[4] = 5;
    A = 0;
    L = 0;
  }
  if (selected[7]){
    size = 50000;
    seed = 2;
    prob[0] = 1;
    prob[1] = 9;
    prob[2] = 1;
    prob[3] = 5;
    prob[4] = 5;
    A = 0;
    L = 0;
  }
  if (selected[8]){
    size = 50000;
    seed = 3;
    prob[0] = 1;
    prob[1] = 9;
    prob[2] = 1;
    prob[3] = 5;
    prob[4] = 5;
    A = 0;
    L = 0;
  }
  if (selected[9]){
    size = 10000;
    seed = 3;
    prob[0] = 0;
    prob[1] = 1;
    prob[2] = 0;
    prob[3] = 0;
    prob[4] = 0;
    A = 0;
    L = 0;
    char *buf = new char[size];
    init(buf,size,prob,seed,rA,rL);
    Interpreter_Impl cpu(0,0);
    cpu.load(buf,size);
    for(int i=0;i<100;i++){
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      while(!cpu.halted()){
        cpu.startCycle();
      }
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "Iteration: " << i << ": " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
      cpu.reset();
    }
    return 0;
  }
  char *buf = new char[size];
  init(buf,size,prob,seed,rA,rL);
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  Interpreter_Impl cpu(0,0);
  cpu.load(buf,size);
  while(!cpu.halted()){
    cpu.startCycle();
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "It took: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
  return 0;
}
