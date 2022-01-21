#include "Room.h"

#include "Switchable.h"
#include "Module.h"

#include <algorithm>

namespace Home
{

class Functor_is_on
{
public:
  bool operator()(Switchable* s)
  {
    return s->is_on();
  }
};

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
  if (!name.empty())
  {
    std::cout << "Status of Room " << name << std::endl;
    std::cout << "In the room " << name << " ";
  }
  else
  {
    std::cout << "Status of Room "<< std::endl;
  }

  auto is_on = [](Switchable* s) -> bool
  {
    return (s->is_on());
  };

  //std::ptrdiff_t count = std::count_if(devices.begin(), devices.end(), is_on);
  std::ptrdiff_t count = std::count_if(devices.begin(), devices.end(), Functor_is_on{});

  std::cout << "there are " << count << " devices on and "
            << devices.size() - static_cast<size_t>(count) << " devices off" << std::endl;

  // for (auto switchable : devices)
  // {
  //   if (auto module = dynamic_cast<Module*>(switchable))
  //   {
  //     module->status();
  //   }
  // }
}

}
