/*
  L298N.cpp - Libreria per gestire i movimenti di un motore DC con il modulo
  L298N Autore:   Andrea Lombardo Sito web: http://www.lombardoandrea.com
*/

#include "L298N.h"

L298N::L298N(uint8_t pinEnable, uint8_t pinIN1, uint8_t pinIN2)
{
  _pinEnable = pinEnable;
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _pwmVal = 100;
  _isMoving = false;
  _canMove = true;
  _lastMs = 0;
  _direction = STOP;

  pinMode(_pinEnable, OUTPUT);
  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);
}

L298N::L298N(uint8_t pinIN1, uint8_t pinIN2)
{
  _pinEnable = -1;
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _pwmVal = 255; // It's always at the max speed due to jumper on module
  _isMoving = false;
  _canMove = true;
  _lastMs = 0;
  _direction = STOP;

  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);
}

void L298N::setSpeed(unsigned short pwmVal)
{
  _pwmVal = pwmVal;
}

unsigned short L298N::getSpeed()
{
  return this->isMoving() ? _pwmVal : 0;
}

void L298N::forward()
{
  digitalWrite(_pinIN1, HIGH);
  digitalWrite(_pinIN2, LOW);

  analogWrite(_pinEnable, _pwmVal);

  _direction = FORWARD;
  _isMoving = true;
}

void L298N::backward()
{
  digitalWrite(_pinIN1, LOW);
  digitalWrite(_pinIN2, HIGH);

  analogWrite(_pinEnable, _pwmVal);

  _direction = BACKWARD;
  _isMoving = true;
}

void L298N::run(L298N::Direction direction)
{
  
  switch (direction)
  {
  case BACKWARD:
    this->backward();
    break;
  case FORWARD:
    this->forward();
    break;
  case STOP:
    this->stop();
    break;
  }
}

void L298N::runFor(unsigned long wait,
                   L298N::Direction direction)
{
  this->run(direction);
  delay(wait);
  this->stop();
}

void L298N::runForwardsBackwards(unsigned long wait)
{
  this->runFor(wait, FORWARD);
  this->runFor(wait, BACKWARD);
  this->stop();
}

void L298N::forwardFor(unsigned long delay)
{
  this->runFor(delay, FORWARD);
}

void L298N::backwardFor(unsigned long delay)
{
  this->runFor(delay, BACKWARD);
}

void L298N::stop()
{
  digitalWrite(_pinIN1, LOW);
  digitalWrite(_pinIN2, LOW);

  analogWrite(_pinEnable, 255);

  _direction = STOP;
  _isMoving = false;
}

boolean L298N::isMoving()
{
  return _isMoving;
}

L298N::Direction L298N::getDirection()
{
  return _direction;
}