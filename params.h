int 		ret1      (void);

struct yuarel {
	char           *scheme;	/* scheme, without ":" and "//" */
	char           *username;	/* username, default: NULL */
	char           *password;	/* password, default: NULL */
	char           *host;	/* hostname or IP address */
	int 		port;	/* port, default: 0 */
	char           *path;	/* path, without leading "/", default: NULL */
	char           *query;	/* query, default: NULL */
	char           *fragment;	/* fragment, default: NULL */
};

struct params {

};

typedef struct param {
	char           *key;
	char           *val;
} PARAM;

int	params_parse_query(char *, PARAM *, int);
void	params_test();

