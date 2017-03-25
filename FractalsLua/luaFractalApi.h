#pragma once
#include "luaLibs.h"

//Fractal streams lua library:

//createFreeFractalStream(integer: streamSize)
//    retValue: userdata: stream (or nil if filed)

//createFractalStream(integer: t1,integer: t2,...,integer: tn)
//    retValue: userdata: stream{t1,t2,...,tn} (or nil if filed)

//createFractalState(userdata: stream)
//    retValue: userdata: state (or nil if filed)

//freeFractalStream(userdata: stream)
//    retValue: boolean: result

//setFractalStreamTocken(userdata: stream,integer: position, integer: tocken)
//    retValue: boolean: result

//setReplaceTockenData(userdata: state,integer: tocken, userdata: stream)
//    retValue: boolean: result

//newLevel(userdata: state)
//    retValue: boolean: result

//stream_eos(userdata: stream)
//    retValue: boolean: end of stream

//stream_reset(userdata: stream)
//    retValue: boolean: result

//stream_peek(userdata: stream)
//    retValue: boolean: result, integer: tocken

//stream_get(userdata: stream)
//    retValue: boolean: result, integer: tocken
void openFractalLib(lua_State *L);