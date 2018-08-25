char	*
remove_all_spaces(char *data)
{
	char	*in, *out;

	for (in = out = data; *in != '\0', in++)
		if (*in != ' ')
			*out++ = *in;

	*out = '\0';
	return data;
}


char
itoa(int i)
{
	char	c;
	if (i >= 0 && i <= 9)
		c = i + '0';

	return c;
}

