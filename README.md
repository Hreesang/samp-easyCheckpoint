# easy-Checkpoint

[![sampctl](https://img.shields.io/badge/sampctl-samp--easyCheckpoint-2f2f2f.svg?style=for-the-badge)](https://github.com/Hreesang/samp-easyCheckpoint)

The purpose of this include is to make setting up checkpoints become easier.

With this include, you can name a checkpoint and receive a response that has the specified name.

I'm sorry if you see some English mistakes in this documentation; I'm not that good in English.

## Functions

Set a checkpoint for player.
```pawn
Checkpoint_Show(playerid, const function[], Float:x, Float:y, Float:z, Float:size)
```

Disable player checkpoint.
```pawn
Checkpoint_Disable(playerid)
```

Check whether the player's checkpoint was shown or no.
```pawn
Checkpoint_Shown(playerid)
```

Set a race checkpoint for player.
```pawn
RaceCheckpoint_Show(playerid, const function[], type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size)
```

Disable player race checkpoint.
```pawn
RaceCheckpoint_Disable(playerid)
```

Check whether the player's race checkpoint was shown or no.
```pawn
RaceCheckpoint_Shown(playerid)
```

## Callbacks

This callback is called before player was shown the checkpoint through ``Checkpoint_Show()`` function. Returning 0 in this callback will prevent player from setting up the checkpoint.
```pawn
OnCheckpointShow(playerid)
```

This callback is called after player entered the checkpoint that was set by ``Checkpoint_Show()``. Returning 0 in this callback will prevent player form executing the checkpoint.
```pawn
OnCheckpointPerformed(playerid)
```

This callback is called before player was shown the checkpoint through ``RaceCheckpoint_Show()`` function. Returning 0 in this callback will prevent player from setting up the checkpoint.
```pawn
OnRaceCheckpointShow(playerid)
```

This callback is called after player entered the checkpoint that was set by ``RaceCheckpoint_Show()``. Returning 0 in this callback will prevent player form executing the checkpoint.
```pawn
OnRaceCheckpointPerformed(playerid)
```

## Tags

Use these tag within the function name in ``Checkpoint_Show()`` and ``RaceCheckpoint_Show`` function.
```pawn
eCheckpoint:functionname
eRaceCheckpoint:functionname
eRaceCP:functioname // the shorter for eRaceCheckpoint
```

Examples:
```pawn
Checkpoint_Show(playerid, eCheckpoint:DEFAULT_CHECKPOINT, 1.0, 2.0, 3.0, 4.0);
RaceCheckpoint_Show(playerid, eRaceCP:RACE_CHECKPOINT, 1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 8.0);
```

## Settings

Put this define before including the library if you want every checkpoint
shown by ``Checkpoint_Show`` will be disabled/closed once player entered it.
```pawn
#define EC_AUTO_CLOSE_CHECKPOINT true
```

Put this define before including the library if you want every checkpoint
shown by ``RaceCheckpoint_Show`` will be disabled/closed once player entered it.
```pawn
#define EC_AUTO_CLOSE_RACE_CHECKPOINT true
```

## Usage
```pawn
#define EC_AUTO_CLOSE_CHECKPOINT false
#include <easyCheckpoint>

public OnPlayerSpawn(playerid)
{
    Checkpoint_Show(playerid, eCheckpoint:BLUEBERRY_CP, 1.0, 2.0, 3.0, 2.5);
    Checkpoint_Show(playerid, eRaceCP:BLUEBERRY_RACECP, 1, 1.0, 2.0, 3.0, 0.0, 0.0, 0.0, 3.0);
    return 1;
}

eCHECKPOINT:BLUEBERRY_CP(playerid)
{
    SendClientMessage(playerid, -1, "You are at the blueberry checkpoint.");
    return 1;
}

eRACECP:BLUEBERRY_RACECP(playerid)
{
    SendClientMessage(playerid, -1, "You are at the blueberry race checkpoint.");
    return 1;
}
```

## Credits

Hreesang for easyCheckpoint, Emmet_ for the snippet from easyDialog, and Southclaws for sampctl.