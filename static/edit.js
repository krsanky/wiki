console.log("edit.js ...");

//do editor.refresh(); after some config changes on running editor?
$(function(){
console.log("start codemirror");

CodeMirror.commands.save = function() { 
	console.log("form#wikieditform submit");
	$('form#wikieditform').submit();
}

var cm_elem = document.getElementById("wiki_forms_text");  
var cm_defaults = CodeMirror.defaults;
console.log(cm_defaults);

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
