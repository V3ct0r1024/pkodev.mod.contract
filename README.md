# pkodev.mod.contract

[![logo-background](https://user-images.githubusercontent.com/3164064/163711104-29410e0d-3c86-411a-9319-9ffeaa62abb8.png)](http://pkodev.net "PKOdev.NET")

Contracts system for the MMORPG game "Tales of Pirates".

## Documentation

- Please refer to [this page](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/doc/pkodev.mod.contract.doc.en.md) to get information about the System in **English language**;
- Please refer to [that page](https://github.com/V3ct0r1024/pkodev.mod.contract/blob/master/doc/pkodev.mod.contract.doc.ru.md) to get information about the System in **Russian language**.

## Information about the modification

- **Name:** pkodev.mod.contract;
- **Version:** 1.1;
- **Author:** [V3ct0r](https://github.com/V3ct0r1024);
- **Type:** for the game client (Game.exe);
- **Supported executable .exe files:** GAME_13X_0, GAME_13X_1, GAME_13X_2, GAME_13X_3, GAME_13X_4, GAME_13X_5.

## How to build

You will need the [**Visual Studio 2022 Community**](https://visualstudio.microsoft.com/vs/community/) IDE installed, which you can download for free from the Microsoft website, and the [**Git**](https://git-scm.com/) VCS.

### Way one - build.bat script

1. Open **Developer Command Prompt for VS 2022**;
2. Execute the following sequence of commands:

	
		git clone https://github.com/V3ct0r1024/pkodev.mod.contract.git
		cd pkodev.mod.contract
		build
	
### Way two - Visual Studio GUI

1. Open **Command Prompt** (cmd.exe);
2. Execute the following sequence of commands:

	
		git clone https://github.com/V3ct0r1024/pkodev.mod.contract.git
		cd pkodev.mod.contract
		start .

3. Double click on the file "**pkodev.mod.contract.sln**". This will launch Visual Studio 2022 Community;
4. Select the desired version of Game.exe in the drop-down list of configurations and click the green arrow to build the modification.

.DLL files of the modification will appear in the directory **pkodev.mod.contract\bin**. You can install them in the client, for example with the following command:

	
	move "Path to the .DLL file" "Path to the client mods directory"

## Gallery

![Image 1](https://raw.githubusercontent.com/V3ct0r1024/pkodev.mod.contract/master/img/active_eng.png)

![Image 2](https://raw.githubusercontent.com/V3ct0r1024/pkodev.mod.contract/master/img/active_rus.png)
![Image 3](https://raw.githubusercontent.com/V3ct0r1024/pkodev.mod.contract/master/img/completed_rus.png)

![Image 4](https://raw.githubusercontent.com/V3ct0r1024/pkodev.mod.contract/master/img/bag.png)

## Discussion on the forum PKOdev.NET

- [English section](https://pkodev.net/topic/5903-contract-system/);
- [Russian section](https://pkodev.net/topic/5902-%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%B0-%D0%BA%D0%BE%D0%BD%D1%82%D1%80%D0%B0%D0%BA%D1%82%D0%BE%D0%B2/).

## Download

The latest release of the modification can be found **[here](https://github.com/V3ct0r1024/pkodev.mod.contract/releases/)**.
