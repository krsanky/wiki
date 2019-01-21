$(function() {
	console.log( "adding ctrl+shift+a key listener" );
	Mousetrap.bind('ctrl+shift+a', function(e) {
		console.log('goto admim');
		window.location.href = '/admin.cgi';
		return false;
	});
});

