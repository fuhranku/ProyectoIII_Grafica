#include "Off.h"

COff::COff(){

}

COff::~COff()
{
}

bool COff::load(string path)
{
	ifstream infile(path);
	string token, v1, v2, v3;
	float v1f, v2f, v3f;
	int index;
	getline(infile, token);
	if (token != "OFF"){
		infile.close();
		return false;
	}
	else{
		//Número de vértices
		infile >> token;
		mNumOfVertices = atoi(token.c_str());
		//Número de caras:
		infile >> token;
		mNumOfFaces = atoi(token.c_str());
		//Número de aristas (se descarta):
		infile >> token;
		//Cargar vértices al modelo:
		for (int i = 0; i < mNumOfVertices; i++){
			infile >> v1;
			v1f = (float) (atof(v1.c_str()));
			if (v1f> max.x)
				max.x = v1f;
			if (v1f < min.x)
				min.x = v1f;
			infile >> v2;
			v2f = (float) (atof(v2.c_str()));
			if (v2f > max.y)
				max.y = v2f;
			if (v2f < min.y)
				min.y = v2f;
			infile >> v3;
			v3f = (float) (atof(v3.c_str()));
			if (v3f > max.z)
				max.z = v3f;
			if (v3f < min.z)
				min.z = v3f;
			mVertices.push_back(glm::vec3(v1f, v2f, v3f));
		}
		//Encuentro centro de x,y,z de cada vértice:
		mid.x = (max.x - min.x) / 2;
		mid.y = (max.y - min.y) / 2;
		mid.z = (max.z - min.z) / 2;
		//Normalizo:
		normalize(); 
		//Cargar caras al modelo:
		int k = 0;
		for (int i = 0; i < mNumOfFaces; i++) {
			infile >> token; 
			index = (atoi(token.c_str()))-2;
			infile >> v1;
			infile >> v3;
			for (int j = 0; j < index; j++) {
				v2 = v3;
				infile >> v3;
				mFaces.push_back(glm::ivec3((atof(v1.c_str())), (atof(v2.c_str())), (atof(v3.c_str()))));
				k++;
			}
			getline(infile, token);
		}
		mNumOfFaces = k;
	}
	infile.close();
	return true;
}
