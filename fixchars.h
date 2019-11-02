#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#define CHECK_PARAMS_EQ(m,n) do{if(m[0] != n * 4){logprintf("Fixchars plugin: Incorrect parameters passed, %d != %d.", m[0] / 4, n);return 0;}}while(0)

int AMXAPI amx_GetCString(AMX *amx, cell param, char *&dest);
int AMXAPI amx_SetCString(AMX *amx, cell param, const char *str, int len);
void AMXAPI amx_Redirect(AMX *amx, char *from, ucell to, AMX_NATIVE *store);

typedef void (*logprintf_t)(char* format, ...);

logprintf_t logprintf;
extern void *pAMXFunctions;

