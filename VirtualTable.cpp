#include "Player.h"

int main(int argc, char* argv[])
{
    // Character* character = new Player(100.f);
    Player player; PlayerConstructor(&player, 100.f);
    Character* character = &player.Parent;
    //

    CharacterUpdate(character);
    
    // delete character
    CharacterDestructor(character);
    
    return 0;
}