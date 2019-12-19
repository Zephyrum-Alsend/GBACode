This project is a prototype for a game for the GameBoy Advance (GBA) portable video game system by Nintendo.

The GBA is an old piece of hardware first released in 2001, received several revisions, and discontinued in 2010.  The 
system is cartridge based and is small enough to fit in one's pocket easily.  Unlike modern systems, the GBA lacks any 
type of Operatiny System, running only a short BIOS on boot before handing full control over to the main program on the 
cartridge.  As a result, use of direct memory access and manipulation is required on the part of the 
programmer.

GBA systems themselves fluctuate between easy and hard to get nowadays, but accurate and reliable emulators are available
for free, obsoleting the need for hardware to play the GBA's library of games (though you'll need hardware to access
save data from physical cartridges).

---Installation---
Download the VisualBoyAdvance-M emulator, linked in the GIT repository, and unpack the .exe to your location of choice.
A gamepad is prefered, as it more closely resembles the GBA's own shape, but keyboard controls are also configurable.
Simply open VBA and access
Options ---> Input ---> Configure ...
to change the controls.

Next, download IlderraffPrototype.gba from the folder of the same name and open the file with VBA.  Simple!

Close the emulator whenever you are finished playing.

---Default Controls---
Up - Move Up
Down - Move Down
Left - Move Left
Right - Move Right
A - Toggle Ability (currently unimplemented)
B - Attack (partially implemented)
L - Dash/Heal (no animations)
R - Change Element (currently unimplemented)
START - Menu (currently unimplemented)
SELECT - Emotes (currently unimplemented)

---Goal---
This being a prototype, it is simply to test functionality and fine tune game feel.  There currently is no goal to
complete!  Sorry!  The prototype does not resemble a fully functioning game yet.





---Design Intent---
The Legend of Zelda: Minish Cap with a bit of Hyper Light Drifter's combat and Dark Souls' emotes.

The Minish Cap is a 3/4ths perspective action adventure game where you use many items at your disposal to defeat enemies,
navigate the terrain and solve puzzles.  The player starts with a simple sword and shield and gains more tools as the
plot progresses, each tool allowing access to new areas of the world.

Hyper Light Drifer is a 3/4ths perspective action adventure game released for modern hardware.  In it, you play as a
nameless drifter afflicted with a fatal disease.  Searching for a cure with only your trusty energy saber and pistol at
your side, explore a decaying and corrupted world as you yourself slowly whither away.  HLD has incredibly tight 
controls, inviting players into a flow state.

Dark Souls is a 3D action adventure RPG for the Xbox 360, PS3, and PC known for methodical and punishing combat.
However, what is pertinent to this prototype is the selection of emotes players have at their disposal.  Emotes serve
no purpose other than to communicate with other players when encountered, and are in fact the sole method of direct
communication within the game.  This prototypes intends to emulate this player-to-player experience in 
player-to-AI interactions with its own set of emotes.

This prototype intends to take the terrain-as-puzzle approach of the Minish Cap and combine it with HLD's fast paced
and finely tuned combat to create a game that is as much about combat as it is terrain traversal.  The emote system
will allow for an organic feeling method of non-combat engagement with AI, and potentially a pacifist playthrough.

To accomplish this, the player's action will double both as combat tools and navigation tools.  

Attacking can both harm enemies and damage obstacles in one's path.  However, some objects will be resilient to physical 
attacks, as such the player can infuse their attacks with an element.  Charging the attack will unleash a strong, 
singular attack of the selected element, while pressing the toggle button will infuse all of their attacks with said 
element but at the cost of constantly draining their stamina gauge.  Certain objects and enemies will require certain 
elements to beat.  If the player ever runs out of stamina, the costs will be deducted from their health instead, to 
encourage proper stamina management.

To restore health, players can heal themselves gradually over time by holding a button.  However, they can only heal
while standing still, leaving them open to further damage.  Holding the heal button while moving will instead activate
a dash: an evasive maneuver that also doubles as rapid traversal.  Dashing consumes stamina so it cannot be used
constantly.  Healing and dashing share a button so the player is forced to choose which option to use -- they physically
cannot do both.