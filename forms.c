#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "forms.h"
#include "util.h"

/*
 * return value should be passed to free()
CONTENT_TYPE=multipart/form-data; boundary=---------------------------804515248930748430817995068
*/
char *
parse_boundary(char * ct_hdr)
{
	char	*first, *rest, *restf;
	char	*boundary = NULL;

	restf = rest = strdup(ct_hdr);
	assert(rest != NULL);

	first = strsep(&rest, " ");
	first = strsep(&rest, "=");

	if (strcasecmp("BOUNDARY", first) == 0) {
		boundary = strdup(rest);
	}

	free(restf);
	return boundary;
}

