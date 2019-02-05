#include "Includes.hxx"
#include "Main.hxx"

CHackUserCommands* HackUserCommands = new CHackUserCommands();

constexpr float max_distance = 8192.0f;

void CHackUserCommands::AutoBhop( C_BasePlayer* pPlayer , CUserCmd* cmd )
{
    if ( pPlayer == nullptr )
        return;

    if ( !Cvars[ hack_autobhop ]->GetBool() )
        return;

    static bool bOnGround = false , bOnWater = false , bOnLadder = false;
    static bool bOnGroundNext = false , bOnWaterNext = false , bOnLadderNext = false;

    static float flGroundDistance = 0.0f;

    if ( !bIsPredicted )
    {
        auto GetGroundDistance = [] ( C_BasePlayer* pPlayer )
        {
            auto TryTouchGround = [] ( C_BasePlayer* pPlayer , const Vector& start , const Vector& end , const Vector& mins , const Vector& maxs , unsigned int fMask , int collisionGroup , trace_t& pm )
            {
                Ray ray;
                ray.Init( start , end , mins , maxs );
                CTraceFilterSimple traceFilter( pPlayer , collisionGroup );
                EngineTrace->TraceRay( ray , fMask , &traceFilter , &pm );
            };

            auto TryTouchGroundInQuadrants = [] ( C_BasePlayer* pPlayer , const Vector& start , const Vector& end , unsigned int fMask , int collisionGroup , trace_t& pm )
            {
                auto TryTouchGround = [] ( C_BasePlayer* pPlayer , const Vector& start , const Vector& end , const Vector& mins , const Vector& maxs , unsigned int fMask , int collisionGroup , trace_t& pm )
                {
                    Ray ray;
                    ray.Init( start , end , mins , maxs );
                    CTraceFilterSimple traceFilter( pPlayer , collisionGroup );
                    EngineTrace->TraceRay( ray , fMask , &traceFilter , &pm );
                };

                Vector mins , maxs;
                Vector minsSrc = _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMins() , Vector , pPlayer );
                Vector maxsSrc = _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMaxs() , Vector , pPlayer );

                float fraction = pm.fraction;
                Vector endpos = pm.endpos;

                // Check the -x, -y quadrant
                mins = minsSrc;
                maxs.Init( min( 0 , maxsSrc.x ) , min( 0 , maxsSrc.y ) , maxsSrc.z );
                TryTouchGround( pPlayer , start , end , mins , maxs , fMask , collisionGroup , pm );
                if ( pm.hit_entity && pm.plane.normal[ 2 ] >= 0.7 )
                {
                    pm.fraction = fraction;
                    pm.endpos = endpos;
                    return;
                }

                // Check the +x, +y quadrant
                mins.Init( max( 0 , minsSrc.x ) , max( 0 , minsSrc.y ) , minsSrc.z );
                maxs = maxsSrc;
                TryTouchGround( pPlayer , start , end , mins , maxs , fMask , collisionGroup , pm );
                if ( pm.hit_entity && pm.plane.normal[ 2 ] >= 0.7 )
                {
                    pm.fraction = fraction;
                    pm.endpos = endpos;
                    return;
                }

                // Check the -x, +y quadrant
                mins.Init( minsSrc.x , max( 0 , minsSrc.y ) , minsSrc.z );
                maxs.Init( min( 0 , maxsSrc.x ) , maxsSrc.y , maxsSrc.z );
                TryTouchGround( pPlayer , start , end , mins , maxs , fMask , collisionGroup , pm );
                if ( pm.hit_entity && pm.plane.normal[ 2 ] >= 0.7 )
                {
                    pm.fraction = fraction;
                    pm.endpos = endpos;
                    return;
                }

                // Check the +x, -y quadrant
                mins.Init( max( 0 , minsSrc.x ) , minsSrc.y , minsSrc.z );
                maxs.Init( maxsSrc.x , min( 0 , maxsSrc.y ) , maxsSrc.z );
                TryTouchGround( pPlayer , start , end , mins , maxs , fMask , collisionGroup , pm );
                if ( pm.hit_entity && pm.plane.normal[ 2 ] >= 0.7 )
                {
                    pm.fraction = fraction;
                    pm.endpos = endpos;
                    return;
                }

                pm.fraction = fraction;
                pm.endpos = endpos;
            };

            Vector point = pPlayer->GetAbsOrigin();
            point.z -= max_distance;

            Vector bumpOrigin;
            bumpOrigin = pPlayer->GetAbsOrigin();
            trace_t pm;
            // Try and move down.
            TryTouchGround( pPlayer , bumpOrigin , point , _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMins() , Vector , pPlayer )
                            , _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMaxs() , Vector , pPlayer ) , MASK_PLAYERSOLID , COLLISION_GROUP_PLAYER_MOVEMENT , pm );

            // Was on ground, but now suddenly am not.  If we hit a steep plane, we are not on ground
            if ( !pm.hit_entity || pm.plane.normal[ 2 ] < 0.7 )
            {
                // Test four sub-boxes, to see if any of them would have found shallower slope we could actually stand on
                TryTouchGroundInQuadrants( pPlayer , bumpOrigin , point , MASK_PLAYERSOLID , COLLISION_GROUP_PLAYER_MOVEMENT , pm );
            }

            return ( ( point - bumpOrigin ) * pm.fraction ).Length();
        };

        flGroundDistance = GetGroundDistance( pPlayer );

        //EngineClient->Con_NPrintf( 1 , "%f" , flGroundDistance );

        if (
            ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::hGroundEntity() , CBaseHandle , pPlayer ).Get() != nullptr )
            )
        {
            bOnGround = true;
        }
        else
        {
            bOnGround = false;
        }

        if ( ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::nWaterLevel() , unsigned short , pPlayer ) > 1 ) )
        {
            bOnWater = true;
        }
        else
        {
            bOnWater = false;
        }

        if ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::nWaterLevel() - 2 , unsigned short , pPlayer ) == MOVETYPE_LADDER )
        {
            bOnLadder = true;
        }
        else
        {
            bOnLadder = false;
        }
    }

    if ( bIsPredicted )
    {
        if (
            ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::hGroundEntity() , CBaseHandle , pPlayer ).Get() != nullptr )
            )
        {
            bOnGroundNext = true;
        }
        else
        {
            bOnGroundNext = false;
        }

        if ( ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::nWaterLevel() , unsigned short , pPlayer ) > 1 ) )
        {
            bOnWaterNext = true;
        }
        else
        {
            bOnWaterNext = false;
        }

        if ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::nWaterLevel() - 2 , unsigned short , pPlayer ) == MOVETYPE_LADDER )
        {
            bOnLadderNext = true;
        }
        else
        {
            bOnLadderNext = false;
        }
    }

    int min_ground_wait_ticks = Cvars[ hack_autobhop_onground_minwait ]->GetInt() , max_ground_wait_ticks = Cvars[ hack_autobhop_onground_maxwait ]->GetInt();

    int min_jump_pressed_inair = Cvars[ hack_autobhop_inair_minwait ]->GetInt() , max_jump_pressed_inair = Cvars[ hack_autobhop_inair_maxwait ]->GetInt();

    int min_perfect_jumps = Cvars[ hack_autobhop_perf_min ]->GetInt() , max_perfect_jumps = Cvars[ hack_autobhop_perf_max ]->GetInt();

    static int RandWait = Offsets->RandomInt( min_ground_wait_ticks , max_ground_wait_ticks );

    static int RandWaitPerf = Offsets->RandomInt( min_perfect_jumps , max_perfect_jumps );

    static bool bWasOnGround = false;

    static bool bLastOnGroundNext = false;

    static bool bWantPerf = true;

    static int bLastButtons = 0;

    if ( old_cmd.buttons & IN_JUMP )
    {
        if ( Cvars[ hack_autobhop ]->GetInt() >= 2 )
        {
            static bool bCanBlock = false;

            if ( bOnGround )
            {
                if ( bWantPerf )
                {
                    cmd->buttons |= IN_JUMP;

                    if ( bWasOnGround && bCanBlock )
                    {
                        cmd->buttons &= ~IN_JUMP;
                        if ( bIsPredicted )
                            bCanBlock = false;
                    }

                    if ( !bIsPredicted )
                        RandWaitPerf = Offsets->RandomInt( min_perfect_jumps , max_perfect_jumps );

                    if ( bIsPredicted )
                        bWantPerf = false;
                }
                else
                {
                    if ( !bIsPredicted )
                        RandWait = Offsets->RandomInt( min_ground_wait_ticks , max_ground_wait_ticks );

                    static int iCount = 0;
                    if ( iCount >= RandWait )
                    {
                        if ( bIsPredicted )
                            iCount = 0;

                        cmd->buttons |= IN_JUMP;
                    }
                    else
                    {
                        if ( bIsPredicted )
                            iCount++;

                        cmd->buttons &= ~IN_JUMP;
                    }
                }

                //if ( bIsPredicted )
                  //  bCanBlock = cmd->buttons & IN_JUMP;

                /*if ( bLastButtons & IN_JUMP )
                {
                    cmd->buttons &= ~IN_JUMP;
                }*/
            }
            else
            {
                //bCanBlock = false;

                cmd->buttons &= ~IN_JUMP;

                if ( !bIsPredicted )
                    RandWait = Offsets->RandomInt( min_jump_pressed_inair , max_jump_pressed_inair );

                static float flWaitGroundDistance = 0.0f;

                if ( !bIsPredicted )
                    flWaitGroundDistance = Offsets->RandomFloat( Cvars[ hack_autobhop_ground_dist_min ]->GetFloat() , Cvars[ hack_autobhop_ground_dist_max ]->GetFloat() );

                if ( flGroundDistance <= 0.001f )
                {
                    cmd->buttons &= ~IN_JUMP;
                }
                else if ( flGroundDistance <= flWaitGroundDistance )
                {
                    static int iCount = 0;
                    if ( iCount >= RandWait )
                    {
                        if ( bIsPredicted )
                            iCount = 0;
                        cmd->buttons |= IN_JUMP;
                    }
                    else
                    {
                        if ( bIsPredicted )
                            iCount++;
                        cmd->buttons &= ~IN_JUMP;
                    }
                }

                if ( bOnLadderNext || bOnWaterNext || bOnGroundNext )
                {
                    if ( min_ground_wait_ticks == 0 && max_ground_wait_ticks == 0
                         || ( RandWaitPerf == 0 ) )
                    {
                        cmd->buttons &= ~IN_JUMP;

                        if ( bIsPredicted )
                            bWantPerf = true;
                    }
                    else
                    {
                        static int iCount = 0;
                        if ( iCount >= RandWaitPerf )
                        {
                            if ( bIsPredicted )
                                iCount = 0;

                            cmd->buttons |= IN_JUMP;
                        }
                        else
                        {
                            if ( bIsPredicted )
                                iCount++;

                            cmd->buttons &= ~IN_JUMP;

                            if ( bIsPredicted )
                                bWantPerf = true;
                        }
                    }
                }
            }

            if ( bOnLadder || bOnWater )
            {
                cmd->buttons |= IN_JUMP;
            }
        }
        else
        {
            static bool bCanBlock = false;

            if ( bOnGround )
            {
                //CONSOLEDEBUG( TEXT( "On ground %i  %i \n" ) , iCountPredicted , ( int ) bIsPredicted );

                cmd->buttons |= IN_JUMP;

                if ( bWasOnGround && bCanBlock )
                {
                    cmd->buttons &= ~IN_JUMP;
                    if ( bIsPredicted )
                        bCanBlock = false;
                }

                if ( bIsPredicted )
                    bCanBlock = cmd->buttons & IN_JUMP;
            }
            else
            {
                bCanBlock = false;

                //CONSOLEDEBUG( TEXT( "In air %i  %i \n" ) , iCountPredicted , ( int ) bIsPredicted );

                cmd->buttons &= ~IN_JUMP;

                if ( bWasOnGround && ( !bIsPredicted ) )
                    RandWait = Offsets->RandomInt( 3 , 6 );

                static float flWaitGroundDistance = 0.0f;

                if ( !bIsPredicted )
                    flWaitGroundDistance = Offsets->RandomFloat( 15.0f , 30.0f );

                if ( flGroundDistance <= 0.001f )
                {
                    cmd->buttons &= ~IN_JUMP;
                }
                else if ( flGroundDistance <= flWaitGroundDistance )
                {
                    static int iCount = 0;
                    if ( iCount >= RandWait )
                    {
                        if ( bIsPredicted )
                            iCount = 0;
                        cmd->buttons |= IN_JUMP;
                    }
                    else
                    {
                        if ( bIsPredicted )
                            iCount++;

                        cmd->buttons &= ~IN_JUMP;
                    }
                }

                if ( bOnLadderNext || bOnWaterNext || bOnGroundNext )
                {
                    cmd->buttons &= ~IN_JUMP;
                }
            }

            if ( bOnLadder || bOnWater )
            {
                cmd->buttons |= IN_JUMP;
            }
        }
    }

    /*if ( bLastOnGroundNext != bOnGround && bIsPredicted )
    {
        static int iCount = -1;
        iCount++;
        if ( iCount >= 1 )
            CONSOLEDEBUG( TEXT( "%i Ground prediction error (Last: %i Cur: %i) \n" ) , iCount , ( int ) ( bool ) ( bLastButtons & IN_JUMP ) , ( int ) ( bool ) ( cmd->buttons & IN_JUMP ) );
    }*/

    bWasOnGround = bOnGround;
    bLastOnGroundNext = bOnGroundNext;
    bLastButtons = cmd->buttons;
}

