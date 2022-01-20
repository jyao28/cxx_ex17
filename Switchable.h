#pragma once

namespace Home
{

class Switchable
{
public:
  virtual bool is_on() const = 0;
  virtual void on() = 0;
  virtual void off() = 0;

  virtual ~Switchable() = default;
};


}