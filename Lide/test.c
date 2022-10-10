

#include "parsing.h"
#include "get_next_line/get_next_line.h"

// int main(void)
// {
// 	int fd;
// 	char *line;
// 	int i = 1;

// 	fd = open("text.txt", O_RDONLY);
// 	while (i)
// 	{
// 		i = get_next_line(fd, &line);
// 		if (i == -1)
// 			exit(1);
// 		else if (i == 0)
// 			break;
// 		if (line[0] == '\0')
// 			printf("1");
// 		printf("%s", line);
// 	}
// 	return (0);
// }

// int	ft_strncmp(const char *s1, const char *s2, int start, int len)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[start] && s2[i] && s1[start] == s2[i] && i < len)
// 	{
// 		i++;
// 		start++;
// 	}
// 	printf("%d | %d\n", s1[start], s2[i]);
// 	return ((unsigned char)s1[start] - (unsigned char)s2[i]);
// }

// int main(void)
// {
// 	char s1[10] = "NO salut";
// 	char s2[3] = "NO ";

// 	printf("%d\n", ft_strncmp(s1, s2, 0, 2));
// 	return (0);
// }

int	len1(char *str)
{
	int len;

	len = 0;
	while(str[len])
		len++;
	return (len);
}

int main(void)
{
	int len;
	char str[10] = "NO salut";
	printf("%d\n", len1(&str[2]));
	return (0);
}
