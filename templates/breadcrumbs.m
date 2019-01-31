<!-- mtemplate breacrumbs.m -->
<style>
	div.breadcrumbs {
/*		background-color:yellow;*/
	}
</style>

<div class="breadcrumbs">
{{for b in breadcrumbs}}
/ <a href="{{b.value}}">{{b.key}}</a> 
{{endfor}}
{{if page}}/ {{page}}{{endif}}
&nbsp;
&nbsp;
&nbsp;
{{for a in actions}}
<a href="{{a.value}}">{{a.key}}</a>
{{endfor}}
</div>
<hr/>

<!-- /mtemplate breacrumbs.m -->
