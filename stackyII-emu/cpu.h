#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void push(uint16_t);
void add();
void sub();
void dup_s(void);
void out();
void drop();
void swap();
void rot();
void lt();
void eq();
void gt();
void neg();
void s_and();
void s_or();
void s_xor();
uint16_t peek();
uint16_t pop();
uint16_t rpeek();
void lshift();
void rshift();
void mul();
void fetch();
void store();
void local(uint16_t val);
void frame(uint16_t val);
void slocal(uint16_t val);
void leave();
#define NOP 0x0000
#define ADD 0x0001
#define SUB 2
#define OUT 3
#define IN 4
#define DUP 5
#define DROP 6
#define SWAP 7
#define ROT 8
#define RET 9
#define LT 10
#define EQ 11
#define GT 12
#define NEG 13
#define LEAVE 14
#define AND 17
#define OR 18
#define XOR 19
#define LSHIFT 20
#define RSHIFT 21
#define MUL 22
#define FETCH 23
#define STORE 24

#define FRAME 0x0400
#define SLOCAL 0x0c00
#define LOCAL 0x0800
#define JUMP 0x2000
#define CALL 0x4000
#define CJUMP 0x6000
#define PUSH 0x8000
