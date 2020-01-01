<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>Oldcode Wiki</title>
<link rel="stylesheet" type="text/css" href="{{url_root}}/static/normalize.css">
<link rel='stylesheet' href='{{url_root}}/static/style.css' type='text/css' media='screen' />
<meta name="viewport" content="width=device-width, initial-scale=1.0">

{{# start extra css }}
{{# these var names are in myhtml.[ch]}}
{{for css in myhtml_extra_css}}
<link rel="stylesheet" type="text/css" href="{{css.value}}">
{{endfor}}
{{# end extra css }}

<script src="{{url_root}}/static/jquery-3.3.1.min.js"></script>
{{# begin extra js }}
{{for js in myhtml_extra_js}}
<script src="{{js.value}}"></script>
{{endfor}}
{{# end extra js }}
</head>

<body>

