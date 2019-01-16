<!-- tmpl new.m -->
<form action='/wiki.cgi?newform' method='post' 
      enctype='application/x-www-form-urlencoded'>

<input type='text' name='page' />

<button type='submit'>submit</button>

{{if dir}}
<!-- dir exists -->
<input type='hidden' name='dir' value='%s'/>
{{else}}
<!-- dir NOT exists -->
{{endif}}

</form>
<!-- end tmpl new.m -->

