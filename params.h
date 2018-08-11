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

struct param {
	char           *key;
	char           *val;
};

/*
extern int 	
yuarel_parse_query(char *query, char delimiter, struct yuarel_param * params, int max_params);
*/

