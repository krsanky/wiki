<!doctype html>

<?
function fun1($a1) {
	return "f1:".$a1;
}
//int file_put_contents ( string $filename , mixed $data [, int $flags = 0 [, resource $context ]] )

?>

<html>
<head><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'><title>oldcode wiki</title><style type='text/css'>body{margin:40px auto;max-width:80%;line-height:1.6;font-size:18px;color:#444; padding:0 10px}h1,h2,h3{line-height:1.2}</style></head>
<body>
<header><h1>Oldcode Wiki</h1></header>
/ <a href='/wiki.cgi?index&'>root</a> / <a href='/wiki.cgi?new&'>[new]</a>  <hr/>

<h1><?=fun1($_POST['dir'])?></h1>
<pre>
<? 
print_r($_POST);
?>
</pre>
<ul>
<? foreach ($_POST as $k => $v): ?>
<li>k:<?=$k?> v:<?=$v?></li>
<? endforeach ?>
<!--
k:wikiformtext v:# file123
k:page v:file123.md
k:dir v:dir123/asdqwe2
-->
<?  if (array_key_exists("dir", $_POST)): ?>
key dir exists<br/>
<? else: ?>
no key dir
<? endif ?>

<?  if (array_key_exists("key123", $_POST)): ?>
key key123 exists<br/>
<? else: ?>
no key key123
<? endif ?>
</ul>

<pre>
write to filei: <?='content/'.$_POST['dir'].'/'.$_POST['page']?>
</pre>
<?
filename = 'content/'.$_POST['dir'].'/'.$_POST['page'];
ret = file_put_contents($filename, $_POST['wikiformtext']);
?>
</body>
</html>



