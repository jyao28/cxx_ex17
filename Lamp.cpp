
#include "Lamp.h"


namespace Home 
{

// Lamp class

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
    std::cout << "~" << type() << " ==> ";
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

NamedLamp::~NamedLamp()
{
  std::cout << "~" << type() << " (" << lamp_name() << ") ==> ";
}

}
