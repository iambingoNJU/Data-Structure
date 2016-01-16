#include <stdio.h>
#include "color.h"

int main()
{
	printf(FONT_COLOR_L_BLUE "l-blue" COLOR_NONE "\n");
	printf(FONT_COLOR_BLUE "blue" COLOR_NONE "\n");
	printf(FONT_COLOR_PURPLE "cyan" COLOR_NONE "\n");
	printf(BACKGROUND_COLOR_BLACK FONT_COLOR_WHITE "cyan" COLOR_NONE "\n");
	
	return 0;
}
