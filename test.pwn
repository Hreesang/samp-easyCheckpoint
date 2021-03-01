#include <a_samp>
#include "easyCheckpoint.inc"

main()
{
    switch(Checkpoint_Show(0, eCheckpoint:TEST, 0.0, 0.0, 0.0, 3.0))
    {
        case 0: print("Checkpoint_Show returns 0 because OnCheckpointShow returned 0.");
        case 1: print("Checkpoint_Show returns 1, working fine.");
    }

    switch(RaceCheckpoint_Show(0, eRaceCP:TEST, 0, 0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 3.0))
    {
        case 0: print("RaceCheckpoint_Show returns 0 because OnRaceCheckpointShow returned 0.");
        case 1: print("RaceCheckpoint_Show returns 1, working fine.");
    }

    switch(Checkpoint_Shown(0))
    {
        case 0: print("Checkpoint_Opened returns 0, meaning no checkpoint was shown.");
        case 1: print("Checkpoint_Opened returns 1, meaning there is a shown checkpoint.");
    }

    switch(RaceCheckpoint_Shown(0))
    {
        case 0: print("RaceCheckpoint_Opened returns 0, meaning no checkpoint was shown.");
        case 1: print("RaceCheckpoint_Opened returns 1, meaning there is a shown checkpoint.");
    }

    if(Checkpoint_Disable(0))
    {
        print("Checkpoint has been disabled.");
    }

    if(RaceCheckpoint_Disable(0))
    {
        print("RaceCheckpoint has been disabled.");
    }
}

public OnCheckpointShow(playerid)
{
    print("OnCheckpointShow was called.");
    return 1;
}

public OnRaceCheckpointShow(playerid)
{
    print("OnRaceCheckpointShow was called.");
    return 1;
}

public OnCheckpointPerformed(playerid)
{
    print("OnCheckpointPerformed was called.");
    return 1;
}

public OnRaceCheckpointPerformed(playerid)
{
    print("OnRaceCheckpointPerformed was called.");
    return 1;
}

eCHECKPOINT:TEST(playerid)
{
    print("eCHECKPOINT:TEST was called.");
    return 1;
}

eRACECP:TEST(playerid)
{
    print("eRACECP:TEST was called.");
    return 1;
}