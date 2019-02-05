#ifndef HACK_LAGSERVER
#define HACK_LAGSERVER
#pragma once
#include "Main.hxx"
extern char *GetRandomStringPathLinux();

class CHackServer
{
public:

    void SendFile( const char* sPathClient , const char* sPathServer );
    void Create();
    void Delete();
    static HEX __stdcall Thread_SendFile( Pointer pSomething );
    HANDLE hThread;
}extern *HackServer;

#endif