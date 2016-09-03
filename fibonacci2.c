/* 
 * Codigo de Fibonacci recursivo
 * Author: Oscar Azofeifa
*/

#include <stdio.h>
#include <string.h>

unsigned int fibonacci(unsigned int ni){ //Tiene como entrada numero entero mayor que cero
	if (ns == 0 || n == 1){
			return 1;
	}
	else {
			return fibonacci(n - 1) + fibonacci(n - 2);
	}
}

int main(){
	unsigned int abc1;
	printf("Ingrese un numero:\n");
	scanf("%u", abc1);
	printf("El fibonacci de %u es %u \n", abc1, fibonacci(abc1) );
}
