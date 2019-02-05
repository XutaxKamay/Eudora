#include "Includes.hxx"
#include "Main.hxx"

inline int CGlobalVarsBase::GetNetworkBase( int nTick , int nEntity )
{
    int nEntityMod = nEntity % nTimestampRandomizeWindow;
    int nBaseTick = nTimestampNetworkingBase * ( int ) ( ( nTick - nEntityMod ) / nTimestampNetworkingBase );
    return nBaseTick;
}

inline CGlobalVarsBase::CGlobalVarsBase( bool bIsClient ) :
    m_bClient( bIsClient ) ,
    nTimestampNetworkingBase( 100 ) ,
    nTimestampRandomizeWindow( 32 )
{}

inline bool CGlobalVarsBase::IsClient() const
{
    return m_bClient;
}

inline bool CGlobalVarsBase::IsRemoteClient() const
{
    return m_bRemoteClient;
}

inline CGlobalVars::CGlobalVars( bool bIsClient ) :
    CGlobalVarsBase( bIsClient )
{
    serverCount = 0;
}