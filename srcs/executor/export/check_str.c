#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define size 100

int		main(void)
{
	char export[size];
	unsigned int i;

	i = 0;
	while (i < size)
	{
		export[i] = '\0';
		i++;
	}
	printf("enter a string for export: \n");
	scanf("%s", export);
	if (export[0] != '\0' && export[1] == '\0')
	{
		printf("\033[90mchecking the first character now\033[0m\n");
		if ((export[0] >= 65 && export[0] <= 90) 
				|| (export[0] >= 97 && export[0] <= 122) 
				|| (export[0] == 95))
		{
			printf("\033[92mright!\033[0m\n>%s\n", export);
			return (0);
		}
		else
		{
			printf("\033[91mwrong!\033[0m\n>%s\n", export);
			return (1);
		}
	}
	else 
	{
		printf("\033[90mchecking the rest of the line now\033[0m\n");
		i = 1;
		while (export[i] != '\0')
		{
			if ((export[0] >= 65 && export[0] <= 90) 
					|| (export[0] >= 97 && export[0] <= 122) 
					|| (export[0] == 95))
			{
				if ((export[i] >= 48 && export[i] <= 59) 
					|| (export[i] >= 65 && export[i] <= 90) 
					|| (export[i] >= 97 && export[i] <= 122) 
					|| (export[i] == 95))
				{
					i++;
					continue ;
				}
				else 
				{
					printf("\033[91mwrong!\033[0m\n>%s\n", export);
					return (1);
				}
			}
			else 
			{
				printf("\033[91mfirst character is wrong!\033[0m\n>%s\n", export);
				return (1);
			}
			i++;
		}
	}
	printf("\033[92mright!\033[0m\n>%s\n", export);
	return (0);
}
