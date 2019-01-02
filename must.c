#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>

#include "params.h"

void 		header   ();

void
jsontest()
{
	struct json_object *jobj;

 	char *str = "{ \"msg-type\": [ \"0xdeadbeef\", \"irc log\" ], \
  		\"msg-from\": { \"class\": \"soldier\", \"name\": \"Wixilav\" }, \
		\"msg-to\": { \"class\": \"supreme-commander\", \"name\": \"[Redacted]\" }, \
		\"msg-log\": [ \
		\"soldier: Boss there is a slight problem with the piece offering to humans\", \
		\"supreme-commander: Explain yourself soldier!\", \
		\"soldier: Well they don't seem to move anymore...\", \
		\"supreme-commander: Oh snap, I came here to see them twerk!\" \
		] \
		}";

	printf("str:\n---\n%s\n---\n\n", str);

	jobj = json_tokener_parse(str);
	printf("jobj from str:\n---\n%s\n---\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));

}

void
web()
{
	PARAMS         *ps;
	char           *qs = getenv("QUERY_STRING");
	char           *p1;

	ps = params_create(10, qs);

	header();

	p1 = params_get(ps, "p1");
	printf("<p>%s</p>\n", p1);


	p1 = params_get(ps, "qwdqwdwqp1");
	printf("<p>[%s]</p>\n", p1);
	params_free(ps);
	printf("<pre>asd\n");
	jsontest();
	printf("</pre>\n");
}

void
header()
{
	printf("Content-type: text/html\n\n");
	printf("<h1>hey!</h1>\n");
}

int
main()
{
	web();
	return EXIT_SUCCESS;
}
