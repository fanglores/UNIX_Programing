#include "lib_dbg.c"

int main ()
{
	dbg_open();

	const char* msg = "Hello, ipc world!";
	dbg_write(msg);

	dbg_close();
}
