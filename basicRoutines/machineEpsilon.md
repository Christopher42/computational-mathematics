**Routine Name:** machineEpsilon

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** "machineEpsilon.h"

**Description/Purpose:** Computes accuracy of a given C++ type on current machine.

**Input:**
No parameters, but must give a typename T as a template argument.

**Output:**
Returns an int, indicating the number of digits of accuracy of the given type.

**Usage/Example:**

machineEpsilon<float>() will return the digits of accuracy for the float type. Other types may be used likewise.
```C++
#include <iostream>
#include "machineEpsilon.h"

int main (void)
{
	std::cout << "single precision is " << machineEpsilon<float>() << " digits.\n";
	std::cout << "double precision is " << machineEpsilon<double>() << " digits.\n";
}
```
Output from the lines above:
```c++
single precision is 8 digits.
double precision is 16 digits.
```


**Implementation/Code:** The following is the code for machineEpsilon<T>()
```c++
template <class T>
int machineEpsilon (void)
{
	int digits = 1;
	T val = 1.1;
	while (val>1)
	{
		digits++;
		val = (val-1)/10 + 1;
	}
	return digits;
}
```
**Last Modified:** December/2017
