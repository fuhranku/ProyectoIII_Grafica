#include "Model.h"

CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;	
	mRotation[0] = mRotation[1] = mRotation[2] = mRotation[3] = 0.0f;
	mScaling[0] = mScaling[1] = mScaling[2] = 1.0f;
	max.x = max.y = max.z = (float) INT_MIN;
	min.x = min.y = min.z = (float) INT_MAX;
	//Color malla:
	rgbMesh[0] = 1.0f; rgbMesh[1] = 1.0f; rgbMesh[2] = 1.0f; rgbMesh[3] = 1.0f;
	//Color relleno:
	rgbFill[0] = 1.0f; rgbFill[1] = 0.0f; rgbFill[2] = 0.0f; rgbFill[3] = 1.0f;
	//Color Puntos:
	rgbPoints[0] = 1.0f; rgbPoints[1] = 1.0f; rgbPoints[2] = 1.0f; rgbPoints[3] = 1.0f;
	//Color normales:
	rgbSideNormals[0] = 1.0f; rgbSideNormals[1] = 1.0f; rgbSideNormals[2] = 0.0f;  rgbSideNormals[3] = 1.0f;
	rgbVerticesNormals[0] = 0.0f; rgbVerticesNormals[1] = 1.0f; rgbVerticesNormals[2] = 1.0f; rgbVerticesNormals[3] = 1.0f;
	//Color Bounding box:
	rgbBoundingBox[0] = 0.0f; rgbBoundingBox[1] = 1.0f; rgbBoundingBox[2] = 0.0f; rgbBoundingBox[3] = 1.0f;
	//Color luz ambiental:
	rgbAmbient[0] = 0.47f; rgbAmbient[1] = 0.42f; rgbAmbient[2] = 0.33f; rgbAmbient[3] = 1.0f;
	//Color luz difusa:
	rgbDiffuse[0] = 0.0f; rgbDiffuse[1] = 0.0f; rgbDiffuse[2] = 0.0f; rgbDiffuse[3] = 1.0f;
	//Color luz especular:
	rgbSpecular[0] = 0.0f; rgbSpecular[1] = 0.0f; rgbSpecular[2] = 0.0f; rgbSpecular[3] = 0.0f;
	//shininess:
	shininess = 20.0f;
	name = "";
	boundingBox = mMesh = mPoints = bfCulling = false;
	zBuffer = mFill = lightBool = true;
	shading = FLAT;
}

CModel::~CModel()
{
	mVertices.clear();
}

bool CModel::getBoundingBoxBool() {
	return boundingBox;
}

//Set Colores:

void CModel::setPickColor(float* color) {
	rgbPick[0] = color[0];
	rgbPick[1] = color[1];
	rgbPick[2] = color[2];
	rgbPick[3] = color[3];
}

void CModel::setMeshColor(float* color) {
	rgbMesh[0] = color[0];
	rgbMesh[1] = color[1];
	rgbMesh[2] = color[2];
	rgbMesh[3] = color[3];
}

void CModel::setFillColor(float* color) {
	rgbFill[0] = color[0];
	rgbFill[1] = color[1];
	rgbFill[2] = color[2];
	rgbFill[3] = color[3];
}

void CModel::setPointsColor(float* color) {
	rgbPoints[0] = color[0];
	rgbPoints[1] = color[1];
	rgbPoints[2] = color[2];
	rgbPoints[3] = color[3];
}

void CModel::setBoundingBoxColor(float* color) {
	rgbBoundingBox[0] = color[0];
	rgbBoundingBox[1] = color[1];
	rgbBoundingBox[2] = color[2];
	rgbBoundingBox[3] = color[3];
}

void CModel::setSideNormalsColor(float* color) {
	rgbSideNormals[0] = color[0];
	rgbSideNormals[1] = color[1];
	rgbSideNormals[2] = color[2];
	rgbSideNormals[3] = color[3];
}

void CModel::setVerticesNormalsColor(float* color) {
	rgbVerticesNormals[0] = color[0];
	rgbVerticesNormals[1] = color[1];
	rgbVerticesNormals[2] = color[2];
	rgbVerticesNormals[3] = color[3];
}

void CModel::setAmbientColor(float* color) {
	rgbAmbient[0] = color[0];
	rgbAmbient[1] = color[1];
	rgbAmbient[2] = color[2];
	rgbAmbient[3] = color[3];
}

