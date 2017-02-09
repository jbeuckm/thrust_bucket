
#ifndef BASE_MODE_FUNCTION
#define BASE_MODE_FUNCTION

class BaseModeFunction {
public:
  bool trapWheelRotation = false;

  BaseModeFunction();

  virtual void getLabel() = 0;

  virtual void handleWheelRotation(int wheelRotation) = 0;
  virtual void handleButtonDown() = 0;
  virtual void handleButtonUp() = 0;
};

#endif
