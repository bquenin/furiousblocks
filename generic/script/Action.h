#ifndef __Action_H_
#define __Action_H_

class Action {
private:
protected:
  float timeStep;
  float nextStep;

public:
  Action(float timeStep);

  virtual ~Action() {};

  void setNextStep(float nextStep);
  float getTimeStep();
  virtual bool execute(float stateTime) = 0;
};

#endif //__Action_H_
