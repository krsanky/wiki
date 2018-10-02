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
char           *params_get(char *, PARAM *, int);
int 		params_testdb();
int 		params_ishex(int);
int 		params_urldecode(char *, char *);
int		isone_formdata_header(char *);
int		params_parse_multipart_POST(char *, char *, PARAM *, int);

