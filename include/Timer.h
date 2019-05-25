#ifndef TIMER_H
#define TIMER_H


class Timer
{
public:
    Timer();

    void Update(float dt);
    void Restart();
    float Get();
    void SetTimer(float time);

private:
    float time;
};

#endif // TIMER_H
