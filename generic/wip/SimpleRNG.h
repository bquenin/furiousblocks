#ifndef __SimpleRNG_H_
#define __SimpleRNG_H_
using namespace std;
class SimpleRNG
{
public:
    SimpleRNG(int u);
    int nextInt();
    double nextDouble();

protected:
private:
    int m_w;
    int m_z;
};
#endif //__SimpleRNG_H_
