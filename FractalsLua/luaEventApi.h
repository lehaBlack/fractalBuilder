#pragma once
#include "luaLibs.h"
//Winapi 'Event' lua library:
//Create:  Event.Create(string: name, bool: initialState) or    --E name:name,    initializeState:initialState
//         Event.Create(bool: initialState,string: name) or     --E name:name,    initializeState:initialState
//         Event.Create(string: name) or                        --E name:name,    initializeState:false
//         Event.Create(bool: initialState) or                  --E name:nonamed, initializeState:initialState
//         Event.Create()                                       --E name:nonamed, initializeState:false
//    retValue: userdata: winapiEvent (or nil if filed)

//Wait:    Event.Wait(userdata: winapiEvent) or                --event:winapiEvent, timeout:0
//         Event.Wait(userdata: winapiEvent, integer: delay)   --event:winapiEvent, timeout:delay
//    retValue: boolean: waitState

//Set:     Event.Set(userdata: winapiEvent)                    --event:winapiEvent
//    retValue: boolean: SetEventState

//Reset:   Event.Reset(userdata: winapiEvent)                  --event:winapiEvent
//    retValue: boolean: ResetEventState
//Destroy: Event.Destroy(userdata: winapiEvent)                --event:winapiEvent
//    retValue: boolean: CloseHandle
void openEventLib(lua_State *L);