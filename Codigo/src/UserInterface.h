#pragma once

#include "../headers/AntTweakBar.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <string>

using std::string;
typedef enum { GL_BEGIN_GL_END, DISPLAY_LIST, VERTEX_POINTER, VBO } DEPLOY_TYPE;
typedef enum { PERSPECTIVE , ORTHO} PROJECTION_TYPE;
typedef enum { FLAT, GOURAUD } SHADING_TYPE;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	glm::vec3 mModelTranslation;
	glm::vec3 mModelScaling;
	glm::vec4 mModelRotation;
	bool mBoundingBox, mFill, mMesh, mPoints, mSideNormalBool, mVerticesNormalBool,bfCulling,zBuffer, lightBool;
	float scaleAll;
	float rgbBoundingBox[4], rgbVerticesNormals[4], rgbSideNormals[4], rgbPoints[4], rgbMesh[4],
	rgbFill[4],rgbAmbient[4],rgbDiffuse[4],rgbSpecular[4], shininess;
	string mDeployMode, currentFile;
	DEPLOY_TYPE m_currentDeploy;
	PROJECTION_TYPE projectionBool;
	SHADING_TYPE shading;
public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(glm::vec3 modelTranslation);
	void setModelScaling(glm::vec3 modelScaling);
	void setModelRotation(glm::vec4 modelRotation);
	void setScaleAll(float scaleAll);
	void setBoundingBox(bool b);
	void setBFCulling(bool b);
	void setZBuffer(bool b);
	void setShininess(float f);
	glm::vec3 getModelTranslation();
	glm::vec3 getModelScaling();
	glm::vec4 getModelRotation();
	bool getBoundingBox();
	bool getSideNormalBool();
	bool getVerticesNormalBool();
	bool getMesh();
	bool getPoints();
	bool getFill();
	bool getBFCulling();
	bool getZBuffer();
	bool getLightStatus();
	float getShininess();
	SHADING_TYPE getShadingType();
	void setShadingType(SHADING_TYPE shading);
	float* getAmbientColor();
	float* getDiffuseColor();
	float* getSpecularColor();
	void setLightStatus(bool b);
	void setFill(bool b);
	void setPoints(bool b);
	void setMesh(bool b);
	float getScaleAll();
	void setMeshColor(float* color);
	void setFillColor(float* color);
	void setPointsColor(float* color);
	void setSideNormalBool(bool b);
	void setAmbientColor(float* color);
	void setDiffuseColor(float* color);
	void setSpecularColor(float* color);
	void setVerticesNormalBool(bool b);
	PROJECTION_TYPE getProjectionBool();
	float* getBoundingBoxColor();
	void setBoundingBoxColor(float* color);
	float* getSideNormalsColor();
	float* getVerticesNormalsColor();
	void setSideNormalsColor(float* color);
	void setVerticesNormalsColor(float* color);
	float* getMeshColor();
	float* getFillColor();
	float* getPointsColor();
	DEPLOY_TYPE getCurrentDeploy();
	string getDeployType();
	void setCurrentFile(string filename);
	void swapToLightMode();
	void swapToRegularMode();

private:
	///Private constructor
	CUserInterface(); 
};