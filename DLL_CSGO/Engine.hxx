#ifndef ENGINE
#define ENGINE
#pragma once

constexpr const int MAX_VIRTUAL_TRIANGLES = 1024;

enum BoneList
{
    BONE_PELVIS ,
    BONE_SPINE1 ,
    BONE_SPINE2 ,
    BONE_SPINE3 ,
    BONE_SPINE4 ,
    BONE_NECK ,
    BONE_L_CLAVICLE ,
    BONE_L_UPPER_ARM ,
    BONE_L_FOREARM ,
    BONE_L_HAND ,
    BONE_HEAD ,
    BONE_FORWARD ,
    BONE_R_CLAVICLE ,
    BONE_R_UPPER_ARM ,
    BONE_R_FOREARM ,
    BONE_R_HAND ,
    BONE_WEAPON ,
    BONE_WEAPON_SLIDE ,
    BONE_WEAPON_R_HAND ,
    BONE_WEAPON_L_HAND ,
    BONE_WEAPON_CLIP1 ,
    BONE_WEAPON_CLIP2 ,
    BONE_SILENCER ,
    BONE_R_THIGH ,
    BONE_R_CALF ,
    BONE_R_FOOT ,
    BONE_L_THIGH ,
    BONE_L_CALF ,
    BONE_L_FOOT ,
    BONE_L_WEAPON_HAND ,
    BONE_R_WEAPON_HAND ,
    BONE_L_FORETWIST ,
    BONE_L_CALFTWIST ,
    BONE_R_CALFTWIST ,
    BONE_L_THIGHTWIST ,
    BONE_R_THIGHTWIST ,
    BONE_L_UPARMTWIST ,
    BONE_R_UPARMTWIST ,
    BONE_R_FORETWIST ,
    BONE_R_TOE ,
    BONE_L_TOE ,
    BONE_R_FINGER01 ,
    BONE_R_FINGER02 ,
    BONE_R_FINGER03 ,
    BONE_R_FINGER04 ,
    BONE_R_FINGER05 ,
    BONE_R_FINGER06 ,
    BONE_R_FINGER07 ,
    BONE_R_FINGER08 ,
    BONE_R_FINGER09 ,
    BONE_R_FINGER10 ,
    BONE_R_FINGER11 ,
    BONE_R_FINGER12 ,
    BONE_R_FINGER13 ,
    BONE_R_FINGER14 ,
    BONE_L_FINGER01 ,
    BONE_L_FINGER02 ,
    BONE_L_FINGER03 ,
    BONE_L_FINGER04 ,
    BONE_L_FINGER05 ,
    BONE_L_FINGER06 ,
    BONE_L_FINGER07 ,
    BONE_L_FINGER08 ,
    BONE_L_FINGER09 ,
    BONE_L_FINGER10 ,
    BONE_L_FINGER11 ,
    BONE_L_FINGER12 ,
    BONE_L_FINGER13 ,
    BONE_L_FINGER14 ,
    BONE_L_FINGER15 ,
    BONE_R_FINGER15 ,
    BONE_MAX
};

// ---------------------------
//  Hit Group standards
// ---------------------------
#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10			// alerts NPC, but doesn't do damage or bleed (1/100th damage)

#define MAX_SURFINFO_VERTS	16

#define FLOW_OUTGOING	0
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		// in & out

#define MAX_QPATH  260

#define BONE_CALCULATE_MASK             0x1F
#define BONE_PHYSICALLY_SIMULATED       0x01    // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL         0x02    // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL          0x04    // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE        0x08    // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER      0x10    // bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK                  0x0007FF00
#define BONE_USED_BY_ANYTHING           0x0007FF00
#define BONE_USED_BY_HITBOX             0x00000100    // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT         0x00000200    // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK        0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0        0x00000400    // bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1        0x00000800
#define BONE_USED_BY_VERTEX_LOD2        0x00001000
#define BONE_USED_BY_VERTEX_LOD3        0x00002000
#define BONE_USED_BY_VERTEX_LOD4        0x00004000
#define BONE_USED_BY_VERTEX_LOD5        0x00008000
#define BONE_USED_BY_VERTEX_LOD6        0x00010000
#define BONE_USED_BY_VERTEX_LOD7        0x00020000
#define BONE_USED_BY_BONE_MERGE         0x00040000    // bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8
#define MAXSTUDIOBONES		256		// total bones actually used

#define BONE_TYPE_MASK                  0x00F00000
#define BONE_FIXED_ALIGNMENT            0x00100000    // bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS          0x00200000    // Vector48
#define BONE_HAS_SAVEFRAME_ROT64        0x00400000    // Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32        0x00800000    // Quaternion32

#define   DISPSURF_FLAG_SURFACE           (1<<0)
#define   DISPSURF_FLAG_WALKABLE          (1<<1)
#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
#define   DISPSURF_FLAG_SURFPROP2         (1<<4)

#define   CONTENTS_EMPTY                0

#define   CONTENTS_SOLID                0x1
#define   CONTENTS_WINDOW               0x2
#define   CONTENTS_AUX                  0x4
#define   CONTENTS_GRATE                0x8
#define   CONTENTS_SLIME                0x10
#define   CONTENTS_WATER                0x20
#define   CONTENTS_BLOCKLOS             0x40
#define   CONTENTS_OPAQUE               0x80
#define   LAST_VISIBLE_CONTENTS         CONTENTS_OPAQUE

#define   ALL_VISIBLE_CONTENTS            (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define   CONTENTS_TESTFOGVOLUME        0x100
#define   CONTENTS_UNUSED               0x200
#define   CONTENTS_BLOCKLIGHT           0x400
#define   CONTENTS_TEAM1                0x800
#define   CONTENTS_TEAM2                0x1000
#define   CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
#define   CONTENTS_MOVEABLE             0x4000
#define   CONTENTS_AREAPORTAL           0x8000
#define   CONTENTS_PLAYERCLIP           0x10000
#define   CONTENTS_MONSTERCLIP          0x20000
#define   CONTENTS_CURRENT_0            0x40000
#define   CONTENTS_CURRENT_90           0x80000
#define   CONTENTS_CURRENT_180          0x100000
#define   CONTENTS_CURRENT_270          0x200000
#define   CONTENTS_CURRENT_UP           0x400000
#define   CONTENTS_CURRENT_DOWN         0x800000

#define   CONTENTS_ORIGIN               0x1000000

#define   CONTENTS_MONSTER              0x2000000
#define   CONTENTS_DEBRIS               0x4000000
#define   CONTENTS_DETAIL               0x8000000
#define   CONTENTS_TRANSLUCENT          0x10000000
#define   CONTENTS_LADDER               0x20000000
#define   CONTENTS_HITBOX               0x40000000

#define   SURF_LIGHT                    0x0001
#define   SURF_SKY2D                    0x0002
#define   SURF_SKY                      0x0004
#define   SURF_WARP                     0x0008
#define   SURF_TRANS                    0x0010
#define   SURF_NOPORTAL                 0x0020
#define   SURF_TRIGGER                  0x0040
#define   SURF_NODRAW                   0x0080

#define   SURF_HINT                     0x0100

#define   SURF_SKIP                     0x0200
#define   SURF_NOLIGHT                  0x0400
#define   SURF_BUMPLIGHT                0x0800
#define   SURF_NOSHADOWS                0x1000
#define   SURF_NODECALS                 0x2000
#define   SURF_NOPAINT                  SURF_NODECALS
#define   SURF_NOCHOP                   0x4000
#define   SURF_HITBOX                   0x8000

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define   MASK_ALL                      (0xFFFFFFFF)
#define   MASK_SOLID                    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCSOLID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCFLUID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_WATER                    (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define   MASK_OPAQUE                   (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define   MASK_OPAQUE_AND_NPCS          (MASK_OPAQUE|CONTENTS_MONSTER)
#define   MASK_BLOCKLOS                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define   MASK_BLOCKLOS_AND_NPCS        (MASK_BLOCKLOS|CONTENTS_MONSTER)
#define   MASK_VISIBLE                  (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_VISIBLE_AND_NPCS         (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define   MASK_SHOT_BRUSHONLY           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define   MASK_SHOT_HULL                (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define   MASK_SHOT_PORTAL              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_SOLID_BRUSHONLY          (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID_BRUSHONLY    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define   MASK_NPCSOLID_BRUSHONLY       (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC           (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC_FLUID     (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define   MASK_SPLITAREAPORTAL          (CONTENTS_WATER|CONTENTS_SLIME)
#define   MASK_CURRENT                  (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define   MASK_DEADSOLID                (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)
#define	  CS_MASK_SHOOT                 (MASK_SOLID|CONTENTS_DEBRIS)

typedef CGameTrace trace_t;

enum Collision_Group_t
{
    COLLISION_GROUP_NONE = 0 ,
    COLLISION_GROUP_DEBRIS ,			// Collides with nothing but world and static stuff
    COLLISION_GROUP_DEBRIS_TRIGGER , // Same as debris, but hits triggers
    COLLISION_GROUP_INTERACTIVE_DEBRIS ,	// Collides with everything except other interactive debris or debris
    COLLISION_GROUP_INTERACTIVE ,	// Collides with everything except interactive debris or debris
    COLLISION_GROUP_PLAYER ,
    COLLISION_GROUP_BREAKABLE_GLASS ,
    COLLISION_GROUP_VEHICLE ,
    COLLISION_GROUP_PLAYER_MOVEMENT ,  // For HL2, same as Collision_Group_Player, for
                                       // TF2, this filters out other players and CBaseObjects
                                       COLLISION_GROUP_NPC ,			// Generic NPC group
                                       COLLISION_GROUP_IN_VEHICLE ,		// for any entity inside a vehicle
                                       COLLISION_GROUP_WEAPON ,			// for any weapons that need collision detection
                                       COLLISION_GROUP_VEHICLE_CLIP ,	// vehicle clip brush to restrict vehicle movement
                                       COLLISION_GROUP_PROJECTILE ,		// Projectiles!
                                       COLLISION_GROUP_DOOR_BLOCKER ,	// Blocks entities not permitted to get near moving doors
                                       COLLISION_GROUP_PASSABLE_DOOR ,	// Doors that the player shouldn't collide with
                                       COLLISION_GROUP_DISSOLVING ,		// Things that are dissolving are in this group
                                       COLLISION_GROUP_PUSHAWAY ,		// Nonsolid on client and server, pushaway in player code

                                       COLLISION_GROUP_NPC_ACTOR ,		// Used so NPCs in scripts ignore the player.
                                       COLLISION_GROUP_NPC_SCRIPTED ,	// USed for NPCs in scripts that should not collide with each other
                                       COLLISION_GROUP_PZ_CLIP ,

                                       COLLISION_GROUP_DEBRIS_BLOCK_PROJECTILE , // Only collides with bullets

                                       LAST_SHARED_COLLISION_GROUP
};

// edict->movetype values
enum MoveType_t
{
    MOVETYPE_NONE = 0 ,	// never moves
    MOVETYPE_ISOMETRIC ,			// For players -- in TF2 commander view, etc.
    MOVETYPE_WALK ,				// Player only - moving on the ground
    MOVETYPE_STEP ,				// gravity, special edge handling -- monsters use this
    MOVETYPE_FLY ,				// No gravity, but still collides with stuff
    MOVETYPE_FLYGRAVITY ,		// flies through the air + is affected by gravity
    MOVETYPE_VPHYSICS ,			// uses VPHYSICS for simulation
    MOVETYPE_PUSH ,				// no clip to world, push and crush
    MOVETYPE_NOCLIP ,			// No gravity, no collisions, still do velocity/avelocity
    MOVETYPE_LADDER ,			// Used by players only when going onto a ladder
    MOVETYPE_OBSERVER ,			// Observer movement, depends on player's observer mode
    MOVETYPE_CUSTOM ,			// Allows the entity to describe its own physics

                                // should always be defined as the last item in the list
                                MOVETYPE_LAST = MOVETYPE_CUSTOM ,

                                MOVETYPE_MAX_BITS = 4
};

// edict->solid values
// NOTE: Some movetypes will cause collisions independent of SOLID_NOT/SOLID_TRIGGER when the entity moves
// SOLID only effects OTHER entities colliding with this one when they move - UGH!

// Solid type basically describes how the bounding volume of the object is represented
// NOTE: SOLID_BBOX MUST BE 2, and SOLID_VPHYSICS MUST BE 6
// NOTE: These numerical values are used in the FGD by the prop code (see prop_dynamic)
enum SolidType_t
{
    SOLID_NONE = 0 ,	// no solid model
    SOLID_BSP = 1 ,	// a BSP tree
    SOLID_BBOX = 2 ,	// an AABB
    SOLID_OBB = 3 ,	// an OBB (not implemented yet)
    SOLID_OBB_YAW = 4 ,	// an OBB, constrained so that it can only yaw
    SOLID_CUSTOM = 5 ,	// Always call into the entity for tests
    SOLID_VPHYSICS = 6 ,	// solid vphysics object, get vcollide from the model and collide with that
    SOLID_LAST ,
};

