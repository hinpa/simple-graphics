#pragma once

// So that I don't forget to write 'releaseResources'
class IObject {
  public:
    virtual ~IObject() {}
    virtual void releaseResources() = 0;
};
