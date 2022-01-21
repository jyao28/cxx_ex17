#include "Room.h"

#include "Switchable.h"
#include "Module.h"

namespace Home
{

// Room
bool Room::add(Switchable& switchable)
{
  devices.emplace_back(&switchable);
  return true;
}

void Room::all_off()
{
  for (auto switchable : devices)
  {
    switchable->off();
  }
}

void Room::all_on()
{
  for (auto switchable : devices)
  {
    switchable->on();
  }
}

void Room::status()
{
  std::cout << "Status of Room " << name << std::endl;

  for (auto switchable : devices)
  {
    if (auto module = dynamic_cast<Module*>(switchable))
    {
      module->status();
    }
  }
}

}
