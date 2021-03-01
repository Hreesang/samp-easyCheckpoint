/*
        easyCheckpoint - separating checkpoints easily

        This include helps scripter to divide the checkpoints or race checkpoints in
        their script. Therefore, there will be no collision between the other 
        checkpoints.

        Created by Hreesang on Sunday, February 7th, 2021.
*/

// -
// Compiletime Configuration
// -

#if defined _easyCheckpoint_defined
    #endinput
#else
    #define _easyCheckpoint_defined
#endif


// -
// Declarations
// -

#if !defined EC_AUTO_CLOSE_CHECKPOINT
    #define EC_AUTO_CLOSE_CHECKPOINT                false
#endif

#if !defined EC_AUTO_CLOSE_RACE_CHECKPOINT
    #define EC_AUTO_CLOSE_RACE_CHECKPOINT           false
#endif

// Tags
#define eCheckpoint:                #
#define eRaceCheckpoint:            #
#define eRaceCP:                    #

// Callbacks
#define eCHECKPOINT:%0(%1)          forward ecp_%0(%1); public ecp_%0(%1)
#define eRACECP:%0(%1)              forward ercp_%0(%1); public ercp_%0(%1)
#define eRACECHECKPOINT:%0(%1)      eRACECP:%0(%1)

// Macros
#define Checkpoint_Shown(%0)        (CallRemoteFunction("Checkpoint_IsShown", "i", %0))    
#define RaceCheckpoint_Shown(%0)    (CallRemoteFunction("RaceCheckpoint_IsShown", "i", %0))

// Variables
static
    gsCPName[MAX_PLAYERS][32 char],
    bool:gsCPOpened[MAX_PLAYERS],

    gsRaceCPName[MAX_PLAYERS][32 char],
    bool:gsRaceCPOpened[MAX_PLAYERS];


// -
// API
// -

    // Called after a checkpoint has just shown. Returning 0 will prevent the checkpoint 
    // from showing.
forward OnCheckpointShow(playerid);

    // Called before the checkpoint performed. Returning 0 will prevent the enter checkpoint 
    // to do anything.
forward OnCheckpointPerformed(playerid);

    // Called after a race checkpoint has just shown. Returning 0 will prevent the race
    // checkpoint from showing.
forward OnRaceCheckpointShow(playerid);

    // Called before the race checkpoint performed. Returning 0 will prevent the entered
    // race checkpoint to do anything.
forward OnRaceCheckpointPerformed(playerid);

    // Show a checkpoint. 
    // Returns 0 if OnCheckpointShow returned false.
    // Returns 1 if everything works fine.
stock Checkpoint_Show(playerid, const function[], Float:x, Float:y, Float:z, Float:size)
{
    #if defined OnCheckpointShow
        if(funcidx("OnCheckpointShow") != -1 && CallLocalFunction("OnCheckpointShow", "i", playerid) == 0)
        {
            return 0;
        }
    #endif

    SetPlayerCheckpoint(playerid, x, y, z, size);
    strpack(gsCPName[playerid], function, 32 char);
    gsCPOpened[playerid] = true;
    return 1;
}

    // If checkpoint has shown, then it will return true; it will be called as
    // a remoted function, so it can work in filterscripts too.
forward Checkpoint_IsShown(playerid);
public Checkpoint_IsShown(playerid)
{
    return gsCPOpened[playerid];
}

    // Disable the current checkpoint
stock Checkpoint_Disable(playerid)
{
    gsCPName[playerid]{0} = 0;
    gsCPOpened[playerid] = false;
    DisablePlayerCheckpoint(playerid);
    return 1;
}

    // Show a race checkpoint. 
    // Returns 0 if OnRaceCheckpointShow returned false.
    // Returns 1 if everything works fine.
stock RaceCheckpoint_Show(playerid, const function[], type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size)
{
    #if defined OnRaceCheckpointShow
        if(funcidx("OnRaceCheckpointShow") != -1 && CallLocalFunction("OnRaceCheckpointShow", "i", playerid) == 0)
        {
            return -1;
        }
    #endif
    
    SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size);
    strpack(gsRaceCPName[playerid], function, 32 char);
    gsRaceCPOpened[playerid] = true;
    return 1;
}

    // If checkpoint has shown, then it will return true; it will be called as
    // a remoted function, so it can work in filterscripts too.
forward RaceCheckpoint_IsShown(playerid);
public RaceCheckpoint_IsShown(playerid)
{
    return gsRaceCPOpened[playerid];
}

    // Disable current race checkpoint.
stock RaceCheckpoint_Disable(playerid)
{
    gsRaceCPName[playerid]{0} = 0;
    gsRaceCPOpened[playerid] = false;
    DisablePlayerRaceCheckpoint(playerid);
    return 1;
}

// -
// Internal
// -

