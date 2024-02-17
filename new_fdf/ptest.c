#include "fdf.h"

int main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	char *s = get_next_line(fd);
	printf("%s", s);
	s = get_next_line(fd);
	printf("%s", s);
}