<div class=main_view>

move {{page}} to:

<form action='{{url_root}}/wiki.cgi?move' method='post' 
      enctype='application/x-www-form-urlencoded'>

{{if dir}}
<input type='hidden' name='dir' value='{{dir}}'/>
{{endif}}

<ul>
	<li><input type=radio name=movedir value='__up__'> ..</input></li>
{{for d in dirs}}
	<li><input type=radio name=movedir value='{{d.value}}'> {{d.value}}</input></li>
{{endfor}}
</ul>

<button type='submit'>submit</button>
</form>

</div>