void CModel::setDiffuseColor(float* color) {
	rgbDiffuse[0] = color[0];
	rgbDiffuse[1] = color[1];
	rgbDiffuse[2] = color[2];
	rgbDiffuse[3] = color[3];
}

void CModel::setSpecularColor(float* color) {
	rgbSpecular[0] = color[0];
	rgbSpecular[1] = color[1];
	rgbSpecular[2] = color[2];
	rgbSpecular[3] = color[3];
}

//Get Colores:

float* CModel::getMeshColor() {
	return rgbMesh;
}

float* CModel::getSideNormalsColor() {
	return rgbSideNormals;
}

float* CModel::getVerticesNormalsColor() {
	return rgbVerticesNormals;
}

float* CModel::getFillColor() {
	return rgbFill;
}

float* CModel::getPointsColor() {
	return rgbPoints;
}

float* CModel::getPickColor() {
	return rgbPick;
}

float* CModel::getBoundingBoxColor() {
	return rgbBoundingBox;
}

void CModel::setBoundingBoxBool(bool b) {
	boundingBox = b;
}

void CModel::setModelName(string name) {
	this->name = name;
}

void CModel::setTranslation(glm::vec3 translation)
{
	mTranslation = translation;
}

void CModel::setScaling(glm::vec3 scaling)
{
	mScaling = scaling;
}

void CModel::setRotation(glm::vec4 rotation)
{
	mRotation = rotation;
}

void CModel::setBFCulling(bool b) {
	bfCulling = b;
}

void  CModel::setZBuffer(bool b) {
	zBuffer = b;
}

bool CModel::getBFCulling() {
	return bfCulling;
}

bool CModel::getZBuffer() {
	return zBuffer;
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}

glm::vec3 CModel::getScaling()
{
	return mScaling;
}

glm::vec4 CModel::getRotation()
{
	return mRotation;
}

string CModel::getModelName() {
	return name;
}

float* CModel::getAmbientColor() {
	return rgbAmbient;
}
float* CModel::getDiffuseColor() {
	return rgbDiffuse;
}
float* CModel::getSpecularColor() {
	return rgbSpecular;
}

void CModel::setShininess(float f) {
	shininess = f;
}

float CModel::getShininess() {
	return shininess;
}

bool CModel::getMesh() {
	return mMesh;
}
bool CModel::getPoints() {
	return mPoints;
}
bool CModel::getFill() {
	return mFill;
}
void CModel::setFill(bool b) {
	mFill = b;
}
void CModel::setPoints(bool b) {
	mPoints = b;
}
void CModel::setMesh(bool b) {
	mMesh = b;
}



float maximum(float a, float b, float c)
{
	float max = (a < b) ? b : a;
	return ((max < c) ? c : max);
}

void CModel::normalize() {
	maxTotal = maximum(max.x, max.y, max.z);
	for (int i = 0; i < mNumOfVertices; i++) {
		mVertices[i].x = (mVertices[i].x - mid.x) / maxTotal;
		mVertices[i].y = (mVertices[i].y - mid.y) / maxTotal;
		mVertices[i].z = (mVertices[i].z - mid.z) / maxTotal;
	}

	updateMaxAndMin();

}

void CModel::updateMaxAndMin() {
	max.x = max.y = max.z = (float)INT_MIN;
	min.x = min.y = min.z = (float)INT_MAX;
	for (int i = 0; i < mNumOfVertices; i++){
		if (mVertices[i].x < min.x)
			min.x = mVertices[i].x;
		if (mVertices[i].x > max.x)
			max.x = mVertices[i].x;
		if (mVertices[i].y < min.y)
			min.y = mVertices[i].y;
		if (mVertices[i].y > max.y)
			max.y = mVertices[i].y;
		if (mVertices[i].z < min.z)
			min.z = mVertices[i].z;
		if (mVertices[i].z > max.z)
			max.z = mVertices[i].z;
	}
}

