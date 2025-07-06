#include "main.h"
#include "renderer.h"
#include "meshField.h"

float g_FieldHeight[42][42] 
{
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f,1.0f},
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f },
	{1.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 1.0f, 3.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 1.0f, 3.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 3.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, -1.0f, 0.0f, 0.0f, -2.0f, -3.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, -1.0f, 0.0f ,0.0f, -1.0f, -3.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, -1.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, -3.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f     },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, -1.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f, -1.0f, -1.0f, -1.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
																															
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f,1.0f},
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f },
	{1.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 1.0f, 3.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 1.0f, 3.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 1.0f, 3.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 1.0f, 3.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 3.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 3.0f, 2.0f, -1.0f, 0.0f, 0.0f, -2.0f, -3.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, -1.0f, 0.0f ,0.0f, -1.0f, -3.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, -2.0f ,-2.0f, -2.0f, -2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, -1.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, -1.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, -3.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 5.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f     },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 5.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 5.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 1.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 5.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 5.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    },
	{1.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, -1.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, -1.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 0.0f, 0.0f ,0.0f, -1.0f, -1.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 0.0f, 0.0f ,0.0f, -1.0f, -1.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,-1.0f, -1.0f, -1.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,-1.0f, -1.0f, -1.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f },
	{1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, -1.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, -1.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f   },
	{1.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 4.0f, 3.0f, 3.0f, 3.0f, 2.0f, 2.0f, 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f    }
};								   
float MeshField::GetHeight(XMFLOAT3 Position)
{
	int x, z;
	//�u���b�N�ԍ��Z�o
	x = Position.x / 5 + 20;
	z = Position.z / -5 + 20;

	XMFLOAT3 pos0, pos1, pos2, pos3;
	pos0 = m_vertex[x][z].Position;
	pos1 = m_vertex[x + 1][z].Position;
	pos2 = m_vertex[x][z + 1].Position;
	pos3 = m_vertex[x + 1][z + 1].Position;

	XMFLOAT3 v12, v1p;
	v12.x = pos2.x - pos1.x;
	v12.y = pos2.y - pos1.y;
	v12.z = pos2.z - pos1.z;

	v1p.x = Position.x - pos1.x;
	v1p.y = Position.y - pos1.y;
	v1p.z = Position.z - pos1.z;

	//�O��
	float cy = v12.z * v1p.x - v12.x * v1p.z;

	float py;
	XMFLOAT3 n;
	if (cy > 0.0f)
	{
		//����|���S��
		XMFLOAT3 v10;
		v10.x = pos0.x - pos1.x;
		v10.y = pos0.y - pos1.y;
		v10.z = pos0.z - pos1.z;

		//�O��
		n.x = v10.y * v12.z - v10.z * v12.y;
		n.y = v10.z * v12.x - v10.x * v12.z;
		n.z = v10.x * v12.y - v10.y * v12.x;

	}
	else
	{
		//�����|���S��
		XMFLOAT3 v13;
		v13.x = pos0.x - pos1.x;
		v13.y = pos0.y - pos1.y;
		v13.z = pos0.z - pos1.z;

		//�O��
		n.x = v12.y * v13.z - v12.z * v13.y;
		n.y = v12.z * v13.x - v12.x * v13.z;
		n.z = v12.x * v13.y - v12.y * v13.x;

	}

	//�����擾
	py = -((Position.x - pos1.x) * n.x + (Position.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;
}
void MeshField::Init()
{
	for (int x = 0; x < 42; x++) {
		for (int z = 0; z < 42; z++) {
			m_vertex[x][z].Position = XMFLOAT3((x - 20) * 5.0f,
										g_FieldHeight[x][z], 
										(z - 20) * -5.0f);
			m_vertex[x][z].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_vertex[x][z].Diffuse = XMFLOAT4(1.0f, 1.0f, 0.5f, 1.0f);
			m_vertex[x][z].TexCoord = XMFLOAT2(x, z);
		}
	}

	//�@���x�N�g���Z�o
	for (int x = 1; x < 41; x++)
	{
		for (int z = 1; z < 41; z++)
		{
			XMFLOAT3 vx, vz, vn;
			vx.x = m_vertex[x + 1][z].Position.x - m_vertex[x - 1][z].Position.x;
			vx.y = m_vertex[x + 1][z].Position.y - m_vertex[x - 1][z].Position.y;
			vx.z = m_vertex[x + 1][z].Position.z - m_vertex[x - 1][z].Position.z;

			vz.x = m_vertex[x][z - 1].Position.x - m_vertex[x][z + 1].Position.x;
			vz.y = m_vertex[x][z - 1].Position.y - m_vertex[x][z + 1].Position.y;
			vz.z = m_vertex[x][z - 1].Position.z - m_vertex[x][z + 1].Position.z;

			//�O��
			vn.x = vz.y * vx.z - vz.z * vx.y;
			vn.y = vz.z * vx.x - vz.x * vx.z;
			vn.z = vz.x * vx.y - vz.y * vx.x;

			//���K��(�������P�ɂ���)
			float len = sqrtf(vn.x * vn.x + vn.y * vn.y + vn.z * vn.z);
			vn.x /= len;
			vn.y /= len;
			vn.z /= len;

			m_vertex[x][z].Normal = vn;
		}
	}
	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 42 * 42;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = m_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffur);

		//�C���f�b�N�X�o�b�t�@����
	{
		unsigned int index[((42 + 1) * 2) * 41 - 2];

		int i = 0;
		for (int x = 0; x < 41; x++)
		{
			for (int z = 0; z < 42; z++)
			{
				index[i] = x * 42 + z;
				i++;

				index[i] = (x + 1) * 42 + z;
				i++;
			}

			if (x == 40)
				break;

			index[i] = (x + 1) * 42 + 41;
			i++;
			index[i] = (x + 1) * 42;
			i++;
		}

		//���_�o�b�t�@����
		D3D11_BUFFER_DESC bd{};
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((43 * 2) * 41 - -2);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	//�e�N�X�`���ǂݍ���
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\Texture\\greenground.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");
}

void MeshField::Uninit()
{
	m_VertexBuffur->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void MeshField::Update()
{

}

void MeshField::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//���[���h�}�g���N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	trans = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffur, &stride, &offset);

	//�C���f�b�N�X�o�b�t�@�ݒ�
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	//Renderer::GetDeviceContext()->Draw(21 * 21, 0);
	Renderer::GetDeviceContext()->DrawIndexed((43 * 2) * 41 - 2, 0, 0);
}
