#include "value.h"

Value::Value()
{
	a = -100000;
	b = 100000;
}

Value::Value(int a=-100000, int b=100000)
{
	this->a = a;
	this->b = b;
}