void CModel::display(int type) {
	glm::vec3 midVertex, normal;
	//Tipo de display:
	switch (type) {
		case COLOR_PICK: {
			//Despliegue:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			for (int i = 0; i < mNumOfFaces; i++) {
				glColor3f(rgbPick[0], rgbPick[1], rgbPick[2]);
				glBegin(GL_TRIANGLES);
				glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
				glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
				glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
				glEnd();
			}
			return;
		}

		case GL_FILL: {
			//Modo de despliegue:
			glPolygonMode(GL_FRONT_AND_BACK, type);
			float shine[] = { shininess };
			//Iluminación:
			{	
				glEnable(GL_LIGHTING);
				glEnable(GL_NORMALIZE);
				glColor3f(rgbFill[0], rgbFill[1], rgbFill[2]);
				glMaterialfv(GL_FRONT, GL_AMBIENT, rgbAmbient);
				glMaterialfv(GL_FRONT, GL_SPECULAR, rgbSpecular);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, rgbDiffuse);
				glMaterialfv(GL_FRONT, GL_SHININESS, shine);
			}

			//Dibujado de triángulos:
			for (int i = 0; i < mNumOfFaces; i++) {

				//Flat Shading:
				if (getShadingType() == FLAT) {
					glNormal3f(mNormal[i].x, mNormal[i].y, mNormal[i].z);
				}
				else {
					glNormal3f(vNormal[mFaces[i].x].x, vNormal[mFaces[i].x].y, vNormal[mFaces[i].x].z);
					glNormal3f(vNormal[mFaces[i].y].x, vNormal[mFaces[i].y].y, vNormal[mFaces[i].y].z);
					glNormal3f(vNormal[mFaces[i].z].x, vNormal[mFaces[i].y].y, vNormal[mFaces[i].y].z);
				}
				//triángulo i del modelo:
				glBegin(GL_TRIANGLES);
				{
					glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
					glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
					glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
				}
				glEnd();

				//Normales de cara:
				if (mSideNormalBool){
					glDisable(GL_LIGHTING);
					midVertex.x = (mVertices[mFaces[i].x].x + mVertices[mFaces[i].y].x + mVertices[mFaces[i].z].x) / 3.0f;
					midVertex.y = (mVertices[mFaces[i].x].y + mVertices[mFaces[i].y].y + mVertices[mFaces[i].z].y) / 3.0f;
					midVertex.z = (mVertices[mFaces[i].x].z + mVertices[mFaces[i].y].z + mVertices[mFaces[i].z].z) / 3.0f;
					glColor3f(rgbSideNormals[0], rgbSideNormals[1], rgbSideNormals[2]);
					glBegin(GL_LINES);
					glVertex3f(midVertex.x, midVertex.y, midVertex.z);
					glVertex3f((midVertex.x + mNormal[i].x)*0.6f, (midVertex.y + mNormal[i].y)*0.6f, (midVertex.z + mNormal[i].z)*0.6f);
					glEnd();
					glEnable(GL_LIGHTING);
				}

			}
			glDisable(GL_NORMALIZE);
			glDisable(GL_LIGHTING);
			break;
		}

		case GL_LINE: {
			//Modo de despliegue:
			glPolygonMode(GL_FRONT_AND_BACK, type);
			glColor3f(rgbMesh[0], rgbMesh[1], rgbMesh[2]);
			//Dibujado de triángulos:
			for (int i = 0; i < mNumOfFaces; i++) {
				//triángulo i del modelo:
				glBegin(GL_TRIANGLES);
				{
					glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
					glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
					glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
				}
				glEnd();

				//Normales de cara:
				if (mSideNormalBool) {
					midVertex.x = (mVertices[mFaces[i].x].x + mVertices[mFaces[i].y].x + mVertices[mFaces[i].z].x) / 3.0f;
					midVertex.y = (mVertices[mFaces[i].x].y + mVertices[mFaces[i].y].y + mVertices[mFaces[i].z].y) / 3.0f;
					midVertex.z = (mVertices[mFaces[i].x].z + mVertices[mFaces[i].y].z + mVertices[mFaces[i].z].z) / 3.0f;
					glColor3f(rgbSideNormals[0], rgbSideNormals[1], rgbSideNormals[2]);
					glBegin(GL_LINES);
					glVertex3f(midVertex.x, midVertex.y, midVertex.z);
					glVertex3f((midVertex.x + mNormal[i].x)*0.6f, (midVertex.y + mNormal[i].y)*0.6f, (midVertex.z + mNormal[i].z)*0.6f);
					glEnd();
				}

			}

			break;
		}

		case GL_POINT: {
			//Modo de despliegue:
			glPolygonMode(GL_FRONT_AND_BACK, type);
			glPointSize(2.0);
			glColor3f(rgbPoints[0], rgbPoints[1], rgbPoints[2]);
			//Dibujado de triángulos:
			for (int i = 0; i < mNumOfFaces; i++) {
				//triángulo i del modelo:
				glBegin(GL_TRIANGLES);
				{
					glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
					glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
					glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
				}
				glEnd();
				//Normales de cara:
				if (mSideNormalBool) {
					midVertex.x = (mVertices[mFaces[i].x].x + mVertices[mFaces[i].y].x + mVertices[mFaces[i].z].x) / 3.0f;
					midVertex.y = (mVertices[mFaces[i].x].y + mVertices[mFaces[i].y].y + mVertices[mFaces[i].z].y) / 3.0f;
					midVertex.z = (mVertices[mFaces[i].x].z + mVertices[mFaces[i].y].z + mVertices[mFaces[i].z].z) / 3.0f;
					glColor3f(rgbSideNormals[0], rgbSideNormals[1], rgbSideNormals[2]);
					glBegin(GL_LINES);
					glVertex3f(midVertex.x, midVertex.y, midVertex.z);
					glVertex3f((midVertex.x + mNormal[i].x)*0.6f, (midVertex.y + mNormal[i].y)*0.6f, (midVertex.z + mNormal[i].z)*0.6f);
					glEnd();
				}

			}
			glPointSize(1.0);
			break;
		}
	}

	//Verifico si se pinta Bounding Box o no:
	if (boundingBox)
		displayBoundingBox();
	//Normales de vértice:
	if (mVerticesNormalBool) {
		for (int i = 0; i < mNumOfVertices; i++) {

				glColor3f(rgbVerticesNormals[0], rgbVerticesNormals[1], rgbVerticesNormals[2]);
				glBegin(GL_LINES);
					glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
					glVertex3f( (mVertices[i].x + vNormal[i].x)*0.6f, (mVertices[i].y + vNormal[i].y)*0.6f, (mVertices[i].z + vNormal[i].z)*0.6f);
				glEnd();
		}
	}	

}

