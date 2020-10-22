#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include <math.h>

int main (int argc, char** argv)
{
	Signature* sig;
	
	sig = malloc(sizeof(Signature));

	sig->size = 0;
	memset(sig->atomic, 0, SIG_SIZE);

	Node* n;
	// char my_sent[] = "((f&f)&f)";
	
	if (argc != 2)
	{
		perror("WRONG NUMBER OF ARGUMENTS");
		return 1;
	}

	char* my_sent = argv[1];

	if ((n = parse(my_sent, 0, strlen(my_sent) - 1)) == NULL)
	{
		printf("\"%s\" is not a formula of LP\n", my_sent);
		return 0;
	}

	get_sig (n, sig);

	print_tree(n, 0);

	printTTable(n, sig);

	return 0;
}
