#include "SOff.h"

CSOff::CSOff()
{
}

CSOff::~CSOff()
{
}

bool CSOff::load(string path)
{
	fstream file;
	string token, v1, v2, v3;

	file.open(path, std::ios::in);

	file >> token;

	if (token != "SOFF")
	{
		file.close();
		return false;
	}
	else
	{
		file >> token;
		mNumOfVertices = atoi(token.c_str());

		for (int i = 0; i < mNumOfVertices; i++)
		{
			file >> v1;
			file >> v2;
			file >> v3;
			mVertices.push_back(glm::vec3((atof(v1.c_str())), (atof(v2.c_str())), (atof(v3.c_str()))));
		}
	
		file.close();
		return true;
	}
}