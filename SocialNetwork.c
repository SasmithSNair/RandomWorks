#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 32
struct friends
{
	char fname[NAME];
	char fid;
};
struct users
{
	char name[NAME];
	int id;
	int fc;
	struct friends *F;
};
int main()
{
	struct users *u = (struct users *)malloc(sizeof(struct users));
	size_t usercount = -1, ID = 0, SIZE = 1;
	int choice;
	printf("Welcome to the Dynamic Social Network Simulation!\n");
	printf("-------------------------------------------------\n");
	printf("1 -> Register User\n2 -> Add Friend Connection\n3 -> View Friends of a User\n4 -> Remove User\n");
	printf("5 -> Display Social Network\n6 -> Exit\n");
	while (1)
	{
		printf("\n>>> ");
		scanf("%d", &choice);
		if (choice == 1)
		{
			usercount++;
			ID++;
			printf("\nEnter username: ");
			getchar();
			if (usercount > 0)
			{
				u = realloc(u, sizeof(struct users) * SIZE);
			}
			fgets(u[usercount].name, NAME, stdin);
			u[usercount].name[strcspn(u[usercount].name, "\n")] = '\0';
			u[usercount].id = ID;
			u[usercount].fc = 0;
			printf("User %s regeistered with id: %d\n", u[usercount].name, u[usercount].id);
			SIZE++;
		}
		else if (choice == 2)
		{
			int uid, fid, i, j, flag = 0;
			printf("\nEnter your user ID: ");
			scanf("%d", &uid);
			printf("Enter friend's user ID: ");
			scanf("%d", &fid);
			for (i = 0; i <= usercount; i++)
			{
				if (u[i].id == uid)
				{
					for (j = 0; j <= usercount; j++)
					{
						if (u[j].id == fid)
						{
							if (u[i].fc > 0)
							{
								u[i].F = realloc(u[i].F, sizeof(struct friends) * (u[i].fc + 1));
							}
							else
							{
								u[i].F = (struct friends*)malloc(sizeof(struct friends));
							}
							strcpy(u[i].F[u[i].fc].fname, u[j].name);
							u[i].F[u[i].fc].fid = u[j].id;
							flag = 1;
							u[i].fc++;
							goto next;
						}
					}
				}
			}
			next:
				if (flag == 1)
				{
					printf("Friendship added between %s and %s\n", u[i].name, u[j].name);
				}
				else
				{
					fprintf(stderr ,"Wrong user ID! Please try again.\n");
				}
		}
		else if (choice == 3)
		{
			int uid;
			printf("Enter your user ID: ");
			scanf("%d", &uid);
			if (uid > 0 && uid <= ID)
			{
				int i, j;
				for (i = 0; i <= usercount; i++)
				{
					if (u[i].id == uid)
					{
						break;
					}
				}
				printf("Friends of %s:\n", u[i].name);
				for (j = 0; j < u[i].fc; j++)
				{
					printf("-> %s\t(ID : %d)\n", u[i].F[j].fname, u[i].F[j].fid);
				}
			}
			else
			{
				fprintf(stderr, "Wrong user ID.\n");
			}
		}
		else if (choice == 4)
		{
			int uid;
			printf("Enter user ID to remove: ");
			scanf("%d", &uid);
			if (uid > 0 && uid <= ID)
			{
				int i, j;
				for (i = 0; i <= usercount; i++)
				{
					if (u[i].id == uid)
					{
						break;
					}
				}
				printf("User %s removed from the network. Friendships updated.\n", u[i].name);
				for (j = i - 1; j < usercount; j++)
				{
					u[i] = u[i + 1];
				}
				usercount--;
			}
			else
			{
				fprintf(stderr, "Wrong user ID.\n");
			}
		}
		else if (choice == 5)
		{
			printf("Social Network:\n");
			int i, j;
			for (i = 0; i <= usercount; i++)
			{
				printf("ID: %d Name: %s Friends: ", u[i].id, u[i].name);
				for (j = 0; j < u[i].fc; j++)
				{
					printf("%s%s", u[i].F[j].fname, (j < (u[i].fc - 1))? ", " : "\n");
				}
			}
		}
		else if (choice == 6)
		{
			printf("Exiting the program. Goodbye!\n");
			break;
		}
		else
		{
			fprintf(stderr, "Invalid input.\n");
			return -1;
		}
	}
	return 0;
}
