

<style>
      .CodeMirror {border: 1px solid black; font-size:13px}
</style>

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
$(function(){
console.log("start codemirror");
var cm_elem = document.getElementById("test_forms_text");  
var cm_defaults = CodeMirror.defaults;
//console.log(cm_defaults);

var cm_cfg = {};
cm_cfg.lineNumbers = true;
cm_cfg.keyMap = "vim";
var editor = CodeMirror.fromTextArea(cm_elem, cm_cfg);
 //   lineNumbers: true,
 //   styleActiveLine: true,
  //  matchBrackets: true


});
</script>

