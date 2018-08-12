int 		ret1      (void);

struct params {

};

typedef struct param {
	char           *key;
	char           *val;
} 		PARAM;

void 		params_initialize(PARAM *, int);
void 		params_free(PARAM *, int);
int 		params_parse_query(char *, PARAM *, int);
const char     *params_get(char *, PARAM *, int);
int 		params_testdb();