//-----------------------------------------------------------------------------
// Skybox visibility
//-----------------------------------------------------------------------------
enum SkyboxVisibility_t
{
    SKYBOX_NOT_VISIBLE = 0 ,
    SKYBOX_3DSKYBOX_VISIBLE ,
    SKYBOX_2DSKYBOX_VISIBLE ,
};

enum ClassId
{
    ClassId_CAI_BaseNPC = 0 ,
    ClassId_CAK47 ,
    ClassId_CBaseAnimating ,
    ClassId_CBaseAnimatingOverlay ,
    ClassId_CBaseAttributableItem ,
    ClassId_CBaseButton ,
    ClassId_CBaseCombatCharacter ,
    ClassId_CBaseCombatWeapon ,
    ClassId_CBaseCSGrenade ,
    ClassId_CBaseCSGrenadeProjectile ,
    ClassId_CBaseDoor ,
    ClassId_CBaseEntity ,
    ClassId_CBaseFlex ,
    ClassId_CBaseGrenade ,
    ClassId_CBaseParticleEntity ,
    ClassId_CBasePlayer ,
    ClassId_CBasePropDoor ,
    ClassId_CBaseTeamObjectiveResource ,
    ClassId_CBaseTempEntity ,
    ClassId_CBaseToggle ,
    ClassId_CBaseTrigger ,
    ClassId_CBaseViewModel ,
    ClassId_CBaseVPhysicsTrigger ,
    ClassId_CBaseWeaponWorldModel ,
    ClassId_CBeam ,
    ClassId_CBeamSpotlight ,
    ClassId_CBoneFollower ,
    ClassId_CBreakableProp ,
    ClassId_CBreakableSurface ,
    ClassId_CC4 ,
    ClassId_CCascadeLight ,
    ClassId_CChicken ,
    ClassId_CColorCorrection ,
    ClassId_CColorCorrectionVolume ,
    ClassId_CCSGameRulesProxy ,
    ClassId_CCSPlayer ,
    ClassId_CCSPlayerResource ,
    ClassId_CCSRagdoll ,
    ClassId_CCSTeam ,
    ClassId_CDEagle ,
    ClassId_CDecoyGrenade ,
    ClassId_CDecoyProjectile ,
    ClassId_CDynamicLight ,
    ClassId_CDynamicProp ,
    ClassId_CEconEntity ,
    ClassId_CEconWearable ,
    ClassId_CEmbers ,
    ClassId_CEntityDissolve ,
    ClassId_CEntityFlame ,
    ClassId_CEntityFreezing ,
    ClassId_CEntityParticleTrail ,
    ClassId_CEnvAmbientLight ,
    ClassId_CEnvDetailController ,
    ClassId_CEnvDOFController ,
    ClassId_CEnvParticleScript ,
    ClassId_CEnvProjectedTexture ,
    ClassId_CEnvQuadraticBeam ,
    ClassId_CEnvScreenEffect ,
    ClassId_CEnvScreenOverlay ,
    ClassId_CEnvTonemapController ,
    ClassId_CEnvWind ,
    ClassId_CFEPlayerDecal ,
    ClassId_CFireCrackerBlast ,
    ClassId_CFireSmoke ,
    ClassId_CFireTrail ,
    ClassId_CFish ,
    ClassId_CFlashbang ,
    ClassId_CFogController ,
    ClassId_CFootstepControl ,
    ClassId_CFunc_Dust ,
    ClassId_CFunc_LOD ,
    ClassId_CFuncAreaPortalWindow ,
    ClassId_CFuncBrush ,
    ClassId_CFuncConveyor ,
    ClassId_CFuncLadder ,
    ClassId_CFuncMonitor ,
    ClassId_CFuncMoveLinear ,
    ClassId_CFuncOccluder ,
    ClassId_CFuncReflectiveGlass ,
    ClassId_CFuncRotating ,
    ClassId_CFuncSmokeVolume ,
    ClassId_CFuncTrackTrain ,
    ClassId_CGameRulesProxy ,
    ClassId_CHandleTest ,
    ClassId_CHEGrenade ,
    ClassId_CHostage ,
    ClassId_CHostageCarriableProp ,
    ClassId_CIncendiaryGrenade ,
    ClassId_CInferno ,
    ClassId_CInfoLadderDismount ,
    ClassId_CInfoOverlayAccessor ,
    ClassId_CItem_Healthshot ,
    ClassID_CItemDogTags ,
    ClassId_CKnife ,
    ClassId_CKnifeGG ,
    ClassId_CLightGlow ,
    ClassId_CMaterialModifyControl ,
    ClassId_CMolotovGrenade ,
    ClassId_CMolotovProjectile ,
    ClassId_CMovieDisplay ,
    ClassId_CParticleFire ,
    ClassId_CParticlePerformanceMonitor ,
    ClassId_CParticleSystem ,
    ClassId_CPhysBox ,
    ClassId_CPhysBoxMultiplayer ,
    ClassId_CPhysicsProp ,
    ClassId_CPhysicsPropMultiplayer ,
    ClassId_CPhysMagnet ,
    ClassId_CPlantedC4 ,
    ClassId_CPlasma ,
    ClassId_CPlayerResource ,
    ClassId_CPointCamera ,
    ClassId_CPointCommentaryNode ,
    ClassId_CPointWorldText ,
    ClassId_CPoseController ,
    ClassId_CPostProcessController ,
    ClassId_CPrecipitation ,
    ClassId_CPrecipitationBlocker ,
    ClassId_CPredictedViewModel ,
    ClassId_CProp_Hallucination ,
    ClassId_CPropDoorRotating ,
    ClassId_CPropJeep ,
    ClassId_CPropVehicleDriveable ,
    ClassId_CRagdollManager ,
    ClassId_CRagdollProp ,
    ClassId_CRagdollPropAttached ,
    ClassId_CRopeKeyframe ,
    ClassId_CSCAR17 ,
    ClassId_CSceneEntity ,
    ClassId_CSensorGrenade ,
    ClassId_CSensorGrenadeProjectile ,
    ClassId_CShadowControl ,
    ClassId_CSlideshowDisplay ,
    ClassId_CSmokeGrenade ,
    ClassId_CSmokeGrenadeProjectile ,
    ClassId_CSmokeStack ,
    ClassId_CSpatialEntity ,
    ClassId_CSpotlightEnd ,
    ClassId_CSprite ,
    ClassId_CSpriteOriented ,
    ClassId_CSpriteTrail ,
    ClassId_CStatueProp ,
    ClassId_CSteamJet ,
    ClassId_CSun ,
    ClassId_CSunlightShadowControl ,
    ClassId_CTeam ,
    ClassId_CTeamplayRoundBasedRulesProxy ,
    ClassId_CTEArmorRicochet ,
    ClassId_CTEBaseBeam ,
    ClassId_CTEBeamEntPoint ,
    ClassId_CTEBeamEnts ,
    ClassId_CTEBeamFollow ,
    ClassId_CTEBeamLaser ,
    ClassId_CTEBeamPoints ,
    ClassId_CTEBeamRing ,
    ClassId_CTEBeamRingPoint ,
    ClassId_CTEBeamSpline ,
    ClassId_CTEBloodSprite ,
    ClassId_CTEBloodStream ,
    ClassId_CTEBreakModel ,
    ClassId_CTEBSPDecal ,
    ClassId_CTEBubbles ,
    ClassId_CTEBubbleTrail ,
    ClassId_CTEClientProjectile ,
    ClassId_CTEDecal ,
    ClassId_CTEDust ,
    ClassId_CTEDynamicLight ,
    ClassId_CTEEffectDispatch ,
    ClassId_CTEEnergySplash ,
    ClassId_CTEExplosion ,
    ClassId_CTEFireBullets ,
    ClassId_CTEFizz ,
    ClassId_CTEFootprintDecal ,
    ClassId_CTEFoundryHelpers ,
    ClassId_CTEGaussExplosion ,
    ClassId_CTEGlowSprite ,
    ClassId_CTEImpact ,
    ClassId_CTEKillPlayerAttachments ,
    ClassId_CTELargeFunnel ,
    ClassId_CTEMetalSparks ,
    ClassId_CTEMuzzleFlash ,
    ClassId_CTEParticleSystem ,
    ClassId_CTEPhysicsProp ,
    ClassId_CTEPlantBomb ,
    ClassId_CTEPlayerAnimEvent ,
    ClassId_CTEPlayerDecal ,
    ClassId_CTEProjectedDecal ,
    ClassId_CTERadioIcon ,
    ClassId_CTEShatterSurface ,
    ClassId_CTEShowLine ,
    ClassId_CTesla ,
    ClassId_CTESmoke ,
    ClassId_CTESparks ,
    ClassId_CTESprite ,
    ClassId_CTESpriteSpray ,
    ClassId_CTest_ProxyToggle_Networkable ,
    ClassId_CTestTraceline ,
    ClassId_CTEWorldDecal ,
    ClassId_CTriggerPlayerMovement ,
    ClassId_CTriggerSoundOperator ,
    ClassId_CVGuiScreen ,
    ClassId_CVoteController ,
    ClassId_CWaterBullet ,
    ClassId_CWaterLODControl ,
    ClassId_CWeaponAug ,
    ClassId_CWeaponAWP ,
    ClassId_CWeaponBaseItem ,
    ClassId_CWeaponBizon ,
    ClassId_CWeaponCSBase ,
    ClassId_CWeaponCSBaseGun ,
    ClassId_CWeaponCycler ,
    ClassId_CWeaponElite ,
    ClassId_CWeaponFamas ,
    ClassId_CWeaponFiveSeven ,
    ClassId_CWeaponG3SG1 ,
    ClassId_CWeaponGalil ,
    ClassId_CWeaponGalilAR ,
    ClassId_CWeaponGlock ,
    ClassId_CWeaponHKP2000 ,
    ClassId_CWeaponM249 ,
    ClassId_CWeaponM3 ,
    ClassId_CWeaponM4A1 ,
    ClassId_CWeaponMAC10 ,
    ClassId_CWeaponMag7 ,
    ClassId_CWeaponMP5Navy ,
    ClassId_CWeaponMP7 ,
    ClassId_CWeaponMP9 ,
    ClassId_CWeaponNegev ,
    ClassId_CWeaponNOVA ,
    ClassId_CWeaponP228 ,
    ClassId_CWeaponP250 ,
    ClassId_CWeaponP90 ,
    ClassId_CWeaponSawedoff ,
    ClassId_CWeaponSCAR20 ,
    ClassId_CWeaponScout ,
    ClassId_CWeaponSG550 ,
    ClassId_CWeaponSG552 ,
    ClassId_CWeaponSG556 ,
    ClassId_CWeaponSSG08 ,
    ClassId_CWeaponTaser ,
    ClassId_CWeaponTec9 ,
    ClassId_CWeaponTMP ,
    ClassId_CWeaponUMP45 ,
    ClassId_CWeaponUSP ,
    ClassId_CWeaponXM1014 ,
    ClassId_CWorld ,
    ClassId_DustTrail ,
    ClassId_MovieExplosion ,
    ClassId_ParticleSmokeGrenade ,
    ClassId_RocketTrail ,
    ClassId_SmokeTrail ,
    ClassId_SporeExplosion ,
    ClassId_SporeTrail ,
    MAX_CLASSID
};

enum DebugTraceCounterBehavior_t
{
    kTRACE_COUNTER_SET = 0 ,
    kTRACE_COUNTER_INC ,
};

