/*
  L298N.cpp - Libreria per gestire i movimenti di un motore DC con il modulo L298N
  Autore:   Andrea Lombardo
  Sito web: http://www.lombardoandrea.com  
*/

#include "L298NX2.h"
#include "L298N.h"

#define DEBUG 0

L298NX2::L298NX2(uint8_t pinEnable_A,
                 uint8_t pinIN1_A,
                 uint8_t pinIN2_A,
                 uint8_t pinEnable_B,
                 uint8_t pinIN1_B,
                 uint8_t pinIN2_B) : _motorA(pinEnable_A,
                                             pinIN1_A,
                                             pinIN2_A),
                                     _motorB(pinEnable_B,
                                             pinIN1_B,
                                             pinIN2_B)
{
  _canMove = true;
  _lastMs = 0;
}

L298NX2::L298NX2(uint8_t pinIN1_A,
                 uint8_t pinIN2_A,
                 uint8_t pinIN1_B,
                 uint8_t pinIN2_B) : _motorA(pinIN1_A,
                                             pinIN2_A),
                                     _motorB(
                                         pinIN1_B,
                                         pinIN2_B)
{
  _canMove = true;
  _lastMs = 0;
}


//Motor A
void L298NX2::setSpeedA(unsigned short pwmVal)
{
  _motorA.setSpeed(pwmVal);
}

unsigned short L298NX2::getSpeedA()
{
  return _motorA.isMoving() ? _motorA.getSpeed() : 0;
}

void L298NX2::forwardA()
{
  _motorA.forward();
}

void L298NX2::backwardA()
{
  _motorA.backward();
}

void L298NX2::runA(L298N::Direction direction)
{
  _motorA.run(direction);
}

void L298NX2::runForA(unsigned long delay_A, L298N::Direction direction_A)
{
  _motorA.runFor(delay_A, direction_A);
}

void L298NX2::forwardForA(unsigned long delay)
{
  this->runForA(delay, L298N::FORWARD);
}

void L298NX2::backwardForA(unsigned long delay)
{
  this->runForA(delay, L298N::BACKWARD);
}

void L298NX2::stopA()
{
  _motorA.stop();
}

boolean L298NX2::isMovingA()
{
  return _motorA.isMoving();
}

L298N::Direction L298NX2::getDirectionA()
{
  return _motorA.getDirection();
}

void L298NX2::moveForwardBarckwardForA(unsigned long delay_A)
{
  _motorA.runForwardsBackwards(delay_A);
}

//Motor B
void L298NX2::setSpeedB(unsigned short pwmVal)
{
  _motorB.setSpeed(pwmVal);
}

unsigned short L298NX2::getSpeedB()
{
  return _motorB.isMoving() ? _motorB.getSpeed() : 0;
}

void L298NX2::forwardB()
{
  _motorB.forward();
}
void L298NX2::backwardB()
{
  _motorB.backward();
}

void L298NX2::runB(L298N::Direction direction)
{
  _motorB.run(direction);
}

void L298NX2::runForB(unsigned long delay_B, L298N::Direction direction_B)
{
  _motorB.runFor(delay_B, direction_B);
}

void L298NX2::forwardForB(unsigned long delay)
{
  this->runForB(delay, L298N::FORWARD);
}

void L298NX2::backwardForB(unsigned long delay)
{
  this->runForB(delay, L298N::BACKWARD);
}

void L298NX2::stopB()
{
  _motorB.stop();
}

boolean L298NX2::isMovingB()
{
  return _motorB.isMoving();
}

L298N::Direction L298NX2::getDirectionB()
{
  return _motorB.getDirection();
}

void L298NX2::moveForwardBarckwardForB(unsigned long delay_B)
{
  _motorB.runForwardsBackwards(delay_B);
}

// Both
void L298NX2::setSpeed(unsigned short pwmVal)
{
  _motorA.setSpeed(pwmVal);
  _motorB.setSpeed(pwmVal);
}

void L298NX2::forward()
{
  _motorA.forward();
  _motorB.forward();
}

void L298NX2::backward()
{
  _motorA.backward();
  _motorB.backward();
}

void L298NX2::run(L298N::Direction direction)
{
  _motorA.run(direction);
  _motorB.run(direction);
}

void L298NX2::runFor(unsigned long delay_v, L298N::Direction direction)
{
  this->run(direction);
  delay(delay_v);
  this->stop();
}

void L298NX2::forwardFor(unsigned long delay)
{
  this->runFor(delay, L298N::FORWARD);
}

void L298NX2::backwardFor(unsigned long delay)
{
  this->runFor(delay, L298N::BACKWARD);
}

void L298NX2::runForwardsBackwardsFor(unsigned long delay_value)
{
  this->forwardFor(delay_value);
  this->backwardFor(delay_value);
  this->stop();
}

void L298NX2::stop()
{
  _motorA.stop();
  _motorB.stop();
}