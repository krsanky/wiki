<!doctype html>

<html>
<head>
<meta charset='utf-8' />
<meta name='viewport' content='width=device-width, initial-scale=1' />
<title>oldcode wiki</title>
<style type='text/css'>
body {
  margin:40px auto;
  max-width:80%%;
  line-height:1.6;
  font-size:18px;
  color:#444; 
  padding:0 10px
}
h1,h2,h3 {
  line-height:1.2
}
</style>
<!-- start extra css -->
{{# these var names are in tmpl.[ch]}}
{{for css in tmpl_extra_css}}
<link rel="stylesheet" type="text/css" href="{{css.value}}">
{{endfor}}
<!-- end extra css -->

<script src="/static/jquery-3.3.1.min.js"></script>
<!-- begin extra js -->
{{for js in tmpl_extra_js}}
<script src="{{js.value}}"></script>
{{endfor}}
<!-- end extra js -->
</head>

<body>
<header><h1><a href="/wiki.cgi">Oldcode Wiki</a></h1></header>

