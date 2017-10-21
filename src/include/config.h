
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>

#include "common.h"

const char * DEFAULT_KEYWORD = "default";
const char * FRONTEND_KEYWORD = "frontend";
const char * BACKEND_KEYWORD = "backend";

void parse_cfg_file(FRONTEND ** FRONTENDS, BACKEND ** BACKENDS, char * cfg_path);

BACKEND * parse_backend_block(char * buffer);
BACKEND_SERVER * parse_backend_server_line(char * buffer);
