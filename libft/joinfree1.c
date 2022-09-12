#include "libft.h"

char	*joinfree1(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
	{
		s3 = ft_strdup(s2);
		return (free(s2), s3);
	}
	s3 = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 2 * (sizeof (char)));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	free(s1);
	s3[i++] = '*';
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	free(s2);
	s3[i + j] = '\0';
	return (s3);
}