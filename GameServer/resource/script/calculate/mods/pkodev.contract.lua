--------------------------------------------------------------
-- The contract system script
--------------------------------------------------------------
--
-- File: pkodev.contract.lua
-- Author: V3ct0r from PKOdev.NET
-- Version: 1.1 (02/02/2023)
-- GitHub: https://github.com/V3ct0r1024/pkodev.mod.contract
--
-- How to install this script:
-- 1) Put this file to 'GameServer\resource\script\calculate\mods' folder
-- 2) Put the following line at the beginning of 'SkillEffect.lua' file:
--		dofile(GetResPath("script\\calculate\\mods\\pkodev.contract.lua"))
-- 3) Add the contract item in the ItemInfo.txt file
-- 		XXXX	Contract	n0184	10130005	0	0	0	0	0	00	99	0	0	0	0	0	1	1	1	1	1	1	0	-1	0	-1	0	0	-1	-1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0	10,10	0,0	0	0	0	0	0	0	0	0	0	ItemUse_PKOdevContract	0	0	0	0	0	0	Upon completion, you are entitled to a reward
-- 4) Specify the item ID in 'contract.conf.item_id' table below:
--		item_id = XXXX
-- 5) Write the code for issuing a reward for completing a contract in the 'contract.conf.CompletionCallback' function
-- 6) To create a new contract use the function 'contract.create':
--		local <result (0 or 1)>, <item_descriptor>, <slot (from 0 to bag_size - 1)>
--			= contract.create(<character_descriptor>, <monster_id>, <monster_number>)
--	  For example:
--		local ret, item, slot = contract.create(role, 103, 7)
-- 7) Done!
--------------------------------------------------------------

print("Loading pkodev.contract.lua")

contract = contract or {}

---------------------------------------
-- Settings
---------------------------------------

contract.log = "pkodev.contract"

contract.conf = {

	-- Contract item ID from ItemInfo.txt
	item_id = 35,
	
	-- User-defined function for reward
	-- @role Character descriptor
	-- @item Item descriptor
	CompletionCallback = function(role, item)
		
		-- Give 1,000 gold
		AddMoney (role, 0, 1000)
		
		-- Set of items
		local arr = {
			{id = 885,  count = 1 }, -- Refining Gem x 1
			{id = 863,  count = 2 }, -- Gem of Rage x 2
			{id = 1849, count = 60}, -- Cake x 60
			{id = 231,  count = 1 }  -- Fairy of Luck x 1
		}
		
		-- Give a random item
		local idx = math.random(1, table.getn(arr))
		GiveItem(role, 0, arr[idx].id , arr[idx].count, 4)
		
		-- Launch fireworks
		PlayEffect(role, 361)
		
	end
	
}

---------------------------------------
-- Constants
---------------------------------------
contract.const = {
	item_type  = 99,               -- Contract item type from ItemInfo.txt
	target_id  = ITEMATTR_VAL_STR, -- Item attribute ID with the ID of target monster
	target_max = ITEMATTR_VAL_AGI, -- Item attribute ID with the total amount of monsters to hunt
	target_cur = ITEMATTR_VAL_DEX  -- Item attribute ID with the total amount of monsters already hunted
}

---------------------------------------
-- Hooks
---------------------------------------

-- Create item function hook
-- @item Item descriptor
-- @item_type Item type ID
-- @item_lv Item level ???
-- @item_event Item event ???
contract.Creat_Item__original = Creat_Item
Creat_Item = function(item, item_type, item_lv, item_event)
	
	if (item_type == contract.const['item_type']) then
		Reset_item_add()
		
		Add_Item_Attr(contract.const['target_id'],  0)
		Add_Item_Attr(contract.const['target_max'], 0)
		Add_Item_Attr(contract.const['target_cur'], 0)
		
		return item_add.cnt, 
			item_add.attr[1][1], item_add.attr[1][2],
			item_add.attr[2][1], item_add.attr[2][2], 
			item_add.attr[3][1], item_add.attr[3][2],
			item_add.attr[4][1], item_add.attr[4][2],
			item_add.attr[5][1], item_add.attr[5][2],
			item_add.attr[6][1], item_add.attr[6][2],
			item_add.attr[7][1], item_add.attr[7][2] 
	end

	return contract.Creat_Item__original(item, item_type, item_lv, item_event)
	
end

