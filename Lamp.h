#pragma once

#include "device.h"

namespace Home
{

class Lamp : public Module
{
public:
  Lamp() = delete;
  Lamp(const Lamp& lamp)
    : Module(*(static_cast<const Module*>(&lamp))),
      state(lamp.state)
  {
    if (dbg_func_trace)
    {
      std::cout << "Lamp::Lamp(const Lamp& <"
                  << module_name() << ", " 
                  << (state ? "true" : "false") 
                << ">)" << std::endl;
    }
  }

  Lamp(const Module& module, bool s) :
    Module {module},
    state {s}
  {
    if (dbg_func_trace)
    {
      std::cout << "Lamp::Lamp("
                  << module_name() << ", " 
                  << (s ? "true" : "false") 
                << ")" << std::endl;
    }

  }

  Lamp(HouseCode  hcode, UnitCode ucode, bool s=false) :
    Module {hcode, ucode},
    state {s}
  {
    if (dbg_func_trace)
    {
      std::cout << "Lamp::Lamp(" 
                  << house_str() << ", " 
                  << unit_str() << ", "
                  << (s ? "true" : "false") 
                << ")" << std::endl;
    }

  }

  std::string type() const override { return "Lamp"; }

  //static std::unique_ptr<Lamp> create();
  static Lamp make_rand_lamp();

  bool      is_on() const { return state; }
  void      on() override;
  void      off() override;

  ~Lamp() override;

protected:
  std::string status_str() const override;

private:
  bool      state {false};

};

class NamedLamp : public Lamp
{
public:
  NamedLamp(const char* name, HouseCode  hcode, UnitCode ucode, bool s=false) :
    Lamp(hcode, ucode, s),
    name(name)
  {
    if (dbg_func_trace)
    {
      std::cout << "NamedLamp::NamedLamp(" 
                  << name << ", "
                  << house_str() << ", " 
                  << unit_str() << ", "
                  << (s ? "true" : "false") 
                << ")" << std::endl;
    }
  }

  std::string type() const override { return "NamedLamp"; }

  void status() const override;
  void on() override;
  void off() override;

  const std::string_view& lamp_name() const
  {
    return name;
  }

  ~NamedLamp() override;

private:
  std::string_view name;

};

}