enum TraceType
{
    TRACE_EVERYTHING = 0 ,
    TRACE_WORLD_ONLY ,				// NOTE: This does *not* test static props!!!
    TRACE_ENTITIES_ONLY ,			// NOTE: This version will *not* test static props
    TRACE_EVERYTHING_FILTER_PROPS ,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

enum modtype_t
{
    mod_bad = 0 ,
    mod_brush ,
    mod_sprite ,
    mod_studio
};

enum Hitboxes
{
    HITBOX_HEAD ,
    HITBOX_NECK ,
    HITBOX_LOWER_NECK ,
    HITBOX_PELVIS ,
    HITBOX_STOMACH ,
    HITBOX_LOWER_CHEST ,
    HITBOX_CHEST ,
    HITBOX_UPPER_CHEST ,
    HITBOX_RIGHT_THIGH ,
    HITBOX_LEFT_THIGH ,
    HITBOX_RIGHT_CALF ,
    HITBOX_LEFT_CALF ,
    HITBOX_RIGHT_FOOT ,
    HITBOX_LEFT_FOOT ,
    HITBOX_RIGHT_HAND ,
    HITBOX_LEFT_HAND ,
    HITBOX_RIGHT_UPPER_ARM ,
    HITBOX_RIGHT_FOREARM ,
    HITBOX_LEFT_UPPER_ARM ,
    HITBOX_LEFT_FOREARM ,
    HITBOX_MAX
};

struct surfacephysicsparams_t
{
    // vphysics physical properties
    float			friction;
    float			elasticity;				// collision elasticity - used to compute coefficient of restitution
    float			density;				// physical density (in kg / m^3)
    float			thickness;				// material thickness if not solid (sheet materials) in inches
    float			dampening;
};

struct surfaceaudioparams_t
{
    // sounds / audio data
    float			reflectivity;		// like elasticity, but how much sound should be reflected by this surface
    float			hardnessFactor;	// like elasticity, but only affects impact sound choices
    float			roughnessFactor;	// like friction, but only affects scrape sound choices

                                        // audio thresholds
    float			roughThreshold;	// surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
    float			hardThreshold;	// surface hardness > this causes "hard" impacts, < this causes "soft" impacts
    float			hardVelocityThreshold;	// collision velocity > this causes "hard" impacts, < this causes "soft" impacts
                                            // NOTE: Hard impacts must meet both hardnessFactor AND velocity thresholds
    float    highPitchOcclusion;       //a value betweeen 0 and 100 where 0 is not occluded at all and 100 is silent (except for any additional reflected sound)
    float    midPitchOcclusion;
    float    lowPitchOcclusion;
};

struct surfacesoundnames_t
{
    unsigned short	walkStepLeft;
    unsigned short	walkStepRight;
    unsigned short	runStepLeft;
    unsigned short	runStepRight;

    unsigned short	impactSoft;
    unsigned short	impactHard;

    unsigned short	scrapeSmooth;
    unsigned short	scrapeRough;

    unsigned short	bulletImpact;
    unsigned short	rolling;

    unsigned short	breakSound;
    unsigned short	strainSound;
};

struct surfacesoundhandles_t
{
    short	walkStepLeft;
    short	walkStepRight;
    short	runStepLeft;
    short	runStepRight;

    short	impactSoft;
    short	impactHard;

    short	scrapeSmooth;
    short	scrapeRough;

    short	bulletImpact;
    short	rolling;

    short	breakSound;
    short	strainSound;
};

struct surfacegameprops_t
{
    // game movement data
    float			maxSpeedFactor;			// Modulates player max speed when walking on this surface
    float			jumpFactor;				// Indicates how much higher the player should jump when on the surface
                                            // Game-specific data
    unsigned short	material;
    // Indicates whether or not the player is on a ladder.
    unsigned char	climbable;
    unsigned char	pad[ 0x4 ];
};

struct surfacedata_t
{
    surfacephysicsparams_t	physics;	// physics parameters
    surfaceaudioparams_t	audio;		// audio parameters
    surfacesoundnames_t		sounds;		// names of linked sounds
    surfacegameprops_t		game;		// Game data / properties

    surfacesoundhandles_t		soundhandles;
};

typedef float Quaternion[ 4 ];
typedef float RadianEuler[ 3 ];

typedef unsigned short MDLHandle_t;

struct mstudiobone_t
{
    int         sznameindex;
    int         parent;		// parent bone
    int         bonecontroller[ 6 ];	// bone controller index, -1 == none
    Vector      pos;
    Quaternion  quat;
    RadianEuler rot;
    Vector      posscale;
    Vector      rotscale;

    Matrix3x4   poseToBone;
    Quaternion  qAlignment;
    int			flags;
};

struct mstudiobbox_t
{
    int         bone;
    int         group;
    Vector      bbmin;
    Vector      bbmax;
    int         szhitboxnameindex;
    float       m_iPad01[ 3 ];
    float       m_flRadius;
    float       m_iPad02[ 4 ];

    const char* GetName()
    {
        if ( !szhitboxnameindex ) return nullptr;
        return ( const char* ) ( ( uint8_t* ) this + szhitboxnameindex );
    }
};

struct mstudiohitboxset_t
{
    int    sznameindex;
    int    numhitboxes;
    int    hitboxindex;

    const char* GetName()
    {
        if ( !sznameindex ) return nullptr;
        return ( const char* ) ( ( uint8_t* ) this + sznameindex );
    }

    mstudiobbox_t* GetHitbox( int i )
    {
        if ( i > numhitboxes ) return nullptr;
        return ( mstudiobbox_t* ) ( ( uint8_t* ) this + hitboxindex ) + i;
    }
};

struct model_t
{
    Pointer   fnHandle;               //0x0000
    char    szName[ 260 ];            //0x0004
    __int32 nLoadFlags;             //0x0108
    __int32 nServerCount;           //0x010C
    __int32 type;                   //0x0110
    __int32 flags;                  //0x0114
    Vector  vecMins;                //0x0118
    Vector  vecMaxs;                //0x0124
    float   radius;                 //0x0130
    char    pad[ 0x4 ];             //0x0134
    MDLHandle_t studio;             //0x0138
    char    pad2[ 0x10 ];              //0x0140
};//Size=0x0150

class studiohdr_t
{
public:
    __int32 id;                     //0x0000
    __int32 version;                //0x0004
    long    checksum;               //0x0008
    char    szName[ 64 ];             //0x000C
    __int32 length;                 //0x004C
    Vector  vecEyePos;              //0x0050
    Vector  vecIllumPos;            //0x005C
    Vector  vecHullMin;             //0x0068
    Vector  vecHullMax;             //0x0074
    Vector  vecBBMin;               //0x0080
    Vector  vecBBMax;               //0x008C
    __int32 flags;                  //0x0098
    __int32 numbones;               //0x009C
    __int32 boneindex;              //0x00A0
    __int32 numbonecontrollers;     //0x00A4
    __int32 bonecontrollerindex;    //0x00A8
    __int32 numhitboxsets;          //0x00AC
    __int32 hitboxsetindex;         //0x00B0
    __int32 numlocalanim;           //0x00B4
    __int32 localanimindex;         //0x00B8
    __int32 numlocalseq;            //0x00BC
    __int32 localseqindex;          //0x00C0
    __int32 activitylistversion;    //0x00C4
    __int32 eventsindexed;          //0x00C8
    __int32 numtextures;            //0x00CC
    __int32 textureindex;           //0x00D0
    __int32					numcdtextures;
    __int32					cdtextureindex;
    __int32					numskinref;
    __int32					numskinfamilies;
    __int32					skinindex;
    __int32					numbodyparts;
    __int32					bodypartindex;
    __int32					numlocalattachments;
    __int32					localattachmentindex;
    __int32					numlocalnodes;
    __int32					localnodeindex;
    __int32					localnodenameindex;
    __int32					numflexdesc;
    __int32					flexdescindex;
    __int32					numflexcontrollers;
    __int32					flexcontrollerindex;
    __int32					numflexrules;
    __int32					flexruleindex;
    __int32					numikchains;
    __int32					ikchainindex;
    __int32					nummouths;
    __int32					mouthindex;
    __int32					numlocalposeparameters;
    __int32					localposeparamindex;

    mstudiohitboxset_t* GetHitboxSet( int i )
    {
        if ( i > numhitboxsets ) return nullptr;
        return ( mstudiohitboxset_t* ) ( ( uint8_t* ) this + hitboxsetindex ) + i;
    }
    mstudiobone_t* GetBone( int i )
    {
        if ( i > numbones ) return nullptr;
        return ( mstudiobone_t* ) ( ( uint8_t* ) this + boneindex ) + i;
    }
};//Size=0x00D4

struct cplane_t
{
    Vector normal;
    float dist;
    byte type;
    byte signbits;
    byte pad[ 2 ];
};

struct csurface_t
{
    const char* name;
    short surfaceProps;
    unsigned short flags;
};

struct virtualmeshlist_t
{
    Vector			*pVerts;
    int				indexCount;
    int				triangleCount;
    int				vertexCount;
    int				surfacePropsIndex;
    byte			*pHull;
    unsigned short	indices[ MAX_VIRTUAL_TRIANGLES * 3 ];
};

struct virtualmeshtrianglelist_t
{
    int				triangleCount;
    unsigned short	triangleIndices[ MAX_VIRTUAL_TRIANGLES * 3 ];
};

struct BrushSideInfo_t
{
    Vector4D plane;			// The plane of the brush side
    unsigned short bevel;	// Bevel plane?
    unsigned short thin;	// Thin?
};

struct virtualmeshparams_t
{
    IVirtualMeshEvent	*pMeshEventHandler;
    void				*userData;
    bool				buildOuterHull;
};

// Engine player info, no game related infos here
// If you change this, change the two byteswap defintions:
// cdll_client_int.cpp and cdll_engine_int.cpp
typedef struct player_info_s
{
    unsigned long            unknown;

    // network xuid
    unsigned long            xuid;

    // scoreboard information
    char			name[ MAX_PLAYER_NAME_LENGTH ];
    // local server user ID, unique while server is running
    int				userID;
    // global unique player identifer
    char			guid[ SIGNED_GUID_LEN + 1 ];
    // friends identification number
    uint32_t			friendsID;
    // friends name
    char			friendsName[ MAX_PLAYER_NAME_LENGTH ];
    // true, if player is a bot controlled by game.dll
    bool			fakeplayer;
    // true if player is the HLTV proxy
    bool			ishltv;
#if defined( REPLAY_ENABLED )
    // true if player is the Replay proxy
    bool			isreplay;
#endif
    // custom files CRC for this player
    CRC32_t			customFiles[ MAX_CUSTOM_FILES ];
    // this counter increases each time the server downloaded a new file
    unsigned char	filesDownloaded;
} player_info_t;

struct client_textmessage_t
{
    int		effect;
    byte	r1 , g1 , b1 , a1;		// 2 colors for effects
    byte	r2 , g2 , b2 , a2;
    float	x;
    float	y;
    float	fadein;
    float	fadeout;
    float	holdtime;
    float	fxtime;
    const char *pVGuiSchemeFontName; // If null, use default font for messages
    const char *pName;
    const char *pMessage;
    bool    bRoundedRectBackdropBox;
    float	flBoxSize; // as a function of font height
    byte	boxcolor[ 4 ];
    char const *pClearMessage; // message to clear
};

//-----------------------------------------------------------------------------
// Hearing info
//-----------------------------------------------------------------------------
struct AudioState_t
{
    Vector m_Origin;
    Angle m_Angles;
    bool m_bIsUnderwater;
};

//-----------------------------------------------------------------------------
// Occlusion parameters
//-----------------------------------------------------------------------------
struct OcclusionParams_t
{
    float	m_flMaxOccludeeArea;
    float	m_flMinOccluderArea;
};

struct BoxTraceInfo_t
{
    float t1;
    float t2;
    int	hitside;
    bool startsolid;
};

typedef struct vmode_s
{
    int			width;
    int			height;
    int			bpp;
    int			refreshRate;
} vmode_t;

class IVirtualMeshEvent
{
public:
    virtual void GetVirtualMesh( void *userData , virtualmeshlist_t *pList ) = 0;
    virtual void GetWorldspaceBounds( void *userData , Vector *pMins , Vector *pMaxs ) = 0;
    virtual void GetTrianglesInSphere( void *userData , const Vector &center , float radius , virtualmeshtrianglelist_t *pList ) = 0;
};

class ITraceFilter
{
public:
    virtual bool ShouldHitEntity( IHandleEntity *pEntity , int contentsMask ) = 0;
    virtual TraceType GetTraceType() const = 0;
};

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

class CTraceFilter : public ITraceFilter
{
public:
    bool ShouldHitEntity( IHandleEntity* pEntityHandle , int contentsMask )
    {
        return !( pEntityHandle == pSkip );
    }

    void* pSkip;
};

typedef bool( *ShouldHitFunc_t )( IHandleEntity *pHandleEntity , int contentsMask );

class CTraceFilterSimple : public ITraceFilter
{
public:

    CTraceFilterSimple::CTraceFilterSimple( const IHandleEntity *passedict , int collisionGroup , ShouldHitFunc_t pExtraShouldHitCheckFn = NULL )
    {
        m_pPassEnt = passedict;
        m_collisionGroup = collisionGroup;
        m_pExtraShouldHitCheckFunction = nullptr;
    }

    virtual bool ShouldHitEntity( IHandleEntity *pHandleEntity , int contentsMask );

    virtual void SetPassEntity( const IHandleEntity *pPassEntity )
    {
        m_pPassEnt = pPassEntity;
    }

    virtual void SetCollisionGroup( int iCollisionGroup )
    {
        m_collisionGroup = iCollisionGroup;
    }

