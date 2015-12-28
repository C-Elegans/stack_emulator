#include "cpu.h"
uint16_t stack[4096];
int sp = 0;
void push(uint16_t val){
	if(sp < 4096-1){
		stack[++sp] = val;
		val++;
	}
}
uint16_t pop(){
	if(sp>=0){
		return stack[sp--];
	}
	printf("Error: Stack underflow! sp= %d",sp);
	exit(-1);
	return -1;
}
void add(){
	uint16_t val1,val2;
	val1=pop();
	val2=pop();
	push(val1+val2);
}
void sub(){
	uint16_t val1,val2;
	val1=pop();
	val2=pop();
	push(val2-val1);
}
uint16_t peek(){
	if(sp>=0 && sp < 4096){
		return stack[sp];
	}
	return 0;
}
void out(){
	uint16_t val = pop();
	printf("Out: %d\n",val);
}
void dup_s(void){
	push(peek());
}