public OnPlayerEnterCheckpoint(playerid)
{
    if(gsCPOpened[playerid])
    {
        #if defined OnCheckpointPerformed
            if(funcidx("OnCheckpointPerformed") != -1 && CallLocalFunction("OnCheckpointPerformed", "i", playerid) == 0)
            {
                return 1;
            }
        #endif

        new
            funcname[32];

        strcat(funcname, "ecp_");
        strcat(funcname, gsCPName[playerid]);

        #if EC_AUTO_CLOSE_CHECKPOINT
            gsCPName[playerid]{0} = 0;
            gsCPOpened[playerid] = false;
            DisablePlayerCheckpoint(playerid);
        #endif
        
        CallLocalFunction(funcname, "i", playerid);
        return 1;
    }

    #if defined EC_OnPlayerEnterCheckpoint
        return EC_OnPlayerEnterCheckpoint(playerid);
    #else
        return 1;
    #endif
}


public OnPlayerEnterRaceCheckpoint(playerid)
{
    if(gsRaceCPOpened[playerid])
    {
        #if defined OnRaceCheckpointPerformed
            if(funcidx("OnRaceCheckpointPerformed") != -1 && CallLocalFunction("OnRaceCheckpointPerformed", "i", playerid) == 0)
            {
                return 1;
            }
        #endif

        new
            funcname[32];

        strcat(funcname, "ercp_");
        strcat(funcname, gsRaceCPName[playerid]);

        #if EC_AUTO_CLOSE_RACE_CHECKPOINT
            gsRaceCPName[playerid]{0} = 0;
            gsRaceCPOpened[playerid] = false;
            DisablePlayerRaceCheckpoint(playerid);
        #endif
        
        CallLocalFunction(funcname, "i", playerid);
        return 1;
    }

    #if defined EC_OnPlayerEnterRaceCP
        return EC_OnPlayerEnterRaceCP(playerid);
    #else
        return 1;
    #endif
}


stock EC_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size)
{
    new
        ret = SetPlayerCheckpoint(playerid, x, y, z, size);

    if(ret)
    {
        gsCPName[playerid]{0} = 0;
        gsCPOpened[playerid] = false;
    }
    return ret;
}

stock EC_DisablePlayerCheckpoint(playerid)
{
    new
        ret = DisablePlayerCheckpoint(playerid);

    if(ret)
    {
        gsCPName[playerid]{0} = 0;
        gsCPOpened[playerid] = false;
    }
    return ret;
}

stock EC_SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size)
{
    new
        ret = SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size);

    if(ret)
    {
        gsRaceCPName[playerid]{0} = 0;
        gsRaceCPOpened[playerid] = false;
    }
    return ret;
}

stock EC_DisablePlayerRaceCP(playerid)
{
    new
        ret = DisablePlayerCheckpoint(playerid);

    if(ret)
    {
        gsRaceCPName[playerid]{0} = 0;
        gsRaceCPOpened[playerid] = false;
    }
    return ret;
}

public OnPlayerConnect(playerid)
{
    gsCPName[playerid]{0} =
    gsRaceCPName[playerid]{0} = 0;
    gsCPOpened[playerid] =
    gsRaceCPOpened[playerid] = false;

    #if defined EC_OnPlayerConnect
        return EC_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}


// -
// Hook
// -

#if defined _ALS_OnPlayerEnterCheckpoint
    #undef OnPlayerEnterCheckpoint
#else
    #define _ALS_OnPlayerEnterCheckpoint
#endif
#define OnPlayerEnterCheckpoint EC_OnPlayerEnterCheckpoint
#if defined EC_OnPlayerEnterCheckpoint
    forward EC_OnPlayerEnterCheckpoint(playerid);
#endif

#if defined _ALS_OnPlayerEnterRaceCP
    #undef OnPlayerEnterRaceCheckpoint
#else
    #define _ALS_OnPlayerEnterRaceCP
#endif
#define OnPlayerEnterRaceCheckpoint EC_OnPlayerEnterRaceCP
#if defined EC_OnPlayerEnterRaceCP
    forward EC_OnPlayerEnterRaceCP(playerid);
#endif

#if defined _ALS_SetPlayerCheckpoint
    #undef SetPlayerCheckpoint
#else
    #define _ALS_SetPlayerCheckpoint
#endif
#define SetPlayerCheckpoint EC_SetPlayerCheckpoint

#if defined _ALS_DisablePlayerCheckpoint
    #undef DisablePlayerCheckpoint
#else
    #define _ALS_DisablePlayerCheckpoint
#endif
#define DisablePlayerCheckpoint EC_DisablePlayerCheckpoint

#if defined _ALS_SetPlayerRaceCheckpoint
    #undef SetPlayerRaceCheckpoint
#else
    #define _ALS_SetPlayerRaceCheckpoint
#endif
#define SetPlayerRaceCheckpoint EC_SetPlayerRaceCheckpoint

#if defined _ALS_DisablePlayerRaceCP
    #undef DisablePlayerRaceCheckpoint
#else
    #define _ALS_DisablePlayerRaceCP
#endif
#define DisablePlayerRaceCheckpoint EC_DisablePlayerRaceCP

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect EC_OnPlayerConnect
#if defined EC_OnPlayerConnect
    forward EC_OnPlayerConnect(playerid);
#endif