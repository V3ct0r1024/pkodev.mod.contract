--------------------------------------------------------------
-- The contract system script
--
-- Author: V3ct0r from PKOdev.NET
-- Version: 1.0 (01/12/2022)
--
-- How to install the system:
-- 1) Put this file to '\GameServer\resource\script\calculate\mods' folder
-- 2) Put the following line at the beginning of 'SkillEffect.lua' file:
--		dofile(GetResPath("script\\calculate\\mods\\pkodev.contract.lua"))
-- 3) Add the contract item in the ItemInfo.txt file
-- 		XXXX	Contract	n0184	10130005	0	0	0	0	0	00	99	0	0	0	0	0	1	1	1	1	1	1	0	-1	0	-1	0	0	-1	-1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0	10,10	0,0	0	0	0	0	0	0	0	0	0	ItemUse_PKOdevContract	0	0	0	0	0	0	Upon completion, you are entitled to a reward
-- 4) Specify the item ID in 'contract.conf.item_id' table below:
--		item_id = XXXX
-- 5) Write the code for issuing a reward for completing a contract in the 'contract.conf.reward_cb' function
-- 6) To create a new contract use the function 'contract.create':
--		local <result (0 or 1)>, <item_descriptor>, <slot (from 0 to bag_size - 1)>
--			= contract.create(<character_descriptor>, <monster_id>, <monster_number>)
--	  For example:
--		local ret, item, slot = contract.create(role, 103, 7)
-- 7) Done!
--------------------------------------------------------------

-- Print a log
print("Loading pkodev.contract.lua")


-- The contract system
contract = contract or {}

---------------------------------------
-- Settings
---------------------------------------

contract.conf = {
	
	-- Contract item ID
	item_id = XXXX,
	
	-- User-defined function for reward
	reward_cb = function(role, item)
		
		-- Give 1,000 gold
		AddMoney (role, 0, 1000)
		
		-- Give an random item
		local arr = 
		{
			-- Refining Gem x 1
			{id = 885, count = 1},
			
			-- or Gem of Rage x 2
			{id = 863, count = 2},
			
			-- or Cake x 60
			{id = 1849, count = 60},
			
			-- or Fairy of Luck x 1
			{id = 231, count = 1}
		}
		
		local r = math.random(1, table.getn(arr))
		GiveItem(role, 0, arr[r].id , arr[r].count, 4)
		
		-- Launch fireworks
		PlayEffect(role, 361)
		
	end
	
}

---------------------------------------
-- Constants
---------------------------------------
contract.const = {
	
	item_type  = 99,               -- Contract item type
	target_id  = ITEMATTR_VAL_STR, -- Item attribute ID with the ID of target monster
	target_max = ITEMATTR_VAL_AGI, -- Item attribute ID with the total amount of monsters to hunt
	target_cur = ITEMATTR_VAL_DEX  -- Item attribute ID with the total amount of monsters already hunted
	
}

---------------------------------------
-- Hooks
---------------------------------------

-- Adding an item to inventory event
contract.Creat_Item__original = Creat_Item
Creat_Item = function(item, item_type, item_lv, item_event)
	
	-- Check the item type
	if ( item_type == contract.const['item_type'] ) then
	
		-- Reset the previous attrbiutes
		Reset_item_add()
		
		-- Add new attributes to the item
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
	
	-- Call the original function Creat_Item(item, item_type, item_lv, item_event)
	return contract.Creat_Item__original(item, item_type, item_lv, item_event)
	
end

