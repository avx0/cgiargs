#include "../cgiargs.h"
#include <stdio.h>

int
main()
{
     char **d = get_cgiargs("QUERY_STRING");
     for (int i = 0; i < arrlen(d); i++) printf("['%s']\n", d[i]);
     arrfree(d);
}
