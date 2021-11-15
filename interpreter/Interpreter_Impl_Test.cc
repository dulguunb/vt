
#include "gen.hh"
#include "Interpreter_Impl.hh"

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
namespace{
  TEST(opcode,opcode){
    int size = 10;
    char *buf = new char[size]{1,2,3,4,5,5,5,0};
    Interpreter_Impl cpu(0,0);
    cpu.load(buf,size);
    cpu.startCycle();
    auto registers = cpu.getRegisters();
    auto IP = cpu.getIP();
    EXPECT_TRUE(registers.first == 0);
    EXPECT_TRUE(registers.second == 0);
    EXPECT_TRUE(IP == 1);
    cpu.startCycle();
    registers = cpu.getRegisters();
    IP = cpu.getIP();
    EXPECT_TRUE(registers.first == 3);
    EXPECT_TRUE(registers.second == 0);
    EXPECT_TRUE(IP == 2);
    cpu.startCycle();
    registers = cpu.getRegisters();
    EXPECT_TRUE(registers.first == 2);
    EXPECT_TRUE(registers.second == 0);
    IP = cpu.getIP();
    EXPECT_TRUE(IP == 3);
    cpu.startCycle();
    IP = cpu.getIP();
    registers = cpu.getRegisters();
    EXPECT_TRUE(registers.first == 2);
    EXPECT_TRUE(registers.second == 2);
    EXPECT_TRUE(IP == 4);
    cpu.startCycle();
    registers = cpu.getRegisters();
    IP = cpu.getIP();
    EXPECT_TRUE(registers.first == 2);
    EXPECT_TRUE(registers.second == 1);
    EXPECT_TRUE(IP == 0);
  }
  TEST(opcode,genhh){
    int size=10;
    char *buf = new char[size];
    int prob[5] = {1,1,1,1,1};
    int seed = 1000;
    int A = 0;
    int L = 0;
    int *rA = &A;
    int *rL = &L;
    init(buf,size,prob,seed,rA,rL);
    for (int i=0;i<size;i++){
      printf("0x%.1X\n",buf[i]);
    }
    Interpreter_Impl cpu(0,0);
    cpu.load(buf,size);
 //   while(!cpu.halted()){
 //     cpu.startCycle();
 //   }
  }
}
