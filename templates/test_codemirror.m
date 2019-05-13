

<form action='/test_codemirror.cgi?post' method='post' 
      enctype='application/x-www-form-urlencoded'>

<textarea name="test_forms_text" 
	id="test_forms_text" 
	rows='26' 
	cols='80'></textarea>

<br/>
<button type='submit'>submit</button>

<input type='hidden' name='page' value='' />

<input type='hidden' name='dir' value=''/>
</form>



<script>
var cm_elem = document.getElementById("test_forms_text");  
var cm = CodeMirror.fromTextArea(myTextArea);
</script>

