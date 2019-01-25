$(function() {
	console.log( "adding ctrl+shift+a key listener" );
	Mousetrap.bind('ctrl+shift+a', function(e) {
		console.log('goto admin');
		window.location.href = '/admin.cgi';
		return false;
	});
	console.log( "adding ctrl+shift+m key listener" );
	Mousetrap.bind('ctrl+shift+m', function(e) {
		console.log('goto menu');
		window.location.href = '/menu.cgi';
		return false;
	});
});