    const IHandleEntity *GetPassEntity( void )
    {
        return m_pPassEnt;
    }

    virtual TraceType GetTraceType() const
    {
        return TraceType::TRACE_EVERYTHING;
    }

private:
    const IHandleEntity *m_pPassEnt;
    int m_collisionGroup;
    ShouldHitFunc_t m_pExtraShouldHitCheckFunction;
};

class CTraceFilterSkipEntity : public ITraceFilter
{
public:
    CTraceFilterSkipEntity( IHandleEntity* pEntityHandle )
    {
        pSkip = pEntityHandle;
    }

    bool ShouldHitEntity( IHandleEntity* pEntityHandle , int contentsMask )
    {
        return !( pEntityHandle == pSkip );
    }
    virtual TraceType GetTraceType() const
    {
        return TraceType::TRACE_EVERYTHING;
    }
    void* pSkip;
};

class CTraceFilterEntitiesOnly : public ITraceFilter
{
public:
    bool ShouldHitEntity( IHandleEntity* pEntityHandle , int contentsMask )
    {
        return true;
    }
    virtual TraceType GetTraceType() const
    {
        return TraceType::TRACE_ENTITIES_ONLY;
    }
};

class CTraceFilterWorldOnly : public ITraceFilter
{
public:
    bool ShouldHitEntity( IHandleEntity* pServerEntity , int contentsMask )
    {
        return false;
    }
    virtual TraceType GetTraceType() const
    {
        return TraceType::TRACE_WORLD_ONLY;
    }
};

class CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
public:

    bool ShouldHitEntity( IHandleEntity* pServerEntity , int contentsMask )
    {
        return false;
    }

    virtual TraceType GetTraceType() const
    {
        return TraceType::TRACE_EVERYTHING;
    }
};

class CTraceFilterPlayersOnlySkipOne : public ITraceFilter
{
public:

    CTraceFilterPlayersOnlySkipOne( IClientEntity* ent )
    {
        pEnt = ent;
    }

    bool ShouldHitEntity( IClientEntity* pEntityHandle , int contentsMask )
    {
        return pEntityHandle != pEnt && pEntityHandle->GetClientClass()->m_ClassID == ClassId_CCSPlayer;
    }

    virtual TraceType GetTraceType() const
    {
        return TraceType::TRACE_ENTITIES_ONLY;
    }

    IClientEntity* pEnt;
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:

    CTraceFilterSkipTwoEntities( IClientEntity* ent1 , IClientEntity* ent2 )
    {
        pEnt1 = ent1;
        pEnt2 = ent2;
    }

    bool ShouldHitEntity( IClientEntity* pEntityHandle , int contentsMask )
    {
        return !( pEntityHandle == pEnt1 || pEntityHandle == pEnt2 );
    }

    virtual TraceType GetTraceType() const
    {
        return TraceType::TRACE_EVERYTHING;
    }

    IClientEntity* pEnt1;
    IClientEntity* pEnt2;
};

__pragma( warning( pop ) )

//-----------------------------------------------------------------------------
// A ray...
//-----------------------------------------------------------------------------
struct Ray
{
    VectorAligned  m_Start;	// starting point, centered within the extents
    VectorAligned  m_Delta;	// direction + length of the ray
    VectorAligned  m_StartOffset;	// Add this to m_Start to get the actual ray start
    VectorAligned  m_Extents;	// Describes an axis aligned box extruded along a ray
    const Matrix3x4 *m_pWorldAxisTransform;
    bool	m_IsRay;	// are the extents zero?
    bool	m_IsSwept;	// is delta != 0?

    Ray() : m_pWorldAxisTransform( nullptr )
    {}

    void Init( Vector const& start , Vector const& end )
    {
        VectorSubtract( end , start , m_Delta );

        m_IsSwept = ( m_Delta.Length() != 0 );

        m_Extents.Init();
        m_pWorldAxisTransform = nullptr;
        m_IsRay = true;

        // Offset m_Start to be in the center of the box...
        m_StartOffset.Init();
        m_Start = start;
    }

    void Init( Vector const& start , Vector const& end , Vector const& mins , Vector const& maxs )
    {
        VectorSubtract( end , start , m_Delta );

        m_pWorldAxisTransform = NULL;
        m_IsSwept = ( m_Delta.Length() != 0 );

        VectorSubtract( maxs , mins , m_Extents );
        m_Extents *= 0.5f;
        m_IsRay = ( m_Extents.Length() < 1e-6 );

        // Offset m_Start to be in the center of the box...
        VectorAdd( mins , maxs , m_StartOffset );
        m_StartOffset *= 0.5f;
        VectorAdd( start , m_StartOffset , m_Start );
        m_StartOffset *= -1.0f;
    }

    // compute inverse delta
    Vector InvDelta() const
    {
        Vector vecInvDelta;
        for ( int iAxis = 0; iAxis < 3; ++iAxis )
        {
            if ( m_Delta[ iAxis ] != 0.0f )
            {
                vecInvDelta[ iAxis ] = 1.0f / m_Delta[ iAxis ];
            }
            else
            {
                vecInvDelta[ iAxis ] = FLT_MAX;
            }
        }
        return vecInvDelta;
    }
};

class CBaseTrace
{
public:
    bool IsDispSurface( void )
    {
        return ( ( dispFlags & DISPSURF_FLAG_SURFACE ) != 0 );
    }
    bool IsDispSurfaceWalkable( void )
    {
        return ( ( dispFlags & DISPSURF_FLAG_WALKABLE ) != 0 );
    }
    bool IsDispSurfaceBuildable( void )
    {
        return ( ( dispFlags & DISPSURF_FLAG_BUILDABLE ) != 0 );
    }
    bool IsDispSurfaceProp1( void )
    {
        return ( ( dispFlags & DISPSURF_FLAG_SURFPROP1 ) != 0 );
    }
    bool IsDispSurfaceProp2( void )
    {
        return ( ( dispFlags & DISPSURF_FLAG_SURFPROP2 ) != 0 );
    }

public:

    // these members are aligned!!
    Vector         startpos;            // start position
    Vector         endpos;              // final position
    cplane_t       plane;               // surface normal at impact

    float          fraction;            // time completed, 1.0 = didn't hit anything

    int            contents;            // contents on other side of surface hit
    unsigned short dispFlags;           // displacement flags for marking surfaces with data

    bool           allsolid;            // if true, plane is not valid
    bool           startsolid;          // if true, the initial point was in a solid area

    CBaseTrace()
    {}
};

class CGameTrace : public CBaseTrace
{
public:

    bool DidHit() const;

public:

    float               fractionleftsolid;  // time we left a solid, only valid if we started in solid
    csurface_t          surface;            // surface hit (impact surface)
    int                 hitgroup;           // 0 == generic, non-zero is specific body part
    short               physicsbone;        // physics bone hit by trace in studio
    unsigned short      worldSurfaceIndex;  // Index of the msurface2_t, if applicable
    IClientEntity*      hit_entity;
    int                 hitbox;                       // box hit by trace in studio

    CGameTrace()
    {}

// No copy constructors allowed
    CGameTrace( const CGameTrace& other ) :
        fractionleftsolid( other.fractionleftsolid ) ,
        surface( other.surface ) ,
        hitgroup( other.hitgroup ) ,
        physicsbone( other.physicsbone ) ,
        worldSurfaceIndex( other.worldSurfaceIndex ) ,
        hit_entity( other.hit_entity ) ,
        hitbox( other.hitbox )
    {
        startpos = other.startpos;
        endpos = other.endpos;
        plane = other.plane;
        fraction = other.fraction;
        contents = other.contents;
        dispFlags = other.dispFlags;
        allsolid = other.allsolid;
        startsolid = other.startsolid;
    }

    CGameTrace& CGameTrace::operator=( const CGameTrace& other )
    {
        startpos = other.startpos;
        endpos = other.endpos;
        plane = other.plane;
        fraction = other.fraction;
        contents = other.contents;
        dispFlags = other.dispFlags;
        allsolid = other.allsolid;
        startsolid = other.startsolid;
        fractionleftsolid = other.fractionleftsolid;
        surface = other.surface;
        hitgroup = other.hitgroup;
        physicsbone = other.physicsbone;
        worldSurfaceIndex = other.worldSurfaceIndex;
        hit_entity = other.hit_entity;
        hitbox = other.hitbox;
        return *this;
    }
};

class IEntityEnumerator
{
public:
    // This gets called with each handle
    virtual bool EnumEntity( IHandleEntity *pHandleEntity ) = 0;
};

class ITraceListData
{
public:
    virtual ~ITraceListData()
    {}

    virtual void Reset() = 0;
    virtual bool IsEmpty() = 0;
    // CanTraceRay will return true if the current volume encloses the ray
    // NOTE: The leaflist trace will NOT check this.  Traces are intersected
    // against the culled volume exclusively.
    virtual bool CanTraceRay( const Ray &ray ) = 0;
};

class ICollideable
{
public:
    // Gets at the entity handle associated with the collideable
    virtual IHandleEntity	*GetEntityHandle() = 0;

    // These methods return the bounds of an OBB measured in "collision" space
    // which can be retreived through the CollisionToWorldTransform or
    // GetCollisionOrigin/GetCollisionAngles methods
    virtual const Vector&	OBBMins() const = 0;
    virtual const Vector&	OBBMaxs() const = 0;

    // Returns the bounds of a world-space box used when the collideable is being traced
    // against as a trigger. It's only valid to call these methods if the solid flags
    // have the FSOLID_USE_TRIGGER_BOUNDS flag set.
    virtual void			WorldSpaceTriggerBounds( Vector *pVecWorldMins , Vector *pVecWorldMaxs ) const = 0;

    // custom collision test
    virtual bool			TestCollision( const Ray &ray , unsigned int fContentsMask , trace_t& tr ) = 0;

    // Perform hitbox test, returns true *if hitboxes were tested at all*!!
    virtual bool			TestHitboxes( const Ray &ray , unsigned int fContentsMask , trace_t& tr ) = 0;

    // Returns the BRUSH model index if this is a brush model. Otherwise, returns -1.
    virtual int				GetCollisionModelIndex() = 0;

    // Return the model, if it's a studio model.
    virtual const model_t*	GetCollisionModel() = 0;

    // Get angles and origin.
    virtual const Vector&	GetCollisionOrigin() const = 0;
    virtual const Angle&	GetCollisionAngles() const = 0;
    virtual const Matrix3x4&	CollisionToWorldTransform() const = 0;

    // Return a SOLID_ define.
    virtual SolidType_t		GetSolid() const = 0;
    virtual int				GetSolidFlags() const = 0;

    // Gets at the containing class...
    virtual IClientUnknown*	GetIClientUnknown() = 0;

    // We can filter out collisions based on collision group
    virtual int				GetCollisionGroup() const = 0;

    // Returns a world-aligned box guaranteed to surround *everything* in the collision representation
    // Note that this will surround hitboxes, trigger bounds, physics.
    // It may or may not be a tight-fitting box and its volume may suddenly change
    virtual void			WorldSpaceSurroundingBounds( Vector *pVecMins , Vector *pVecMaxs ) = 0;

    virtual bool			ShouldTouchTrigger( int triggerSolidFlags ) const = 0;

    // returns NULL unless this collideable has specified FSOLID_ROOT_PARENT_ALIGNED
    virtual const Matrix3x4	*GetRootParentToWorldTransform() const = 0;
};

class IEngineTrace
{
public:
    // Returns the contents mask + entity at a particular world-space position
    virtual int		GetPointContents( const Vector &vecAbsPosition , int contentsMask = MASK_ALL , IHandleEntity** ppEntity = NULL ) = 0;

    // Returns the contents mask of the world only @ the world-space position (static props are ignored)
    virtual int		GetPointContents_WorldOnly( const Vector &vecAbsPosition , int contentsMask = MASK_ALL ) = 0;

    // Get the point contents, but only test the specific entity. This works
    // on static props and brush models.
    //
    // If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
    // bFailed to true if bFailed is non-null.
    virtual int		GetPointContents_Collideable( ICollideable *pCollide , const Vector &vecAbsPosition ) = 0;

    // Traces a ray against a particular entity
    virtual void	ClipRayToEntity( const Ray &ray , unsigned int fMask , IHandleEntity *pEnt , trace_t *pTrace ) = 0;

    // Traces a ray against a particular entity
    virtual void	ClipRayToCollideable( const Ray &ray , unsigned int fMask , ICollideable *pCollide , trace_t *pTrace ) = 0;

    // A version that simply accepts a ray (can work as a traceline or tracehull)
    virtual void	TraceRay( const Ray &ray , unsigned int fMask , ITraceFilter *pTraceFilter , trace_t *pTrace ) = 0;

