#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <db.h>
#include <assert.h>

#include "params.h"

void
params_initialize(PARAM * params, int max_params)
{
	for (int i = 0; i < max_params; i++) {
		params[i].key = NULL;
		params[i].val = NULL;
	}
}

void
params_free(PARAM * params, int max_params)
{
	for (int i = 0; i < max_params; i++) {
		free(params[i].key);
		free(params[i].val);
	}
	free(params);
}

int
params_parse_query(char *query, PARAM * params, int max_params)
{
	char           *string, *fstring;
	char           *found;
	char           *key;
	int 		idx = 0;

	fstring = string = strdup(query);
	assert(string != NULL);

	while ((found = strsep(&string, "&")) != NULL) {
		if (idx >= max_params)
			break;

		key = strsep(&found, "=");

		params[idx].key = strdup(key);
		assert(params[idx].key != NULL);

		if (found != NULL) {
			params[idx].val = strdup(found);
			assert(params[idx].val != NULL);
		} else {
			params[idx].val = NULL;
		}

		idx++;
	}

	free(fstring);
	return 0;
}

const char     *
params_get(char *key, PARAM * params, int max_params)
{
	for (int i=0; i<max_params; i++) {
		if (params[i].key != NULL)
			if (strcmp(key, params[i].key) == 0)
				return params[i].val;
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
