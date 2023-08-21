#include "main.h"







/**
 * _getline - reads a line from a given stream
 */
ssize_t _getline(char **line_ptr, size_t *n, FILE *data_stream)
{
	ssize_t nchar = 0;
	int descript;

	if (line_ptr == NULL)
		return (nchar);	

	if (*n == 0)
		*n = 1024;

	descript = open(data_stream, O_RDWR);

	nchar = read(descript, *line_ptr, *n);

	*n = nchar;

	return (nchar);
}
