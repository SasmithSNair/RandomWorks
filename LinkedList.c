/* Doubly Linked List in C */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct LinkedList
{
	struct LinkedList *prev;
	char elem[32];
	struct LinkedList *next;
};
struct LinkedList DisplayList(struct LinkedList *L)
{
	if (L != NULL)
	{
		printf("%s\n", L->elem);
		DisplayList(L->next);
	}
}
int main()
{
	size_t MAX, i, j, index = -1;
	printf("Enter limit: ");
	scanf("%d", &MAX);
	struct LinkedList *L = (struct LinkedList *)malloc(sizeof(struct LinkedList) * MAX);
	for (i = 1; i <= MAX; i++)
	{
		printf("Enter element %d: ", i);
		index++;
		if (index == 0)
		{
			L[index].prev = NULL;
			getchar();
			fgets(L[index].elem, 32, stdin);
			L[index].elem[strcspn(L[index].elem, "\n")] = '\0';
			L[index].next = &L[index + 1];
		}
		else if (index == MAX - 1)
		{
			L[index].prev = &L[index - 1];
			fgets(L[index].elem, 32, stdin);
			L[index].elem[strcspn(L[index].elem, "\n")] = '\0';
			L[index].next = NULL;
		}
		else
		{
			L[index].prev = &L[index - 1];
			fgets(L[index].elem, 32, stdin);
			L[index].elem[strcspn(L[index].elem, "\n")] = '\0';
			L[index].next = &L[index + 1];
		}
	}
	printf("LinkedList created.\n");
	printf("Elements in linked list:\n");
	DisplayList(L);
	return 0;
}