void CHackUserCommands::EdgeJump( C_BasePlayer* pPlayer , CUserCmd* Cmd )
{
    if ( Cvars[ hack_edgejump ]->GetInt() != 0 )
    {
        static bool bOnGround = true , bOnWater = true , bOnLadder = true;

        if ( !bIsPredicted )
        {
            if (
                ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::hGroundEntity() , CBaseHandle , pPlayer ).Get() != nullptr )
                )
            {
                bOnGround = true;
            }
            else
            {
                bOnGround = false;
            }

            if ( ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::nWaterLevel() , unsigned short , pPlayer ) > 1 ) )
            {
                bOnWater = true;
            }
            else
            {
                bOnWater = false;
            }

            if ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::nWaterLevel() - 2 , unsigned short , pPlayer ) == MOVETYPE_LADDER )
            {
                bOnLadder = true;
            }
            else
            {
                bOnLadder = false;
            }
        }

        static bool bNextOnGround = true;

        if ( bIsPredicted )
        {
            if (
                ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::hGroundEntity() , CBaseHandle , pPlayer ).Get() != nullptr )
                )
            {
                bNextOnGround = true;
            }
            else
            {
                bNextOnGround = false;
            }
        }

        bool bShouldJump = ( bOnGround && !bNextOnGround );

        if ( !bOnWater && !bOnLadder && bShouldJump )
            Cmd->buttons |= IN_JUMP;
    }
}

