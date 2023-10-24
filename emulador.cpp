#include "getinput.h"


int main() {
  Memory mem;

  CPU cpu;

  cpu.Initialize();
  cpu.cpuPrint();

  Memory newMem = cpu.getMemory();
  memoryAsk(newMem);
  cpu.setMemory(newMem);

  cpu.cpuPrint();

  vector<Instruction> program_to_load;
  program_to_load = programAsk();
  cpu.load_program(program_to_load);


  cpu.run();
}
