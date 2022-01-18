#include "device.h"

#include <iostream>
#include <cstdlib>

void Device::dump()
{
  std::cout << "House Code: " << houseName() << std::endl
            << "Unit Code:  " << static_cast<int>(unit_code) << std::endl;
}

void Lamp::dump()
{
  Device::dump();
  std::cout << "State:      " << ((state) ? "On" : "Off") << std::endl;
}


Lamp Lamp::make_lamp()
{
  // Lamp lamp;
  // lamp.house_code = static_cast<HouseCode>((rand()%17));
  // lamp.unit_code = static_cast<UnitCode>((rand()%5));
  // lamp.state = false;
  // return lamp;

  return Lamp {
    Device{  static_cast<HouseCode>((rand()%16)+1), 
       static_cast<UnitCode>((rand()%4)+1) },
    false
    };
}


void Lamp::on()
{
  state = true;
  std::cout << "Lamp(" << device_name() << ") has been turned ON." << std::endl;
}
void Lamp::off()
{
  state = false;
  std::cout << "Lamp(" << device_name() << ") has been turned OFF." << std::endl;
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