//void CHackUserCommands::TimeScale( C_BasePlayer* pPlayer , CUserCmd*Cmd )
//{
//	float flWaitTime = 1.0f / Cvars[ hack_timescale ]->GetFloat();
//
//	bTimeScale = ( flWaitTime > 1.0f );
//
//	if ( bTimeScale )
//	{
//		bShouldInvertTimeScale = ( flWaitTime < 2.0f );
//
//		if ( bShouldInvertTimeScale )
//			iTicksRemainderTimeScale = ( int ) ( ( ( 1.0f - ( flWaitTime - 1.0f ) ) / ( flWaitTime - 1.0f ) ) + 0.5f ) + 1;
//		else
//			iTicksRemainderTimeScale = ( int ) flWaitTime;
//
//		bPausing = bShouldInvertTimeScale ? ( Cmd->command_number % iTicksRemainderTimeScale ) == 0 : ( Cmd->command_number % iTicksRemainderTimeScale );
//
//		if ( bPausing )
//			Cmd->tick_count = TICKCOUNT_PAUSE;
//	}
//}

void CHackUserCommands::AngelStrafe( C_BasePlayer* pPlayer , CUserCmd* Cmd )
{
    static bool bSaveAngle = true;

    if ( Cvars[ hack_angelstrafe ]->GetInt() == 1 )
    {
        if ( bSaveAngle )
        {
            a_AngelAngle = Cmd->viewangles;
            bSaveAngle = false;
        }

        Cmd->viewangles = a_AngelAngle;
        MovementFix( pPlayer , Cmd );
    }
    else
    {
        if ( !bSaveAngle )
        {
            EngineClient->SetViewAngles( a_AngelAngle );
            bSaveAngle = true;
        }
    }
}

