<? 
$filename = 'content/';
if (array_key_exists('dir', $_POST)) {
	$filename .= $_POST['dir'] . '/';
}
$filename .= $_POST['page'];

$ret = file_put_contents($filename, $_POST['wikiformtext']);

$location = "Location: /wiki.cgi?view&";
$location .= "ret={$ret}&";
if (array_key_exists('dir', $_POST)) {
	$location .= "d={$_POST['dir']}&";
}
$location .= "p={$_POST['page']}";

//print("[location] ".$location);
header($location);
?>

