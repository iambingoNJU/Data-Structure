#include <iostream>
using namespace std;

#include <bitset>
#include <assert.h>
const int DefaultSize=96;

template <class T>
class MapSet
{
private:
	int setSize;
	bitset<DefaultSize> set;	
	T *AllElem;
public:
	MapSet():setSize(DefaultSize) { AllElem=new T[DefaultSize]; assert(AllElem!=NULL); }
	MapSet(MapSet<T>& MS);
	~MapSet();
};

