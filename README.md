This is a simple, stack based cpu, designed to be easy to implement on an FPGA.
It is a 16 bit machine, with 8 or 16 bit instructions.
The stack will be 4096 16 bit words, and the return stack will be 128 16 bit words.

8 bit instructions:
nop: 0x00, does nothing

add: 0x01, pops two values off the stack, adds them, and pushes the result onto the stack

sub: 0x02, pops two values off the stack, subtracts the second from the first, and pushes the result

out: 0x03, pops a value off of the stack and outputs it to the console (LEDs on the real thing)

in:  0x04, does nothing right now

dup: 0x05, duplicates the top of the stack

drop: 0x06, pops the top of the stack

swap: 0x07, swaps the top of the stack with the next value on the stack

rot: 0x08, rotates the top 3 values

ret: 0x09, returns from a subroutine

lt: 0x0A, pushes a 1 if the second value on the stack is less than the top of the stack, 0 otherwise

eq: 0x0B, pushes a 1 if the top two values on the stack are equal

gt: 0x0C, pushes a 1 if the second value on the stack is greater than the top of the stack, 0 otherwise

16 bit instructions

jump: 0x2XXX, reads the 13 bit two's complement displacement and adds it to the instruction pointer

cjump: 0x6XXX, pops the top of the stack and adds the 13 bit two's complement displacement to the instruction pointer only if the value popped is not 0

call: 0x4XXXX, pushes the old ip onto the return stack, then reads the 13 bit two's complement displacement and adds it to the instruction pointer

push: 0x8XXXX, reads the 15 bit value in the instruction and pushes it onto the stack
