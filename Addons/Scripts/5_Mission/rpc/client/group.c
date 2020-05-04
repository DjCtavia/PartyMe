class PM_RPC_C_group
{
    void PM_RPC_C_group()
    {
        GetRPCManager().AddRPC("PartyMe", "PlayerJoinGroup", this, SingleplayerExecutionType.Both);
    }

    /*
        Description:
            When player is joining a group, we need at least
            4 parameters to initialize it
        Data:
            Param1: Player ID
            Param2: Player name
            Param3: Player position
            Param4: Player health
    */
    void PlayerJoinGroup(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        Param4<string, string, vector, float> data;
        if (!ctx.Read(data)) return;

        ref PM_Event_Params eventParams = new PM_Event_Params;
        eventParams.playerIdFrom = data.param1;
        eventParams.name = data.param2;
        eventParams.position = data.param3;
        eventParams.health = data.param4;
        PM_GetEvents().CallEvent("PlayerJoinGroup", eventParams);
    }
};