#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <array>
#include <iostream>

constexpr bool dbg_func_trace {true};

namespace Home {


enum class HouseCode
{ 
  INVALID, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
};

using House = HouseCode;

using UnitCode = std::uint8_t;

class Module
{
public:
  Module() = delete;

  Module(const Module& Module) = default;

  Module(HouseCode  hcode, UnitCode   ucode) :
    house_code {hcode},
    unit_code  {ucode}
  {
    
  }

  virtual ~Module() {};

  virtual std::string type() const { return "Module"; }

  bool is_valid() const 
  {
    return house_code != HouseCode::INVALID && unit_code != 0;
  }

  std::string module_name() const
  {
    return house_str() + ' ' + unit_str();
  }

  std::pair<HouseCode, UnitCode> id() const
  {
    return std::pair<HouseCode, UnitCode>(house_code, unit_code);
  }

  virtual void status() const;

  virtual bool is_on() const = 0;
  virtual void on() = 0;
  virtual void off() = 0;


  //void set_id(const std::pair<HouseCode, UnitCode>& id);
  //void set_id(HouseCode house_code, UnitCode unit_code);

protected:
  virtual std::string status_str() const;

  std::string house_str() const
  {
    if (house_code == HouseCode::INVALID) return "-";

    char c = static_cast<int>('A') + static_cast<int>(house_code) - static_cast<int>(HouseCode::A);
    return { c };
  }

  std::string unit_str() const
  {
     return (unit_code >= 1 && unit_code <= 16) ?
        std::to_string(unit_code) :
        "-";
  }

private:
  HouseCode  house_code {HouseCode::INVALID};
  UnitCode   unit_code {0};

};

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

  ~NamedLamp() override {};

private:
  std::string_view name;

};

class Room
{
public:
  Room() = delete;
  Room(const char* name) : name(name) {}
  Room(const Room&) = delete;

  bool add(Module& Module);
  void all_off();
  void all_on();

  //void set_name(const char* name)
  //{
  //  this->name = name;
  //}
  void status();

private:
  const std::string_view name;
  static constexpr unsigned dsz {4};
  using DeviceList = std::array<Module*, dsz>;
  DeviceList devices;
  unsigned device_count {0};

};



}
