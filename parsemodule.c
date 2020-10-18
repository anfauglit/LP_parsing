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
	if (f == l)
		return NewNode(expr[f]);

	char temp;

	int i = 0;

	for (int j = f; j < l; ++j)
	{
		temp = expr[j];
		if (temp == '(')
			--i;	
		if (temp == ')')
			++i;
		if (i == -1)
		{
			if (temp == '&' || temp == 'v' || temp == '>' || temp == '=')
			{
				Node* node = NewNode(temp);
				node->l_child = parse (expr, f + 1, j - 1);
				node->r_child = parse (expr, j + 1, l - 1);
				return node;
			}
			if (temp == '-')
			{
				Node* node = NewNode(temp);
				node->l_child = parse (expr, j + 1, l - 1);
				return node;	
			}
		}
	}

	return NULL;
	
}
