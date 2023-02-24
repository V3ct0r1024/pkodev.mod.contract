


# pkodev.mod.contract / Contracts system

![The "Contract"](https://raw.githubusercontent.com/V3ct0r1024/pkodev.mod.contract/master/img/active_eng.png)

This system for the MMORPG game "Tales of Pirates" is a "Monster Hunt" type quest, the purpose of which is to defeat a certain amount of specific monsters. A player is given a special item - **“Contract”**, which indicates which monster and how many the player have to defeat. As monsters are defeated, the player's current progress is updated in the "Contract". After defeating the required number of monsters, the "Contract" is considered completed, and the player can receive a reward by using the "Contract" item.

The system consists of a [**pkodev.mod.loader**](https://github.com/V3ct0r1024/pkodev.mod.loader) modification for the game client (Game.exe) and a Lua script for the game server (GameServer.exe).

Modification of the client is necessary to visualize the specified characteristics of the item in the hint field for the "Contract" when the player hover the mouse cursor over it's item. The target monster ID, the number of monsters already defeated, and the number of monsters needed to complete the "Contract" are stored in the following item stats: ITEMATTR_VAL_STR, ITEMATTR_VAL_DEX, and ITEMATTR_VAL_AGI, respectively. The purpose of the mod is to display these item characteristics in a form understandable to the player. For example, if ITEMATTR_VAL_STR = 103, ITEMATTR_VAL_DEX = 5, and ITEMATTR_VAL_AGI = 10, then the player will see the following information when hovering the mouse over "Contract":

    Hunt: 'Forest Spirit' x 10
    Progress: 5 / 10

The Lua script for the game server is the core of the Contracts system, which contains the System settings and the logic of its operation. For example, when defeating next monster, the script will search the character's inventory for a suitable active "Contract", and if such the item is found, the System will update its state. An important setting of the script is the function that is necessary for issuing a reward after the player successfully completes the "Contract".

## Some features of the System

 1. "Contract" can be **picked up**, **thrown away**, **transferred to another player**, **put in a bank** or **sold**;
 2. If a player has **multiple "Contracts"** in his inventory to hunt the same monster, then when defeating this monster, the "Contract" is selected **randomly**;
 3. To receive a reward after completing a "Contract", the player should **use an item** of the "Contract", for example by double-clicking on it. The player will see a corresponding message in the system chat if the "Contract" has not yet been completed;
 4. **The content and amount of the reward are determined by the administrator** in a special function of the System script;
 5. **ID and item type** for "Contract" must be **unique** and **set by the administrator** in the System settings. The default item type is **99**, the default item ID is undefined.

## Information about the modification

-   **Name:**  pkodev.mod.contract;
-   **Version:**  1.1;
-   **Author:**  [V3ct0r](https://github.com/V3ct0r1024);
-   **Type:** for game client (Game.exe);
-   **Supported executable files (.exe):**  GAME_13X_0, GAME_13X_1, GAME_13X_2, GAME_13X_3, GAME_13X_4, GAME_13X_5.

## Installing the Contracts system

### Game server

1. Add a "Contract" item to the **[GameServer\resource\ItemInfo.txt](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/GameServer/resource/ItemInfo.txt)** file. To do this, select any suitable ID (XXXX) and item type (99 by default):

		XXXX	Contract	n0184	10130005	0	0	0	0	0	00	99	0	0	0	0	0	1	1	1	1	1	1	0	-1	0	-1	0	0	-1	-1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0,0	0	10,10	0,0	0	0	0	0	0	0	0	0	0	ItemUse_PKOdevContract	0	0	0	0	0	0	After completion you will receive a reward!


2. Place Lua script **[pkodev.contract.lua](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/GameServer/resource/script/calculate/mods/pkodev.contract.lua)** in **GameServer\resource\script\calculate\mods** directory (create **mods** folder if necessary).

3. Open the **pkodev.contract.lua** file and configure it as follows:

	 -  Write the "Contract" item ID from ItemInfo.txt (XXXX) to the **item_id** variable:
				
			 item_id = XXXX,

	 -  In the **CompletionCallback()** function, write a code that will give players a reward after completing "Contracts". By default, the function gives a player 1,000 gold coins, a random item (Refining Gem x 1, or Gem of Rage x 2, or Cake x 60, or Fairy of Luck x 1) and launches fireworks:

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
 
	 -  Open the file **GameServer\resource\script\calculate\SkillEffect.lua** and at the very beginning write the line:

			dofile(GetResPath("script\\calculate\\mods\\pkodev.contract.lua"))

  4. The Contracts system has been successfully installed on your server. Congratulations!
    
### Game client

 1.  Add a "Contract" item to the **[Client\scripts\table\ItemInfo.txt](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/GameServer/resource/ItemInfo.txt)** file (see above "Installing the Contracts system" > "Game server" > point 1). **[Compile](https://pkodev.net/topic/26-client-txt-tables-compiling/)** ItemInfo.txt.
 2. Add to the file **[Client\scripts\table\StringSet.txt](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/Client/scripts/table/Add%20to%20StringSet.txt%20(EN).txt)** the following strings that a player will see when hovering the mouse over the "Contract":
 
		[1000]	"(Completed)"
		[1001]	"(Active)"
		[1002]	"Hunt: '{0}' x {1}"
		[1003]	"Progress: {0} / {1}"
	**Note 1:** If IDs of strings 1000 - 1003 are already taken, then write any free IDs instead.  
	**Note 2:** After adding these strings to the StringSet.txt file, delete the StringSet.bin file if it exists, otherwise the changes will not be applied.  
	**Note 3:** In string **1002**, marker **{0}** is the name of the monster, and **{1}** is the number of monsters to defeat. In string **1003** marker **{0}** indicates the number of monsters already defeated, marker **{1}** is similar to string **1002**.  
 3. Install mod loading system [**pkodev.mod.loader**](https://github.com/V3ct0r1024/pkodev.mod.loader) if it hasn't already been installed.
 4. Place the mod DLL file **[pkodev.mod.contract.client.13x_{ID}.dll](https://github.com/V3ct0r1024/pkodev.mod.contract/releases/)** for your version of Game.exe and the mod settings file **[pkodev.mod.contract.json](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/cfg/pkodev.mod.contract.json)** in the **mods\pkodev.mod.contract** folder of the game client.
 5. Open the mod's settings file **pkodev.mod.contract.json** and write the following parameters into it according to your choice:

		1. itemType - type of the item "Contract" specified in the ItemInfo.txt file. The default value is 99.
		2. colorCompleted - the color of the "(Completed)" label in the hint for the "Contract" item in the format 0xAARRGGBB. The default value is 0xFF00FF00 (Green).
		3. colorActive - the color of the "(Completed)" label in the hint for the "Contract" item in the format 0xAARRGGBB. The default value is 0xFFFFA500 (Orange).
		4. STRING_001 - string ID for the "(Completed)" label from the StringSet.txt file. The default value is 1000.
		5. STRING_002 - string ID for the "(Active)" label from the StringSet.txt file. The default value is 1001.
		6. STRING_003 - string ID for the "Hunt: '{0}' x {1}" label from the StringSet.txt file. The default value is 1002.
		7. STRING_004 - string ID for the "Progress: {0} / {1}" label from the StringSet.txt file. The default value is 1003.
		
	**Note:** This file can be left unchanged if you used the default values in the ItemInfo.txt and StringSet.txt files.  
6. The contracts system setup for the game client is now complete!

## Creating "Contracts" and issuing them to the players

"Contracts" are created using the **contract.create()** function, which takes as its arguments the **handle of a character** to which the contract is to be issued, the **ID of a monster** a player will need to defeat, and **a number of monsters** that the player have to defeat. As a result, the function returns a tuple of three elements: **success flag**, **new item descriptor**, and **item slot number in the character's inventory**.

**Syntax:**

	local <Result LUA_TRUE|LUA_FALSE>, <Item descriptor>, <Item slot> = contract.create(<Character descriptor>, <Monster ID>, <Number of monsters>)

**Example:**
	
	local ret, item, pos = contract.create(role, 103, 7)

As the result, a **"Contract"** will be created to defeat the **seven Forest Spirits**, which will appear in the inventory of the **role** character. In case of an error, the function will return the value **LUA_FALSE** to the **ret** variable and write a log message to the **pkodev.contract.txt** file.

**Note:** Creation of "Contracts" can be organized, for example, through a special NPC or other item.

## Discussion on the PKOdev.NET forum

 - [English section](https://pkodev.net/topic/5903-contract-system/)
 - [Russian section](https://pkodev.net/topic/5902-%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%B0-%D0%BA%D0%BE%D0%BD%D1%82%D1%80%D0%B0%D0%BA%D1%82%D0%BE%D0%B2/)

## Useful links

 1. [Lua script of the Contracts system for the game server](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/GameServer/resource/script/calculate/mods/pkodev.contract.lua)
 2. [ItemInfo.txt with an example of the "Contract" item](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/GameServer/resource/ItemInfo.txt)
 3. [Strings for the file StringSet.txt](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/Client/scripts/table/Add%20to%20StringSet.txt%20(EN).txt)
 4. [Modification binary files for the client (.dll)](https://github.com/V3ct0r1024/pkodev.mod.contract/releases/)
 5. [The file with the modification settings for the client (pkodev.mod.contract.json)](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/cfg/pkodev.mod.contract.json)
 6. [Mod loading system pkodev.mod.loader](https://github.com/V3ct0r1024/pkodev.mod.loader)
