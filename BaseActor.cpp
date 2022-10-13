#include "BaseActor.h"

#include <iostream>

namespace
{
    BaseActorVtable Vtable = {nullptr, &BaseActorVirtualUpdate};
}

void BaseActorConstructor(BaseActor* self)
{
    self->Vptr = &Vtable;
    self->HasVirtualDestructor = true;
}

void BaseActorDestructor(BaseActor* self)
{
    if (self->HasVirtualDestructor)
        static_cast<BaseActorVtable*>(self->Vptr)->ChildDestructor(self);
    else
        std::cout << "BaseActor Destructor !" << std::endl;
}

void BaseActorVirtualDestructor(BaseActor* self)
{
    std::cout << "BaseActor Destructor !" << std::endl;
}

void BaseActorVirtualUpdate(BaseActor* self)
{
    std::cout << "BaseActor Update !" << std::endl;
}

void BaseActorUpdate(BaseActor* self)
{
    static_cast<BaseActorVtable*>(self->Vptr)->Update(self);
}