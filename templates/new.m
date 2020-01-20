<div class=main_view>
<form action='/wiki.cgi?newform' method='post' 
      enctype='application/x-www-form-urlencoded'>

<input type='text' name='page' />

<button type='submit'>submit</button>

{{if dir}}
<input type='hidden' name='dir' value='{{dir}}'/>
{{endif}}

<p>Currently new pages must have .md extension</p>
</form>
</div>

