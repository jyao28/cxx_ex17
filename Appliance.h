#pragma once

#include "device.h"

namespace Home
{

class Appliance : public Module
{
public:
  Appliance(HouseCode  hcode, UnitCode ucode, bool s=false) :
    Module {hcode, ucode},
    state {s}
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

  bool state;
};

}