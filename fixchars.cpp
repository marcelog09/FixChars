// -----------------------------------------------------
//
//  FixChars Plugin v. 0.1 beta
//  by ScriptHunter
//
//  Contribute:
//      https://github.com/scripthunter7/FixChars
//
//
// -----------------------------------------------------

#include "fixchars.h"

int Fixchars_FixCharacter(int chr) {
    switch (chr) {
        case 161: return 94;
        case 176: return 124;
        case 192: return 128;
        case 193: return 129;
        case 194: return 130;
        case 196: return 131;
        case 198: return 132;
        case 199: return 133;
        case 200: return 134;
        case 201: return 135;
        case 202: return 136;
        case 203: return 137;
        case 204: return 138;
        case 205: return 139;
        case 206: return 140;
        case 207: return 141;
        case 210: return 142;
        case 211: return 143;
        case 212: return 144;
        case 213: return 144;
        case 214: return 145;
        case 217: return 146;
        case 218: return 147;
        case 219: return 148;
        case 220: return 149;
        case 223: return 150;
        case 224: return 151;
        case 225: return 152;
        case 226: return 153;
        case 228: return 154;
        case 230: return 155;
        case 231: return 156;
        case 232: return 157;
        case 233: return 158;
        case 234: return 159;
        case 235: return 160;
        case 236: return 161;
        case 237: return 162;
        case 238: return 163;
        case 239: return 164;
        case 242: return 165;
        case 243: return 166;
        case 244: return 167;
        case 245: return 167;
        case 246: return 168;
        case 249: return 169;
        case 250: return 170;
        case 251: return 171;
        case 252: return 172;
        case 209: return 173;
        case 241: return 174;
        case 191: return 175;
	}
    return chr;
}

int Fixchars_FixString(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = Fixchars_FixCharacter((unsigned char)str[i]);
        i++;
    }
    return i+1;
}

// We need to store addresses of original functions
AMX_NATIVE 
    GameTextForAll,
    GameTextForPlayer,
    CreateMenu,
    SetMenuColumnHeader,
    AddMenuItem,
    TextDrawCreate,
    CreatePlayerTextDraw,
    TextDrawSetString,
    PlayerTextDrawSetString;

void FixStringParam(int str_param_index, cell* params, AMX* amx) {
    char *str;
    amx_GetCString(amx, params[str_param_index], str);
    int len = Fixchars_FixString(str);
    amx_SetCString(amx, params[str_param_index], str, len);
}

// https://wiki.sa-mp.com/wiki/GameTextForAll
cell AMX_NATIVE_CALL Fixchars_GameTextForAll(AMX* amx, cell* params) {
    CHECK_PARAMS_EQ(params, 3);
    FixStringParam(1, params, amx); // which parameter is the string? 1st.
    return GameTextForAll(amx, params); // we need to call the original function with the modified string
}

// https://wiki.sa-mp.com/wiki/GameTextForPlayer
cell AMX_NATIVE_CALL Fixchars_GameTextForPlayer(AMX* amx, cell* params) {
    CHECK_PARAMS_EQ(params, 4);
    FixStringParam(2, params, amx);
    return GameTextForPlayer(amx, params);
}

// https://wiki.sa-mp.com/wiki/CreateMenu
cell AMX_NATIVE_CALL Fixchars_CreateMenu(AMX* amx, cell* params) {
    CHECK_PARAMS_EQ(params, 6);
    FixStringParam(1, params, amx);
    return CreateMenu(amx, params);
}

// https://wiki.sa-mp.com/wiki/SetMenuColumnHeader
cell AMX_NATIVE_CALL Fixchars_SetMenuColumnHeader(AMX* amx, cell* params) {
    CHECK_PARAMS_EQ(params, 3);
    FixStringParam(3, params, amx);
    return SetMenuColumnHeader(amx, params);
}

// https://wiki.sa-mp.com/wiki/AddMenuItem
cell AMX_NATIVE_CALL Fixchars_AddMenuItem(AMX* amx, cell* params) {
    CHECK_PARAMS_EQ(params, 3);
    FixStringParam(3, params, amx);
    return AddMenuItem(amx, params);
}

// https://wiki.sa-mp.com/wiki/TextDrawCreate
cell AMX_NATIVE_CALL Fixchars_TextDrawCreate(AMX* amx, cell* params) {
    CHECK_PARAMS_EQ(params, 3);
    FixStringParam(3, params, amx);
    return TextDrawCreate(amx, params);
}

// https://wiki.sa-mp.com/wiki/CreatePlayerTextDraw
cell AMX_NATIVE_CALL Fixchars_CreatePlayerTextDraw(AMX* amx, cell* params) {
    CHECK_PARAMS_EQ(params, 4);
    FixStringParam(4, params, amx);
    return CreatePlayerTextDraw(amx, params);
}

// https://wiki.sa-mp.com/wiki/TextDrawSetString
cell AMX_NATIVE_CALL Fixchars_TextDrawSetString(AMX* amx, cell* params) {
    CHECK_PARAMS_EQ(params, 2);
    FixStringParam(2, params, amx);
    return TextDrawSetString(amx, params);
}

// https://wiki.sa-mp.com/wiki/PlayerTextDrawSetString
cell AMX_NATIVE_CALL Fixchars_PlayerTextDrawSetString(AMX* amx, cell* params) {
    CHECK_PARAMS_EQ(params, 3);
    FixStringParam(3, params, amx);
    return PlayerTextDrawSetString(amx, params);
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **data) {
    pAMXFunctions = data[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t) data[PLUGIN_DATA_LOGPRINTF];
    logprintf(" * Fixchars plugin was loaded.");
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    logprintf(" * Fixchars plugin was unloaded.");
}

AMX_NATIVE_INFO PluginNatives[] = {
    {0, 0}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
    amx_Redirect(amx, "GameTextForAll", (ucell)Fixchars_GameTextForAll, &GameTextForAll);
    amx_Redirect(amx, "GameTextForPlayer", (ucell)Fixchars_GameTextForPlayer, &GameTextForPlayer);
    amx_Redirect(amx, "CreateMenu", (ucell)Fixchars_CreateMenu, &CreateMenu);
    amx_Redirect(amx, "SetMenuColumnHeader", (ucell)Fixchars_SetMenuColumnHeader, &SetMenuColumnHeader);
    amx_Redirect(amx, "AddMenuItem", (ucell)Fixchars_AddMenuItem, &AddMenuItem);
    amx_Redirect(amx, "TextDrawCreate", (ucell)Fixchars_TextDrawCreate, &TextDrawCreate);
    amx_Redirect(amx, "CreatePlayerTextDraw", (ucell)Fixchars_CreatePlayerTextDraw, &CreatePlayerTextDraw);
    amx_Redirect(amx, "TextDrawSetString", (ucell)Fixchars_TextDrawSetString, &TextDrawSetString);
    amx_Redirect(amx, "PlayerTextDrawSetString", (ucell)Fixchars_PlayerTextDrawSetString, &PlayerTextDrawSetString);
    //logprintf(" * [Fixchars] Functions successfully redirected.");
    return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
    return AMX_ERR_NONE;
}