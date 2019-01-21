<form action='/test_forms.cgi?post' method='post' 
      enctype='application/x-www-form-urlencoded'>

<textarea name="test_forms_text" 
	rows='26' 
	cols='80'>{{test_forms_text}}</textarea>

<br/>
<button type='submit'>submit</button>

<input type='hidden' name='page' value='{{page}}' />

<input type='hidden' name='dir' value='{{dir}}'/>

</form>



