/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Entities/Object.h"
#include "Entities/Player.h"
#include "BattleGround.h"
#include "BattleGroundBE.h"
#include "Server/WorldPacket.h"
#include "Tools/Language.h"

#ifdef ENABLE_MODULES
#include "ModuleMgr.h"
#endif

BattleGroundBE::BattleGroundBE()
{
    // set start delay timers
    m_startDelayTimes[BG_STARTING_EVENT_FIRST]  = BG_START_DELAY_1M;
    m_startDelayTimes[BG_STARTING_EVENT_SECOND] = BG_START_DELAY_30S;
    m_startDelayTimes[BG_STARTING_EVENT_THIRD]  = BG_START_DELAY_15S;
    m_startDelayTimes[BG_STARTING_EVENT_FOURTH] = BG_START_DELAY_NONE;

    // set arena start message id
    m_startMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_ARENA_ONE_MINUTE;
    m_startMessageIds[BG_STARTING_EVENT_SECOND] = LANG_ARENA_THIRTY_SECONDS;
    m_startMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_ARENA_FIFTEEN_SECONDS;
    m_startMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_ARENA_HAS_BEGUN;
}

void BattleGroundBE::StartingEventOpenDoors()
{
    OpenDoorEvent(BG_EVENT_DOOR);

#ifdef ENABLE_MODULES
    sModuleMgr.OnStartBattleGround(this);
#endif
}

bool BattleGroundBE::HandlePlayerUnderMap(Player* player)
{
    player->TeleportTo(GetMapId(), 6238.930176f, 262.963470f, 0.889519f, player->GetOrientation());
    return true;
}

bool BattleGroundBE::HandleAreaTrigger(Player* player, uint32 trigger)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return false;

    switch (trigger)
    {
    case 4538:                                          // buff trigger?
        //buff_guid = BgObjects[BG_BE_OBJECT_BUFF_1];
        break;
    case 4539:                                          // buff trigger?
        //buff_guid = BgObjects[BG_BE_OBJECT_BUFF_2];
        break;
        // OUTSIDE OF ARENA, TELEPORT!
    case 4919:
        player->NearTeleportTo(6220.90f, 318.94f, 5.1f, 5.3f);
        break;
    case 4921:
        player->NearTeleportTo(6250.27f, 208.50f, 4.77f, 1.9f);
        break;
    case 4922:
        player->NearTeleportTo(6214.4f, 227.12f, 4.28f, 0.8f);
        break;
    case 4923:
        player->NearTeleportTo(6180.98f, 265.28f, 4.27f, 6.06f);
        break;
    case 4924:
        player->NearTeleportTo(6269.0f, 295.06f, 4.46f, 3.98f);
        break;
    case 4944: // under arena -20
    case 5039: // under arena -40
    case 5040: // under arena -60
        player->NearTeleportTo(6238.930176f, 262.963470f, 0.889519f, player->GetOrientation());
        break;
    default:
        return false;
    }
    return true;
}
