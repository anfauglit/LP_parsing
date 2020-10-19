#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

struct node{
	char data;
	Node* l_child;
	Node* r_child;
};

static Node* NewNode(char d)
{
	Node* node = malloc(sizeof(Node));
	node->data = d;
	node->l_child = NULL;
	node->r_child = NULL;

	return node;
}

void print_tree(Node* root, int h)
{
	if (root != NULL) {
		for (int i = 0; i < h; ++i) printf("\u2013");
	
		printf("%c\n", root->data);
		print_tree(root->l_child, h + 1);
		print_tree(root->r_child, h + 1);
	}
}

Node* parse (const char* expr, int f, int l) 
// function arguments: expression, index of the first element, index of the last
// element
{
	char temp;

	Node* node;

	int i = 0;

	for (int j = f; j <= l; ++j)
	{
		temp = expr[j];
		if (temp == '(')
			--i;	
		else if (temp == ')')
			++i;
		else if (i == -1)
		{
			if (temp == '&' || temp == 'v' || temp == '>' || temp == '=')
			{
				node = NewNode(temp);
				if ((node->l_child = parse (expr, f + 1, j - 1)) == NULL)
					return NULL;
				if ((node->r_child = parse (expr, j + 1, l - 1)) == NULL)
					return NULL;
				j = l - 1;
			}
			else if (temp == '-')
			{
				node = NewNode(temp);
				if ((node->l_child = parse (expr, j + 1, l - 1)) == NULL)
					return NULL;
				j = l - 1;
			}
		}
	}
	if (i == 0)
		if (f == l)
			return NewNode(expr[f]);
		else if (f < l)
			return node;

	return NULL;
	
}
