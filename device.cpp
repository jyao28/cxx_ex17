#include "device.h"

#include <iostream>
#include <cstdlib>

namespace Home {

void Device::set_id(const std::pair<HouseCode, UnitCode>& id)
{
  house_code = id.first;
  unit_code  = id.second;
}

void Device::set_id(HouseCode house_code, UnitCode unit_code)
{
  this->house_code = house_code;
  this->unit_code = unit_code;
}

void Device::status() const
{
  std::cout << "House Code: " << houseName() << std::endl
            << "Unit Code:  " << static_cast<int>(unit_code) << std::endl;
}

void Lamp::status() const
{
  Device::status();
  std::cout << "State:      " << ((state) ? "On" : "Off") << std::endl;
}


Lamp Lamp::make_rand_lamp()
{
  return Lamp {
      {  static_cast<HouseCode>((rand()%16)+1), 
        static_cast<UnitCode>((rand()%4)+1)
      },
      false
    };
}


void Lamp::on()
{
  state = true;
  if (is_valid())
  {
    std::cout << type() << "(" << device_name() << ") has been turned ON." << std::endl;
  }
}
void Lamp::off()
{
  state = false;
  if (is_valid())
  {
    std::cout << type() << "(" << device_name() << ") has been turned OFF." << std::endl;
  }
}

Lamp::~Lamp()
{
  std::cout << "Lamp::" << type() << "(" << device_name() << ") has been destroyed." << std::endl;
}


}

///////////////////////////
// C++ testing

int f1(int x, int)
{
  return x;
}

int f1(const int& x)
{
  return x+1;
}

int f2(int x)
{
  return f1(x) + f1(2);
}
