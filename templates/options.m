<form method="post">


<button type='submit'>submit</button>
<table>
	<tr>
		<th>
			modify <a href="#" id="clear_modify">clear</a>
		</th>
		<th>name</th>
		<th>value</th>
	</tr>
	<tr>
		<td>
			<input type="radio" name="modify_var_name" value="editor"/> 
			{{editor}}
		</td>
		<td>editor</td>
		<td>
			<select name="editor">
				<option value="undefined">undefined</option>
				<option value="vi">vi</option>
				<option value="emacs">emacs</option>
				<option value="sublime">sublime</option>
			</select> 
		</td>
	</tr>
	<tr>
		<td>
			<input type="radio" name="modify_var_name" value="bogus_var1"/> {{bogus_var1}}
		</td>
		<td>bogus_var1</td>
		<td>
			<input type='text' name="bogus_var1">
		</td>
	</tr>
</table>


<button type='submit'>submit</button>
</form>

<script>
$('#clear_modify').click(function(){
	$('input[name=modify_var_name]').prop('checked', false);
	return false;
});

//localStorage.setItem('colorSetting', '#a4509b');

</script>
