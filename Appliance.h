#pragma once

#include "Module.h"
#include <string_view>

namespace Home
{

class Appliance : public Module
{
public:
  Appliance(const char* name, HouseCode  hcode, UnitCode ucode, bool s=false) :
    Module {hcode, ucode},
    state {s},
    name(name)
  {
    if (dbg_func_trace)
    {
      std::cout << "Appliance::Appliance(" 
                  << house_str() << ", " 
                  << unit_str() << ", "
                  << (s ? "true" : "false") 
                << ")" << std::endl;
    }

  }

  ~Appliance() override;

  std::string type() const override { return "Appliance"; };

  bool      is_on() const { return state; }
  void      on() override;
  void      off() override;

private:
  virtual std::string status_str() const;

  std::string_view name;
  bool state;
};

}