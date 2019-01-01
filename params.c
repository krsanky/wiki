#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <db.h>
#include <assert.h>

#include "params.h"
#include "util.h"

/*
typedef struct params {
	char           *query_string;
	int		nparams;
	PARAM          *params;
} PARAMS;
*/
PARAMS         *
params_create(int num, char *qs)
{
	//PARAM * params;
	PARAMS         *params;
	int 		ret;

	if (qs == NULL) {
		return NULL;
	}
	if ((params = malloc(sizeof(PARAM))) == NULL)
		return NULL;
	if ((params->params = malloc(sizeof(PARAM) * num)) == NULL)
		return NULL;

	for (int i = 0; i < num; i++) {
		params->params[i].key = NULL;
		params->params[i].val = NULL;
	}

	params->nparams = num;

	ret = params_parse_query(qs, params);

	return params;
}

int
params_free(PARAMS * ps)
{
	for (int i = 0; i < ps->nparams; i++) {
		free(ps->params[i].key);
		free(ps->params[i].val);
	}
	free(ps->params);
	free(ps);
	return 0;
}

int
params_parse_query(char *query, PARAMS * ps)
{
	char           *string, *fstring;
	char           *found;
	char           *key;
	int 		idx = 0;

	fstring = string = strdup(query);
	assert(string != NULL);

	while ((found = strsep(&string, "&")) != NULL) {
		if (idx >= ps->nparams)
			break;

		key = strsep(&found, "=");

		ps->params[idx].key = strdup(key);
		assert(ps->params[idx].key != NULL);

		if (found != NULL) {
			ps->params[idx].val = strdup(found);
			assert(ps->params[idx].val != NULL);
		} else {
			ps->params[idx].val = NULL;
		}

		idx++;
	}

	free(fstring);
	return 0;
}

char           *
params_get(PARAMS * ps, char *key)
{
	for (int i = 0; i < ps->nparams; i++) {
		if (ps->params[i].key != NULL)
			if (strcmp(key, ps->params[i].key) == 0)
				return ps->params[i].val;
	}
	return NULL;
}

int
params_testdb()
{
	DB             *db;
	DBT 		key;
	DBT 		val;
	DBT 		gval;
	char           *val_;
	char           *key_;
	int 		ret;

	db = dbopen(NULL, O_RDWR, 0, DB_HASH, NULL);
	if (db == NULL) {
		printf("dbopen err\n");
		return EXIT_FAILURE;
	}
	val_ = malloc(3);
	strlcpy(val_, "v1", 3);
	key_ = malloc(3);
	strlcpy(key_, "k1", 3);

	key.data = key_;
	key.size = strlen(key_) + 1;
	val.data = val_;
	val.size = strlen(val_) + 1;
	db->put(db, &key, &val, 0);
	ret = db->get(db, &key, &gval, 0);
	printf("errno(ret):%d\n", ret);
	if (ret != 0) {
		printf("dbread err\n");
		return EXIT_FAILURE;
	}
	printf("k:%s v:%s\n", key.data, gval.data);
	db->close(db);

	return 0;
}

int
params_ishex(int x)
{
	return (x >= '0' && x <= '9') ||
	(x >= 'a' && x <= 'f') ||
	(x >= 'A' && x <= 'F');
}

int
params_urldecode(char *s, char *dec)
{
	char           *o;
	const char     *end = s + strlen(s);
	int 		c;

	for (o = dec; s <= end; o++) {
		c = *s++;
		if (c == '+')
			c = ' ';
		else if (c == '%' && (!params_ishex(*s++) ||
				      !params_ishex(*s++) ||
				      !sscanf(s - 2, "%2x", &c)))
			return -1;

		if (dec)
			*o = c;
	}

	return o - dec;
}

/*
int
params_parse_multipart_POST(char *text, char *boundary, PARAM * params, int max_params)
{
	printf("<pre>\n");
	printf("params_parse_multipart_POST(---------\n");
	printf("BODY:\n");
	printf("%s\n===\n", text);
	char           *start;
	char           *end;
	start = strstr(text, boundary);
	printf("match1[[[%.120s]]]\n", start);
	end = strstr(start, boundary);


	printf("</pre>\n");
	return 0;
}
*/
