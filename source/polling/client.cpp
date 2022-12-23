#include <unistd.h>

#include "lib_dbg.c"

int main ()
{
	dbg_open();

	const char* msg = "Hello, polling world!";
	while (true)
	{
		sleep(3);
		dbg_write(msg);
	}

	dbg_close();
}