-- Player killed monster event
contract.GetExp_PKM__original = GetExp_PKM
GetExp_PKM = function(monster, role)

	-- Call the original function GetExp_PKM(dead, atk)
	contract.GetExp_PKM__original(monster, role)
	
	-- Get the main character's descriptor
	role = TurnToCha(role)

	-- Number of contracts in the player's bag
	local ret = CheckBagItem(role, contract.conf['item_id'])
	
	-- Check that player has contracts
	if ( ret > 0 ) then
		
		-- Monster ID 
		local id = GetChaTypeID(monster)
		
		-- List of contracts in the bag
		local arr = {}
		local k = 0

		-- Build the list of contracts
		for i = 0, ( GetKbCap(role) - 1 ), 1 do
			
			-- Get the item descriptor
			local item = GetChaItem(role, 2, i)
			
			-- Check the item ID
			if ( GetItemID(item) == contract.conf['item_id'] ) then
				
				-- Get the monster ID from contract
				local target_id = GetItemAttr(item, contract.const['target_id'])
				
				-- Check the monster ID
				if ( id == target_id ) then
				
					-- Get amount of monsters to hunt
					local target_cur = GetItemAttr(item, contract.const['target_cur'])
					local target_max = GetItemAttr(item, contract.const['target_max'])
					
					-- Check that the contract is not completed
					if ( target_cur < target_max ) then
					
						-- Add the item to the list
						k = k + 1
						arr[k] = { item_ = item, cur_ = target_cur, max_ = target_max }
						
					end
				
				end
			
			end
			
		end
		
		-- Check that matching contracts have been found
		if ( k > 0 ) then
			
			-- Randomly select a contract
			local r = math.random(1, k)
	
			-- Increase the number of hunted monsters
			arr[r].cur_ = arr[r].cur_ + 1
			
			-- Update amount of hunted monsters
			SetItemAttr(arr[r].item_, contract.const['target_cur'], arr[r].cur_)
			
			-- Synchronize the bag
			SynChaKitbag(role, 13)
			
			-- Check that the contract is not completed
			if ( arr[r].cur_ < arr[r].max_ ) then
				
				-- Write a message
				BickerNotice( role, string.format( "Contract: Remaining '%s' to hunt: %d / %d!", 
					GetMonsterName(id), arr[r].cur_, arr[r].max_ ) )

				
			else
				
				-- Write a message
				BickerNotice( role, string.format( "Contract: All '%s' are killed! The contract is completed.", 
					GetMonsterName(id) ) )
					
			end
				
		end
		
	end
	
end

---------------------------------------
-- Useful functions
---------------------------------------

-- Create a contract
contract.create = function(role, target_id, number)
	
	-- Get the main character's descriptor
	role = TurnToCha(role)
	
	-- Check that the bag is not locked
	if ( KitbagLock(role, 0) == LUA_FALSE ) then
	
		-- Error
		LG("pkodev.contract", "Can't create the contract item (id:", contract.conf['item_id'], ") because the bag is locked!") 
		return LUA_FALSE, nil, 0
		
	end
	
	-- Check that the bag has one free slot
	if ( GetChaFreeBagGridNum(role) == 0 ) then
	
		-- Error
		LG("pkodev.contract", "Can't create the contract item (id:", contract.conf['item_id'], ") because there are no free slots in the bag!") 
		return LUA_FALSE, nil, 0
		
	end
	
	-- Create an item
	local r1, r2 = MakeItem(role, contract.conf['item_id'], 1, 4)
	
	-- Check the result
	if ( r1 == 0 ) then
	
		-- Error
		LG("pkodev.contract", "Can't create the contract item (id:", contract.conf['item_id'], ")!") 
		return LUA_FALSE, nil, 0
		
	end
	
	-- Get the item descriptor
	local item = GetChaItem(role, 2, r2)
	
	-- Set contract data
	local a1 = SetItemAttr(item, contract.const['target_id'], target_id)
	local a2 = SetItemAttr(item, contract.const['target_max'], number)
	local a3 = SetItemAttr(item, contract.const['target_cur'], 0)
	
	-- Check that the data is set
	if ( (a1 == 0) or (a2 == 0) or (a3 == 0) ) then
	
		-- Error
		LG("pkodev.contract", "Can't set the contract data! a1 = ", a1, ", a2 = ", a2, ", a3 = ", a3) 
		return LUA_FALSE, item, r2
	
	end
	
	-- Synchronize the kitbag
	SynChaKitbag(role, 13)
	
	-- Write a message to the player
	SystemNotice(role, string.format("You received a monster hunt contract [%s] x %d!", GetMonsterName(target_id), number))

	-- The contract is successfully created!
	return LUA_TRUE, item, r2
	
end

-- Contract item use event
ItemUse_PKOdevContract = function(role, item)

	-- Get the main character's descriptor
	role = TurnToCha(role)
	
	-- Get contract data
	local target_id  = GetItemAttr(item, contract.const['target_id'])
	local target_max = GetItemAttr(item, contract.const['target_max'])
	local target_cur = GetItemAttr(item, contract.const['target_cur'])
	
	-- Check that the contract is not completed
	if ( target_cur < target_max ) then
		
		-- Print a message
		SystemNotice( role, string.format("You have to kill [%s] x %d more to complete this contract!", 
			GetMonsterName(target_id), (target_max - target_cur) ) )
		
		-- Cancel the item usage
		UseItemFailed(role)

	else
		
		-- Print a message
		SystemNotice(role, "You have successfully completed the contract, congratulations!")
		
		-- Call user-defined reward function
		if ( contract.conf['reward_cb'] ~= nil ) then
			
			contract.conf['reward_cb'](role, item)

		end
		
	end
	
end