    // A version that sets up the leaf and entity lists and allows you to pass those in for collision.
    virtual void	SetupLeafAndEntityListRay( const Ray &ray , ITraceListData *pTraceData ) = 0;
    virtual void    SetupLeafAndEntityListBox( const Vector &vecBoxMin , const Vector &vecBoxMax , ITraceListData *pTraceData ) = 0;
    virtual void	TraceRayAgainstLeafAndEntityList( const Ray &ray , ITraceListData *pTraceData , unsigned int fMask , ITraceFilter *pTraceFilter , trace_t *pTrace ) = 0;

    // A version that sweeps a collideable through the world
    // abs start + abs end represents the collision origins you want to sweep the collideable through
    // vecAngles represents the collision angles of the collideable during the sweep
    virtual void	SweepCollideable( ICollideable *pCollide , const Vector &vecAbsStart , const Vector &vecAbsEnd ,
                                      const Angle &vecAngles , unsigned int fMask , ITraceFilter *pTraceFilter , trace_t *pTrace ) = 0;

    // Enumerates over all entities along a ray
    // If triggers == true, it enumerates all triggers along a ray
    virtual void	EnumerateEntities( const Ray &ray , bool triggers , IEntityEnumerator *pEnumerator ) = 0;

    // Same thing, but enumerate entitys within a box
    virtual void	EnumerateEntities( const Vector &vecAbsMins , const Vector &vecAbsMaxs , IEntityEnumerator *pEnumerator ) = 0;

    // Convert a handle entity to a collideable.  Useful inside enumer
    virtual ICollideable *GetCollideable( IHandleEntity *pEntity ) = 0;

    // HACKHACK: Temp for performance measurments
    virtual int GetStatByIndex( int index , bool bClear ) = 0;

    //finds brushes in an AABB, prone to some false positives
    virtual void GetBrushesInAABB( const Vector &vMins , const Vector &vMaxs , CUtlVector<int> *pOutput , int iContentsMask = 0xFFFFFFFF ) = 0;

    //Creates a CPhysCollide out of all displacements wholly or partially contained in the specified AABB
    virtual CPhysCollide* GetCollidableFromDisplacementsInAABB( const Vector& vMins , const Vector& vMaxs ) = 0;

    // gets the number of displacements in the world
    virtual int GetNumDisplacements() = 0;

    // gets a specific diplacement mesh
    virtual void GetDisplacementMesh( int nIndex , virtualmeshlist_t *pMeshTriList ) = 0;

    //retrieve brush planes and contents, returns true if data is being returned in the output pointers, false if the brush doesn't exist
    virtual bool GetBrushInfo( int iBrush , CUtlVector<BrushSideInfo_t> *pBrushSideInfoOut , int *pContentsOut ) = 0;

    virtual bool PointOutsideWorld( const Vector &ptTest ) = 0; //Tests a point to see if it's outside any playable area

                                                                // Walks bsp to find the leaf containing the specified point
    virtual int GetLeafContainingPoint( const Vector &ptTest ) = 0;

    virtual ITraceListData *AllocTraceListData() = 0;
    virtual void FreeTraceListData( ITraceListData * ) = 0;

    /// Used only in debugging: get/set/clear/increment the trace debug counter. See comment below for details.
    virtual int GetSetDebugTraceCounter( int value , DebugTraceCounterBehavior_t behavior ) = 0;
};

class INetChannelInfo
{
public:

    enum
    {
        GENERIC = 0 ,	// must be first and is default group
        LOCALPLAYER ,	// bytes for local player entity update
        OTHERPLAYERS ,	// bytes for other players update
        ENTITIES ,		// all other entity bytes
        SOUNDS ,			// game sounds
        EVENTS ,			// event messages
        USERMESSAGES ,	// user messages
        ENTMESSAGES ,	// entity messages
        VOICE ,			// voice data
        STRINGTABLE ,	// a stringtable update
        MOVE ,			// client move cmds
        STRINGCMD ,		// string command
        SIGNON ,			// various signondata
        TOTAL ,			// must be last and is not a real group
    };

    virtual const char  *GetName( void ) const = 0;	// get channel name
    virtual const char  *GetAddress( void ) const = 0; // get channel IP address as string
    virtual float		GetTime( void ) const = 0;	// current net time
    virtual float		GetTimeConnected( void ) const = 0;	// get connection time in seconds
    virtual int			GetBufferSize( void ) const = 0;	// netchannel packet history size
    virtual int			GetDataRate( void ) const = 0; // send data rate in byte/sec

    virtual bool		IsLoopback( void ) const = 0;	// true if loopback channel
    virtual bool		IsTimingOut( void ) const = 0;	// true if timing out
    virtual bool		IsPlayback( void ) const = 0;	// true if demo playback

    virtual float		GetLatency( int flow ) const = 0;	 // current latency (RTT), more accurate but jittering
    virtual float		GetAvgLatency( int flow ) const = 0; // average packet latency in seconds
    virtual float		GetAvgLoss( int flow ) const = 0;	 // avg packet loss[0..1]
    virtual float		GetAvgChoke( int flow ) const = 0;	 // avg packet choke[0..1]
    virtual float		GetAvgData( int flow ) const = 0;	 // data flow in bytes/sec
    virtual float		GetAvgPackets( int flow ) const = 0; // avg packets/sec
    virtual int			GetTotalData( int flow ) const = 0;	 // total flow in/out in bytes
    virtual int			GetSequenceNr( int flow ) const = 0;	// last send seq number
    virtual bool		IsValidPacket( int flow , int frame_number ) const = 0; // true if packet was not lost/dropped/chocked/flushed
    virtual float		GetPacketTime( int flow , int frame_number ) const = 0; // time when packet was send
    virtual int			GetPacketBytes( int flow , int frame_number , int group ) const = 0; // group size of this packet
    virtual bool		GetStreamProgress( int flow , int *Recvd , int *total ) const = 0;  // TCP progress if transmitting
    virtual float		GetTimeSinceLastRecvd( void ) const = 0;	// get time since last Recvd packet in seconds
    virtual	float		GetCommandInterpolationAmount( int flow , int frame_number ) const = 0;
    virtual void		GetPacketResponseLatency( int flow , int frame_number , int *pnLatencyMsecs , int *pnChoke ) const = 0;
    virtual void		GetRemoteFramerate( float *pflFrameTime , float *pflFrameTimeStdDeviation ) const = 0;

    virtual float		GetTimeoutSeconds() const = 0;

    int *LastOutGoingCommand()
    {
        return _POffset( 0x4CB0 , int );
    }

    int *ChokedCommands()
    {
        return _POffset( 0x4CAC , int );
    }
};

class SurfInfo
{
public:
    // Shape of the surface.
    Vector			m_Verts[ MAX_SURFINFO_VERTS ];
    unsigned long	m_nVerts;

    // Plane of the surface.
    VPlane			m_Plane;

    // For engine use only..
    void			*m_pEngineData;
};

class IVEngineClient
{
public:
    // Find the model's surfaces that intersect the given sphere.
        // Returns the number of surfaces filled in.
    virtual int					GetIntersectingSurfaces(
        const model_t *model ,
        const Vector &vCenter ,
        const float radius ,
        const bool bOnlyVisibleSurfaces ,	// Only return surfaces visible to vCenter.
        SurfInfo *pInfos ,
        const int nMaxInfos ) = 0;

    // Get the lighting intensivty for a specified point
    // If bClamp is specified, the resulting Vector is restricted to the 0.0 to 1.0 for each element
    virtual Vector				GetLightForPoint( const Vector &pos , bool bClamp ) = 0;

    // Traces the line and reports the material impacted as well as the lighting information for the impact point
    virtual IMaterial			*TraceLineMaterialAndLighting( const Vector &start , const Vector &end ,
                                                               Vector &diffuseLightColor , Vector& baseColor ) = 0;

    // Given an input text buffer data pointer, parses a single token into the variable token and returns the new
    //  reading position
    virtual const char			*ParseFile( const char *data , char *token , int maxlen ) = 0;
    virtual bool				_CopyFile( const char *source , const char *destination ) = 0;

    // Gets the dimensions of the game window
    virtual void				GetScreenSize( int& width , int& height ) = 0;

    // Forwards szCmdString to the server, sent reliably if bReliable is set
    virtual void				ServerCmd( const char *szCmdString , bool bReliable = true ) = 0;
    // Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
    // Note: Calls to this are checked against FCVAR_CLIENTCMD_CAN_EXECUTE (if that bit is not set, then this function can't change it).
    //       Call ClientCmd_Unrestricted to have access to FCVAR_CLIENTCMD_CAN_EXECUTE vars.
    virtual void				ClientCmd( const char *szCmdString ) = 0;

    // Fill in the player info structure for the specified player index (name, model, etc.)
    virtual bool				GetPlayerInfo( int ent_num , player_info_t *pinfo ) = 0;

    // Retrieve the player entity number for a specified userID
    virtual int					GetPlayerForUserID( int userID ) = 0;

    // Retrieves text message system information for the specified message by name
    virtual client_textmessage_t *TextMessageGet( const char *pName ) = 0; // 10

                                                                           // Returns true if the console is visible
    virtual bool				Con_IsVisible( void ) = 0;

    // Get the entity index of the local player
    virtual int					GetLocalPlayer( void ) = 0;

    // Client DLL is hooking a model, loads the model into memory and returns  pointer to the model_t
    virtual const model_t		*LoadModel( const char *pName , bool bProp = false ) = 0;

    // Get the exact server timesstamp ( server time ) from the last message Recvd from the server
    virtual float				GetLastTimeStamp( void ) = 0;

    // Given a CAudioSource (opaque pointer), retrieve the underlying CSentence object ( stores the words, phonemes, and close
    //  captioning data )
    virtual CSentence			*GetSentence( CAudioSource *pAudioSource ) = 0; // 15
                                                                                // Given a CAudioSource, determines the length of the underlying audio file (.wav, .mp3, etc.)
    virtual float				GetSentenceLength( CAudioSource *pAudioSource ) = 0;
    // Returns true if the sound is streaming off of the hard disk (instead of being memory resident)
    virtual bool				IsStreaming( CAudioSource *pAudioSource ) const = 0;

    // Copy current view orientation into va
    virtual void				GetViewAngles( Angle& va ) = 0;
    // Set current view orientation from va
    virtual void				SetViewAngles( Angle& va ) = 0;

    // Retrieve the current game's maxclients setting
    virtual int					GetMaxClients( void ) = 0; // 20

                                                           // Given the string pBinding which may be bound to a key,
                                                           //  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
    virtual	const char			*Key_LookupBinding( const char *pBinding ) = 0;

    // Given the name of the key "mouse1", "e", "tab", etc., return the string it is bound to "+jump", "impulse 50", etc.
    virtual const char			*Key_BindingForKey( ButtonCode_t &code ) = 0;
    virtual void				Key_SetBinding( ButtonCode_t , char const* ) = 0;

    // key trapping (for binding keys)
    virtual void				StartKeyTrapMode( void ) = 0;
    virtual bool				CheckDoneKeyTrapping( ButtonCode_t &code ) = 0;

    // Returns true if the player is fully connected and active in game (i.e, not still loading)
    virtual bool				IsInGame( void ) = 0;
    // Returns true if the player is connected, but not necessarily active in game (could still be loading)
    virtual bool				IsConnected( void ) = 0;
    // Returns true if the loading plaque should be drawn
    virtual bool				IsDrawingLoadingImage( void ) = 0;
    virtual void				HideLoadingPlaque( void ) = 0;

    // Prints the formatted string to the notification area of the screen ( down the right hand edge
    //  numbered lines starting at position 0
    virtual void				Con_NPrintf( int pos , const char *fmt , ... ) = 0; // 30
                                                                                    // Similar to Con_NPrintf, but allows specifying custom text color and duration information
    virtual void				Con_NXPrintf( const struct con_nprint_s *info , const char *fmt , ... ) = 0;

    // Is the specified world-space bounding box inside the view frustum?
    virtual int					IsBoxVisible( const Vector& mins , const Vector& maxs ) = 0;

    // Is the specified world-space boudning box in the same PVS cluster as the view origin?
    virtual int					IsBoxInViewCluster( const Vector& mins , const Vector& maxs ) = 0;

    // Returns true if the specified box is outside of the view frustum and should be culled
    virtual bool				CullBox( const Vector& mins , const Vector& maxs ) = 0;

    // Allow the sound system to paint additional data (during lengthy rendering operations) to prevent stuttering sound.
    virtual void				Sound_ExtraUpdate( void ) = 0;

    // Get the current game directory ( e.g., hl2, tf2, cstrike, hl1 )
    virtual const char			*GetGameDirectory( void ) = 0;

