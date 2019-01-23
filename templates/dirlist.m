<h1>dir:{{dir}}</h1>

<h2>dirs</h2>
<ul>
{{for d in dirs}}
	<li>{{d.value}}</li>
{{endfor}}
</ul>

<h2>files</h2>
<ul>
{{for f in files}}
	<li>{{f.value}}</li>
{{endfor}}
</ul>

