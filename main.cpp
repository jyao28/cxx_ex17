#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>

#include "device.h"
#include "ex.h"

using Home::Lamp;
using Home::HouseCode;

constexpr size_t sz {4};
using LampArray = std::array<Home::Lamp, sz>;

void all_lamps_on(LampArray& lamps)
{
  for (auto& lamp : lamps)
  {
    lamp.on();
  }
}

void all_lamps_off(LampArray& lamps)
{
  for (auto& lamp : lamps)
  {
    lamp.off();
  }
}

uint num_lamps_on(const LampArray& lamps)
{
  uint count {0};
  for (auto& lamp : lamps)
  {
    if (lamp.is_valid() && lamp.is_on())
    {
      ++count;
    }
  }

  return count;
}


int main()
{
  // initialize random seed
  srand (clock());

  std::cout << "Ex2 and Ex3 ----------" << std::endl;

  {
  Home::Lamp lamp = Home::Lamp::make_rand_lamp();
  Home::Lamp lamp2 = Home::Lamp::make_rand_lamp();
  Home::Lamp lamp3 = Home::Lamp::make_rand_lamp();

  // test explicit keyword
  Home::Lamp lamp4 {false}; // pass
  // Home::Lamp lamp5 = true; // failed

  lamp.status();

  lamp.on();
  lamp2.off();
  lamp3.on();
  }

  {
  std::cout << "Ex4 ------------------------" << std::endl;
  LampArray lamps { {
      {{Home::HouseCode::A, 1}, false},
      {{Home::HouseCode::B, 1}, false},
      {{Home::HouseCode::C, 3}, false} 
    }
  };

  std::cout << "Ex6, 7 ---------------------" << std::endl;

  lamps[0].set_id(std::pair<Home::HouseCode, Home::UnitCode>(Home::HouseCode::A, 1));
  lamps[2].on();

  std::cout << "Number of lamps ON: " << num_lamps_on(lamps) << std::endl;

  std::cout << "> All lamps ON" << std::endl;
  all_lamps_on(lamps);

  std::cout << "Number of lamps ON: " << num_lamps_on(lamps) << std::endl;
  }

  // Ex8
  test_pass_by();

  return 0;
}

