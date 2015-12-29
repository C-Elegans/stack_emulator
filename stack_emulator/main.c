#include <stdio.h>
#include "cpu.h"
FILE *fileptr;
char *buffer;
char *buf_end;
long filelen;
char* ip;
extern int sp;
extern uint16_t* stack;
void ret(){
	ip = buffer + rpop();
}
int decodeInstruction(){
	char op = *ip++;
	if(op&PUSH){ //push
		
		uint16_t val= ((op&63)<<8) + *(uint8_t*)(ip++);
		
		push(val);
		return 2;
	}
	else if (op&CALL && !(op&JUMP)){ //Call
		
		rpush((ip+1) - buffer);
		int16_t val=(op&31);
		val = val << 8;
		val += (*(uint8_t*)(ip++)) & 255;
		if(val&(1<<12)){
			val = val | (15<<12);
		}
		ip += val;
	}
	else if(op&JUMP){ //jump + cjump
		if(op&64){ //cjump
			if(pop()){
				ip++;
				return 2;
			}
		}
		int16_t val=(op&31);
		val = val << 8;
		val += (*(uint8_t*)(ip++)) & 255;
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
		case NEG:neg();break;
		case RPUSH:rpush(pop());break;
		case RPOP:push(rpop());break;
		case RCP:push(rpeek());break;
		case AND:s_and();break;
		case OR:s_or();break;
		case XOR:s_xor();break;
		case LSHIFT:lshift();break;
		case RSHIFT:rshift();break;
		case MUL:mul();break;
		case FETCH:fetch();break;
		case STORE:store();break;
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

	buffer = (char *)malloc((8192)*sizeof(char)); // Enough memory for file + \0
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
