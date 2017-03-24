#pragma once
#include "luaLibs.h"

//Winapi 'Mutex' lua library:
//Create:  Mutex.Create(string: name, bool: initialState) or    --M name:name,    initializeState:initialState
//         Mutex.Create(bool: initialState,string: name) or     --M name:name,    initializeState:initialState
//         Mutex.Create(string: name) or                        --M name:name,    initializeState:free
//         Mutex.Create(bool: initialState) or                  --M name:nonamed, initializeState:initialState
//         Mutex.Create()                                       --M name:nonamed, initializeState:free
//    retValue: userdata: winapiMutex (or nil if filed)

//tryLock: Mutex.tryLock(userdata: winapiMutex) or              --mutex:winapiMutex, timeout:INFINITE
//         Mutex.tryLock(userdata: winapiMutex, integer: delay) --mutex:winapiMutex, timeout:delay
//    retValue: boolean: waitState

//Release: Mutex.Release(userdata: winapiMutex)                 --mutex:winapiMutex
//    retValue: boolean: ReleaseMutexState

//Destroy: Mutex.Destroy(userdata: winapiMutex)				    --mutex:winapiMutex
//    retValue: boolean: CloseHandle
void openMutexLib(lua_State *L);