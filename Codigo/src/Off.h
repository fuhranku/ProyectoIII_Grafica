#pragma once

#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;
using namespace std;

class COff : public CModel{
	public:
		COff();
		~COff();
		bool load(string path);
};

