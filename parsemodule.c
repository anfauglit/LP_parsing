#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "parse.h"
#include <math.h>

#define MASK 1

#ifndef SIG_SIZE
#define SIG_SIZE 26
#endif

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

void get_sig (Node* root, Signature* sig)
{
	if (root->l_child == NULL)
	{
		if (sig->atomic[root->data - 'a'] == 0) {
			sig->size++;
			sig->atomic[root->data - 'a']	= sig->size;
		}
	}
	else
		get_sig (root->l_child, sig);

	if (root->r_child != NULL)
		get_sig (root->r_child, sig);
}

int getTValue (Node* node, Signature* sig, int sigma)
{
	if (node->l_child == NULL) {
		printf("%i ",(sigma >> (sig->atomic[node->data - 'a'] - 1)) & MASK);
		return sigma >> (sig->atomic[node->data - 'a'] - 1) & MASK;
	}
	else if (node->data == '-')
		return ~getTValue(node->l_child, sig, sigma) & MASK;
	else {
		int p = getTValue(node->l_child, sig, sigma);
		int q = getTValue(node->r_child, sig, sigma);
		if (node->data == '&')
			return p & q;
		else if (node->data == 'v')
			return p | q; 
		else if (node->data == '>')
			return (~p & MASK) | q; 
		else if (node->data == '=')
			return ((~p & MASK) | q) & ((~q & MASK) | p);
	}
}

void printTTable (Node* node, Signature* sig)
{
	for (int i = 0; i < sig->size; ++i)
		for (int j = 0; j < SIG_SIZE; ++j) 
			if (sig->atomic[j] == i + 1) {
				printf("%c ", (char) (j + 'a'));
				break;
			}
	printf("TVal\n");

	for (int i = 0; i < pow(2, sig->size); ++i)
		printf("%i\n", getTValue(node, sig, i));
}
