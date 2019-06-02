#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/tree.h>

struct mynode {
	RB_ENTRY(mynode) entry;
	int i;
}; 

int	int_cmp(struct mynode *, struct mynode *);
void	print_tree(struct mynode *);

int
int_cmp(struct mynode *e1, struct mynode *e2)
{
	return (e1->i < e2->i ? -1 : e1->i > e2->i);
}

RB_HEAD(inttree, mynode) head = RB_INITIALIZER(&head);
RB_PROTOTYPE(inttree, mynode, entry, int_cmp);
RB_GENERATE(inttree, mynode, entry, int_cmp);

int testdata[] = {
	20, 16, 17, 13, 3, 6, 1, 8, 2, 4, 10, 19, 5, 9, 12, 15, 18,
	7, 11, 14
};

int
main(void)
{
	unsigned long	i;
	struct mynode	*n;

	for (i = 0; i < sizeof(testdata) / sizeof(testdata[0]); i++) {
		if ((n = malloc(sizeof(struct mynode))) == NULL) {
			printf("err\n");
			return EXIT_FAILURE;	
		}
		n->i = testdata[i];
		RB_INSERT(inttree, &head, n);
	}

	RB_FOREACH(n, inttree, &head) {
		printf("%d\n", n->i);
	}

	print_tree(RB_ROOT(&head));
	printf("\n");

	return EXIT_SUCCESS;
}

void
print_tree(struct mynode *n)
{
	struct mynode *left, *right;

	if (n == NULL) {
		printf("nil");
		return;
	}
	left = RB_LEFT(n, entry);
	right = RB_RIGHT(n, entry);
	if (left == NULL && right == NULL)
		printf("%d", n->i);
	else {
		printf("%d(", n->i);
		print_tree(left);
		printf(",");
		print_tree(right);
		printf(")");
	}
}



