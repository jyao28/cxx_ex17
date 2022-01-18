#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>

#include "device.h"

constexpr size_t sz {8};

void all_lamps_on(std::array<Lamp, sz>& lamps)
{
  for (auto& lamp : lamps)
  {
    lamp.on();
  }
}

void all_lamps_off(std::array<Lamp, sz>& lamps)
{
  for (auto& lamp : lamps)
  {
    lamp.off();
  }
}

int main()
{
  // initialize random seed
  srand (clock());

  std::cout << "Ex2 and Ex3 ----------" << std::endl;

  Lamp lamp = Lamp::make_lamp();
  Lamp lamp2 = Lamp::make_lamp();
  Lamp lamp3 = Lamp::make_lamp();

  lamp.dump();

  lamp.on();
  lamp2.off();
  lamp3.on();

  std::cout << "Ex4 ----------" << std::endl;

  std::array<Lamp, sz> lamps {};

  for (auto& lamp : lamps)
  {
    lamp = Lamp::make_lamp();
    lamp.off();
  }

  all_lamps_on(lamps);

  return 0;
}

