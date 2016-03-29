//
//  main.c
//  Euler
//
//  Created by Michael Nolan on 1/10/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "functions.h"
#define COUNT 10
void quicksort(int* array, int left, int right){
	
	int pivot = array[(left+right)/2];
	int i=left;
	int j=right;
	while (i <=j) {
		while (array[i] < pivot)
			i++;
		while (array[j] > pivot)
			j--;
		if (i <= j) {
			int tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++;
			j--;
		}
	}
	if(left<j){
		quicksort(array, left, j);
	}
	if (i < right){
		quicksort(array, i, right);
	}
}

int main(int argc, const char * argv[]) {
	int array[COUNT];
	for(int i=0;i<COUNT;i++){
		array[i] = rand() & 31;
	}
	quicksort(array, 0, COUNT-1);
	for(int i=0;i<COUNT;i++){
		printf("i:%d val:%d\n",i,array[i]);
	}
}
