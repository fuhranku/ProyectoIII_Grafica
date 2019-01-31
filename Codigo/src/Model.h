#pragma once

#include "../headers/GL/glew.h"
#define GLFW_INCLUDE_GLU
#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include "UserInterface.h"
#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

#define COLOR_PICK -1000

class CModel{
	protected:
		vector<glm::vec3> mVertices, mNormal, vNormal;
		vector<glm::ivec3> mFaces;
		GLuint list,vbo, vindex;
		int mNumOfFaces, mNumOfVertices;
		float maxTotal, rgbPick[4],rgbBoundingBox[4],rgbVerticesNormals[4],
		rgbSideNormals[4],rgbPoints[4],rgbMesh[4],rgbFill[4], rgbAmbient[4], rgbDiffuse[4], rgbSpecular[4],shininess;
		glm::vec3 max, min, mid, mTranslation, mScaling;
		glm::vec4 mRotation;
		string name;
		bool boundingBox,mFill,mMesh,mPoints, mSideNormalBool, mVerticesNormalBool,bfCulling, zBuffer, lightBool;
		SHADING_TYPE shading;
	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		void display(int type);
		void setNormals();
		void displayList();
		void displayVBO();
		void createList(int type);
		void createVBO();
		void setTranslation(glm::vec3 translation);
		void setScaling(glm::vec3 scaling);
		void setRotation(glm::vec4 rotation);
		void normalize();
		bool getMesh();
		bool getPoints();
		bool getFill();
		void setFill(bool b);
		void setPoints(bool b);
		void setMesh(bool b);
		void setBFCulling(bool b);
		void setZBuffer(bool b);
		void setLightStatus(bool b);
		void setShininess(float f);
		glm::vec3 getTranslation();
		glm::vec3 getScaling();
		glm::vec4 getRotation();
		bool getBFCulling();
		bool getZBuffer();
		bool getLightStatus();
		string getModelName();
		void setFillColor(float* color);
		void setPointsColor(float* color);
		void setModelName(string name);
		float* getPickColor();
		void setPickColor(float* color);
		float* getMeshColor();
		void setMeshColor(float* color);
		float* getBoundingBoxColor();
		float getShininess();
		float* getFillColor();
		float* getPointsColor();
		float* getSideNormalsColor();
		float* getAmbientColor();
		float* getDiffuseColor();
		float* getSpecularColor();
		float* getVerticesNormalsColor();
		void setAmbientColor(float* color);
		void setDiffuseColor(float* color);
		void setSpecularColor(float* color);
		void setBoundingBoxColor(float* color);
		void setSideNormalsColor(float* color);
		void setVerticesNormalsColor(float* color);
		bool getBoundingBoxBool();
		void setBoundingBoxBool(bool b);
		void displayBoundingBox();
		void updateMaxAndMin();
		void vertexPointer(int type);
		void setSideNormalBool(bool b);
		void setVerticesNormalBool(bool b);
		bool getSideNormalBool();
		bool getVerticesNormalBool();
		glm::vec3 getTriangles();
		void calculateVertexNormals();
		void averageNormal(glm::vec3 vertex);
		SHADING_TYPE getShadingType();
		void setShadingType(SHADING_TYPE shading);
		void displayLight(GLenum light);
private:
	bool vertexEquals(glm::vec3 v1, glm::vec3 v2);
};