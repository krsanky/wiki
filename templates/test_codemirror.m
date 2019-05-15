

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
<div style="font-size: 13px; width: 300px; height: 30px;">Key buffer: <span id="command-display"></span></div>

<script>
$(function(){
console.log("start codemirror");

CodeMirror.commands.save = function(){ alert("Saving"); };

var cm_elem = document.getElementById("test_forms_text");  
var cm_defaults = CodeMirror.defaults;
//console.log(cm_defaults);

var cm_cfg = {
	lineNumbers: true,
	matchBrackets: true,
	styleActiveLine: true,
	showCursorWhenSelecting: true,
};
cm_cfg.keyMap = "vim";

var editor = CodeMirror.fromTextArea(cm_elem, cm_cfg);
var commandDisplay = document.getElementById('command-display');
var keys = '';
CodeMirror.on(editor, 'vim-keypress', function(key) {
	keys = keys + key;
	commandDisplay.innerHTML = keys;
});
CodeMirror.on(editor, 'vim-command-done', function(e) {
	keys = '';
	commandDisplay.innerHTML = keys;
});

});
</script>

