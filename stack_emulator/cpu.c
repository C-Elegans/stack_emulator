#include "cpu.h"
#define STACK_SIZE 512
#define RSTACK_SIZE 128
#define TOS stack[sp]
#define NOS stack[sp-1]
#define ROS stack[sp-2]
//#define STACK_DEBUG
uint16_t stack[STACK_SIZE];
uint16_t rstack[RSTACK_SIZE];
int sp = 0;
int rsp = 0;
void push(uint16_t val){
#ifdef STACK_DEBUG
	printf("push %d sp: %d\n",val,sp);
#endif
	if(sp < STACK_SIZE-1){
		stack[++sp] = val;
		val++;
	}
}
uint16_t pop(){
#ifdef STACK_DEBUG
	printf("pop\n");
#endif
	if(sp>=0){
		return stack[sp--];
	}
	printf("Error: Stack underflow! sp= %d",sp);
	exit(-1);
	return -1;
}
uint16_t rpop(){
#ifdef STACK_DEBUG
	printf("rpop\n");
#endif
	if(rsp>=0){
		return rstack[rsp--];
	}
	printf("Error: Return Stack underflow! rsp= %d",rsp);
	exit(-1);
	return 0;
}
uint16_t rpeek(){
	return rstack[rsp];
}
void rpush(uint16_t val){
	#ifdef STACK_DEBUG
	printf("rpush %d sp: %d\n",val,rsp);
#endif
	if(rsp < RSTACK_SIZE-1){
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
	if(sp>=0 && sp < STACK_SIZE){
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
	if(sp>0 && sp < STACK_SIZE){
		uint16_t temp = NOS;
		NOS = TOS;
		TOS = temp;
	}
}
void rot(){
	if(sp >1 && sp < STACK_SIZE){
		uint16_t tos = TOS; //tos = nos nos=ros ros=tos
		uint16_t nos = NOS;
		uint16_t ros = ROS;
		TOS = ros;
		NOS = tos;
		ROS = nos;
	}
}
void lt(){
	uint16_t val1,val2;
	val1 = pop();
	val2 = pop();
	push(val2<val1? 0xffff: 0x0000);
}
void eq(){
	uint16_t val1,val2;
	val1 = pop();
	val2 = pop();
	push((val2==val1)? 0xffff: 0x0000);
}
void gt(){
	uint16_t val1,val2;
	val1 = pop();
	val2 = pop();
	push(val2>val1? 0xffff: 0x0000);
}
void neg(){
	uint16_t tmp = pop();
	tmp = ~tmp;
	push(tmp);
}