void CModel::displayLight(GLenum light) {
	float translation[] = { mTranslation.x,  mTranslation.y, mTranslation.z, 0.0f };
	//Trasladar luz:
	glLightfv(light, GL_POSITION, translation);

	glPushMatrix();
	{
		glTranslatef(mTranslation.x, mTranslation.y, mTranslation.z);
		glScalef(mScaling.x, mScaling.y, mScaling.z);
		glColor3f(rgbMesh[0], rgbMesh[1], rgbMesh[2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		for (int i = 0; i < mNumOfFaces; i++) {
			glBegin(GL_TRIANGLES);
			{
				glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
				glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
				glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
			}
			glEnd();
		}
	}
	glPopMatrix();
}

void CModel::createList(int type){
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	glColor3fv(rgbPick);
	display(type);
	glEndList();
}

void CModel::displayList() {
	glCallList(list);
	glDeleteLists(list, 1);
}

void CModel::displayBoundingBox() {
	glColor3f(rgbBoundingBox[0], rgbBoundingBox[1], rgbBoundingBox[2]);
	glPushAttrib(GL_ENABLE_BIT);
	glLineStipple(1, 0x00FF);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
		glVertex3f(min.x, min.y, max.z);
		glVertex3f(max.x, min.y, max.z);

		glVertex3f(min.x, min.y, max.z);
		glVertex3f(min.x, max.y, max.z);

		glVertex3f(max.x, min.y, max.z);
		glVertex3f(max.x, max.y, max.z);

		glVertex3f(min.x, max.y, max.z);
		glVertex3f(max.x, max.y, max.z);

		glVertex3f(max.x, max.y, max.z);
		glVertex3f(max.x, max.y, min.z);

		glVertex3f(max.x, min.y, max.z);
		glVertex3f(max.x, min.y, min.z);

		glVertex3f(min.x, min.y, max.z);
		glVertex3f(min.x, min.y, min.z);

		glVertex3f(min.x, max.y, max.z);
		glVertex3f(min.x, max.y, min.z);

		glVertex3f(min.x, max.y, min.z);
		glVertex3f(max.x, max.y, min.z);

		glVertex3f(min.x, max.y, min.z);
		glVertex3f(min.x, min.y, min.z);

		glVertex3f(max.x, max.y, min.z);
		glVertex3f(max.x, min.y, min.z);

		glVertex3f(min.x, min.y, min.z);
		glVertex3f(max.x, min.y, min.z);
	glEnd();
	glPopAttrib();
}

void CModel::displayVBO() {

	createVBO();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);
	glDrawElements(GL_TRIANGLES, mNumOfFaces*3, GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	//glFlush();
}

void CModel::createVBO() {
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &vindex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);
	glBufferData(GL_ARRAY_BUFFER, mNumOfVertices * 3, &mVertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumOfFaces*3, &mFaces[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}

void CModel::vertexPointer(int type) {

	//glm::vec3 vertices = getTriangles();
	switch (type) {
		case GL_LINE: {
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			{
				glColorPointer(4, GL_FLOAT, 0, &rgbMesh[0]);
				glVertexPointer(3, GL_FLOAT, 0, &mVertices[0]);
				glDrawElements(GL_TRIANGLES, mNumOfFaces * 3, GL_UNSIGNED_INT, &mFaces[0]);
			}
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			break;
		}
		/*case GL_FILL:
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			{
				glColorPointer(4, GL_FLOAT, 0, &rgbMesh[0]);
				glVertexPointer(3, GL_FLOAT, 0, &mVertices[0]);
				glDrawElements(GL_LINES, mNumOfFaces * 3, GL_UNSIGNED_INT, &mFaces[0]);
			}
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			break;
		case GL_POINT:
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			{
				glColorPointer(4, GL_FLOAT, 0, &rgbMesh[0]);
				glVertexPointer(3, GL_FLOAT, 0, &mVertices[0]);
				glDrawElements(GL_LINES, mNumOfFaces * 3, GL_UNSIGNED_INT, &mFaces[0]);
			}
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			break;*/
	}

}

bool CModel::getSideNormalBool() {
	return mSideNormalBool;
}
bool CModel::getVerticesNormalBool() {
	return mVerticesNormalBool;
}
void CModel::setSideNormalBool(bool b) {
	mSideNormalBool = b;
}
void CModel::setVerticesNormalBool(bool b) {
	mVerticesNormalBool = b;
}

void CModel::setNormals() {
	glm::vec3 a, b, n; 
	for (int i = 0; i < mNumOfFaces; i++) {
		a.x = mVertices[mFaces[i].x].x - mVertices[mFaces[i].y].x;
		a.y = mVertices[mFaces[i].x].y - mVertices[mFaces[i].y].y;
		a.z = mVertices[mFaces[i].x].z - mVertices[mFaces[i].y].z;

		b.x = mVertices[mFaces[i].x].x - mVertices[mFaces[i].z].x;
		b.y = mVertices[mFaces[i].x].y - mVertices[mFaces[i].z].y;
		b.z = mVertices[mFaces[i].x].z - mVertices[mFaces[i].z].z;

		n = glm::cross(a, b);
		n = glm::normalize(n);
		this->mNormal.push_back(n);
	}

	calculateVertexNormals();
}

glm::vec3 CModel::getTriangles() {
	glm::vec3 result;

	for (int i = 0; i < mNumOfFaces/3; i++) {
		result[i] = mVertices[mFaces[i].x ].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z;
		result[i + 1] = mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z;
		result[i + 2] = mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z;
	}
	return result;
}

void CModel::calculateVertexNormals() {

	for (int i = 0; i < mNumOfVertices; i++){
			averageNormal(mVertices[i]);
	}
}

void CModel::averageNormal(glm::vec3 vertex){
	glm::vec3 average, vector;
	average.x = average.y = average.z = 0.0f;
	int quantity = 0;

	for (int j = 0; j <mNumOfFaces; j++) {
			if ( vertexEquals(vertex,mVertices[mFaces[j].x]) ||
				vertexEquals(vertex, mVertices[mFaces[j].y]) || 
				vertexEquals(vertex, mVertices[mFaces[j].z])) 
			{
					average.x += mNormal[j].x;
					average.y += mNormal[j].y;
					average.z += mNormal[j].z;
					quantity++;
			}
	}
	
	average.x /= quantity;
	average.y /= quantity;
	average.z /= quantity;

	vector.x = average.x;
	vector.y = average.y;
	vector.z = average.z;

	vector = glm::normalize(vector);

	vNormal.push_back(vector);
}

bool CModel::vertexEquals(glm::vec3 v1, glm::vec3 v2) {
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return true;
	return false;
}

SHADING_TYPE CModel::getShadingType() {
	return shading;
}
void CModel::setShadingType(SHADING_TYPE shading) {
	this->shading = shading;
}

void CModel::setLightStatus(bool b) {
	lightBool = b;
}

bool CModel::getLightStatus() {
	return lightBool;
}