#include <string.h>

#define SIG_SIZE 26

typedef struct node Node;

typedef struct sig {
	int atomic[SIG_SIZE];
	int size;
} Signature;

typedef struct {
	Node* root;
	Signature* sig;
} Tree;

void get_sig (Node* root, Signature* sig);

void print_tree(Node* root, int h);

Node* parse (const char* expr, int f, int l);

int getTValue (Node* node, Signature* sig, int sigma);

void printTTable (Node* node, Signature* sig);
