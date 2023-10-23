#include "cpu.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void Instruction::instructionPrint() {
  printf(" %d %d %d\n", opcode, address_type, source);
}

vector<Instruction> programAsk() {
  vector<Instruction> program;
  Instruction instruction;

  string word;
  int addressing_type;
  int source;

  // incluir todas las instrucciones
  while (true) {
    printf("\nIntroduce  el codigo de la instruccion que quieras ejecutar\n");
    printf(" (presiona la letra q para salir)                           \n");
    printf("===========================================================\n");
    printf("                Instrucciones disponibles                  \n");
    printf("CLA - 01                                                   \n");
    printf("LDA - 10                                                   \n");
    printf("STA - 11                                                   \n");
    printf("SUB - 21                                                   \n");
    printf("ADD - 20                                                   \n");
    printf("JMP - 30                                                   \n");
    printf("JMZ - 31                                                   \n");
    printf("JMN - 32                                                   \n");
    printf("HLT - 99                                                   \n");
    printf("Codigo: ");
    cin >> word;

    if (word == "q") {
      break;
    }

    printf("Que tipo de direccionamiento quieres utilizar\n");
    printf("=============================================\n");
    printf("Inmediato - 0                                \n");
    printf("Absoluto - 1                                 \n");
    printf("Indirecto - 2                                \n");
    printf("Direccionamiento: ");

    cin >> addressing_type;

    printf("Finalmente introduce la direccion de memoria, o el numero si es "
           "inmediato\n");
    printf("==============================\n");
    printf("Source: ");
    cin >> source;
    printf("\n");

    Instruction instr;

    if (word == "01") {
      instr.opcode = cla;
    } else if (word == "10") {
      instr.opcode = lda;
    } else if (word == "11") {
      instr.opcode = sta;
    } else if (word == "21") {
      instr.opcode = sub;
    } else if (word == "20") {
      instr.opcode = add;
    } else if (word == "30") {
      instr.opcode = jmp;
    } else if (word == "99") {
      instr.opcode = hlt;
    } else if (word == "31") {
      instr.opcode = jmz;
    } else if (word == "32") {
      instr.opcode = jmn;
    } else {
      cout << "Instruccion no valida, intentalo de nuevo" << endl;
      continue;
    }

    if (addressing_type < 0 || addressing_type > 2) {
      cout << "Tipo de direccionamiento no valido, intentalo de nuevo" << endl;
      continue;
    }

    instr.address_type = static_cast<Addressing>(addressing_type);
    instr.source = source;

    program.push_back(instr);
    printf("Tu programa hasta ahora: \n");
    for (int i = 0; i < program.size(); i++) {
      printf("0%d ", i + 1);
      program[i].instructionPrint();
    }
  }
  printf("\n\n");
  return program;
}

void memoryAsk(Memory &memory) {
  while (true) {
    int mem_address;
    int data;

    printf("\nTu memoria\n");
    memory.print();
    printf("En que direccion de memoria quieres guardar tu dato? (Escibre -1 "
           "para salir)\n");
    cin >> mem_address;

    if (mem_address == -1) {
      return;
    }

    printf("Que dato entero quieres guardar?\n");
    cin >> data;

    memory.Data[mem_address] = data;
  }
  printf("\n");
  return;
}
