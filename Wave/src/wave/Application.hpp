#pragma once

#include <wave/Core.hpp>

namespace wave {

class WAVE_API Application {
public:
  Application();
  virtual ~Application();

  void Run();
};

Application *CreateApplication();

} // namespace wave