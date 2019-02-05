#pragma once

class IMDLCache : public IAppSystem
{
public:
    // Used to install callbacks for when data is loaded + unloaded
    // Returns the prior notify
    virtual void SetCacheNotify( Pointer pNotify ) = 0;

    // NOTE: This assumes the "GAME" path if you don't use
    // the UNC method of specifying files. This will also increment
    // the reference count of the MDL
    virtual MDLHandle_t FindMDL( const char *pMDLRelativePath ) = 0;

    // Reference counting
    virtual int AddRef( MDLHandle_t handle ) = 0;
    virtual int Release( MDLHandle_t handle ) = 0;
    virtual int GetRef( MDLHandle_t handle ) = 0;

    // Gets at the various data associated with a MDL
    virtual studiohdr_t *GetStudioHdr( MDLHandle_t handle ) = 0;
    virtual studiohwdata_t *GetHardwareData( MDLHandle_t handle ) = 0;
    virtual Pointer GetVCollide( MDLHandle_t handle ) = 0;
    virtual unsigned char *GetAnimBlock( MDLHandle_t handle , int nBlock ) = 0;
    virtual Pointer GetVirtualModel( MDLHandle_t handle ) = 0;
    virtual int GetAutoplayList( MDLHandle_t handle , unsigned short **pOut ) = 0;
    virtual Pointer GetVertexData( MDLHandle_t handle ) = 0;

    // Brings all data associated with an MDL into memory
    virtual void TouchAllData( MDLHandle_t handle ) = 0;

    // Gets/sets user data associated with the MDL
    virtual void SetUserData( MDLHandle_t handle , void* pData ) = 0;
    virtual void *GetUserData( MDLHandle_t handle ) = 0;

    // Is this MDL using the error model?
    virtual bool IsErrorModel( MDLHandle_t handle ) = 0;

    // Flushes the cache, force a full discard
    virtual void Flush( int nFlushFlags ) = 0;

    // Flushes a particular model out of memory
    virtual void Flush( MDLHandle_t handle , int nFlushFlags ) = 0;

    // Returns the name of the model (its relative path)
    virtual const char *GetModelName( MDLHandle_t handle ) = 0;

    // faster access when you already have the studiohdr
    virtual Pointer GetVirtualModelFast( const studiohdr_t *pStudioHdr , MDLHandle_t handle ) = 0;

    // all cache entries that subsequently allocated or successfully checked
    // are considered "locked" and will not be freed when additional memory is needed
    virtual void BeginLock() = 0;

    // reset all protected blocks to normal
    virtual void EndLock() = 0;

    // returns a pointer to a counter that is incremented every time the cache has been out of the locked state (EVIL)
    virtual int *GetFrameUnlockCounterPtrOLD() = 0;

    // Finish all pending async operations
    virtual void FinishPendingLoads() = 0;

    virtual Pointer GetVCollideEx( MDLHandle_t handle , bool synchronousLoad = true ) = 0;
    virtual bool GetVCollideSize( MDLHandle_t handle , int *pVCollideSize ) = 0;

    virtual bool GetAsyncLoad( int type ) = 0;
    virtual bool SetAsyncLoad( int type , bool bAsync ) = 0;

    virtual void BeginMapLoad() = 0;
    virtual void EndMapLoad() = 0;
    virtual void MarkAsLoaded( MDLHandle_t handle ) = 0;

    virtual void InitPreloadData( bool rebuild ) = 0;
    virtual void ShutdownPreloadData() = 0;

    virtual bool IsDataLoaded( MDLHandle_t handle , int type ) = 0;

    virtual int *GetFrameUnlockCounterPtr( int type ) = 0;

    virtual studiohdr_t *LockStudioHdr( MDLHandle_t handle ) = 0;
    virtual void UnlockStudioHdr( MDLHandle_t handle ) = 0;

    virtual bool PreloadModel( MDLHandle_t handle ) = 0;

    // Hammer uses this. If a model has an error loading in GetStudioHdr, then it is flagged
    // as an error model and any further attempts to load it will just get the error model.
    // That is, until you call this function. Then it will load the correct model.
    virtual void ResetErrorModelStatus( MDLHandle_t handle ) = 0;

    virtual void MarkFrame() = 0;
};