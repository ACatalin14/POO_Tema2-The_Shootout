# The Shootout

This is a small OOP course project made in my 1st year of faculty using C++. It is a console app which consists in a survival game played in rounds, where you can observe a series of players (agents) walking on a map and trying to kill eachother. All you need to do is to give the map's dimensions, the number of participants, and then *Let the games begin!*

## Game Rules

Before the game will start, the map is created and the players are randomly distributed on the map. Then, each player is assigned a weapon and an armor of random types. Each round all the players must make one of the following decisions:
- move away from the current position to north, east, south or west;
- stay in place and execute a specific attack to hurt a player (or more players at once);

Each player is of one of the three types (Secret Agent, Ninja, Samurai) which gives some specific attributes:
- **visibility area**, where he/she can see its enemies. Based on what the player is able to see, he/she will make the appropriate decision (focus on hurting a weak rival, or running away from them if they are too powerful); its value depends on the player's type:
  - small visibility area for a Samurai;
  - medium visibility area for a Secret Agent;
  - large visibility area for a Ninja;
- **max HP**, which is assigned depending on the player's type:
  - 100HP for a Secret Agent;
  - 80HP for a Samurai;
  - 75HP for a Ninja;

The available **weapons** in this game are:
- _pistol_ (handgun), it can cause medium damage to one single player which is inside the handgun's damage area (this area is of medium size);
- _katana_, it can cause very high damage to one player and it can give to the possessor the ability to see other enemies' HP and armor so that he/she knows who is the weakest enemy to attack; its disadvantage is the damage area extremely small (1 unit radius);
- _shuriken_, the most interesting weapon, it can attack multiple enemies at once thanks to its boomerang-style attack. The downside is the low damage it can cause.

The available **armors** in this game are:
- _bulletproof vest_, it can absorb 20DP (damage points);
- _camouflage_, it can absorb 30DP;
- _kimono_, it can absorb 10DP;

**[TODO]:** A player will get **special powers** (more HP/double damage/increase stats etc.) if he is a perfect combination (one of the following):
- _Secret Agent_ who has _a pistol_ and _a bulletproof vest_;
- _Ninja_ who has _a shuriken_ and _a camouflage_;
- _Samurai_ who has _a katana_ and _a kimono_;


Each iteration of the game, the user is asked how many rounds to simulate. Each round, the updated map will be displayed with the corresponding changes. The game ends when the map contains only one player (_the survivor_).