-- Player killed monster function hook
-- @monster Monster descriptor
-- @role Character descriptor
contract.GetExp_PKM__original = GetExp_PKM
GetExp_PKM = function(monster, role)

	contract.GetExp_PKM__original(monster, role)
	
	role = TurnToCha(role)
	
	local ret = CheckBagItem(role, contract.conf['item_id'])
	
	if (ret > 0) then
		local id = GetChaTypeID(monster)
		local contracts = {}
		local counter = 0

		for i = 0, (GetKbCap(role) - 1), 1 do
			local item = GetChaItem(role, 2, i)
			if (GetItemID(item) == contract.conf['item_id']) then
				local target_id = GetItemAttr(item, contract.const['target_id'])
				if (id == target_id) then
					local target_cur = GetItemAttr(item, contract.const['target_cur'])
					local target_max = GetItemAttr(item, contract.const['target_max'])
					if (target_cur < target_max) then
						counter = counter + 1
						contracts[counter] = { item_ = item, cur_ = target_cur, max_ = target_max }
					end
				end
			end
		end
		
		if (counter > 0) then
			local idx = math.random(1, counter)
			contracts[idx].cur_ = contracts[idx].cur_ + 1
			SetItemAttr(contracts[idx].item_, contract.const['target_cur'], contracts[idx].cur_)
			SynChaKitbag(role, 13)
			if (contracts[idx].cur_ < contracts[idx].max_) then
				BickerNotice(role, string.format("Contract: Remaining '%s' to hunt: %d / %d!", 
					GetMonsterName(id), contracts[idx].cur_, contracts[idx].max_))
			else
				BickerNotice(role, string.format("Contract: All '%s' are killed! The contract is completed.", 
					GetMonsterName(id)))
			end
		end
	end
	
end

---------------------------------------
-- Useful functions
---------------------------------------

-- Create a contract
-- @role Character descriptor
-- @target_id Monster to hunt ID
-- @number Monsters amount
contract.create = function(role, target_id, number)
	
	role = TurnToCha(role)
	
	if (KitbagLock(role, 0) == LUA_FALSE) then
		LG(contract.log, "Can't create the contract item (ID:", contract.conf['item_id'], ") because the bag is locked!") 
		return LUA_FALSE, nil, 0
	end
	
	if (GetChaFreeBagGridNum(role) == 0) then
		LG(contract.log, "Can't create the contract item (ID:", contract.conf['item_id'], ") because there are no free slots in the bag!") 
		return LUA_FALSE, nil, 0
	end
	
	local r1, r2 = MakeItem(role, contract.conf['item_id'], 1, 4)
	if (r1 == 0) then
		LG(contract.log, "Can't create contract item (ID:", contract.conf['item_id'], ")!") 
		return LUA_FALSE, nil, 0
	end
	
	local item = GetChaItem(role, 2, r2)
	local a1 = SetItemAttr(item, contract.const['target_id'], target_id)
	local a2 = SetItemAttr(item, contract.const['target_max'], number)
	local a3 = SetItemAttr(item, contract.const['target_cur'], 0)
	
	if ((a1 == 0) or (a2 == 0) or (a3 == 0)) then
		LG(contract.log, "Can't set contract data! a1 = ", a1, ", a2 = ", a2, ", a3 = ", a3) 
		return LUA_FALSE, item, r2
	end
	
	SynChaKitbag(role, 13)
	
	SystemNotice(role, string.format("You received a monster hunt contract ('%s' x %d!)",
		GetMonsterName(target_id), number))

	return LUA_TRUE, item, r2
	
end

-- Contract item use event (for ItemInfo.txt)
-- @role Character descriptor
-- @item Item descriptor
ItemUse_PKOdevContract = function(role, item)

	role = TurnToCha(role)
	
	local target_id  = GetItemAttr(item, contract.const['target_id'])
	local target_max = GetItemAttr(item, contract.const['target_max'])
	local target_cur = GetItemAttr(item, contract.const['target_cur'])
	
	if (target_cur < target_max) then
		SystemNotice(role, string.format("You have to kill [%s] x %d more to complete this contract!", 
			GetMonsterName(target_id), (target_max - target_cur)))
		UseItemFailed(role)
	else
		SystemNotice(role, "You have successfully completed the contract, congratulations!")
		if (contract.conf['CompletionCallback'] ~= nil) then
			contract.conf['CompletionCallback'](role, item)
		end
	end
	
end