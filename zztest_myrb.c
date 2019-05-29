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
RB_PROTOTYPE(inttree, mynode, entry, int_cmp)
RB_GENERATE(inttree, mynode, entry, int_cmp)

int testdata[] = {
 20, 16, 17, 13, 3, 6, 1, 8, 2, 4, 10, 19, 5, 9, 12, 15, 18,
 7, 11, 14
};

int
main(void)
{
	printf("rb tree test...\n");
	return EXIT_SUCCESS;
}

