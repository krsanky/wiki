<div class=main_view>
<form action='{{url_root}}/wiki.cgi?newdirform' method='post' 
      enctype='application/x-www-form-urlencoded'>

<input type='text' name='newdir' />
<input type='hidden' name='dir' value='{{dir}}' />

<button type='submit'>submit</button>

{{if dir}}
<!-- dir exists -->
<input type='hidden' name='dir' value='{{dir}}'/>
{{else}}
<!-- dir NOT exists -->
{{endif}}

</form>
</div>

