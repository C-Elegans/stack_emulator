#include "cpu.h"
#define TOS stack[sp]
#define NOS stack[sp-1]
#define ROS stack[sp-2]
uint16_t stack[4096];
char* rstack[128];
int sp = 0;
int rsp = 0;
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
char* rpop(){
	if(rsp>=0){
		return rstack[rsp--];
	}
	printf("Error: Return Stack underflow! rsp= %d",rsp);
	exit(-1);
	return NULL;
}
void rpush(char* val){
	if(rsp < 128-1){
		rstack[++rsp] = val;
	}
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
void swap(){
	if(sp>0 && sp < 4096){
		uint16_t temp = NOS;
		NOS = TOS;
		TOS = temp;
	}
}
void rot(){
	if(sp >1 && sp < 4096){
		uint16_t temp1 = TOS; //tos = nos nos=ros ros=tos
		uint16_t temp2 = NOS;
		TOS = temp2;
		NOS = ROS;
		ROS = temp1;
	}
}
