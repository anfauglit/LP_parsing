#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

int main (int argc, char** argv)
{
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

	print_tree(n, 0);

	return 0;
}
