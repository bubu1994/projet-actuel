#include <stdio.h>
#include <stdlib.h>
#include "./includes/fdf.h"

int	comma_is_in(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
			return (1);
		i++;
	}
	return (0);
}

int	comma_pos(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != ',')
		i++;
	return (i);
}

int	hexachar_to_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else
		return -1;
}

unsigned int	hexastr_to_int(char *s)
{
	unsigned int	res;
	int				digit;

	res = 0;
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		s = s + 2;
	while (*s)
	{
		digit = hexachar_to_digit(*s);
		if (digit == -1)
		{
			perror("Invalid color");
			exit(1);
		}
		res = res * 16 + digit;
		s++;
	}
	return (res);
}

int main()
{
	char *s = "10,0xFF0000";
	int pos = comma_pos(s);

	char *s_hexa = "0xFFFFFF";
	
	printf("%d\n", hexastr_to_int(s_hexa));
}

