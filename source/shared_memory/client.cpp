#include "lib_dbg.c"

int main()
{
	dbg_open();
	
	printf ("shared memory value %s\n", ap);

	dbg_close();
}
