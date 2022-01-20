#include "Module.h"

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


}
