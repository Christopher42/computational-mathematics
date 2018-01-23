//Input: type parameter
//Output: a single int, indicating the number of decimal digits that may be represented in float form.
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

//aliasing float and double cases of machineEpsilon for ease of use.
int inline machineEpsilonSingle() {return machineEpsilon<float>();}
int inline machineEpsilonDouble() {return machineEpsilon<double>();}