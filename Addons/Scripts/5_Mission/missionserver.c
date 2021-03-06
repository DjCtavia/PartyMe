modded class MissionServer
{
    ref PM_RPC_S_handler                	m_pm_rpc_handler;
	ref PM_S_Invitations					m_pm_invitations;

	void MissionServer()
	{
		InitPartyMe();
	}

    void InitPartyMe()
    {
        GetServerSettings();
        m_pm_rpc_handler = new PM_RPC_S_handler;
		m_pm_invitations = new PM_S_Invitations;
        PM_GetGroupManager();
        PM_Server_GetGroupPositionUpdater();
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);

        PM_GetGroupManager().SetPlayerEntity(identity.GetId(), player);
        PM_GetGroupManager().SetPlayerIdentity(identity.GetId(), identity);
		Print("[PartyMe] InvokeOnConnect | PlayerBase: " + player + " | identity: " + identity);

        // RPCs
        GetRPCManager().SendRPC("PartyMe", "PlayerJoinServer", new Param2<string, string>(identity.GetId(), identity.GetName()));
		GetRPCManager().SendRPC("PartyMe", "GroupSettings", new Param1<PM_Settings_Group>(GetServerSettings().group), false, identity);
    }

    override void InvokeOnDisconnect(PlayerBase player)
	{
        super.InvokeOnDisconnect(player);

        if (player)
        {
            PlayerIdentity identity = player.GetIdentity();

            if (identity)
            {
				ref PM_Event_Params eventParams = new PM_Event_Params;
        		eventParams.playerIdFrom = identity.GetId();

                Print("[PartyMe] Calling disconnect event");
				PM_GetEvents().CallEvent("PlayerDisconnect", eventParams);
                GetRPCManager().SendRPC("PartyMe", "PlayerDisconnect", new Param1<string>(identity.GetId()));
            }
        }
	}

    override void OnClientRespawnEvent(PlayerIdentity identity, PlayerBase player)
    {
        super.OnClientRespawnEvent(identity, player);

        // We reasign the PlayerBase for constant update later.
        PM_GetGroupManager().SetPlayerEntity(identity.GetId(), player);
    }

	//-------------------------------------------------------------------------- Utils
	PlayerIdentity GetPlayerIdentity(string playerId)
	{
		for (int playerIndex = 0; playerIndex < m_Players.Count(); playerIndex++)
		{
			PlayerIdentity pIdentity = m_Players.Get(playerIndex).GetIdentity();
			
			if (pIdentity && pIdentity.GetId() == playerId)
			{
				return pIdentity;
			}
		}
		return null;
	}
};