    // Get access to the world to screen transformation matrix
    virtual const VMatrix& 		WorldToScreenMatrix() = 0;

    // Get the matrix to move a point from world space into view space
    // (translate and rotate so the camera is at the origin looking down X).
    virtual const VMatrix& 		WorldToViewMatrix() = 0;

    // The .bsp file can have mod-specified data lumps. These APIs are for working with such game lumps.

    // Get mod-specified lump version id for the specified game data lump
    virtual int					GameLumpVersion( int lumpId ) const = 0;
    // Get the raw size of the specified game data lump.
    virtual int					GameLumpSize( int lumpId ) const = 0; // 40
                                                                      // Loads a game lump off disk, writing the data into the buffer pointed to by pBuffer
                                                                      // Returns false if the data can't be read or the destination buffer is too small
    virtual bool				LoadGameLump( int lumpId , void* pBuffer , int size ) = 0;

    // Returns the number of leaves in the level
    virtual int					LevelLeafCount() const = 0;

    // Gets a way to perform spatial queries on the BSP tree
    virtual Pointer		GetBSPTreeQuery() = 0;

    // Convert texlight to gamma...
    virtual void		LinearToGamma( float* linear , float* gamma ) = 0;

    // Get the lightstyle value
    virtual float		LightStyleValue( int style ) = 0; // 45

                                                          // Computes light due to dynamic lighting at a point
                                                          // If the normal isn't specified, then it'll return the maximum lighting
    virtual void		ComputeDynamicLighting( const Vector& pt , const Vector* pNormal , Vector& color ) = 0;

    // Returns the color of the ambient light
    virtual void		GetAmbientLightColor( Vector& color ) = 0;

    // Returns the dx support level
    virtual int			GetDXSupportLevel() = 0;

    // GR - returns the HDR support status
    virtual bool        SupportsHDR() = 0;

    // Replace the engine's material system pointer.
    virtual void		Mat_Stub( IMaterialSystem *pMatSys ) = 0; // 50

                                                                  // Get the name of the current map
    virtual void GetChapterName( char *pchBuff , int iMaxLength ) = 0;
    virtual char const	*GetLevelName( void ) = 0;
    virtual char const	*GetLevelNameShort( void ) = 0;
    virtual char const	*GetMapGroupName( void ) = 0;

    // Obtain access to the voice tweaking API
    virtual struct IVoiceTweak_s *GetVoiceTweakAPI( void ) = 0;

    ///// new virtual added on 14\08\2014 /////
    virtual void SetVoiceCasterID( unsigned int someint ) = 0; // 56

                                                               // Tell engine stats gathering system that the rendering frame is beginning/ending
    virtual void		EngineStats_BeginFrame( void ) = 0;
    virtual void		EngineStats_EndFrame( void ) = 0;

    // This tells the engine to fire any events (temp entity messages) that it has queued up this frame.
    // It should only be called once per frame.
    virtual void		FireEvents() = 0;

    // Returns an area index if all the leaves are in the same area. If they span multple areas, then it returns -1.
    virtual int			GetLeavesArea( unsigned short *pLeaves , int nLeaves ) = 0;

    // Returns true if the box touches the specified area's frustum.
    virtual bool		DoesBoxTouchAreaFrustum( const Vector &mins , const Vector &maxs , int iArea ) = 0; // 60
    virtual int			GetFrustumList( Pointer *pList , int listMax ) = 0;
    virtual bool		ShouldUseAreaFrustum( int i ) = 0;

    // Sets the hearing origin (i.e., the origin and orientation of the listener so that the sound system can spatialize
    //  sound appropriately ).
    virtual void		SetAudioState( const AudioState_t& state ) = 0;

    // Sentences / sentence groups
    virtual int			SentenceGroupPick( int groupIndex , char *name , int nameBufLen ) = 0;
    virtual int			SentenceGroupPickSequential( int groupIndex , char *name , int nameBufLen , int sentenceIndex , int reset ) = 0;
    virtual int			SentenceIndexFromName( const char *pSentenceName ) = 0;
    virtual const char *SentenceNameFromIndex( int sentenceIndex ) = 0;
    virtual int			SentenceGroupIndexFromName( const char *pGroupName ) = 0;
    virtual const char *SentenceGroupNameFromIndex( int groupIndex ) = 0;
    virtual float		SentenceLength( int sentenceIndex ) = 0;

    // Computes light due to dynamic lighting at a point
    // If the normal isn't specified, then it'll return the maximum lighting
    // If pBoxColors is specified (it's an array of 6), then it'll copy the light contribution at each box side.
    virtual void		ComputeLighting( const Vector& pt , const Vector* pNormal , bool bClamp , Vector& color , Vector *pBoxColors = NULL ) = 0;

    // Activates/deactivates an occluder...
    virtual void		ActivateOccluder( int nOccluderIndex , bool bActive ) = 0;
    virtual bool		IsOccluded( const Vector &vecAbsMins , const Vector &vecAbsMaxs ) = 0; // 74
    virtual int			GetOcclusionViewId( void ) = 0;

    // The save restore system allocates memory from a shared memory pool, use this allocator to allocate/free saverestore
    //  memory.
    virtual void		*SaveAllocMemory( size_t num , size_t size ) = 0;
    virtual void		SaveFreeMemory( void *pSaveMem ) = 0;

    // returns info interface for client netchannel
    virtual INetChannelInfo	*GetNetChannelInfo( void ) = 0;

    // Debugging functionality:
    // Very slow routine to draw a physics model
    virtual void		DebugDrawPhysCollide( const CPhysCollide *pCollide , IMaterial *pMaterial , const Matrix3x4& transform , const color32 &color ) = 0; //79
                                                                                                                                                               // This can be used to notify test scripts that we're at a particular spot in the code.
    virtual void		CheckPoint( const char *pName ) = 0; // 80
                                                             // Draw portals if r_DrawPortals is set (Debugging only)
    virtual void		DrawPortals() = 0;
    // Determine whether the client is playing back or recording a demo
    virtual bool		IsPlayingDemo( void ) = 0;
    virtual bool		IsRecordingDemo( void ) = 0;
    virtual bool		IsPlayingTimeDemo( void ) = 0;
    virtual int			GetDemoRecordingTick( void ) = 0;
    virtual int			GetDemoPlaybackTick( void ) = 0;
    virtual int			GetDemoPlaybackStartTick( void ) = 0;
    virtual float		GetDemoPlaybackTimeScale( void ) = 0;
    virtual int			GetDemoPlaybackTotalTicks( void ) = 0;
    // Is the game paused?
    virtual bool		IsPaused( void ) = 0; // 90

                                              // What is the game timescale multiplied with the host_timescale?
    virtual float GetTimescale( void ) const = 0;

    // Is the game currently taking a screenshot?
    virtual bool		IsTakingScreenshot( void ) = 0;
    // Is this a HLTV broadcast ?
    virtual bool		IsHLTV( void ) = 0;
    // Is this a Replay demo?
    //virtual bool		IsReplay( void ) = 0;
    // is this level loaded as just the background to the main menu? (active, but unplayable)
    virtual bool		IsLevelMainMenuBackground( void ) = 0;
    // returns the name of the background level
    virtual void		GetMainMenuBackgroundName( char *dest , int destlen ) = 0;

    // Occlusion system control
    virtual void		SetOcclusionParameters( const OcclusionParams_t &params ) = 0; // 96

                                                                                       // What language is the user expecting to hear .wavs in, "english" or another...
    virtual void		GetUILanguage( char *dest , int destlen ) = 0;

    // Can skybox be seen from a particular point?
    virtual SkyboxVisibility_t IsSkyboxVisibleFromPoint( const Vector &vecPoint ) = 0;

    // Get the pristine map entity lump string.  (e.g., used by CS to reload the map entities when restarting a round.)
    virtual const char*	GetMapEntitiesString() = 0;

    // Is the engine in map edit mode ?
    virtual bool		IsInEditMode( void ) = 0; // 100

                                                  // current screen aspect ratio (eg. 4.0f/3.0f, 16.0f/9.0f)
    virtual float		GetScreenAspectRatio( int viewportWidth , int viewportHeight ) = 0;

    // allow the game UI to login a user
    virtual bool		REMOVED_SteamRefreshLogin( const char *password , bool isSecure ) = 0; // 100
    virtual bool		REMOVED_SteamProcessCall( bool & finished ) = 0;

    // allow other modules to know about engine versioning (one use is a proxy for network compatability)
    virtual unsigned int	GetEngineBuildNumber() = 0; // engines build
    virtual const char *	GetProductVersionString() = 0; // mods version number (steam.inf)

                                                           // Communicates to the color correction editor that it's time to grab the pre-color corrected frame
                                                           // Passes in the actual size of the viewport
    virtual void			GrabPreColorCorrectedFrame( int x , int y , int width , int height ) = 0;

    virtual bool			IsHammerRunning() const = 0;

    // Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
    // And then executes the command string immediately (vs ClientCmd() which executes in the next frame)
    //
    // Note: this is NOT checked against the FCVAR_CLIENTCMD_CAN_EXECUTE vars.
    virtual void			ExecuteClientCmd( const char *szCmdString ) = 0; //108

                                                                             // returns if the loaded map was processed with HDR info. This will be set regardless
                                                                             // of what HDR mode the player is in.
    virtual bool MapHasHDRLighting( void ) = 0;
    virtual bool MapHasLightMapAlphaData( void ) = 0;

    virtual int	GetAppID() = 0;

    // Just get the leaf ambient light - no caching, no samples
    virtual Vector			GetLightForPointFast( const Vector &pos , bool bClamp ) = 0;

    // This version does NOT check against FCVAR_CLIENTCMD_CAN_EXECUTE.
    virtual void			ClientCmd_Unrestricted( char  const* , int , bool );
    virtual void			ClientCmd_Unrestricted( const char *szCmdString ) = 0; // 114

                                                                                   // This used to be accessible through the cl_restrict_server_commands cvar.
                                                                                   // By default, Valve games restrict the server to only being able to execute commands marked with FCVAR_SERVER_CAN_EXECUTE.
                                                                                   // By default, mods are allowed to execute any server commands, and they can restrict the server's ability to execute client
                                                                                   // commands with this function.
    virtual void			SetRestrictServerCommands( bool bRestrict ) = 0;

    // If set to true (defaults to true for Valve games and false for others), then IVEngineClient::ClientCmd
    // can only execute things marked with FCVAR_CLIENTCMD_CAN_EXECUTE.
    virtual void			SetRestrictClientCommands( bool bRestrict ) = 0;

    // Sets the client renderable for an overlay's material proxy to bind to
    virtual void			SetOverlayBindProxy( int iOverlayID , void *pBindProxy ) = 0;

    virtual bool			CopyFrameBufferToMaterial( const char *pMaterialName ) = 0;

    // Causes the engine to read in the user's configuration on disk
    virtual void			ReadConfiguration( const int iController , const bool readDefault ) = 0;

