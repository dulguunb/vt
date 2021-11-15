#ifndef INTERPRETER_IMPL
#define INTERPRETER_IMPL
  // HALT (opcode 0): stop execution 
  // CLRA (opcode 1): set content of register A to 0 
  // INC3A (opcode 2): increment register A by 3 
  // DECA (opcode 3): decrement register A by 1 
  // SETL (opcode 4): copy value of register A to L 
  // BACK7 (opcode 5): decrement L; if value of L is positive, jump back by 7 instructions (i.e. loop 
  // body is 6 one-byte instructions and the BACK7 itself). Otherwise fall through to next instruction
#include <vector>
#include <utility>
#include <cstdio>
#include <iostream>
class Interpreter_Impl{
  private:
    unsigned int IP; // instruction pointer
    int A; // accumulator register
    int L; // loop counter register
    std::vector<char> rom; // ROM
    std::vector<unsigned char> stack; //stack
    unsigned short  pc; // program counter
    unsigned short  sp; // stack pointer
    unsigned char  opcode; // opcode
    bool isHalted; // notifies when machine is halted
  public:
    Interpreter_Impl(int bootA,int bootL);
    Interpreter_Impl() = delete;
    void startCycle();
    void load(char *buffer,int size);
    void dump();
    bool halted();
    const std::pair<int,int> getRegisters();
    const unsigned int getIP();
    void reset();
};


#endif
