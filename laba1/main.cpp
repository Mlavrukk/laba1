#include "Header.h"

int main()
{
    Lines a(2);
    Lines b(2);
    a += point(0.19, -0.7);
    cout << a[0] << a[1] << a[2] << endl;
    cout << b[0] << b[1] << endl;
    a += b;
    cout << a;

    cout << a[0];
    a[0] = point(0.3, 0.3);
    cout << a[0];

    Lines c = point(1, -0.39) + b;
    cout << c;

    Lines d = c;
    if (a == d) {
        cout << "C==D" << endl;
    }
    else {
        cout << "C!=D" << endl;
    }
    cout << "Length a: " << a.length() << endl;

    Lines L(0, 0);
    L += point(0.2, 0.4);
    L += point(0.4, 0);
    for (size_t i = 0; i < L.get_size(); i++)
    {
        cout << L[i];
    }
    cout << L;
}