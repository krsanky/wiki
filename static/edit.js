console.log("edit.js ...");

var cm_elem = undefined;
var editor = undefined;

var init_cm = function() {
	console.log("start codemirror");

	CodeMirror.commands.save = function() { 
		c = editor.getCursor();
		console.log("form#wikieditform submit (cursor:");
		console.log(c);

		//console.log("hidden line:"+$("input[name=line]").val());
		$("input[name=ch]").val(c.ch);
		$("input[name=line]").val(c.line);

		$('form#wikieditform').submit();
	}

	cm_elem = document.getElementById("wiki_forms_text");  
	//var cm_defaults = CodeMirror.defaults;
	//console.log(cm_defaults);

	var cm_cfg = {
		lineNumbers: true,
		matchBrackets: true,
		styleActiveLine: true,
		theme: 'colorforth',
		showCursorWhenSelecting: true,
	};
	//cm_cfg.keyMap = undefined; //default
	cm_cfg.keyMap = "vim";

	editor = CodeMirror.fromTextArea(cm_elem, cm_cfg);
};

$(function(){
	init_cm();
});

