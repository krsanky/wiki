<div class="grid-1">

  <div>
    <h3>files</h3>
    <ul>
    {{for p in pages}}
    	<li>{{p.value}}</li>
    {{endfor}}
    </ul>
  </div>

  <div>
    <h3>dirs</h3>
    <ul>
    {{for d in dirs}}
    	<li>{{d.value}}</li>
    {{endfor}}
    </ul>
  </div>
    
</div>

