#include "Device.h"

#include <iostream>
#include <cstdlib>

namespace Home {

Module::~Module()
{
  if (dbg_func_trace)
  {
    std::cout << "~Module::Module ( " << module_name() << " )" << std::endl;
  }
}

void Module::status() const
{
  std::cout << type() << " ( " << status_str() << " )" << std::endl;
}

std::string Module::status_str() const
{
  return std::string("HouseCode: ") + house_str() + std::string(", UnitCode: ") + unit_str();
}


// Room
bool Room::add(Switchable& switchable)
{
  if (device_count < devices.size())
  {
    devices[device_count] = &switchable;
    ++device_count;
    return true;
  }

  return false;
}

void Room::all_off()
{
  auto iter = std::begin(devices);
  unsigned i;
  for (i=0;
       i<device_count;
       ++i, ++iter)
  {
    (*iter)->off();
  }
}

void Room::all_on()
{
  auto iter = std::begin(devices);
  unsigned i;
  for (i=0;
       i<device_count;
       ++i, ++iter)
  {
    (*iter)->on();
  }
}

void Room::status()
{
  std::cout << "Status of Room " << name << std::endl;

  auto iter = std::begin(devices);
  unsigned i;
  for (i=0;
       i<device_count;
       ++i, ++iter)
  {
    if (auto module = dynamic_cast<Module*>(*iter))
    {
      module->status();
    }
  }

}


}
