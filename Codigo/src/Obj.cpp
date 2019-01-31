#include "Obj.h"

CObj::CObj()
{

}


CObj::~CObj()
{
}

bool CObj::load(string path){
	ifstream infile(path);
	string token, v1, v2, v3;
	float v1f, v2f, v3f;
	while (true){
		infile >> token;
		if (infile.eof())
			break;
		
		if (!checkValidToken(token)){
			getline(infile, token);
		}
		else{
			if (token == "v"){
				infile >> v1;
				v1f = (float)(atof(v1.c_str()));
				if (v1f > max.x)
					max.x = v1f;
				if (v1f < min.x)
					min.x = v1f;
				infile >> v2;
				v2f = (float)(atof(v2.c_str()));
				if (v2f > max.y)
					max.y = v2f;
				if (v2f < min.y)
					min.y = v2f;
				infile >> v3;
				v3f = (float)(atof(v3.c_str()));
				if (v3f > max.z)
					max.z = v3f;
				if (v3f < min.z)
					min.z = v3f;
				mVertices.push_back(glm::vec3(v1f,v2f,v3f));
			}
			else if (token == "f"){
				infile >> token;
				v1 = token.substr(0, token.find("/"));
				infile >> token;
				v2 = token.substr(0, token.find("/"));
				infile >> token;
				v3 = token.substr(0, token.find("/"));
				mFaces.push_back(glm::ivec3((atoi(v1.c_str()))-1, (atoi(v2.c_str()))-1, (atoi(v3.c_str())-1)));
			}
		}
	}
	//Encuentro centro de x,y,z de cada vértice:
	mid.x = (max.x + min.x) / 2;
	mid.y = (max.y + min.y) / 2;
	mid.z = (max.z + min.z) / 2;
	//Obtengo número de caras y vértices:
	mNumOfFaces = (int) mFaces.size();
	mNumOfVertices = (int)mVertices.size();
	//Normalizo:
	normalize();
	infile.close();
	return true;
}

bool CObj::checkValidToken(string token) {
	if (token == "v" || token == "f")
		return true;
	return false;
}

