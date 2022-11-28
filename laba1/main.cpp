#include "Header.h"

int main()
{
	Lines a(0,0);
	a+=point(0.2, 0.4);
	a += point(0.4, 0);
	for (size_t i = 0; i < a.get_size(); i++)
	{
		cout << a[i];
	}
	cout << a;
	
}