    virtual void			SetAchievementMgr( IAchievementMgr *pAchievementMgr ) = 0;
    virtual IAchievementMgr*GetAchievementMgr() = 0;
    virtual bool			MapLoadFailed( void ) = 0;
    virtual void			SetMapLoadFailed( bool bState ) = 0;
    virtual bool			IsLowViolence() = 0;
    virtual const char		*GetMostRecentSaveGame( void ) = 0;
    virtual void			SetMostRecentSaveGame( const char *lpszFilename ) = 0;
    virtual void			StartXboxExitingProcess() = 0;
    virtual bool			IsSaveInProgress() = 0;
    virtual bool			IsAutoSaveDangerousInProgress( void ) = 0;
    virtual UINT			OnStorageDeviceAttached( int iController ) = 0;
    virtual void			OnStorageDeviceDetached( int iController ) = 0;
    virtual char* const		GetSaveDirName( void ) = 0;
    // generic screenshot writing
    virtual void			WriteScreenshot( const char *pFilename ) = 0;
    virtual void			ResetDemoInterpolation( void ) = 0;
    // For non-split screen games this will always be zero
    virtual int				GetActiveSplitScreenPlayerSlot() = 0;
    virtual int				SetActiveSplitScreenPlayerSlot( int slot ) = 0;
    // This is the current # of players on the local host
    virtual bool			SetLocalPlayerIsResolvable( char const *pchContext , int nLine , bool bResolvable ) = 0;
    virtual bool			IsLocalPlayerResolvable() = 0;
    virtual int				GetSplitScreenPlayer( int nSlot ) = 0;
    virtual bool			IsSplitScreenActive() = 0;
    virtual bool			IsValidSplitScreenSlot( int nSlot ) = 0;
    virtual int				FirstValidSplitScreenSlot() = 0; // -1 == invalid
    virtual int				NextValidSplitScreenSlot( int nPreviousSlot ) = 0; // -1 == invalid
                                                                               //Finds or Creates a shared memory space, the returned pointer will automatically be AddRef()ed
    virtual Pointer GetSinglePlayerSharedMemorySpace( const char *szName , int ent_num = MAX_EDICTS ) = 0;
    // Computes an ambient cube that includes ALL dynamic lights
    virtual void ComputeLightingCube( const Vector& pt , bool bClamp , Vector *pBoxColors ) = 0;
    //All callbacks have to be registered before demo recording begins. TODO: Macro'ize a way to do it at startup
    virtual void RegisterDemoCustomDataCallback( int szCallbackSaveID , int pCallback ) = 0;
    virtual void RecordDemoCustomData( int pCallback , const void *pData , size_t iDataLength ) = 0;
    // global sound pitch scaling
    virtual void SetPitchScale( float flPitchScale ) = 0;
    virtual float GetPitchScale( void ) = 0;
    // Load/unload the SFM - used by Replay
    virtual bool		LoadFilmmaker() = 0;
    virtual void		UnloadFilmmaker() = 0;
    // leaf flag management. Allows fast leaf enumeration of leaves that have a flag set
    // set a bit in a leaf flag
    virtual void SetLeafFlag( int nLeafIndex , int nFlagBits ) = 0;
    // you must call this once done modifying flags. Not super fast.
    virtual void RecalculateBSPLeafFlags( void ) = 0;
    virtual bool DSPGetCurrentDASRoomNew( void ) = 0;
    virtual bool DSPGetCurrentDASRoomChanged( void ) = 0;
    virtual bool DSPGetCurrentDASRoomSkyAbove( void ) = 0;
    virtual float DSPGetCurrentDASRoomSkyPercent( void ) = 0;
    virtual void SetMixGroupOfCurrentMixer( const char *szgroupname , const char *szparam , float val , int setMixerType ) = 0;
    virtual int GetMixLayerIndex( const char *szmixlayername ) = 0;
    virtual void SetMixLayerLevel( int index , float level ) = 0;
    virtual int	 GetMixGroupIndex( char  const* groupname ) = 0;
    virtual void SetMixLayerTriggerFactor( int i1 , int i2 , float fl ) = 0;
    virtual void SetMixLayerTriggerFactor( char  const* char1 , char  const* char2 , float fl ) = 0;
    virtual bool IsCreatingReslist() = 0;
    virtual bool IsCreatingXboxReslist() = 0;
    virtual void SetTimescale( float flTimescale ) = 0;
    // Methods to set/get a gamestats data container so client & server running in same process can send combined data
    virtual void SetGamestatsData( CGamestatsData *pGamestatsData ) = 0;
    virtual CGamestatsData *GetGamestatsData() = 0;
    virtual void GetMouseDelta( int &dx , int &dy , bool b ) = 0; // unknown
                                                                  // Given the string pBinding which may be bound to a key,
                                                                  //  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
                                                                  // Increment start count to iterate through multiple keys bound to the same binding
                                                                  // iAllowJoystick defaults to -1 witch returns joystick and non-joystick binds, 0 returns only non-joystick, 1 returns only joystick
    virtual	const char *Key_LookupBindingEx( const char *pBinding , int iUserId = -1 , int iStartCount = 0 , int iAllowJoystick = -1 ) = 0;
    virtual int			Key_CodeForBinding( char  const* , int , int , int ) = 0;
    // Updates dynamic light state. Necessary for light cache to work properly for d- and elights
    virtual void UpdateDAndELights( void ) = 0;
    // Methods to get bug count for internal dev work stat tracking.
    // Will get the bug count and clear it every map transition
    virtual int			GetBugSubmissionCount() const = 0;
    virtual void		ClearBugSubmissionCount() = 0;
    // Is there water anywhere in the level?
    virtual bool	DoesLevelContainWater() const = 0;
    // How much time was spent in server simulation?
    virtual float	GetServerSimulationFrameTime() const = 0;
    virtual void SolidMoved( class IClientEntity *pSolidEnt , class ICollideable *pSolidCollide , const Vector* pPrevAbsOrigin , bool accurateBboxTriggerChecks ) = 0;
    virtual void TriggerMoved( class IClientEntity *pTriggerEnt , bool accurateBboxTriggerChecks ) = 0;
    // Using area bits, check whether the area of the specified point flows into the other areas
    virtual void ComputeLeavesConnected( const Vector &vecOrigin , int nCount , const int *pLeafIndices , bool *pIsConnected ) = 0;
    // Is the engine in Commentary mode?
    virtual bool IsInCommentaryMode( void ) = 0;
    virtual void SetBlurFade( float amount ) = 0;
    virtual bool IsTransitioningToLoad() = 0;
    virtual void SearchPathsChangedAfterInstall() = 0;
    virtual void ConfigureSystemLevel( int nCPULevel , int nGPULevel ) = 0;
    virtual void SetConnectionPassword( char const *pchCurrentPW ) = 0;
    virtual Pointer GetSteamAPIContext() = 0;
    virtual void SubmitStatRecord( char const *szMapName , UINT uiBlobVersion , UINT uiBlobSize , const void *pvBlob ) = 0;
    // Sends a key values server command, not allowed from scripts execution
    // Params:
    //	pKeyValues	- key values to be serialized and sent to server
    //				  the pointer is deleted inside the function: pKeyValues->deleteThis()
    virtual void ServerCmdKeyValues( KeyValues *pKeyValues ) = 0; // 203
                                                                  // Tells the engine what and where to paint
    virtual void SpherePaintSurface( const model_t* model , const Vector& location , unsigned char chr , float fl1 , float fl2 ) = 0;
    virtual bool HasPaintmap( void ) = 0;
    // Enable paint in the engine for project Paint
    virtual void EnablePaintmapRender() = 0;
    //virtual void TracePaintSurface( const model_t *model, const Vector& position, float radius, CUtlVector<Color>& surfColors ) = 0;
    virtual void SphereTracePaintSurface( const model_t* model , const Vector& position , const Vector &vec2 , float radius , CUtlVector<unsigned char , CUtlMemory<unsigned char , int>> & utilVecShit ) = 0;
    virtual void RemoveAllPaint() = 0;
    virtual void PaintAllSurfaces( unsigned char uchr ) = 0;
    virtual void RemovePaint( const model_t* model ) = 0;

    virtual bool IsActiveApp() = 0;

    // is this client running inside the same process as an active server?
    virtual bool IsClientLocalToActiveServer() = 0;

    // Callback for LevelInit to tick the progress bar during time consuming operations
    virtual void TickProgressBar() = 0;

    // Returns the requested input context
    virtual InputContextHandle_t GetInputContext( int id ) = 0;
    virtual void				GetStartupImage( char* filename , int size ) = 0;
    virtual bool				IsUsingLocalNetworkBackdoor( void ) = 0;
    virtual void				SaveGame( const char* , bool , char* , int , char* , int ) = 0;
    virtual void				GetGenericMemoryStats(/* GenericMemoryStat_t */ void ** ) = 0;
    virtual bool				GameHasShutdownAndFlushedMemory( void ) = 0;
    virtual int					GetLastAcknowledgedCommand( void ) = 0;
    virtual void				FinishContainerWrites( int i ) = 0;
    virtual void				FinishAsyncSave( void ) = 0;
    virtual int					GetServerTick( void ) = 0;
    virtual const char*			GetModDirectory( void ) = 0;
    virtual bool				AudioLanguageChanged( void ) = 0;
    virtual bool				IsAutoSaveInProgress( void ) = 0;
    virtual void				StartLoadingScreenForCommand( const char* command ) = 0;
    virtual void				StartLoadingScreenForKeyValues( KeyValues* values ) = 0;
    virtual void				SOSSetOpvarFloat( const char* , float ) = 0;
    virtual void				SOSGetOpvarFloat( const char* , float & ) = 0;
    virtual bool				IsSubscribedMap( const char* , bool ) = 0;
    virtual bool				IsFeaturedMap( const char* , bool ) = 0;
    virtual void				GetDemoPlaybackParameters( void ) = 0;
    virtual int					GetClientVersion( void ) = 0;
    virtual bool				IsDemoSkipping( void ) = 0;
    virtual void				SetDemoImportantEventData( const KeyValues* values ) = 0;
    virtual void				ClearEvents( void );
    virtual int					GetSafeZoneXMin( void );
    virtual bool				IsVoiceRecording( void );
    virtual void				ForceVoiceRecordOn( void );
    virtual bool				IsReplay( void );

    // let client lock mouse to the window bounds
    //virtual void SetMouseWindowLock( bool bLockToWindow ) = 0;
};

class CGlowObjectManager_CSGO
{
public:

    int RegisterGlowObject( C_BaseEntity *pEntity , const Vector &vGlowColor , float flGlowAlpha , bool bRenderWhenOccluded , bool bRenderWhenUnoccluded , int nSplitScreenSlot )
    {
        int nIndex;
        if ( m_nFirstFreeSlot == GlowObjectDefinition_t::END_OF_FREE_LIST )
        {
            nIndex = m_GlowObjectDefinitions.AddToTail();
        }
        else
        {
            nIndex = m_nFirstFreeSlot;
            m_nFirstFreeSlot = m_GlowObjectDefinitions[ nIndex ].m_nNextFreeSlot;
        }

        m_GlowObjectDefinitions[ nIndex ].m_hEntity = pEntity;
        m_GlowObjectDefinitions[ nIndex ].m_vGlowColor = vGlowColor;
        m_GlowObjectDefinitions[ nIndex ].m_flGlowAlpha = flGlowAlpha;
        m_GlowObjectDefinitions[ nIndex ].flUnk = 0.0f;
        m_GlowObjectDefinitions[ nIndex ].m_flBloomAmount = 1.0f;
        m_GlowObjectDefinitions[ nIndex ].localplayeriszeropoint3 = 0.0f;
        m_GlowObjectDefinitions[ nIndex ].m_bRenderWhenOccluded = bRenderWhenOccluded;
        m_GlowObjectDefinitions[ nIndex ].m_bRenderWhenUnoccluded = bRenderWhenUnoccluded;
        m_GlowObjectDefinitions[ nIndex ].m_bFullBloomRender = false;
        m_GlowObjectDefinitions[ nIndex ].m_nFullBloomStencilTestValue = 0;
        m_GlowObjectDefinitions[ nIndex ].m_nSplitScreenSlot = nSplitScreenSlot;
        m_GlowObjectDefinitions[ nIndex ].m_nNextFreeSlot = GlowObjectDefinition_t::ENTRY_IN_USE;

        return nIndex;
    }

    void UnregisterGlowObject( int nGlowObjectHandle )
    {
        m_GlowObjectDefinitions[ nGlowObjectHandle ].m_nNextFreeSlot = m_nFirstFreeSlot;
        m_GlowObjectDefinitions[ nGlowObjectHandle ].m_hEntity = NULL;
        m_nFirstFreeSlot = nGlowObjectHandle;
    }

    int HasGlowEffect( C_BaseEntity *pEntity )
    {
        for ( int i = 0; i < m_GlowObjectDefinitions.Count(); ++i )
        {
            if ( !m_GlowObjectDefinitions[ i ].IsUnused() && m_GlowObjectDefinitions[ i ].m_hEntity == pEntity )
            {
                return i;
            }
        }

        return NULL;
    }

    class GlowObjectDefinition_t
    {
    public:
        void Set( float r , float g , float b , float a )
        {
            m_vGlowColor = Vector( r , g , b );
            m_flGlowAlpha = a;
            m_bRenderWhenOccluded = true;
            m_bRenderWhenUnoccluded = false;
            m_flBloomAmount = 1.0f;
        }

        C_BaseEntity* getEnt()
        {
            return m_hEntity;
        }

        bool IsUnused() const
        {
            return m_nNextFreeSlot != GlowObjectDefinition_t::ENTRY_IN_USE;
        }

    public:
        C_BaseEntity * m_hEntity;
        Vector            m_vGlowColor;
        float            m_flGlowAlpha;

        char            unknown[ 4 ]; //pad
        float            flUnk; //confirmed to be treated as a float while reversing glow functions
        float            m_flBloomAmount;
        float            localplayeriszeropoint3;

        bool            m_bRenderWhenOccluded;
        bool            m_bRenderWhenUnoccluded;
        bool            m_bFullBloomRender;
        char            unknown1[ 1 ]; //pad

        int                m_nFullBloomStencilTestValue; // 0x28
        int                iUnk; //appears like it needs to be zero
        int                m_nSplitScreenSlot; //Should be -1

                                               // Linked list of free slots
        int                m_nNextFreeSlot;

        // Special values for GlowObjectDefinition_t::m_nNextFreeSlot
        static const int END_OF_FREE_LIST = -1;
        static const int ENTRY_IN_USE = -2;
    };

