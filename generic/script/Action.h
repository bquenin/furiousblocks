#ifndef __Action_H_
#define __Action_H_


class Action {
private:
protected:
  float timeStep = 0;
  float nextStep = 0;
  virtual bool execute(float stateTime) = 0;

public:
  void setNextStep(float nextStep);
  float getTimeStep();
};

#endif //__Action_H_