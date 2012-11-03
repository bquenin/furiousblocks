#ifndef __Action_H_
#define __Action_H_


class Action {
private:
protected:
  float timeStep;
  float nextStep = 0;

public:
  Action(float timeStep);
  void setNextStep(float nextStep);
  float getTimeStep();
  virtual bool execute(float stateTime) = 0;
};

#endif //__Action_H_
