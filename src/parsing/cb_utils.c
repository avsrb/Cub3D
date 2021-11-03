#include "../../inc/cub3d.h"

int	cb_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*spacecutter(char *str)
{
	char	*pstr;
	int		i;

	pstr = str;
	i = 0;
	if (*str == '\0')
		return (NULL);
	while (*str != '\0')
	{
		if (*str != ' ')
		{
			pstr[i] = *str;
			i++;
		}
		str++;
	}
	pstr[i] = '\0';
	return (pstr);
}