void CHackUserCommands::MovementFix( C_BasePlayer*pPlayer , CUserCmd* Cmd )
{
    Vector2D vMovements( Cmd->forwardmove , Cmd->sidemove );

    if ( vMovements.Length() == 0 )
        return;

    int m_MoveType = _OffsetManualthis( CBasePlayer::DT_BasePlayer::nWaterLevel() - 2 , unsigned short , pPlayer );
    if ( m_MoveType == MOVETYPE_NOCLIP || m_MoveType == MOVETYPE_OBSERVER )
    {
        float flFactor = 0.0f;

        if ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::iObserverMode() , int , pPlayer ) != OBS_MODE_ROAMING )
        {
            static ConVar *noclipspeed = Cvar->FindVar( "sv_noclipspeed" );
            flFactor = noclipspeed->GetFloat();
        }
        else
        {
            static ConVar *specspeed = Cvar->FindVar( "sv_specspeed" );
            flFactor = specspeed->GetFloat();
        }

        if ( Cmd->buttons & IN_SPEED )
        {
            flFactor /= 2.0f;
        }

        Vector vRealF , vRealR;
        Angle aRealDir = Cmd->viewangles;
        aRealDir.Normalize180();

        AngleToVectors( aRealDir , &vRealF , &vRealR , nullptr );
        vRealF.FastNormalize();
        vRealR.FastNormalize();

        Angle aWishDir = a_FixAngle;
        aWishDir.Normalize180();

        Vector vWishF , vWishR;
        AngleToVectors( aWishDir , &vWishF , &vWishR , nullptr );

        float flForwardMove = old_cmd.forwardmove * flFactor;
        float flSideMove = old_cmd.sidemove * flFactor;
        float flUpMove = old_cmd.upmove * flFactor;

        vWishF.FastNormalize();
        vWishR.FastNormalize();

        Vector vWishVel = vWishF * flForwardMove + vWishR * flSideMove;
        vWishVel[ 2 ] += flUpMove;

        /*
            u = a * x * n + b * y * n
            v = c * x * n + d * y * n
            w = ( e * x * n + f * y * n ) + ( g * n )

            x = -(du-bv)/((bc-ad)n)
            y = (cu-av)/((bc-ad)n)
            g = (a(fv-dw)+b(cw-ev)+u(de-cf))/(bc-ad)n
        */

        Real a = vRealF[ 0 ] , b = vRealR[ 0 ] , c = vRealF[ 1 ] , d = vRealR[ 1 ] , e = vRealF[ 2 ] , f = vRealR[ 2 ];
        Real u = vWishVel[ 0 ] , v = vWishVel[ 1 ] , w = vWishVel[ 2 ];
        Real n = flFactor;
        Real flDivide = ( ( b * c - a * d ) * n );

        if ( flDivide == 0.0f )
            return;

        Real x = -( d * u - b * v ) / flDivide;
        Real y = ( c * u - a * v ) / flDivide;
        Real z = ( a * ( f * v - d * w ) + b * ( c * w - e * v ) + u * ( d * e - c * f ) ) / flDivide;

        Cmd->forwardmove = x;
        Cmd->sidemove = y;
        Cmd->upmove = z;
    }
    else if ( m_MoveType == MOVETYPE_LADDER )
    {
        //???
    }
    else
    {
       // First we compute the vectors like the game is doing, with our current viewangles that are being send to server
       // That's where we should be going server-side.

        Vector vRealF , vRealR;
        Angle aRealDir = Cmd->viewangles;
        aRealDir.Normalize180();

        AngleToVectors( aRealDir , &vRealF , &vRealR , nullptr );
        vRealF[ 2 ] = 0;
        vRealR[ 2 ] = 0;

        vRealF.FastNormalize();
        vRealR.FastNormalize();

        // Ok now we compute the vectors as the gamemovement but this time with our client viewangles.
        // This is where we want to go.

        Angle aWishDir = a_FixAngle;
        aWishDir.Normalize180();

        Vector vWishF , vWishR;
        AngleToVectors( aWishDir , &vWishF , &vWishR , nullptr );

        vWishF[ 2 ] = 0;
        vWishR[ 2 ] = 0;

        vWishF.FastNormalize();
        vWishR.FastNormalize();

        // We now compute our wished velocity based on our current movements.
        Vector vWishVel;
        vWishVel[ 0 ] = vWishF[ 0 ] * old_cmd.forwardmove + vWishR[ 0 ] * old_cmd.sidemove;
        vWishVel[ 1 ] = vWishF[ 1 ] * old_cmd.forwardmove + vWishR[ 1 ] * old_cmd.sidemove;
        vWishVel[ 2 ] = 0;

        /*
            Now we want to compute the corresponding movements to the angles that we're sending to server, and not from our actual client viewangles!
            This is important because otherwhise you would just fix the movements only for your client viewangles, and we don't want that for obvious reasons.
            So basically , vRealVel must be equal to vWishVel, and that no matter what our angles are.
            In details there is two ways of doing it, one is wrong, the other one is correct:

            This one wich is correct:

            vWishF[ 0 ] * Cmd->forwardmove + vWishR[ 0 ] * Cmd->sidemove == vRealF[ 0 ] * unknownforwardmove? + vRealR[ 0 ] * unknownsidemove?
            vWishF[ 1 ] * Cmd->forwardmove + vWishR[ 1 ] * Cmd->sidemove == vRealF[ 1 ] * unknownforwardmove? + vRealR[ 1 ] * unknownsidemove?

            Or this one wich is wrong:

            vWishF[ 0 ] * unknownforwardmove? + vWishR[ 0 ] * unknownsidemove? == vRealF[ 0 ] * Cmd->forwardmove + vRealR[ 0 ] * Cmd->sidemove
            vWishF[ 1 ] * unknownforwardmove? + vWishR[ 1 ] * unknownsidemove? == vRealF[ 1 ] * Cmd->forwardmove + vRealR[ 1 ] * Cmd->sidemove

            Since the server is not using our client viewangles we don't want to guess the movements values of vWishDir!

            Well with these two equations, we can actually get the movements!

            For example in our system:

            a * x + b * y = j * f + k * s
            c * x + d * y = l * f + m * s

            ... The solutions will look horrible, let's optimize that.

            v = a * x + b * y
            w = c * x + d * y

            Looks better.

            Okay let's calculate our solutions now.
            a * x + b * y - v = 0
            c * x + d * y - w = 0

            Let's find x.

            ax + by - v = 0
            ax = -(by -v)
            x = -(by - v) / a

            Okay we have x now, but we need y.
            Let's find it.

            c(-(by - v) / a + dy - w = 0
            -c(by - v) / a + dy - w = 0
            -c(by - v) / a + dy = w
            a( -c(by - v) / a ) + dya = wa
            -c(by - v) + dya = wa
            -cby + cv + dya = wa
            -cby + dya = wa - cv
            y(ad - cb) = wa - cv
            y = (wa - cv) / (ad - cb)

            We finally find y!

            y = (aw - cv) / (ad - cb) ....

            Problem. x have still its y variable in the equation. Let's solve that.

            x = -(b ( (aw - cv) / (ad - cb) ) - v)/a

            Let's simplifiy this...

            -xa = b ( (aw - cv) / (ad - cb) ) - v
            -xa + v = b ( (aw - cv) / (ad - cb) )
            ( -xa + v ) / b = (aw - cv) / (ad - cb)

            y = ( v - xa ) / b

            c * x + d * ( ( v - xa ) / b ) - w = 0
            cx + d * ( ( v - xa ) / b ) = w
            d * ( ( v - xa ) / b ) = w - cx
            ( v - xa ) / b = ( w - cx ) / d
            v - xa = ( bw - bcx ) / d
            d(v - xa) = bw - bcx
            dv - bw = dxa - bcx
            dv - bw = x(da - bc)
            (dv - bw) / (da - bc) = x

            x = (dv - bw) / (ad - bc)

            Funny thing is that we found the same ad - bc as divider for both fiding y and x. Useful for little optimizations.

            Full solutions:

            x = ( d * v - b * w ) / ( a * d - b * c )
            y = ( a * w -  c * v ) / ( a * d - b * c )

            with

            a = vRealF[ 0 ] , b = vRealR[ 0 ] , c = vRealF[ 1 ] , d = vRealR[ 1 ]
            v = vWishVel[ 0 ]
            w = vWishVel[ 1 ]

            This partially fix the z angle, but not complety and is not probably fixable anyway, because it's overriding sidemove and you can't do anything really about it sadly.
            But it still works for some important values!
        */

        Real a = vRealF[ 0 ] , b = vRealR[ 0 ] , c = vRealF[ 1 ] , d = vRealR[ 1 ];
        Real v = vWishVel[ 0 ] , w = vWishVel[ 1 ];

        Real flDivide = ( a * d - b * c );

        if ( flDivide == 0.0f )
            return;

        Real x = ( d * v - b * w ) / flDivide;
        Real y = ( a * w - c * v ) / flDivide;

        Cmd->forwardmove = x;
        Cmd->sidemove = y;
    }

    static ConVar *forwardspeed = Cvar->FindVar( "cl_forwardspeed" );
    static ConVar *sidespeed = Cvar->FindVar( "cl_sidespeed" );
    static ConVar *upspeed = Cvar->FindVar( "cl_upspeed" );

    static Vector vDefaultMovements( ( Real ) atof( forwardspeed->GetDefault() ) ,
        ( Real ) atof( sidespeed->GetDefault() ) , ( Real ) atof( upspeed->GetDefault() ) );

    Cmd->forwardmove = clamp( Cmd->forwardmove , -vDefaultMovements.x , vDefaultMovements.x );
    Cmd->sidemove = clamp( Cmd->sidemove , -vDefaultMovements.y , vDefaultMovements.y );
    Cmd->upmove = clamp( Cmd->upmove , -vDefaultMovements.z , vDefaultMovements.z );

    int oldbuttons = Cmd->buttons;
    Cmd->buttons &= ~IN_LEFT;
    Cmd->buttons &= ~IN_RIGHT;
    Cmd->buttons &= ~IN_MOVELEFT;
    Cmd->buttons &= ~IN_FORWARD;
    Cmd->buttons &= ~IN_BACK;
    Cmd->buttons &= ~IN_MOVERIGHT;

    if ( Cvars[ hack_angelstrafe ]->GetBool() )
        return;

    static int FlipLeft = 1;
    static int FlipRight = 1;
    static int FlipForward = 1;
    static int FlipBack = 1;

    if ( Cmd->sidemove > 0.0f )
    {
        if ( FlipLeft > 0 )
        {
            Cmd->buttons |= IN_MOVELEFT;
            Cmd->buttons |= IN_MOVERIGHT;

            if ( HackUserCommands->bIsPredicted )
                FlipLeft--;
        }
        else
        {
            Cmd->buttons |= IN_MOVERIGHT;
        }

        if ( HackUserCommands->bIsPredicted )
            FlipRight = Offsets->RandomInt( 0 , 3 );
    }

    if ( Cmd->sidemove < 0.0f )
    {
        if ( FlipRight > 0 )
        {
            Cmd->buttons |= IN_MOVELEFT;
            Cmd->buttons |= IN_MOVERIGHT;

            if ( HackUserCommands->bIsPredicted )
                FlipRight--;
        }
        else
        {
            Cmd->buttons |= IN_MOVELEFT;
        }

        if ( HackUserCommands->bIsPredicted )
            FlipLeft = Offsets->RandomInt( 0 , 3 );
    }

    if ( Cmd->forwardmove > 0.0f )
    {
        if ( FlipForward > 0 )
        {
            Cmd->buttons |= IN_BACK;
            Cmd->buttons |= IN_FORWARD;

            if ( HackUserCommands->bIsPredicted )
                FlipForward--;
        }
        else
        {
            Cmd->buttons |= IN_FORWARD;
        }

        if ( HackUserCommands->bIsPredicted )
            FlipBack = Offsets->RandomInt( 0 , 3 );
    }

    if ( Cmd->forwardmove < 0.0f )
    {
        if ( FlipBack > 0 )
        {
            Cmd->buttons |= IN_BACK;
            Cmd->buttons |= IN_FORWARD;
            if ( HackUserCommands->bIsPredicted )
                FlipBack--;
        }
        else
        {
            Cmd->buttons |= IN_BACK;
        }

        if ( HackUserCommands->bIsPredicted )
            FlipForward = Offsets->RandomInt( 0 , 3 );
    }

    if ( Cmd->sidemove == 0.0f )
    {
        if ( ( oldbuttons & IN_MOVELEFT ) && ( oldbuttons & IN_MOVERIGHT ) || ( ( oldbuttons & IN_FORWARD ) && ( oldbuttons & IN_BACK ) ) )
        {
            Cmd->buttons |= IN_MOVERIGHT;
            Cmd->buttons |= IN_MOVELEFT;
        }
        else
        {
            Cmd->buttons &= ~IN_MOVERIGHT;
            Cmd->buttons &= ~IN_MOVELEFT;
        }
    }

    if ( Cmd->forwardmove == 0.0f )
    {
        if ( ( oldbuttons & IN_MOVELEFT ) && ( oldbuttons & IN_MOVERIGHT ) || ( ( oldbuttons & IN_FORWARD ) && ( oldbuttons & IN_BACK ) ) )
        {
            Cmd->buttons |= IN_FORWARD;
            Cmd->buttons |= IN_BACK;
        }
        else
        {
            Cmd->buttons &= ~IN_FORWARD;
            Cmd->buttons &= ~IN_BACK;
        }
    }
}

