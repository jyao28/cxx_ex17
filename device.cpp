#include "Device.h"

#include <iostream>
#include <cstdlib>

namespace Home {

// void Module::set_id(const std::pair<HouseCode, UnitCode>& id)
// {
//   house_code = id.first;
//   unit_code  = id.second;
// }
// 
// void Module::set_id(HouseCode house_code, UnitCode unit_code)
// {
//   this->house_code = house_code;
//   this->unit_code = unit_code;
// }

void Module::status() const
{
  std::cout << type() << " ( " << status_str() << " )" << std::endl;
}

std::string Module::status_str() const
{
  return std::string("HouseCode: ") + house_str() + std::string(", UnitCode: ") + unit_str();
}

std::string Lamp::status_str() const
{
  return Module::status_str() + ", " + 
         std::string("State: ") + ((state) ? "ON" : "OFF");
}

Lamp Lamp::make_rand_lamp()
{
  return Lamp {
           static_cast<HouseCode>((rand()%16)+1), 
           static_cast<UnitCode>((rand()%4)+1)
         };
}


void Lamp::on()
{
  state = true;
  if (is_valid())
  {
    std::cout << "Lamp" << "(" << module_name() << ") has been turned ON." << std::endl;
  }
}
void Lamp::off()
{
  state = false;
  if (is_valid())
  {
    std::cout << "Lamp" << "(" << module_name() << ") has been turned OFF." << std::endl;
  }
}

Lamp::~Lamp()
{
  if (dbg_func_trace)
  {
    std::cout << "~Lamp::" << type() << " ( " << module_name() << " )" << std::endl;
  }
}

// NamedLamp
void NamedLamp::status() const
{
  Lamp::status();
}

void NamedLamp::on()
{
  std::cout << lamp_name() << " : ";
  Lamp::on();
}

void NamedLamp::off()
{
  std::cout << lamp_name() << " : ";
  Lamp::off();
}

// Room
bool Room::add(Module& Module)
{
  if (device_count < devices.size())
  {
    devices[device_count] = &Module;
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
    auto lamp = dynamic_cast<Lamp*>(*iter);
    if (lamp)
    {
      lamp->off();
    }
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
    auto lamp = dynamic_cast<Lamp*>(*iter);
    if (lamp)
    {
      lamp->on();
    }
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
    (*iter)->status();
  }

}


}
