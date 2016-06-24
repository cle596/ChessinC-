#include "value.h"
#include "macros.h"

Value::Value()
{
	a = -inf;
	b = inf;
}

Value::Value(int a=-100000, int b=100000,int d=1)
{
	this->a = a;
	this->b = b;
	this->d = d;
}
