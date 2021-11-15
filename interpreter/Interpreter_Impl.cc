#include "Interpreter_Impl.hh"

Interpreter_Impl::Interpreter_Impl(int bootA,int bootL){
  A = bootA;
  L = bootL;
  IP = 0;
  pc = 0;
  sp = 0;
  isHalted = false;
  opcode = 0;
  rom.reserve(100000);
  stack.reserve(100000);
}

void Interpreter_Impl::load(char *buffer,int size){
  for(int i=0;i<size;i++){
    rom[i] = buffer[i];
  }
}
void Interpreter_Impl::dump(){

}
bool Interpreter_Impl::halted(){
  return isHalted;
}
const std::pair<int,int> Interpreter_Impl::getRegisters(){
  return std::make_pair(A,L);
}
const unsigned int Interpreter_Impl::getIP(){
  return IP;
}
void Interpreter_Impl::reset(){
  IP = 0;
}
void Interpreter_Impl::startCycle(){
  opcode = rom[IP]; //& 1111;
  switch (opcode){
    case 0x0:{
      isHalted = true;
      break;
    }
    break;
    case 0x1:{
      A = 0;
      IP++;
    }
    break;
    case 0x2:{
      A+=3;
      IP++;
    }
    break;
    case 0x3:{
      A--;
      IP++;
    }
    break;
    case 0x4:{
      L = A;
      IP++;
    }
    break;
    case 0x5:{
      L--;
      if (L >= 0){
       if(IP >= 6){
          IP-=6;
        }
        else{
          IP=0;
        }
      }
      else{
        IP++;
      }
    }
    break;
  }
}
