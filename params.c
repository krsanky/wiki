#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <db.h>

#include "params.h"

int 	
params_parse_query(char *query, PARAM *params, int max_params)
{
	return 0;
}

void
params_test()
{
	DB             *db;

	DBT 		key;
	DBT 		val;
	DBT 		gval;
	char           *val_;
	char           *key_;
	int 		ret;

	/*
	DB *
	dbopen(const char *file, int flags, int mode, DBTYPE type, const void *openinfo);
	*/
	db = dbopen(NULL, O_RDWR, 0, DB_HASH, NULL);
	if (db == NULL) {
		printf("dbopen err\n");
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}
	printf("k:%s v:%s\n", key.data, gval.data);
	db->close(db);
}

