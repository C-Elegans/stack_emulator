#include <stdio.h>
#include "cpu.h"
#define EXIT(msg) puts(msg); exit(1);
FILE *fileptr;
uint16_t *buffer;
uint16_t *buf_end;
long filelen;
uint16_t* ip;
extern int sp;
extern uint16_t* stack;
void ret(){
	ip = buffer + pop();
}
int decodeInstruction(){
	uint16_t op = *ip++;
	if(op&PUSH){ //push
		
		uint16_t val= op&0x7fff;
		if(val&0x4000)val|=0x8000;
		
		push(val);
		return 2;
	}
	else if (op&CALL && !(op&JUMP)){ //Call
		
		push((ip) - buffer);
		int16_t val = op&0x1fff;
		if(val&0x1000)val|=0xe000;
		
		ip += val-1;
	}
	else if(op&JUMP){ //jump + cjump
		if(op&64){ //cjump
			if(pop()){
				return 2;
			}
		}
		
		int16_t val = op&0x1fff;
		if(val&0x1000)val|=0xe000;
		ip += val-1;
		return 0;
	
	}
	else if (op&LOCAL && op&FRAME){//SLOCAL
		uint16_t val = op&0x03ff;
		slocal(val);
	}
	else if((op&LOCAL)){
		uint16_t val = op&0x03ff;
		local(val);
	}
	else if(op&FRAME){
		uint16_t val = op&0x03ff;
		frame(val);
	}
	
	switch(op){
		case NOP: break;
		case ADD:add(); break;
		case SUB:sub(); break;
		case OUT:out(); break;
		case DUP:dup_s(); break;
		case DROP:drop(); break;
		case SWAP:swap(); break;
		case ROT:rot(); break;
		case RET:ret(); break;
		case LT:lt();break;
		case EQ:eq();break;
		case GT:gt();break;
		case NEG:neg();break;
		case AND:s_and();break;
		case OR:s_or();break;
		case XOR:s_xor();break;
		case LSHIFT:lshift();break;
		case RSHIFT:rshift();break;
		case MUL:mul();break;
		case FETCH:fetch();break;
		case STORE:store();break;
		case LEAVE:leave();break;
	}
	return 1;

}
int main(int argc, char** argv){
	if(argc != 2){
		puts("Usage ./sim [program]");
		return -1;
	}
		
	

	fileptr = fopen(argv[1], "rb");  // Open the file in binary mode
	if(fileptr == NULL) {EXIT("Could not open file")}
	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(fileptr);             // Get the current byte offset in the file
	if(filelen > 8192) {EXIT("File too large")}
	rewind(fileptr);                      // Jump back to the beginning of the file

	buffer = (uint16_t *)malloc((8192)*sizeof(uint16_t)); // Enough memory for file + \0
	buf_end = buffer + filelen/2;
	fread(buffer, filelen, 1, fileptr); // Read in the entire file
	fclose(fileptr); // Close the file
	
	
	ip = buffer;
	while(ip<buf_end){
		printf("%x\n",*ip);
		decodeInstruction();
		
		//printf("TOS: %d\n",peek());
	
	}
	
	
	return 0;
}
