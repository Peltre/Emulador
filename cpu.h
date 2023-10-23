#ifndef CPU_H
#define CPU_H
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>

using namespace std;
enum Addressing { Inm, Abs, Ind };

enum operation_codes {
  cla = 01,
  lda = 10,
  sta = 11,
  sub = 21,
  add = 20,
  jmp = 30,
  jmz = 31,
  jmn = 32,
  hlt = 99,
};

struct Instruction {
  operation_codes opcode;
  Addressing address_type;
  int source;

  void instructionPrint();
};

struct Memory {
  // in this emulator we will only have 100 memory addresses
  static const unsigned short MAX_MEMORY = 100;
  int Data[MAX_MEMORY];
  std::vector<Instruction> Program;

  void Load();

  void print();
};

class CPU {
private:
  unsigned short PC; // program counter
  Instruction IR;    // instruction register

  unsigned short A; // accumulator

  unsigned short N; // negative flag
  unsigned short Z; // zero flag
  //

  // initialize cpu with default values
  // our program will start at memory address 0
  Memory mem;
  int find_data(Addressing, int src);

public:
  // Operations
  void CLA(Addressing, int src);
  void LDA(Addressing, int src);
  void STA(Addressing, int src);
  void SUB(Addressing, int src);
  void ADD(Addressing, int src);
  void JMP(Addressing, int src);
  void JMZ(Addressing, int src);
  void JMN(Addressing, int src);
  void HLT(Addressing, int src);

  void Initialize();

  void run();
  void execute(Instruction);

  void cpuPrint();
  void updateFlags();

  Memory getMemory() { return mem; }
  void setMemory(Memory newMem) { mem = newMem; }

  // NOTE: THIS JUST FOR DEBUGGIN DELETE
  int show_address(int pos) { return mem.Data[pos]; }
  void show_accumulator() { std::cout << A << std::endl; }
  void load_memory(int pos, int src) { mem.Data[pos] = src; }
  void load_program(vector<Instruction> program) { mem.Program = program; }
};

// memory
void Memory::print() {
  printf("    |  +0  +1  +2  +3  +4  +5  +6  +7  +8  +9\n");
  int row = 0;
  int column = 0;
  for (int i = 0; i < 10; i++) {
    printf("%d  |", row);
    for (int j = 0; j < 10; j++) {
      if (Data[column + j] < 10) {
        // if number below 0 then print a zero before it
        printf("  0%d", Data[column + j]);
        continue;
      }
      printf("  %d", Data[column + j]);
    }
    printf("\n");
    row += 10;
    column += 10;
  }
}

void Memory::Load() {
  for (int i = 0; i < MAX_MEMORY; i++) {
    Data[i] = 0;
  }
}

// cpu
void CPU::cpuPrint() {
  mem.print();
  printf("Accumulator: %d\n", A);
  printf("Program Counter: %d\n", PC - 1);
  printf("Instruction Registry: ");
  IR.instructionPrint();
}

void CPU::updateFlags() {
  if (A < 0) {
    N = 1;
    return;
  }
  if (A == 0) {
    Z = 1;
    return;
  }
  N = 0;
  Z = 0;
}

// aux for operations
int CPU::find_data(Addressing type_address, int src) {
  int address;
  switch (type_address) {
  case Inm:
    return src;
  case Abs:
    return mem.Data[src];
  case Ind:
    int pointer = mem.Data[src];
    return mem.Data[pointer];
  }
  return address;
};

void CPU::run() {
  // while it doesnt encounter HLT keep running
  while (true) {
    if (mem.Program[PC].opcode != hlt) {
      updateFlags();
      execute(mem.Program[PC]);
      cpuPrint();
      sleep(3);
      continue;
    }
    execute(mem.Program[PC]);
    cpuPrint();
    return;
  }
  // do {
  //   updateFlags();
  //   execute(mem.Program[PC]);
  //   cpuPrint();
  //   sleep(3);
  // } while (mem.Program[PC].opcode != hlt);
  // cpuPrint();
}

void CPU::execute(Instruction instruction) {
  switch (instruction.opcode) {
  case cla:
    CLA(instruction.address_type, instruction.source);
    IR = instruction;
    break;
  case lda:
    LDA(instruction.address_type, instruction.source);
    IR = instruction;
    break;
  case sta:
    STA(instruction.address_type, instruction.source);
    IR = instruction;
    break;
  case sub:
    SUB(instruction.address_type, instruction.source);
    IR = instruction;
    break;
  case add:
    ADD(instruction.address_type, instruction.source);
    IR = instruction;
    break;
    // TODO: IMPLEMENT JMP AND CLA
  case jmp:
    JMP(instruction.address_type, instruction.source);
    IR = instruction;
    break;
  case jmz:
    JMZ(instruction.address_type, instruction.source);
    IR = instruction;
    break;
    // LDA(instruction.address_type, instruction.source);
  case jmn:
    JMN(instruction.address_type, instruction.source);
    IR = instruction;
    break;
  case hlt:
    HLT(instruction.address_type, instruction.source);
    IR = instruction;
    break;
  default:
    break;
  }
}

// clear accumulator
void CPU::CLA(Addressing type_address, int src) {
  A = 0;
  PC += 1;
  return;
}

// load accumulator
void CPU::LDA(Addressing type_address, int src) {
  int data = find_data(type_address, src);
  A = data;
  PC += 1;
  return;
}

// store accumulator
void CPU::STA(Addressing type_address, int src) {
  if (type_address == Abs) {
    mem.Data[src] = A;
  } else {
    // indirect storage
    mem.Data[mem.Data[src]] = A;
  }
  PC += 1;
  return;
}

// substract
void CPU::SUB(Addressing type_address, int src) {
  int data = find_data(type_address, src);
  A -= data;
  PC += 1;
  return;
}

// add
void CPU::ADD(Addressing type_address, int src) {
  int data = find_data(type_address, src);
  A += data;
  PC += 1;
  return;
}

// jump
void CPU::JMP(Addressing type_address, int src) {
  PC = src;
  return;
}

// jump on zero
void CPU::JMZ(Addressing type_address, int src) {
  // if zero flag active
  if (Z == 1) {
    PC = src;
    return;
  }
  PC += 1;
  return;
}

// jump on negative
void CPU::JMN(Addressing type_address, int src) {
  // if negative flag active
  if (N == 1) {
    PC = src;
    return;
  }
  PC += 1;
  return;
}

// halt
void CPU::HLT(Addressing type_address, int src) {
  PC += 1;
  return;
}

void CPU::Initialize() {
  mem.Load();
  PC = 0;
  A = 0;
  Z = N = 0;
}
#endif
