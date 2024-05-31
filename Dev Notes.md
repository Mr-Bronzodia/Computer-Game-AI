Following on from the 2-D RPG base we've been provided for the project, try to turn this base into a 2-D Action-RPG with loose Rogue-lite elements. Obviously just a prototype with basic features/implementations.

The game mostly revolves around an arena in which the player fights against enemies to increase their might (score system) which can then be used to buy upgrades (such as +damage, +shield/protection, +speed).

Outside of the arena, is a neutral area where the player can talk with AI NPCs. One of these NPCs is a healer - the grim reaper. Talking to the reaper gives health but expends might. If all might and health is lost then the game is over. 

Might is the players score. Might starts at 5. Enemies can damage the players health and a small amount of might.  Upon killing an enemy the player should earn 1 might, enemies can damage the player for between 0.25 to 0.75 depending on enemy type.

It is also possible for the player to gain upgrades via pickups which drop from slain enemies, these pickups are less potent. Another pickup is a might potion (health) which allows the player to refill their might.

# Title: Colosseum of Might

## General backstory/idea
The player has been sentenced to the arena to live the rest of their days, they must build their might and strength in order to break free of their new-found prison.

## Features
+ 'Might system' - acts as score, used to buy upgrades, upgrades are enhanced by might (multiplied)
+ Enemies - found only in the arena, attack the player and their might
+ Pick-ups - less potent upgrades, enhance player skills
+ Upgrades - bought for might, more potent
+ Grim Reaper NPC - uses might to fully heal 

## Inspirations 
+ FATE 
+ Diablo 
+ Vampire Survivors

Both Action RPGs, FATE inspired the pickup system as well as the idea of score affecting the player. Both FATE and Diablo loosely inspired gameplay and, specifically,  the idea of a neutral/NPC area as well as a non-neutral battle arena. Vampire Survivors inspired the idea of simple gameplay as the main focus in on obtaining upgrades, the player only having a single attack as well as the random arena combat. 

## Enemies
Enemies will use Computer Vision to recognise and target the player, they will also make use of the A* algorithm for efficient pathfinding.

There should be a small range of enemies, which each deal different damage rates. These should be randomly chosen and placed within the arena. 

Attibutes
+ health = 25/50/75
+ damage = 0.25/0.5/0.75

## Player
Player only has 1 attack, bound to Spacebar which is affected by aforementioned upgrades and so on. 

Attributes
+ health = 100
+ might = 5
+ damage =2
+ shield = 0
+ speed = 1

Upgrades (limited)
+ +health (+25 health)
+ +damage (+2 dmg)
+ +shield (+0.2 shield) (reduces enemy damage by shield val)
+ +speed (+1 speed)

Pick-ups (infinite)
+ heal (heal 25%)
+ +dmg (+1 dmg)
+ +shield (+0.1 shl)
+ +speed (+0.5 speed)