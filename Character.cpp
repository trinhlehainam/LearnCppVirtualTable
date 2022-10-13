#include "Character.h"

#include <iostream>

namespace
{
    CharacterVtable Vtable = {
        [](void* self)
        {
            CharacterDestructor(static_cast<Character*>(self));
        },
        &CharacterOverrideUpdate, &CharacterVirtualAttack
    };
}

void CharacterConstructor(Character* self)
{
    // Call Parent's Constructor
    BaseActorConstructor(&self->Parent);

    self->Parent.Vptr = &Vtable;
}

void CharacterConstructor(Character* self, float AttackDamage)
{
    CharacterDestructor(self);

    self->AttackDamage = AttackDamage;
}

void CharacterDestructor(Character* self)
{
    std::cout << "Character Destructor !" << std::endl;

    // if parent's Destructor is declared as virtual, Compiler implicitly calls parent's Virtual Destructor at the end of this class Destructor
    // This code is done at compiler time
    if (self->Parent.HasVirtualDestructor)
        BaseActorVirtualDestructor(&self->Parent);
}

void CharacterOverrideUpdate(Character* self)
{
    // Use parent Update
    // Super::Update (Unreal Engine) or BaseActor::Update
    BaseActorVirtualUpdate(&self->Parent);
    
    std::cout << "Character Update !" << std::endl;

    CharacterAttack(self);
}

void CharacterVirtualAttack(Character* self)
{
    std::cout << "Character Attack Damage: " << self->AttackDamage << std::endl;
}

void CharacterUpdate(Character* self)
{
    static_cast<CharacterVtable*>(self->Parent.Vptr)->Update(self);
}

void CharacterAttack(Character* self)
{
    static_cast<CharacterVtable*>(self->Parent.Vptr)->Attack(self);
}