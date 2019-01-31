
#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;
using namespace std;

class CObj : public CModel
{
public:
	CObj();
	~CObj();
	bool load(string path);
private:
	bool checkValidToken(string token);
};
