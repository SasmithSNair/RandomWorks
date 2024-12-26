/* File management simulation in C */

/* Features:
 * Create Directory
 * Create File
 * Rename Directory
 * Rename File
 * Delete Directory
 * Delete File
 * Display Tree
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USIZE 32
struct File
{
	char file[USIZE];
};
struct Dir
{
	char dir[USIZE];
	size_t f_index;
	struct File *f;
};
struct Dir *mkDir(struct Dir *d, size_t index)
{
	if (d != NULL)
	{
		int i, e = 0;
		char dirname[USIZE], fname[USIZE];
		printf("Enter name of directory: ");
		fgets(dirname, USIZE, stdin);
		dirname[strcspn(dirname, "\n")] = '\0';
		for (i = 0; i <= index; i++)
		{
			if (!strcmp(d[i].dir, dirname))
			{
				printf("[+] Directory %s already exists.\n", dirname);
				e = 1;
				break;
			}
		}
		if (e == 0)
		{
			if (index > 0)
			{
				d = realloc(d, sizeof(struct Dir) * (index + 2));
			}
			strcpy(d[index].dir, dirname);
			d[index].f_index = -1;
			d[index].f = (struct File *)malloc(sizeof(struct File));
			printf("[+] Directory created:\t%s\n", dirname);
			return d;
		}
	}
	else
	{
		fprintf(stderr, "[+] Error allocating memory.\n");
		return NULL;
	}
}
struct Dir *mkFile(struct Dir *d, size_t index)
{
	if (d != NULL)
	{
		if ((long long int)index == -1)
		{
			fprintf(stderr, "[+] No directories created.\n");
			return NULL;
		}
		else
		{
			size_t i, j;
			long long int choice, found = 0;
			char fname[USIZE];
			printf("Select directory:\n");
			for (i = 0; i <= index; i++)
			{
				printf("%d -> %s\n", i + 1, d[i].dir);
			}
			printf(">>> ");
			scanf("%lld", &choice);
			getchar();
			choice--;
			if (choice >= 0 && choice <= index)
			{
				printf("Enter filename: ");
				fgets(fname, USIZE, stdin);
				fname[strcspn(fname, "\n")] = '\0';
				if (d[choice].f_index != -1)
				{
					for (j = 0; j <= d[choice].f_index; j++)
					{
						if (!strcmp(d[choice].f[j].file, fname))
						{
							found = 1;
						}
					}
				}
				if (found == 0)
				{
					d[choice].f_index++;
					if (d[choice].f_index > 0)
					{
						d[choice].f = realloc(d[choice].f, sizeof(struct File) * (d[choice].f_index + 1));
					}
					strcpy(d[choice].f[d[choice].f_index].file, fname);
					printf("[+] File created: %s in directory: %s\n", d[choice].f[d[choice].f_index].file, d[choice].dir);
					return d;
				}
				else
				{
					fprintf(stderr, "[+] File %s already exists.\n", fname);
					return NULL;
				}
			}
			else
			{
				fprintf(stderr, "[+] Invalid choice.\n");
				return NULL;
			}
		}
	}
	else
	{
		printf("[+] Memory allcation failed.\n");
		return NULL;
	}
}
struct Dir *rDir(struct Dir *d, size_t index)
{
	if (d != NULL)
	{
		if ((long long int)index > -1)
		{
			size_t i;
			long long int choice;
			printf("Choose directory to rename:\n");
			for (i = 0; i <= index; i++)
			{
				printf("%d -> %s\n", i + 1, d[i].dir);
			}
			printf(">>> ");
			scanf("%lld", &choice);
			getchar();
			choice--;
			if (choice >= 0 && choice <= index)
			{
				printf("Enter new name: ");
				fgets(d[choice].dir, USIZE, stdin);
				d[choice].dir[strcspn(d[choice].dir, "\n")] = '\0';
				printf("[+] Rename successful.\n");
				return d;
			}
			else
			{
				fprintf(stderr, "[+] Invalid choice.\n");
				return NULL;
			}
		}
		else
		{
			fprintf(stderr, "[+] No directories created.\n");
			return NULL;
		}
	}
	else
	{
		fprintf(stderr, "[+] Memory allocation failed.\n");
		return NULL;
	}
}
struct Dir *rFile(struct Dir *d, size_t index)
{
	if (d != NULL)
	{
		if ((long long int)index > -1)
		{
			long long int i, j;
			long long int choice0, choice1;
			char fname[USIZE];
			printf("Choose directory:\n");
			for (i = 0; i <= index; i++)
			{
				printf("%d -> %s\n", i + 1, d[i].dir);
			}
			printf(">>> ");
			scanf("%lld", &choice0);
			getchar();
			choice0--;
			if (choice0 >= 0 && choice0 <= index)
			{
				printf("Choose file to be renamed:\n");
				for (j = 0; j <= d[choice0].f_index; j++)
				{
					printf("%d -> %s\n", j + 1, d[choice0].f[j].file);
				}
				printf(">>> ");
				scanf("%lld", &choice1);
				getchar();
				choice1--;
				if (choice1 >= 0 && choice1 <= d[choice0].f_index)
				{
					printf("Enter new name: ");
					fgets(d[choice0].f[choice1].file, USIZE, stdin);
					d[choice0].f[choice1].file[strcspn(d[choice0].f[choice1].file, "\n")] = '\0';
					printf("[+] Rename successful.\n");
					return d;
				}
				else
				{
					fprintf(stderr, "[+] Invalid choice.\n");
					return NULL;
				}
			}
			else
			{
				fprintf(stderr, "[+] Invalid choice.\n");
				return NULL;
			}
		}
		else
		{
			fprintf(stderr, "[+] No directories created.\n");
			return NULL;
		}
	}
	else
	{
		fprintf(stderr, "[+] Error allocating memory.\n");
		return NULL;
	}
}
struct Dir *delDir(struct Dir *d, size_t index)
{
	if (d != NULL)
	{
		if ((long long int)index > -1)
		{
			size_t i, j;
			long long int choice;
			struct Dir *temp = (struct Dir *)malloc(sizeof(struct Dir) * (index + 1));
			printf("Choose directory to be deleted:\n");
			for (i = 0; i <= index; i++)
			{
				printf("%d -> %s\n", i + 1, d[i].dir);
			}
			printf(">>> ");
			scanf("%lld", &choice);
			getchar();
			choice--;
			if (choice >= 0 && choice <= index)
			{
				printf("[+] Directory %s deleted.\n", d[choice].dir);
				i = 0;
				for (j = 0; j <= index; j++)
				{
					if (j != (size_t)choice)
					{
						temp[i] = d[j];
						i++;
					}
				}
				return temp;
			}
			else
			{
				fprintf(stderr, "[+] Invalid choice.\n");
				return NULL;
			}
		}
		else
		{
			fprintf(stderr, "[+] No directories created.\n");
			return NULL;
		}
	}
	else
	{
		fprintf(stderr, "[+] Memory allocation failed.\n");
		return NULL;
	}
}
struct Dir *delFile(struct Dir *d, size_t index)
{
	if (d != NULL)
	{
		if ((long long int)index > -1)
		{
			long long int i, j, k, choice0, choice1;
			printf("Choose directory:\n");
			for (i = 0; i <= index; i++)
			{
				printf("%d -> %s\n", i + 1, d[i].dir);
			}
			printf(">>> ");
			scanf("%lld", &choice0);
			getchar();
			choice0--;
			if (choice0 >= 0 && choice0 <= index)
			{
				printf("Choose file to be deleted:\n");
				for (j = 0; j <= d[choice0].f_index; j++)
				{
					printf("%d -> %s\n", j + 1, d[choice0].f[j].file);
				}
				printf(">>> ");
				scanf("%lld", &choice1);
					getchar();
				choice1--;
				printf("[+] File deleted %s from directory: %s\n", d[choice0].f[choice1].file, d[choice0].dir);
				struct File *tmp = (struct File *)malloc(sizeof(struct File) * d[choice0].f_index);
				if (tmp == NULL)
				{
					fprintf(stderr, "[+] Failed to access memory.\n");
				}
				else
				{
					j = 0;
					for (k = 0; k <= d[choice0].f_index; k++)
					{
						if (k != choice1)
						{
							tmp[j] = d[choice0].f[k];
							j++;
						}
					}
					d[choice0].f = tmp;
					d[choice0].f_index--;
					return d;
				}
			}
			else
			{
				printf("Invalid choice.\n");
				return NULL;
			}
		}
		else
		{
			fprintf(stderr, "[+] No directories created.\n");
			return NULL;
		}
	}
	else
	{
		printf("Memory allocation failed.\n");
		return NULL;
	}
}
void printTree(struct Dir *d, size_t index)
{
	if ((long long int)index != -1)
	{
		if (d != NULL)
		{
			size_t i, j;
			for (i = 0; i <= index; i++)
			{
				printf("# %s\n", d[i].dir);
				if (d[i].f_index != -1)
				{
					for (j = 0; j <= d[i].f_index; j++)
					{
						printf("\t-> %s\n", d[i].f[j].file);
					}
				}
			}
		}
		else
		{
			fprintf(stderr, "[+] Error allocating memory.\n");
		}
	}
	else
	{
		fprintf(stderr, "[+] No directories created.\n");
	}
}
int main()
{
	size_t index = -1;
	struct Dir *d = (struct Dir *)malloc(sizeof(struct Dir));
	struct Dir *temp = (struct Dir *)malloc(sizeof(struct Dir));
	long long int choice;
	printf("File Management System\n");
	printf("----------------------\n");
	printf("1 -> Make directory\n2 -> Make file\n3 -> Rename directory\n4 -> Rename file\n5 -> Delete directory\n");
	printf("6 -> Delete file\n7 -> Display tree\n8 -> Exit\n");
	while (1)
	{
		temp = d;
		printf("$ ");
		scanf("%lld", &choice);
		getchar();
		switch(choice)
		{
			case 1:
				index++;
				if ((temp = mkDir(d, index)) != NULL)
				{
					d = temp;
				}
				else
				{
					fprintf(stderr, "[+] Operation failed.\n");
					index--;
				}
				break;
			case 2:
				if ((temp = mkFile(d, index)) != NULL)
				{
					d = temp;
				}
				else
				{
					fprintf(stderr, "[+] Operation failed.\n");
				}
				break;
			case 3:
				if ((temp = rDir(d, index)) != NULL)
				{
					d = temp;
				}
				else
				{
					fprintf(stderr, "[+] Operation failed.\n");
				}
				break;
			case 4:
				if ((temp = rFile(d, index)) != NULL)
				{
					d = temp;
				}
				else
				{
					fprintf(stderr, "[+] Operation failed.\n");
				}
				break;
			case 5:
				if ((temp = delDir(d, index)) != NULL)
				{
					d = temp;
					index--;
				}
				else
				{
					fprintf(stderr, "[+] Operation failed.\n");
				}
				break;
			case 6:
				if ((temp = delFile(d, index)) != NULL)
				{
					d = temp;
				}
				else
				{
					fprintf(stderr, "[+] Operation failed.\n");
				}
				break;
			case 7:
				printTree(d, index);
				break;
			case 8:
				printf("[+] Program terminated.\n");
				goto exit;
			default:
				printf("[+] Invalid choice.\n");
				break;
		}
	}
	exit:
		if (d != NULL)
		{
			free(d);
		}
		return 0;
}
