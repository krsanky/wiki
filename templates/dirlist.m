<style>
.indent-1 {float: left;}
.indent-1 section {width: 50%; float: left;}
</style>

<section class="indent-1">
  <section>
    <h3>dirs</h3>
    <ul>
    {{for d in dirs}}
    	<li>{{d.value}}</li>
    {{endfor}}
    </ul>
  </section>
    
  <section class="right-section">
    <h3>pages</h3>
    <ul>
    {{for p in pages}}
    	<li>{{p.value}}</li>
    {{endfor}}
    </ul>
  </section>
</section>

<script>
$(function() {
console.log("dirlist.md");
});
</script>

