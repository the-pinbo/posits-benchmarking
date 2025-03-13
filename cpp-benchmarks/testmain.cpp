#include "include/softposit_cpp.h"

int main(int argc, char *argv[]){
	posit16 x = 1;
	posit16 y = 1.5;
	posit8 x8 = 1;
	quire16 q;
	quire8 q8;

	x += p16(1.5)*5.1;

	printf("%.13f  sizeof: %d\n", x.toDouble(), sizeof(posit16));

	x = q.qma(4, 1.2).toPosit();
	printf("%.13f  sizeof: %d\n", x.toDouble(), sizeof(quire16));

	x8 = q8.qma(4, 1.2).toPosit();
	printf("%.13f  sizeof: %d\n", x8.toDouble(), sizeof(quire8));
	
	std::cout << x;

	return 0;
}


