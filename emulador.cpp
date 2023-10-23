#include "getinput.h"

// TODO: LDA 10
// TODO: STA 11
// TODO: SUB 21
// TODO: ADD 20
// TODO: JMP 30
// TODO: HLT 99
// TODO: CLA 01
// TODO: IMPLEMENT PC
// MIGHT NEED TO IMPLEMENT VECTOR WITH ALL INSTRUCTIONS
//
int main() {
  Memory mem;
  // Instruction instr1;
  // Instruction instr2;
  // Instruction instr3;
  // Instruction instr4;
  // Instruction instr5;
  //
  // instr1.opcode = lda;
  // instr1.address_type = Abs;
  // instr1.source = 56;
  //
  // instr2.opcode = add;
  // instr2.address_type = Inm;
  // instr2.source = 10;
  //
  // instr3.opcode = sta;
  // instr3.address_type = Ind;
  // instr3.source = 56;
  //
  // instr4.opcode = jmp;
  // instr4.address_type = Abs;
  // instr4.source = 1;
  //
  // instr5.opcode = hlt;
  // instr5.address_type = Abs;
  // instr5.source = 10;
  //
  CPU cpu;
  // cpu.Initialize();
  // cpu.load_memory(56, 52);
  // cpu.load_memory(9, 30);
  // cpu.LDA(Abs, 56);
  // cpu.cpuPrint();
  // cpu.ADD(Inm, 10);
  // cpu.cpuPrint();
  // cpu.STA(Abs, 56);
  // cpu.cpuPrint();
  // cpu.SUB(Abs, 9);
  // cpu.cpuPrint();
  // printf("\n\n\n Ahora si se viene lo feo perro\n");
  //
  cpu.Initialize();
  cpu.cpuPrint();

  Memory newMem = cpu.getMemory();
  memoryAsk(newMem);
  cpu.setMemory(newMem);

  cpu.cpuPrint();

  vector<Instruction> program_to_load;
  program_to_load = programAsk();
  cpu.load_program(program_to_load);
  // cpu.load_program(instr1);
  // cpu.load_program(instr2);
  // cpu.load_program(instr3);
  // cpu.load_program(instr4);
  // cpu.load_program(instr5);
  // cpu.cpuPrint();

  cpu.run();
}
