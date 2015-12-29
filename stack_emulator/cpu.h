#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void push(uint16_t);
void rpush(uint16_t);
uint16_t rpop();
void add();
void sub();
void dup_s(void);
void out();
void swap();
void rot();
void lt();
void eq();
void gt();
void neg();
uint16_t peek();
uint16_t pop();
uint16_t rpeek();
#define NOP 0
#define ADD 1
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
#define RPUSH 14
#define RPOP 15
#define RCP 16
#define JUMP 32
#define CALL 64
#define CJUMP 96
#define PUSH 128