    CUtlVector< GlowObjectDefinition_t > m_GlowObjectDefinitions;
    int m_nFirstFreeSlot;
    int max_size;
    int pad;
    int size;
    GlowObjectDefinition_t* m_GlowObjectDefinitions2;
    int currentObjects;
};

class IBaseInterface
{
public:
    virtual	~IBaseInterface()
    {}
};

enum EInterfaceID
{
    ICLIENTPANEL_STANDARD_INTERFACE = 0 ,
};

class IPhysicsSurfaceProps
{
public:
    virtual ~IPhysicsSurfaceProps( void )
    {}

  // parses a text file containing surface prop keys
    virtual int		ParseSurfaceData( const char *pFilename , const char *pTextfile ) = 0;
    // current number of entries in the database
    virtual int		SurfacePropCount( void ) const = 0;

    virtual int		GetSurfaceIndex( const char *pSurfacePropName ) const = 0;
    virtual void	GetPhysicsProperties( int surfaceDataIndex , float *density , float *thickness , float *friction , float *elasticity ) const = 0;

    virtual surfacedata_t	*GetSurfaceData( int surfaceDataIndex ) = 0;
    virtual const char		*GetString( unsigned short stringTableIndex ) const = 0;

    virtual const char		*GetPropName( int surfaceDataIndex ) const = 0;

    // sets the global index table for world materials
    // UNDONE: Make this per-CPhysCollide
    virtual void	SetWorldMaterialIndexTable( int *pMapArray , int mapSize ) = 0;

    // NOTE: Same as GetPhysicsProperties, but maybe more convenient
    virtual void	GetPhysicsParameters( int surfaceDataIndex , surfacephysicsparams_t *pParamsOut ) const = 0;
};

class INetMessage
{
public:
    virtual	~INetMessage()
    {};

    // Use these to setup who can hear whose voice.
    // Pass in client indices (which are their ent indices - 1).

    virtual void	SetNetChannel( INetChannelInfo * netchan ) = 0; // netchannel this message is from/for
    virtual void	SetReliable( bool state ) = 0;	// set to true if it's a reliable message

    virtual bool	Process( void ) = 0; // calls the recently set handler to process this message

    virtual	bool	ReadFromBuffer( bf_read &buffer ) = 0; // returns true if parsing was OK
    virtual	bool	WriteToBuffer( bf_write &buffer ) = 0;	// returns true if writing was OK

    virtual bool	IsReliable( void ) const = 0;  // true, if message needs reliable handling

    virtual int				GetType( void ) const = 0; // returns module specific header tag eg svc_serverinfo
    virtual int				GetGroup( void ) const = 0;	// returns net message group of this message
    virtual const char		*GetName( void ) const = 0;	// returns network message name, eg "svc_serverinfo"
    virtual INetChannelInfo		*GetNetChannel( void ) const = 0;
    virtual const char		*ToString( void ) const = 0; // returns a human readable string about message content
    virtual size_t			GetSize() const = 0;
};


class CNetMessage : public INetMessage
{
public:
    CNetMessage()
    {
        m_bReliable = true;
        m_NetChannel = NULL;
    }

    virtual ~CNetMessage()
    {};

    virtual int		GetGroup() const
    {
        return INetChannelInfo::GENERIC;
    }
    INetChannelInfo *GetNetChannel() const
    {
        return m_NetChannel;
    }

    virtual void	SetReliable( bool state )
    {
        m_bReliable = state;
    };
    virtual bool	IsReliable() const
    {
        return m_bReliable;
    };
    virtual void    SetNetChannel( INetChannelInfo * netchan )
    {
        m_NetChannel = netchan;
    }
    virtual bool	Process()
    {
        return false;
    };	// no handler set

public:
    bool				m_bReliable;	// true if message should be send reliable
    INetChannelInfo	    *m_NetChannel;	// netchannel this message is from/for
};
typedef enum
{
    NA_NULL = 0 ,
    NA_LOOPBACK ,
    NA_BROADCAST ,
    NA_IP ,
} netadrtype_t;

class netadr_t
{
public:

    netadr_t()
    {
        for ( int i = 0; i < 4; i++ )
            ip[ i ] = 0;
        type = NA_IP;
        port = 0;
    }

    netadrtype_t	type;
    unsigned char	ip[ 4 ];
    unsigned short	port;
};

typedef struct netpacket_s
{
    netadr_t		from;		// sender IP
    int				source;		// Recvd source
    double			Recvd;	// Recvd time
    unsigned char	*data;		// pointer to raw packet data
    bf_read			message;	// easy bitbuf data access
    int				size;		// size in bytes
    int				wiresize;   // size in bytes before decompression
    bool			stream;		// was send as stream
    struct netpacket_s *pNext;	// for internal use, should be NULL in public
} netpacket_t;

class INetChannel;

class INetChannelHandler
{
public:
    virtual	~INetChannelHandler( void )
    {};

    virtual void ConnectionStart( INetChannel *chan ) = 0;	// called first time network channel is established

    virtual void ConnectionClosing( const char *reason ) = 0; // network channel is being closed by remote site

    virtual void ConnectionCrashed( const char *reason ) = 0; // network error occured

    virtual void PacketStart( int incoming_sequence , int outgoing_acknowledged ) = 0;	// called each time a new packet arrived

    virtual void PacketEnd( void ) = 0; // all messages has been parsed

    virtual void FileRequested( const char *fileName , unsigned int transferID , bool isReplayDemoFile ) = 0; // other side request a file for download

    virtual void FileRecvd( const char *fileName , unsigned int transferID , bool isReplayDemoFile ) = 0; // we Recvd a file

    virtual void FileDenied( const char *fileName , unsigned int transferID , bool isReplayDemoFile ) = 0;	// a file request was denied by other side

    virtual void FileSent( const char *fileName , unsigned int transferID , bool isReplayDemoFile ) = 0;	// we sent a file

    virtual bool ChangeSplitscreenUser( int );
};

class INetChannel : public INetChannelInfo
{
public:
    virtual	~INetChannel( void )
    {};

    virtual void	SetDataRate( float rate ) = 0;
    virtual bool	RegisterMessage( Pointer msg ) = 0;
    virtual bool	UnregisterMessage( Pointer msg ) = 0;
    virtual bool	StartStreaming( unsigned int challengeNr ) = 0;
    virtual void	ResetStreaming( void ) = 0;
    virtual void	SetTimeout( float seconds , bool bForceExact = false ) = 0;
    virtual void	SetDemoRecorder( Pointer recorder ) = 0;
    virtual void	SetChallengeNr( unsigned int chnr ) = 0;

    virtual void	Reset( void ) = 0;
    virtual void	Clear( void ) = 0;
    virtual void	Shutdown( const char *reason ) = 0;

    virtual void	ProcessPlayback( void ) = 0;
    virtual bool	ProcessStream( void ) = 0;
    virtual void	ProcessPacket( struct netpacket_s* packet , bool bHasHeader ) = 0;

    virtual bool	SendNetMsg( INetMessage &msg , bool bForceReliable = false , bool bVoice = false ) = 0;
    virtual bool	SendData( bf_write &msg , bool bReliable = true ) = 0;
    virtual bool	SendFile( const char *filename , unsigned int transferID , bool isReplayDemo ) = 0;
    virtual void	DenyFile( const char *filename , unsigned int transferID , bool isReplayDemo ) = 0;
    virtual void	RequestFile_OLD( const char *filename , unsigned int transferID ) = 0;	// get rid of this function when we version the
    virtual void	SetChoked( void ) = 0;
    virtual int		SendDatagram( bf_write *data ) = 0;
    virtual bool	Transmit( bool onlyReliable = false ) = 0;

    virtual const netadr_t	&GetRemoteAddress( void ) const = 0;
    virtual INetChannelHandler *GetMsgHandler( void ) const = 0;
    virtual int				GetDropNumber( void ) const = 0;
    virtual int				GetSocket( void ) const = 0;
    virtual unsigned int	GetChallengeNr( void ) const = 0;
    virtual void			GetSequenceData( int &nOutSequenceNr , int &nInSequenceNr , int &nOutSequenceNrAck ) = 0;
    virtual void			SetSequenceData( int nOutSequenceNr , int nInSequenceNr , int nOutSequenceNrAck ) = 0;

    virtual void	UpdateMessageStats( int msggroup , int bits ) = 0;
    virtual bool	CanPacket( void ) const = 0;
    virtual bool	IsOverflowed( void ) const = 0;
    virtual bool	IsTimedOut( void ) const = 0;
    virtual bool	HasPendingReliableData( void ) = 0;

    virtual void	SetFileTransmissionMode( bool bBackgroundMode ) = 0;
    virtual void	SetCompressionMode( bool bUseCompression ) = 0;
    virtual unsigned int RequestFile( const char *filename , bool isReplayDemoFile ) = 0;
    virtual float	GetTimeSinceLastRecvd( void ) const = 0;	// get time since last Recvd packet in seconds

    virtual void	SetMaxBufferSize( bool bReliable , int nBytes , bool bVoice = false ) = 0;

    virtual bool	IsNull() const = 0;
    virtual int		GetNumBitsWritten( bool bReliable ) = 0;
    virtual void	SetInterpolationAmount( float flInterpolationAmount ) = 0;
    virtual void	SetRemoteFramerate( float flFrameTime , float flFrameTimeStdDeviation , float flFrameStartTimeStdDeviation ) = 0;

    // Max # of payload bytes before we must split/fragment the packet
    virtual void	SetMaxRoutablePayloadSize( int nSplitSize ) = 0;
    virtual int		GetMaxRoutablePayloadSize() = 0;

    // For routing messages to a different handler
    virtual bool	SetActiveChannel( INetChannel *pNewChannel ) = 0;
    virtual void	AttachSplitPlayer( int nSplitPlayerSlot , INetChannel *pChannel ) = 0;
    virtual void	DetachSplitPlayer( int nSplitPlayerSlot ) = 0;

    virtual bool	IsRemoteDisconnected() const = 0;

    virtual bool	WasLastMessageReliable() const = 0;
};

class CCLCMsg_RespondCvarValue
{
public:
    char _0x0000[ 24 ];
    char* sCvarValue; //0x0018
    char _0x0020[ 40 ];
    char* sCvarName; //0x0048
};//Size=0x0050

typedef struct CMsg_CVars
{
    const char* sTest[ 10 ];
} CMsg_CVars;

class CNETMsg_SetConVar
{
public:
    CUtlVector<CMsg_CVars> m_ConVars;
};

class CCLCMsg_Move
{
public:
    char pad[ 8 ];
    int backup_commands;
    int new_commands;
    Pointer pData;
};

class pCustomFiles
{
public:
    CRC32_t CustomFiles[ 0x10 ]; //0x0000
}; //Size=0x0010

class CCLCMsg_ClientInfo
{
public:
    char pad_0x0000[ 0xC ]; //0x0000
    CRC32_t CRCTable; //0x000C
    uint32 ServerCount; //0x0010
    unsigned char isreplay; //0x0014
    unsigned char ishltv; //0x0015
    unsigned char b_uk222; //0x0016
    unsigned char b_uk0; //0x0017
    uint32 FriendsID; //0x0018
    char* FriendsName; //0x001C
    pCustomFiles* CustomFiles; //0x0020
    char pad_0x0024[ 0x34 ];
}; //Size=0x05AC

class CCLCMsg_VoiceData
{
public:
    char pad_0x0000[ 0x18 ]; //0x0000
    __int64 xuid; //0x0018
    __int32 format; //0x0020
    __int32 sequence_bytes; //0x0024
    __int32 section_number; //0x0028
    __int32 uncompressed_sample_offset; //0x002C
    __int32 i_uk; //0x0030
    __int32 i_uk2; //0x0034
    char pad_0x0038[ 0x4 ]; //0x0038
    char* pcData; //0x003C
    char pad_0x0040[ 0xC ]; //0x0040
    __int32 N0000051C; //0x004C
    __int32 N000004B7; //0x0050
    __int32 N000004B8; //0x0054
    __int32 i4094; //0x0058
    __int32 im1; //0x005C
    __int32 N00000009; //0x0060
    __int32 N0000000A; //0x0064
    char sPlayerName[ 132 ]; //0x13D7888
    char sSteamID[ 38 ]; //0x13D7888
    char pad_0x0112[ 0x16 ]; //0x0112
    char N0000003C[ 38 ]; //0x13D7888
    char pad_0x014E[ 0x336 ]; //0x014E
};

enum VoiceDataFormat_t
{
    VOICEDATA_FORMAT_STEAM = 0 ,
    VOICEDATA_FORMAT_ENGINE = 1
};

int GetSplitScreenPlayerSlot();

#endif