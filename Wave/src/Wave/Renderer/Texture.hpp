#pragma once

#include <Wave/Core.hpp>

namespace Wave {

class Texture {
public:
  virtual ~Texture() {}

  virtual void Bind(uint slot = 0) const = 0;

  virtual uint GetWidth() const = 0;
  virtual uint GetHeight() const = 0;
};

class Texture2D : public Texture {
public:
  virtual ~Texture2D() {}

  static Ref<Texture2D> Create(const std::string &path);
};

} // namespace Wave