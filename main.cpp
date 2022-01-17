#include <iostream>

#include "device.h"

int main()
{

  Lamp lamp {Lamp::make_lamp()};
  Lamp lamp2 {Lamp::make_lamp()};
  Lamp lamp3 {Lamp::make_lamp()};

  lamp.on();

  lamp.dump();
  lamp2.dump();
  lamp3.dump();

  return 0;
}