void CHackUserCommands::Modify( C_BasePlayer* pPlayer , CUserCmd* Cmd )
{
    if ( pPlayer == nullptr )
        return;

    if ( !bIsPredicted )
    {
        MovementRecorder->PreThink( Cmd , pPlayer );
    }

    EdgeJump( pPlayer , Cmd );
    AutoBhop( pPlayer , Cmd );
    AngelStrafe( pPlayer , Cmd );
    //TimeScale( pPlayer , Cmd );

    auto AntiMMAC = [] ( C_BasePlayer* pPlayer , CUserCmd*Cmd )
    {
        Cmd->viewangles.Normalize180();

        static ConVar *pitchdown = Cvar->FindVar( "cl_pitchdown" );
        static ConVar *pitchup = Cvar->FindVar( "cl_pitchup" );
        static Real flPitchDown = ( Real ) atof( pitchdown->GetDefault() );
        static Real flPitchUp = ( Real ) atof( pitchup->GetDefault() );

        Cmd->viewangles.x = clamp( Cmd->viewangles.x , -flPitchUp , flPitchDown );
        Cmd->viewangles.z = 0.0f;
    };

    AntiMMAC( pPlayer , Cmd );

    MovementRecorder->Think( Cmd , pPlayer );

    if ( bIsPredicted )
    {
        // This can be done only after prediction because it does not affect any movements.
        Backtrack->AdjustTickCount( Cmd );
        MovementRecorder->PostThink( Cmd , pPlayer );
        //Cmd->command_number += ( Globals->tickcount - Cmd->tick_count );
    }
}

void CHackUserCommands::ModifyAndUpdate( C_BasePlayer* pPlayer , CUserCmd* Cmd )
{
    bIsPredicted = false;

    old_cmd = *Cmd;
    a_FixAngle = Cmd->viewangles;

    if ( pPlayer != nullptr )
    {
        Modify( pPlayer , Cmd );
        Update( pPlayer , Cmd );
    }
}

void CHackUserCommands::Update( C_BasePlayer* pPlayer , CUserCmd* Cmd )
{
    if ( pPlayer != nullptr )
    {
        HackPrediction->PreThink( pPlayer , Cmd );
        HackPrediction->Think( pPlayer , Cmd );

        *Cmd = old_cmd;
        bIsPredicted = true;

        Modify( pPlayer , Cmd );

        HackPrediction->PostThink( pPlayer );
    }
}