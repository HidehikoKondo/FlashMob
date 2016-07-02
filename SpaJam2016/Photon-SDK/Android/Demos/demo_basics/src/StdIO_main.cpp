#include "BasicsApplication.h"
#include "StdIO_UIListener.h"

int main()
{
	BasicsApplication::run(new StdIO_UIListener());
}