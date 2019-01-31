#include <stdio.h>
#include <stdlib.h>

#include "params.h"

int
main()
{
	printf("test_params\n");
	
	return EXIT_SUCCESS;
}



/*
i
dir:OpenBSD/dir123
dir2:OpenBSD/dir123
href_dir:OpenBSD str:OpenBSD dir2:dir123
href_dir:OpenBSD/dir123 str:dir123 dir2:(null)
main.c main() QUERY_STRING: pagetype:
main.c main() QUERY_STRING:new& pagetype:new
mdict_new OK dir:(null)
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[17]
buf:page=qwd123123.md
make new file dir:(null) page:qwd123123.md
main.c main() QUERY_STRING:index& pagetype:index
main.c main() QUERY_STRING:index&d=BSD& pagetype:index
dir:BSD
dir2:BSD
href_dir:BSD str:BSD dir2:(null)
main.c main() QUERY_STRING:new&d=BSD& pagetype:new
dir:BSD
dir2:BSD
href_dir:BSD str:BSD dir2:(null)
mdict_new OK dir:BSD
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[18]
buf:page=qq.md&dir=BSD
make new file dir:BSD page:qq.md
params_urldecode: ret:4 decode:BSD
strlen dir:3
wikinewform:: fullpath:content/BS/qq.md
main.c main() QUERY_STRING:index& pagetype:index
main.c main() QUERY_STRING:index&d=OpenBSD& pagetype:index
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
main.c main() QUERY_STRING:new&d=OpenBSD& pagetype:new
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
mdict_new OK dir:OpenBSD
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[29]
buf:page=qqqqqqqqq.md&dir=OpenBSD
make new file dir:OpenBSD page:qqqqqqqqq.md
params_urldecode: ret:8 decode:OpenBSD
strlen dir:7
wikinewform:: fullpath:content/OpenBS/qqqqqqqqq.md
main.c main() QUERY_STRING:index&d=OpenBSD& pagetype:index
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
main.c main() QUERY_STRING:index&d=OpenBSD& pagetype:index
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
main.c main() QUERY_STRING:new&d=OpenBSD& pagetype:new
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
mdict_new OK dir:OpenBSD
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[24]
buf:page=test.md&dir=OpenBSD
make new file dir:OpenBSD page:test.md
params_urldecode: ret:8 decode:OpenBSD
strlen dir:7
wikinewform:: fullpath:content/OpenBS/test.md
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[24]
buf:page=test.md&dir=OpenBSD
make new file dir:OpenBSD
params_urldecode: ret:726 decode:OpenBSD
strlen dir:725
wikinewform:: fullpath:content/OpenBSD
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[24]
buf:page=test.md&dir=OpenBSD
make new file dir:OpenBSD page:test.md
params_urldecode: ret:8 decode:OpenBSD
strlen dir:7
wikinewform:: fullpath:content/OpenBS/test.md
main.c main() QUERY_STRING:index&d=OpenBSD& pagetype:index
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
main.c main() QUERY_STRING:new&d=OpenBSD& pagetype:new
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
mdict_new OK dir:OpenBSD
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[29]
buf:page=qwd123123.md&dir=OpenBSD
make new file dir:OpenBSD page:qwd123123.md
params_urldecode: ret:8 decode:OpenBSD
strlen dir:7
wikinewform:: fullpath:content/OpenBS/qwd123123.md
main.c main() QUERY_STRING:index&d=OpenBSD& pagetype:index
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
main.c main() QUERY_STRING:index&d=OpenBSD/dir123& pagetype:index
dir:OpenBSD/dir123
dir2:OpenBSD/dir123
href_dir:OpenBSD str:OpenBSD dir2:dir123
href_dir:OpenBSD/dir123 str:dir123 dir2:(null)
main.c main() QUERY_STRING:new&d=OpenBSD/dir123& pagetype:new
dir:OpenBSD/dir123
dir2:OpenBSD/dir123
href_dir:OpenBSD str:OpenBSD dir2:dir123
href_dir:OpenBSD/dir123 str:dir123 dir2:(null)
mdict_new OK dir:OpenBSD/dir123
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[38]
buf:page=qwd123123.md&dir=OpenBSD%2Fdir123
make new file dir:OpenBSD%2Fdir123 page:qwd123123.md
params_urldecode: ret:15 decode:OpenBSD/dir123
strlen dir:16
wikinewform:: fullpath:content/OpenBSD/dir123/qwd123123.md
main.c main() QUERY_STRING:index& pagetype:index
main.c main() QUERY_STRING:new& pagetype:new
mdict_new OK dir:(null)
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[21]
buf:page=d2d2d2d2d2d%2Cmd
make new file dir:(null) page:d2d2d2d2d2d%2Cmd
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[19]
buf:page=d2d2d2d2d2d.md
make new file dir:(null) page:d2d2d2d2d2d.md
main.c main() QUERY_STRING:index& pagetype:index
main.c main() QUERY_STRING:index&d=OpenBSD& pagetype:index
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
main.c main() QUERY_STRING:new&d=OpenBSD& pagetype:new
dir:OpenBSD
dir2:OpenBSD
href_dir:OpenBSD str:OpenBSD dir2:(null)
mdict_new OK dir:OpenBSD
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[29]
buf:page=qwd123123.md&dir=OpenBSD
make new file dir:OpenBSD page:qwd123123.md
params_urldecode: ret:8 decode:OpenBSD
strlen dir:7
418 wikinewform:: fullpath:content
424 wikinewform:: fullpath:content/OpenBS/
wikinewform:: fullpath:content/OpenBS/qwd123123.md



main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[29]
buf:page=qwd123123.md&dir=OpenBSD
make new file dir:OpenBSD page:qwd123123.md
params_urldecode: ret:8 decode:OpenBSD
strlen dir:7
418 wikinewform:: dir:OpenBS fullpath:content
424 wikinewform:: fullpath:content/OpenBS/
wikinewform:: fullpath:content/OpenBS/qwd123123.md
main.c main() QUERY_STRING:index& pagetype:index
main.c main() QUERY_STRING:index&d=BSD& pagetype:index
dir:BSD
dir2:BSD
href_dir:BSD str:BSD dir2:(null)
main.c main() QUERY_STRING:index& pagetype:index
main.c main() QUERY_STRING:index&d=dev& pagetype:index
dir:dev
dir2:dev
href_dir:dev str:dev dir2:(null)
main.c main() QUERY_STRING:new&d=dev& pagetype:new
dir:dev
dir2:dev
href_dir:dev str:dev dir2:(null)
mdict_new OK dir:dev
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[18]
buf:page=ad.md&dir=dev
make new file dir:dev page:ad.md
params_urldecode: ret:4 decode:dev
strlen dir:3
418 wikinewform:: dir:de fullpath:content
424 wikinewform:: fullpath:content/de/
wikinewform:: fullpath:content/de/ad.md
main.c main() QUERY_STRING:index&d=dev& pagetype:index
dir:dev
dir2:dev
href_dir:dev str:dev dir2:(null)
main.c main() QUERY_STRING:index&d=dev/lang& pagetype:index
dir:dev/lang
dir2:dev/lang
href_dir:dev str:dev dir2:lang
href_dir:dev/lang str:lang dir2:(null)
main.c main() QUERY_STRING:new&d=dev/lang& pagetype:new
dir:dev/lang
dir2:dev/lang
href_dir:dev str:dev dir2:lang
href_dir:dev/lang str:lang dir2:(null)
mdict_new OK dir:dev/lang
main.c main() QUERY_STRING:newform pagetype:newform
wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[32]
buf:page=qwd123123.md&dir=dev%2Flang
make new file dir:dev%2Flang page:qwd123123.md
params_urldecode: ret:137 decode:dev/lang
strlen dir:138
418 wikinewform:: dir:dev/lang fullpath:content
424 wikinewform:: fullpath:content/dev/lang/
wikinewform:: fullpath:content/dev/lang/qwd123123.md



^[[A^[[A



*/


