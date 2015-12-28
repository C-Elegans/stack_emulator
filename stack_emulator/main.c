#include <stdio.h>
#include "cpu.h"
FILE *fileptr;
char *buffer;
char *buf_end;
long filelen;
char* ip;
extern int sp;
void ret(){
	ip = rpop();
}
int decodeInstruction(){
	char op = *ip++;
	if(op&PUSH){
		uint16_t val= ((op&127)<<8) + *ip++;
		push(val);
		return 2;
	}
	else if (op&CALL && !(op&JUMP)){
		
		rpush(ip);
		int16_t val=(op&31);
		val = val << 8;
		val += (*ip++) & 255;
		if(val&(1<<12)){
			val = val | (15<<12);
		}
		ip += val;
	}
	else if(op&JUMP){
		if(op&64){
			if(!pop()){
				ip++;
				return 2;
			}
		}
		int16_t val=(op&31);
		val = val << 8;
		val += (*ip++) & 255;
		if(val&(1<<12)){
			val = val | (15<<12);
		}
		ip += val;
		return 0;
	
	}
	
	
	switch(op){
		case NOP: break;
		case ADD:add(); break;
		case SUB:sub(); break;
		case OUT:out(); break;
		case DUP:dup_s(); break;
		case SWAP:swap(); break;
		case ROT:rot(); break;
		case RET:ret(); break;
		case LT:lt();break;
		case EQ:eq();break;
		case GT:gt();break;
		default:{
			printf("Invalid Opcode %d\n",op);
			exit(-1);
		}
	}
	return 1;

}
int main(int argc, char** argv){
	if(argc != 2){
		puts("Usage ./sim [program]");
		return -1;
	}
		
	

	fileptr = fopen(argv[1], "rb");  // Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file

	buffer = (char *)malloc((filelen+1)*sizeof(char)); // Enough memory for file + \0
	buf_end = buffer + filelen;
	fread(buffer, filelen, 1, fileptr); // Read in the entire file
	fclose(fileptr); // Close the file
	
	
	ip = buffer;
	while(ip<buf_end){
		decodeInstruction();
		//printf("TOS: %d\n",peek());
	
	}
	
	
	
	return 0;
}
