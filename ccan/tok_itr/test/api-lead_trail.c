#include <ccan/tok_itr/tok_itr.h>
#include <ccan/tap/tap.h>

#include <string.h>

int main(int argc, char *argv[]) {
#	define TOK1 "blah"
#	define TOK2 "@#$%zlk"
#	define TOK3 "(*aksjhdn$"
#	define TOK4 "\"///\\zxkkkkkhs)(*&"
	const char *arr[] = {"", "", TOK1, "", TOK2, "", "", "", TOK3, "", TOK4, "", "", ""};
	char str[128];
	char val[32];
	struct tok_itr itr;
	int i;

	plan_tests( 2*14 + 1 );

	diag("++++lead_trail++++");
#define TOKALL "::" TOK1 "::" TOK2 "::::" TOK3 "::" TOK4 ":::"
	strncpy(str, TOKALL, 128);
	/*diag("str: %s\n", str);*/
	diag("test token iterator with leading and trailing empty tokens");

	i = 0;
	for(tok_itr_init(&itr, str, ':'); !tok_itr_end(&itr); tok_itr_next(&itr) ) {
		ok1( tok_itr_val(&itr, val, 32) == strlen(arr[i]) );	
		/*diag("%d: '%s'\t(%s) %d\n", i, val, str, strlen(arr[i]) );*/
		ok1( strcmp(val, arr[i++]) == 0 );
	}	
	
	diag("test whether iterator modified the string it iterated over");
	ok1( strcmp(str, TOKALL) == 0 );

	diag("----lead_trail----\n#");

	return exit_status();
}