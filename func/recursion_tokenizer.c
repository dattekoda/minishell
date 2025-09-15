#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

typedef enum {
	ND_ADD,
	ND_SUB,
	ND_MUL,
	ND_DIV,
	ND_NUM,
}	NodeKind;

typedef enum {
	TK_RESERVED,
	TK_NUM,
	TK_EOF,
}	TokenKind;

typedef struct Token Token;

struct Token {
	TokenKind	kind;
	Token		*next;
	int			val;
	char		*str;
};

typedef struct Node Node;

struct Node {
	NodeKind	kind;
	Node		*lhs;
	Node		*rhs;
	int			val;
};

Token	*token;

void	error(char *fmt, ...) {
	va_list	ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
	exit(1);
}

bool	consume(char op) {
	if (token->kind != TK_RESERVED || token->str[0] != op)
		return false;
	token = token->next;
	return true;
}

void	expect(char op) {
	if (token->kind != TK_RESERVED || token->str[0] != op)
		error("'%c'ではありません。", op);
	token = token->next;
}

int	expect_number() {
	if (token->kind != TK_NUM)
		error("数ではありません。");
	int	val = token->val;
	token = token->next;
	return (val);
}

bool	at_eof() {
	return (token->kind == TK_EOF);
}

Token	*new_token(TokenKind kind, Token *cur, char *str) {
	Token	*tok = calloc(1, sizeof(Token));

	tok->kind = kind;
	tok->str = str;
	cur->next = tok;
	return (tok);
}

Token	*tokenize(char *p) {
	Token	head;
	head.next = NULL;
	Token	*cur = &head;

	while (*p) {
		if (isspace(*p)) {
			p++;
			continue;
		}
		if (*p == '+' || *p == '-' \
		|| *p == '*' || *p == '/' \
		|| *p == '(' || *p == ')') {
			cur = new_token(TK_RESERVED, cur, p++);
			continue;
		}
		if (isdigit(*p)) {
			cur = new_token(TK_NUM, cur, p);
			cur->val = strtol(p, &p, 10);
			continue;
		}
		error("トークナイズできない。");
	}
	new_token(TK_EOF, cur, p);
	return (head.next);
}

Node	*new_node(NodeKind kind, Node *lhs, Node *rhs) {
	Node	*node = calloc(1, sizeof(Node));
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;
	return node;
}

Node	*new_node_num(int val) {
	Node	*node = calloc(1, sizeof(Node));
	node->kind = ND_NUM;
	node->val = val;
	return (node);
}

Node	*expr();

Node	*primary() {
	if (consume('(')) {
		Node	*node = expr();
		expect(')');
		return (node);
	}
	return (new_node_num(expect_number()));
}

Node	*mul() {
	Node	*node = primary();

	for (;;) {
		if (consume('*'))
			node = new_node(ND_MUL, node, primary());
		else if (consume('/'))
			node = new_node(ND_DIV, node, primary());
		else
			return node;
	}
}

Node	*expr() {
	Node	*node = mul();

	for (;;) {
		if (consume('+'))
			node = new_node(ND_ADD, node, mul());
		else if (consume('-'))
			node = new_node(ND_SUB, node, mul());
		else
			return node;
	}
}

// void	gen(Node *node) {
// 	if (node->kind == ND_NUM) {
// 		printf("	push %d\n", node->val);
// 		return ;
// 	}

// 	gen(node->lhs);
// 	gen(node->rhs);
// 	printf("	pup rdi\n");
// 	printf("	pop rax\n");

// 	switch (node->kind) {
// 		case	ND_ADD:
// 			printf("	add rax, rdi\n");
// 			break ;
// 		case	ND_SUB:
// 			printf("	sub rax, rdi\n");
// 			break ;
// 		case	ND_MUL:
// 			printf("	imul rax, rdi\n");
// 			break ;
// 		case	ND_DIV:
// 			printf("	cqo\n");
// 			printf("	idiv rdi\n");
// 			break ;
// 	}
// 	printf("	push rax");
// }

static char	op_char(NodeKind k) {
	switch (k) {
		case ND_ADD:	return '+';
		case ND_SUB:	return '-';
		case ND_MUL:	return '*';
		case ND_DIV:	return '/';
		default:		return '?';
	}
}

static void	print_inorder(const Node	*n) {
	if (!n)	return ;
	if (n->kind == ND_NUM) {
		printf("%d\n", n->val);
		return ;
	}
	print_inorder(n->lhs);
	printf("%c\n", op_char(n->kind));
	print_inorder(n->rhs);
}

static void print_right_then_op_then_left(const Node *root) {
	if (!root) return;
	if (root->kind == ND_NUM) {
		printf("%d\n", root->val);
		return;
	}
	print_inorder(root->rhs);
	printf("%c\n", op_char(root->kind));
	print_inorder(root->lhs);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s \"EXPR\"\n", argv[0]);
		return 1;
	}
	token = tokenize(argv[1]);
	Node *root = expr();
	if (!at_eof()) {
		fprintf(stderr, "未処理のトークンがあります。\n");
		return 1;
	}

	print_right_then_op_then_left(root);
	return 0;
}
