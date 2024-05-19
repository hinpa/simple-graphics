#pragma once

#include "../WindowInterface/WindowClass.h"
#include <stdexcept>

class WindowClass : public IWindow {
  private:
    virtual void Destroy() override;

  public:
    virtual int Initialize(int width, int height,
                                 const char *name) override;
    WindowClass() {}
    WindowClass(int width, int height, const char *name) {
        if (Initialize(width, height, name) != 0) {
            throw std::runtime_error("Could not create GLFW Window");
        }
    }
    virtual void MakeContextCurrent() override;
    ~WindowClass();
    virtual void exec() override;
    virtual float GetAspectRatio() override;
    void TurnModel(float &x, float &y);
    void Move(float &x, float &y, float &z);
};
