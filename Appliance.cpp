#include "Appliance.h"

namespace Home
{

// Appliance

std::string Appliance::status_str() const
{
  return Module::status_str() + ", " + 
         std::string("State: ") + ((state) ? "ON" : "OFF");
}

void Appliance::on()
{
  state = true;
  if (is_valid())
  {
    if (!name.empty())
      std::cout << name << " : ";
    std::cout << "Appliance" << "(" << module_name() << ") has been turned ON." << std::endl;
  }
}

void Appliance::off()
{
  state = false;
  if (is_valid())
  {
    if (!name.empty())
      std::cout << name << " : ";
    std::cout << "Appliance" << "(" << module_name() << ") has been turned OFF." << std::endl;
  }
}

Appliance::~Appliance()
{
  if (dbg_func_trace)
  {
    std::cout << "~" << type() << " ==> " ;
  }
}

}
