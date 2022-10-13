#include "Player.h"

#include <iostream>

namespace
{
    const PlayerVtable Vtable = {
        [](void* self)
        {
            PlayerDestructor(static_cast<Player*>(self));
        },
        &CharacterOverrideUpdate, &CharacterVirtualAttack
    };
}

void PlayerConstructor(Player* self)
{
    // Call Parent's Constructor
    CharacterConstructor(&self->Parent);

    self->Parent.Parent.Vptr = &Vtable;
}

void PlayerConstructor(Player* self, float AttackDamage)
{
    PlayerConstructor(self);

    self->Parent.AttackDamage = AttackDamage;
}

void PlayerDestructor(Player* self)
{
    std::cout << "Player Destructor !" << std::endl;

    // if parent's Destructor is declared as virtual, Compiler implicitly calls parent's Virtual Destructor at the end of this class Destructor
    // This code is done at compiler time
    if (self->Parent.Parent.HasVirtualDestructor)
        CharacterDestructor(&self->Parent);
}

void PlayerUpdate(Player* self)
{
    static_cast<const PlayerVtable*>(self->Parent.Parent.Vptr)->Update(&self->Parent);
}

void PlayerAttack(Player* self)
{
    static_cast<const PlayerVtable*>(self->Parent.Parent.Vptr)->Attack(&self->Parent);
}
