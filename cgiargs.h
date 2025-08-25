#ifndef CGIARGS_H
#define CGIARGS_H

#define STB_DS_IMPLEMENTATION
#include ".stb_ds_cgiargs.h"
#include <string.h>
#include "utils.c"
#include <errno.h>

char **
get_cgiargs(const char *env_var)
{
     char *str = getenv(env_var);

     if (!str)
     {
	  strerror(errno);
	  exit(-2);
     }

/*
  "d1=&d2=&d3=&vendor=apple&product=&orderby=&da=desc&sg=&eg=&j1=" =>
  { "d1=", "d2=", "d3=", "vendor=apple", "product=", "orderby=", "da=desc", "sg=", "eg=", "j1=" }
*/
     char **b = {0};
     char *token;
     token = strtok(str, "&");
     while (token != NULL)
     {
	  arrput(b, token);
	  token = strtok(NULL, "&");
     }

/*
  { "d1=", "d2=", "d3=", "vendor=apple", "product=", "orderby=", "da=desc", "sg=", "eg=", "j1=" } =>
  { "d1", "", "d2", "", "d3", "", "vendor", "apple", "product", "", "orderby", "", "da", "desc", "sg", "", "eg", "", "j1", "" }

*/
     char **d = {0};
     char *value2 = NULL;
     for (int i = 0; i < arrlen(b); i++)
     {
	  strtok_r (b[i], "=", &value2);
	  arrput(d, b[i]);
	  arrput(d, value2);
     }

     for (int i = 0; i < arrlen(d); i++)
     {
	  d[i] = replace_substring(d[i], "+", " ");
	  d[i] = replace_substring(d[i], "%3A", ":");
	  d[i] = replace_substring(d[i], "%2F", "/");
	  d[i] = replace_substring(d[i], "%2C", ",");
	  d[i] = replace_substring(d[i], "%28", "(");
	  d[i] = replace_substring(d[i], "%29", ")");
	  d[i] = replace_substring(d[i], "%5B", "[");
	  d[i] = replace_substring(d[i], "%5D", "]");
	  d[i] = replace_substring(d[i], "%3B", ";");
	  d[i] = replace_substring(d[i], "%40", "@");
     }

     arrfree(b);
     return d;
}

#endif
