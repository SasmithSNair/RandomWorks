/* A multi pointer array in C */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USIZE 64
struct MPA
{
	char string[USIZE];
	long long int index;
	struct MPA *mp;
};
void displayArray(struct MPA *mpa, long long int lim)
{
	if (mpa != NULL)
	{
		long long int i, j;
		for (i = 0; i < lim; i++)
		{
			printf("Element %d: %s\n", i + 1, mpa[i].string);
			printf("Pointing to:\n");
			for (j = 0; j < lim - 1; j++)
			{
				printf("\tElement: %s at index: %d\n", mpa[i].mp[j].string, mpa[i].mp[j].index);
			}
		}
	}
	else
	{
		fprintf(stderr, "[+] Error accessing memory.\n");
	}
}
int main()
{
	struct MPA *mpa;
	long long int lim, i, j, k;
	printf("Enter limit: ");
	scanf("%lld", &lim);
	getchar();
	mpa = (struct MPA *)malloc(sizeof(struct MPA) * lim);
	if (mpa == NULL)
	{
		fprintf(stderr, "[+] Error allocating memory.\n");
		return -1;
	}
	for (i = 0; i < lim; i++)
	{
		printf("Enter element %d: ", i + 1);
		fgets(mpa[i].string, USIZE, stdin);
		mpa[i].string[strcspn(mpa[i].string, "\n")] = '\0';
		mpa[i].index = i;
		mpa[i].mp = (struct MPA *)malloc(sizeof(struct MPA) * lim - 1);
		if (mpa[i].mp == NULL)
		{
			fprintf(stderr, "[+] Error allocating memory.\n");
		}
	}
	for (i = 0; i < lim; i++)
	{
		k = 0;
		for (j = 0; j < lim; j++)
		{
			if (i != j)
			{
				mpa[i].mp[k] = mpa[j];
				k++;
			}
		}
	}
	printf("[+] Multi-Pointer Array: Connection Established.\nArray:\n");
	displayArray(mpa, lim);
	return 0;
}
