#include "cell_image.h"

int feed_bitmap[] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff
,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff
,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff
,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff
,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff
,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff
,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00
,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
int cell_bitmap[] = {0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff
,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff
,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff
,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff
,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00
,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00
,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00
,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00
,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00
,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00
,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff
,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff
,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff
,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff
};
int mothercell_bitmap[] = {0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0xff
,0xff,0xff,0x00,0xff,0xff,0x00,0xff,0x00,0x00,0xff,0x00,0xff,0xff,0x00,0xff,0xff
,0xff,0x00,0xff,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0xff,0x00,0xff
,0xff,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0xff
,0x00,0xff,0x00,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0x00,0xff,0x00
,0x00,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0x00
,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00
,0x00,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0x00
,0x00,0xff,0x00,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0x00,0xff,0x00
,0xff,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0xff
,0xff,0x00,0xff,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0xff,0x00,0xff
,0xff,0xff,0x00,0xff,0xff,0x00,0xff,0x00,0x00,0xff,0x00,0xff,0xff,0x00,0xff,0xff
,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff
};
int collector_bitmap[] = {0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff
,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff
,0xff,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0xff
,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff
,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00
,0x00,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00
,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff
,0xff,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0xff
,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff
,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff
};
int decomposers_bitmap[] = {0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff
,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff
,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff
,0xff,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0xff
,0xff,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0xff
,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00
,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00
,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00
,0xff,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0xff
,0xff,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0xff
,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff
,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff
,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff
};