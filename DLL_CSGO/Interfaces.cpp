#include "Includes.hxx"
#include "Main.hxx"

Interface<ICvar> Cvar = Interface<ICvar>( false , 0 , AutoConvertC( TEXT( "VEngineCvar" ) ) , TEXT( "vstdlib.dll" ) );
Interface<IBaseClientDLL> BaseClient = Interface<IBaseClientDLL>( false , 0 , AutoConvertC( TEXT( "VClient" ) ) , TEXT( "client.dll" ) );
Interface<IClientEntityList> ClientEntityList = Interface<IClientEntityList>( false , 0 , AutoConvertC( TEXT( "VClientEntityList" ) ) , TEXT( "client.dll" ) );
Interface<CInput> Input;
Interface<CGlobalVars> Globals;
Interface<IEngineTrace> EngineTrace = Interface<IEngineTrace>( false , 0 , AutoConvertC( TEXT( "EngineTraceClient" ) ) , TEXT( "engine.dll" ) );
Interface<IVEngineClient> EngineClient = Interface<IVEngineClient>( false , 0 , AutoConvertC( TEXT( "VEngineClient" ) ) , TEXT( "engine.dll" ) );
Interface<IPanel> Panel = Interface<IPanel>( false , 0 , AutoConvertC( TEXT( "VGUI_Panel" ) ) , TEXT( "vgui2.dll" ) );
Interface<IVRenderView> RenderView = Interface<IVRenderView>( false , 0 , AutoConvertC( TEXT( "VEngineRenderView" ) ) , TEXT( "engine.dll" ) );
Interface<IVModelInfo> ModelInfo = Interface<IVModelInfo>( false , 0 , AutoConvertC( TEXT( "VModelInfoClient" ) ) , TEXT( "engine.dll" ) );
Interface<IVDebugOverlay> DebugOverlay = Interface<IVDebugOverlay>( false , 0 , AutoConvertC( TEXT( "VDebugOverlay" ) ) , TEXT( "engine.dll" ) );
Interface<IMaterialSystem> MaterialSystem = Interface<IMaterialSystem>( false , 0 , AutoConvertC( TEXT( "VMaterialSystem" ) ) , TEXT( "materialsystem.dll" ) );
Interface<IVModelRender> ModelRender = Interface<IVModelRender>( false , 0 , AutoConvertC( TEXT( "VEngineModel" ) ) , TEXT( "engine.dll" ) );
Interface<IViewRender> ViewRender;
Interface<IClientMode> ClientMode;
Interface<IKeyValuesSystem> KeyValuesSystem = Interface<IKeyValuesSystem>( _CallFunction<Pointer>( ( Pointer ) GetProcAddress( _GetModule<HMODULE>( TEXT( "vstdlib.dll" ) )
                                                                           , AutoConvertC( TEXT( "KeyValuesSystem" ) ) ) )
                                                                           , AutoConvertC( TEXT( "KeyValuesSystem" ) ) , TEXT( "vstdlib.dll" ) );
Interface<IStudioRender> StudioRender = Interface<IStudioRender>( false , 0 , AutoConvertC( TEXT( "VStudioRender" ) ) , TEXT( "studiorender.dll" ) );
Interface<IPhysicsSurfaceProps> PhysicsSurfaceProps = Interface<IPhysicsSurfaceProps>( false , 0 , AutoConvertC( TEXT( "VPhysicsSurfaceProps" ) ) , TEXT( "vphysics.dll" ) );
Interface<CPrediction> Prediction = Interface<CPrediction>( false , 0 , AutoConvertC( TEXT( "VClientPrediction" ) ) , TEXT( "client.dll" ) );
Interface<CGameMovement> GameMovement = Interface<CGameMovement>( false , 0 , AutoConvertC( TEXT( "GameMovement" ) ) , TEXT( "client.dll" ) );
Interface<IMDLCache> MDLCache = Interface<IMDLCache>( false , 0 , AutoConvertC( TEXT( "MDLCache" ) ) , TEXT( "datacache.dll" ) );
Interface<IBaseFileSystem> FileSystem = Interface<IBaseFileSystem>( false , 0 , AutoConvertC( TEXT( "VBaseFileSystem" ) ) , TEXT( "FileSystem_Stdio.dll" ) );
Interface<ISurface> Surface = Interface<ISurface>( false , 0 , AutoConvertC( TEXT( "VGUI_Surface" ) ) , TEXT( "vguimatsurface.dll" ) );

