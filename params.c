#include "params.h"

int
rest1(void)
{
	return 1;
}
/********************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <db.h>

int
main(int argc, char **argv)
{
	DB             *db;

	printf("%s argc:%d\n", argv[0], argc);

//DB * 	dbopen(const char *file, int flags, int mode, DBTYPE type, const void *openinfo);
	db = dbopen(NULL, O_RDWR, 0, DB_HASH, NULL);
	if (db == NULL) {
		printf("dbopen err\n");
		exit(EXIT_FAILURE);
	}
	DBT 		key;
	DBT 		val;
	DBT 		gval;
	char           *val_;
	char           *key_;
	int 		ret;

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
	return 0;
}

           typedef struct {
                   void *data;
                   size_t size;
           } DBT;
     The elements of the DBT structure are defined as follows:
           data    A pointer to a byte string.
           size    The length of the byte string.

           typedef struct {
                   DBTYPE type;
                   int (*close)(const DB *db);
                   int (*del)(const DB *db, const DBT *key,
                       unsigned int flags);
                   int (*fd)(const DB *db);
                   int (*get)(const DB *db, DBT *key, DBT *data,
                       unsigned int flags);
                   int (*put)(const DB *db, DBT *key, const DBT *data,
                       unsigned int flags);
                   int (*sync)(const DB *db, u_int flags);
                   int (*seq)(const DB *db, DBT *key, DBT *data,
                       unsigned int flags);
           } DB;
*/



