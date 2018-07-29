#include "myhtml.h"
/*
<!DOCTYPE html>
<html><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Better Motherfucking Website</title>

<style type="text/css">
body{margin:40px auto;max-width:650px;line-height:1.6;font-size:18px;color:#444; padding:0 10px}
h1,h2,h3{line-height:1.2}
</style>
*/

void
myhtml_header()
{
	printf("\
<!doctype html>\n\
<html>\n\
<head><meta charset='utf-8'>\
<meta name='viewport' content='width=device-width, initial-scale=1'>\
<head>\
<title>wiki</title>\
<style type='text/css'>\
body{margin:40px auto;max-width:80%%;line-height:1.6;font-size:18px;color:#444; padding:0 10px}\
h1,h2,h3{line-height:1.2}\
</style>\
</head>\n\
<body>\n\
<header><h1>Oldcode WIKI</h1></header>\
\n");
}

void
myhtml_footer()
{
	printf("\
</body>\
</html>\
\n");
}

void
myhtml_topnav()
{
	printf("<hr/>\n");
	printf("<a href=\"/\">home</a> ");
	printf("<a href='/wiki.cgi?index'>index</a>\n");
	/* printf("<a href='/edit.cgi?asd=123'>edit</a> "); */
	printf("<hr/>\n");
}
