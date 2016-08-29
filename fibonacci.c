/* 
 * Codigo de Fibonacci recursivo
 * Author: Oscar Azofeifa
*/

#include <stdio.h>
#include <string.h>

unsigned int fibonacci(unsigned int n){ //Tiene como entrada numero entero mayor que cero
	if (n == 0 || n == 1){
			return 1;
	}
	else {
			return fibonacci(n - 1) + fibonacci(n - 2);
	}
}

int main(){
	unsigned int n;
	printf("Ingrese un numero:\n");
	scanf("%u", &n);
	printf("El fibonacci de %u es %u \n", n, fibonacci(n) );
}