/*

Interfaces[I_Prediction] = new C_Interface( GetInstanceInterface( "VClientPrediction" , "client" ) , "I_Prediction" );
Interfaces[I_EntityList] = new C_Interface( GetInstanceInterface( "VClientEntityList" , "client" ) , "I_EntityList" );
Interfaces[I_GameMovement] = new C_Interface( GetInstanceInterface( "GameMovement" , "client" ) , "I_GameMovement" );

Interfaces[I_Cvar] = new C_Interface( GetInstanceInterface( "VEngineCvar" , "vstdlib" ) , "I_Cvar" );

Interfaces[I_Engine] = new C_Interface( GetInstanceInterface( "VEngineClient" , "engine" ) , "I_Engine" );
Interfaces[I_RenderView] = new C_Interface( GetInstanceInterface( "VEngineRenderView" , "engine" ) , "I_RenderView" );
Interfaces[I_GameEvent] = new C_Interface( GetInstanceInterface( "GAMEEVENTSMANAGER" , "engine" ) , "I_GameEvent" );
Interfaces[I_EngineTrace] = new C_Interface( GetInstanceInterface( "EngineTraceClient" , "engine" ) , "I_Enginetrace" );
Interfaces[I_EngineVGUI] = new C_Interface( GetInstanceInterface( "VEngineVGui" , "engine" ) , "I_Enginevgui" );
Interfaces[I_Effects] = new C_Interface( GetInstanceInterface( "VEngineEffects" , "engine" ) , "I_Effects" );
Interfaces[I_ModelRender] = new C_Interface( GetInstanceInterface( "VEngineModel" , "engine" ) , "I_ModelRender" );
Interfaces[I_ModelInfo] = new C_Interface( GetInstanceInterface( "VModelInfoClient" , "engine" ) , "I_Modelinfo" );
Interfaces[I_DebugOverlay] = new C_Interface( GetInstanceInterface( "VDebugOverlay" , "engine" ) , "I_DebugOverlay" );

Interfaces[I_StudioRender] = new C_Interface( GetInstanceInterface( "VStudioRender" , "studiorender" ) , "I_StudioRender" );

Interfaces[I_PhysicAPI] = new C_Interface( GetInstanceInterface( "VPhysicsSurfaceProps" , "vphysics" ) , "I_PhysicAPI" );

Interfaces[I_MaterialSystemForDraw] = new C_Interface( GetInstanceInterface( "VMaterialSystem" , "materialsystem" ) , "I_MaterialSystemForDraw" );
Interfaces[I_MaterialSystem] = new C_Interface( GetInstanceInterface( "VMaterialSystem" , "materialsystem" ) , "I_MaterialSystem" );

Interfaces[I_Surface] = new C_Interface( GetInstanceInterface( "VGUI_Surface" , "vguimatsurface" ) , "I_Surface" );
Interfaces[I_IInput] = new C_Interface( GetInstanceInterface( "VGUI_Input" , "vgui2" ) , "I_IInput" );
Interfaces[I_Panel] = new C_Interface( GetInstanceInterface( "VGUI_Panel" , "vgui2" ) , "I_Panel" );

Interfaces[I_FileSystem] = new C_Interface( GetInstanceInterface( "VBaseFileSystem" , "FileSystem_Stdio" ) , "I_FileSystem" );

*/