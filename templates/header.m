<!doctype html>

<html>
<head>
<meta charset='utf-8' />
<meta name='viewport' content='width=device-width, initial-scale=1' />
<title>oldcode wiki</title>

<link rel='stylesheet' href='/static/style.css' type='text/css' media='screen' />

<!-- start extra css -->
{{# these var names are in myhtml.[ch]}}
{{for css in myhtml_extra_css}}
<link rel="stylesheet" type="text/css" href="{{css.value}}">
{{endfor}}
<!-- end extra css -->

<script src="/static/jquery-3.3.1.min.js"></script>
<!-- begin extra js -->
{{for js in myhtml_extra_js}}
<script src="{{js.value}}"></script>
{{endfor}}
<!-- end extra js -->
</head>

<body>
<header><h2><a href="/wiki.cgi">Oldcode Wiki</a></h2></header>

