#include <iostream>
#include "device.h"

#include "ex.h"

using Home::Lamp;

// Ex8 tests
void lamp_status(Lamp lamp)
{
  lamp.status();
}

void lamp_status_r(Lamp& lamp)
{
  lamp.status();
}

void lamp_status_r(const Lamp* lamp)
{
  lamp->status();
}

void lamp_status_cr(const Lamp& lamp)
{
  lamp.status();
}

void test_pass_by()
{
  std::cout << "Ex8 -- Compare pass by value, by reference and by pointer -----" << std::endl;
  {
    std::cout << "Ex8.1  ---------------------" << std::endl;
    Home::Lamp lamp = Home::Lamp::make_rand_lamp();
    lamp_status(lamp);
  }


  std::cout << "    Ex8.2  ---------------------" << std::endl;
  {
    Home::Lamp lampr = Home::Lamp::make_rand_lamp();
    lamp_status_r(&lampr);
  }

  std::cout << "    Ex8.3  ---------------------" << std::endl;
  {
    Home::Lamp lampr = Home::Lamp::make_rand_lamp();
    lamp_status_r(lampr);
  }

  std::cout << "    Ex8.4  ---------------------" << std::endl;
  {
    Home::Lamp lampr = Home::Lamp::make_rand_lamp();
    lamp_status_cr(lampr);
  }

}
////////////////////
