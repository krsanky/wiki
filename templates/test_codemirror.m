<form action='/test_codemirror.cgi' method='post' 
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
console.log("seeme123");
var cm_elem = document.getElementById("test_forms_text");  
var cm = CodeMirror.fromTextArea(cm_elem);
</script>

