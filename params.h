int 		ret1      (void);

typedef struct param {
	char           *key;
	char           *val;
} 		PARAM;

typedef struct params {
	char           *query_string;
	int 		nparams;
	PARAM          *params;
} 		PARAMS;

PARAMS         *params_create(int, char *);
int 		params_free(PARAMS *);
int 		params_parse_query(char *, PARAMS *);
int 		params_ishex(int);
int 		params_urldecode(char *, char *);
char           *params_get(PARAMS *, char *);

int 		params_testdb();
int 		isone_formdata_header(char *);
/* int 		params_parse_multipart_POST(char *, char *, PARAM *, int); */
