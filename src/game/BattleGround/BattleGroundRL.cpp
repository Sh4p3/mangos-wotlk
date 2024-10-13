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
#include "BattleGroundRL.h"
#include "Tools/Language.h"
#include "Server/WorldPacket.h"

#ifdef ENABLE_MODULES
#include "ModuleMgr.h"
#endif

BattleGroundRL::BattleGroundRL()
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

void BattleGroundRL::StartingEventOpenDoors()
{
    OpenDoorEvent(BG_EVENT_DOOR);

#ifdef ENABLE_MODULES
    sModuleMgr.OnStartBattleGround(this);
#endif
}

bool BattleGroundRL::HandlePlayerUnderMap(Player* player)
{
    player->TeleportTo(GetMapId(), 1285.810547f, 1667.896851f, 39.957642f, player->GetOrientation());
    return true;
}

bool BattleGroundRL::HandleAreaTrigger(Player* player, uint32 trigger)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return false;

    switch (trigger)
    {
    case 4696:                                          // buff trigger?
    case 4697:                                          // buff trigger?
        break;
        // OUTSIDE OF ARENA, TELEPORT!
    case 4927:
    case 4928:
        player->NearTeleportTo(1230.77f, 1662.42f, 34.56f, 0.0f);
        break;
    case 4929:
    case 4930:
        player->NearTeleportTo(1341.16f, 1673.52f, 34.43f, 3.5f);
        break;
    case 4931:
        player->NearTeleportTo(1294.74f, 1584.5f, 31.62f, 1.66f);
        break;
    case 4932:
        player->NearTeleportTo(1277.5f, 1751.07f, 31.61f, 4.7f);
        break;
    case 4933:
        player->NearTeleportTo(1269.14f, 1713.85f, 34.46f, 5.23f);
        break;
    case 4934:
        player->NearTeleportTo(1298.14f, 1713.8f, 33.58f, 4.55f);
        break;
    case 4935:
        player->NearTeleportTo(1306.32f, 1620.75f, 34.25f, 1.97f);
        break;
    case 4936:
        player->NearTeleportTo(1277.97f, 1615.51f, 34.56f, 1.15f);
        break;
    case 4941: // under arena +10
    case 5041: // under arena -10
    case 5042: // under arena -30
        player->NearTeleportTo(1285.810547f, 1667.896851f, 39.957642f, player->GetOrientation());
        break;
    default:
        return false;
    }
    return true;
}
