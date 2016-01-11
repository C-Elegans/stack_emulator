//
//  main.c
//  Euler
//
//  Created by Michael Nolan on 1/10/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include "functions.h"
#define COUNT 60
long S(long val){
	long sum = 0;
	for(long i=2;i<val;i++){
		if(((i*i*i)%val) == 1)sum += val;
		
	}
	return sum;
	
}

int main(int argc, const char * argv[]) {
	
	printf("S(%ld)=%ld\n",13082761331670030,S(13082761331670030));
}
