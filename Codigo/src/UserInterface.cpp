#include "UserInterface.h"
#include "Windows.h"


extern int gWidth, gHeight;
void TW_CALL CallbackLoad(void *clientData);
string loadPath();

// Global static pointer used to ensure a single instance of the class.
CUserInterface * CUserInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface * CUserInterface::Instance() 
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		 mInterface = new CUserInterface();
 
   return mInterface;
}

CUserInterface::CUserInterface()
{

	TwEnumVal DeployType[] = { {GL_BEGIN_GL_END, "Gl Begin / Gl End"}, {DISPLAY_LIST, "Display List"}, {VERTEX_POINTER, "Vertex Pointer"}, {VBO, "VBO"} };
	TwType DeployTwType = TwDefineEnum("DeployType", DeployType, 4);
	TwEnumVal ProjectionType[] = { { PERSPECTIVE, "Perspective" },{ ORTHO, "Ortho" }};
	TwType ProjectionTwType = TwDefineEnum("ProjectionType", ProjectionType, 2);
	TwEnumVal ShadingType[] = { { FLAT, "Flat" },{ GOURAUD, "Gouraud" } };
	TwType ShadingTwType = TwDefineEnum("ShadingType", ShadingType, 2);

	currentFile = "None";
	mUserInterface = TwNewBar("Despliegue de objetos 3D");
	mMesh = mFill = mPoints = mSideNormalBool = mVerticesNormalBool = bfCulling = false;
	zBuffer = lightBool = true;
	projectionBool = PERSPECTIVE;
	m_currentDeploy = GL_BEGIN_GL_END;
	shading = FLAT;

	//Configuraciones previas:
	TwDefine("'Despliegue de objetos 3D' refresh = '0.0001f'");
	TwDefine("'Despliegue de objetos 3D' resizable = false");
	TwDefine("'Despliegue de objetos 3D' fontresizable = false");
	TwDefine("'Despliegue de objetos 3D' movable = false");
	TwDefine("'Despliegue de objetos 3D' position = '10 20'");
	TwDefine("'Despliegue de objetos 3D' size = '250 500'");
	TwDefine("'Despliegue de objetos 3D' color = '0 0 0'");
	TwDefine("'Despliegue de objetos 3D' valueswidth=fit ");



	//Color malla:
	rgbMesh[0] = 0.0f; rgbMesh[1] = 0.0f; rgbMesh[2] = 0.0f; rgbMesh[3] = 1.0f;
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
	//traslación:
	mModelTranslation[0] = mModelTranslation[1]= mModelTranslation[2] = 0.0f;
	//Escalamiento:
	mModelScaling[0] = mModelScaling[1] = mModelScaling[2] = 1.0f;
	scaleAll = 0.0f;
	//Rotación:
	mModelRotation[0] = mModelRotation[1] = mModelRotation[2] = mModelRotation[3] = 0.0f;
	 //shininess:
	shininess = 20.0f;
	//Nombre archivo:
	TwAddVarRO(mUserInterface, "Current File", TW_TYPE_STDSTRING, &currentFile, "label='Model Name' readonly=true");
	TwAddSeparator(mUserInterface, "", NULL);

	//Encender la luz(oculto en modo modelo):
	TwAddVarRO(mUserInterface, "Light", TW_TYPE_BOOLCPP, &lightBool, "label='Turn light On/Off' readonly=false visible = false");

	//Tipo de despliegue:
	TwAddVarRW(mUserInterface, "Deploy type", DeployTwType, &m_currentDeploy, NULL);

	//Tipo de proyección:
	TwAddVarRW(mUserInterface, "Projection type", ProjectionTwType, &projectionBool, NULL);
	//Tipo de sombreado:
	TwAddVarRW(mUserInterface, "Shading type", ShadingTwType, &shading, NULL);
	//Backface Culling:
	TwAddVarRW(mUserInterface, "Backface culling", TW_TYPE_BOOLCPP, &bfCulling, "label='Backface Culling'");
	//Z-Buffer:
	TwAddVarRW(mUserInterface, "Z-buffer", TW_TYPE_BOOLCPP, &zBuffer, "label='Z-Buffer'");
	//Estilos de despliegue:
	TwAddVarRO(mUserInterface, "Fill", TW_TYPE_BOOLCPP, &mFill, "group='Deploy Style' label='Fill' readonly=false");
	TwAddVarRO(mUserInterface, "Mesh", TW_TYPE_BOOLCPP, &mMesh, "group='Deploy Style' label='Mesh' readonly=false");
	TwAddVarRO(mUserInterface, "Points", TW_TYPE_BOOLCPP, &mPoints, "group='Deploy Style' label='Points' readonly=false");

	//Bounding box:
	TwAddVarRO(mUserInterface, "Bounding box", TW_TYPE_BOOLCPP, &mBoundingBox, "label='Bounding Box' readonly=false");
	//Normales:
	TwAddVarRO(mUserInterface, "Side", TW_TYPE_BOOLCPP, &mSideNormalBool, "label='Side' readonly=false");
	TwAddVarRO(mUserInterface, "Vertices", TW_TYPE_BOOLCPP, &mVerticesNormalBool, "label='Vertices' readonly=false");
	
	//Shininess:
	TwAddVarRW(mUserInterface,"Shininess ", TW_TYPE_FLOAT, &shininess, " label='Shininess' step=0.1 ");

	//Traslación:
	TwAddVarRW(mUserInterface, "X ", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Y ", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Z ", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Translation' step=0.01 ");

	//Escalamiento:
	TwAddVarRW(mUserInterface, "X", TW_TYPE_FLOAT, &mModelScaling[0], " group='Scaling' step=0.01 ");
	TwAddVarRW(mUserInterface, "Y", TW_TYPE_FLOAT, &mModelScaling[1], " group='Scaling' step=0.01 ");
	TwAddVarRW(mUserInterface, "Z", TW_TYPE_FLOAT, &mModelScaling[2], " group='Scaling' step=0.005 ");
	TwAddVarRW(mUserInterface, "All axis", TW_TYPE_FLOAT, &scaleAll, " group='Scaling' step=0.01 min=-0.02 max=0.02 ");

	//Rotación:
	TwAddVarRW(mUserInterface, "Rotation", TW_TYPE_QUAT4F, &mModelRotation[0], NULL);

	//Colores:
	TwAddVarRW(mUserInterface, "Points Color", TW_TYPE_COLOR3F, &rgbPoints, "group='Display type color' label = 'Points'");
	TwAddVarRW(mUserInterface, "Mesh Color", TW_TYPE_COLOR3F, &rgbMesh, "group='Display type color' label = 'Mesh'");
	TwAddVarRW(mUserInterface, "Fill Color", TW_TYPE_COLOR3F, &rgbFill, "group='Display type color' label = 'Fill'");
	TwAddVarRW(mUserInterface, "BoundingBox Color", TW_TYPE_COLOR3F, &rgbBoundingBox, "group='Properties color' label = 'Bounding box'");
	TwAddVarRW(mUserInterface, "Side Normal Color", TW_TYPE_COLOR3F, &rgbSideNormals, "group='Properties color' label = 'Sides Normals'");
	TwAddVarRW(mUserInterface, "Vertex Normal Color", TW_TYPE_COLOR3F, &rgbVerticesNormals, "group='Properties color' label = 'Vertex Normals'");
	TwAddVarRW(mUserInterface, "Ambient Color", TW_TYPE_COLOR3F, &rgbAmbient, "group='Illumination color' label = 'Ambient'");
	TwAddVarRW(mUserInterface, "Diffuse Color", TW_TYPE_COLOR3F, &rgbDiffuse, "group='Illumination color' label = 'Diffuse'");
	TwAddVarRW(mUserInterface, "Specular Color", TW_TYPE_COLOR3F, &rgbSpecular, "group='Illumination color' label = 'Specular'");
	TwAddSeparator(mUserInterface, "sep2", NULL);

	//Carga:
	TwAddButton(mUserInterface, "Load", CallbackLoad, NULL, NULL);

	//Configuraciones:
	TwDefine("'Despliegue de objetos 3D'/Translation opened=false ");
	TwDefine("'Despliegue de objetos 3D'/Scaling opened=false ");
	TwDefine("'Despliegue de objetos 3D'/'Display type color' opened=false ");
	TwDefine("'Despliegue de objetos 3D'/'Properties color' opened=false ");
	TwDefine("'Despliegue de objetos 3D'/'Illumination color' opened=false ");
	TwDefine("'Despliegue de objetos 3D'/Rotation opened=true ");

}

void TW_CALL CallbackLoad(void *clientData)
{
	string path = loadPath();

}

CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setModelTranslation(glm::vec3 modelTranslation)
{
	mModelTranslation[0] = modelTranslation.x;
	mModelTranslation[1] = modelTranslation.y;
	mModelTranslation[2] = modelTranslation.z;
}

void CUserInterface::setModelScaling(glm::vec3 modelScaling)
{
	mModelScaling[0] = modelScaling.x;
	mModelScaling[1] = modelScaling.y;
	mModelScaling[2] = modelScaling.z;
}

//Set Colores:

void CUserInterface::setMeshColor(float* color) {
	rgbMesh[0] = color[0];
	rgbMesh[1] = color[1];
	rgbMesh[2] = color[2];
	rgbMesh[3] = color[3];
}

void CUserInterface::setBoundingBoxColor(float* color) {
	rgbBoundingBox[0] = color[0];
	rgbBoundingBox[1] = color[1];
	rgbBoundingBox[2] = color[2];
	rgbBoundingBox[3] = color[3];
}

void CUserInterface::setSideNormalsColor(float* color) {
	rgbSideNormals[0] = color[0];
	rgbSideNormals[1] = color[1];
	rgbSideNormals[2] = color[2];
	rgbSideNormals[3] = color[3];
}

void CUserInterface::setVerticesNormalsColor(float* color) {
	rgbVerticesNormals[0] = color[0];
	rgbVerticesNormals[1] = color[1];
	rgbVerticesNormals[2] = color[2];
	rgbVerticesNormals[3] = color[3];
}

void CUserInterface::setFillColor(float* color) {
	rgbFill[0] = color[0];
	rgbFill[1] = color[1];
	rgbFill[2] = color[2];
	rgbFill[3] = color[3];
}

void CUserInterface::setPointsColor(float* color) {
	rgbPoints[0] = color[0];
	rgbPoints[1] = color[1];
	rgbPoints[2] = color[2];
	rgbPoints[3] = color[3];
}

void CUserInterface::setAmbientColor(float* color) {
	rgbAmbient[0] = color[0];
	rgbAmbient[1] = color[1];
	rgbAmbient[2] = color[2];
	rgbAmbient[3] = color[3];
}

void CUserInterface::setDiffuseColor(float* color) {
	rgbDiffuse[0] = color[0];
	rgbDiffuse[1] = color[1];
	rgbDiffuse[2] = color[2];
	rgbDiffuse[3] = color[3];
}

void CUserInterface::setSpecularColor(float* color) {
	rgbSpecular[0] = color[0];
	rgbSpecular[1] = color[1];
	rgbSpecular[2] = color[2];
	rgbSpecular[3] = color[3];
}

//Get Colores:

float* CUserInterface::getMeshColor() {
	return rgbMesh;
}

float* CUserInterface::getFillColor() {
	return rgbFill;
}

float* CUserInterface::getPointsColor() {
	return rgbPoints;
}

float* CUserInterface::getBoundingBoxColor() {
	return rgbBoundingBox;
}

float* CUserInterface::getSideNormalsColor() {
	return rgbSideNormals;
}

float* CUserInterface::getVerticesNormalsColor() {
	return rgbVerticesNormals;
}

float* CUserInterface::getAmbientColor() {
	return rgbAmbient;
}
float* CUserInterface::getDiffuseColor() {
	return rgbDiffuse;
}
float* CUserInterface::getSpecularColor() {
	return rgbSpecular;
}

void CUserInterface::setBoundingBox(bool b) {
	mBoundingBox = b;
}

void CUserInterface::setScaleAll(float scaleAll) {
	this->scaleAll = scaleAll;
}

void CUserInterface::setModelRotation(glm::vec4 modelRotation) {
	mModelRotation[0] = modelRotation[0];
	mModelRotation[1] = modelRotation[1];
	mModelRotation[2] = modelRotation[2];
	mModelRotation[3] = modelRotation[3];
}

SHADING_TYPE CUserInterface::getShadingType() {
	return shading;
}

glm::vec3 CUserInterface::getModelTranslation()
{
	return mModelTranslation;
}

glm::vec3 CUserInterface::getModelScaling()
{
	return mModelScaling;
}

bool CUserInterface::getBoundingBox() {
	return mBoundingBox;
}

glm::vec4 CUserInterface::getModelRotation()
{
	return mModelRotation;
}

DEPLOY_TYPE CUserInterface::getCurrentDeploy() {
	return m_currentDeploy;
}


float CUserInterface::getScaleAll() {
	return scaleAll;
}

void CUserInterface::setCurrentFile(string filename) {
	currentFile = filename;
}

string loadPath()
{
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "OBJ Files(.obj)\0*.obj\0OFF Files(.off)\0*.off;";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	ofn.lpstrTitle = "Abrir archivo a desplegar";
	string fileNameStr;
	if (GetOpenFileName(&ofn)) {
		fileNameStr = fileName;
	}
	
	return fileNameStr;
}

string CUserInterface::getDeployType() {
		if (m_currentDeploy == GL_BEGIN_GL_END) return "glbeg";
		if (m_currentDeploy == DISPLAY_LIST) return "DL";
		if (m_currentDeploy == VERTEX_POINTER) return "VP";
		if (m_currentDeploy == VBO) return "VBO";
		return NULL;
}

bool CUserInterface::getMesh() {
	return mMesh;
}
bool CUserInterface::getPoints() {
	return mPoints;
}
bool CUserInterface::getFill() {
	return mFill;
}
void CUserInterface::setFill(bool b) {
	mFill = b;
}
void CUserInterface::setPoints(bool b) {
	mPoints = b;
}
void CUserInterface::setMesh(bool b) {
	mMesh = b;
}

void CUserInterface::setBFCulling(bool b) {
	bfCulling = b;
}

void CUserInterface::setShininess(float f) {
	shininess = f;
}

void  CUserInterface::setZBuffer(bool b) {
	zBuffer = b;
}

bool CUserInterface::getSideNormalBool() {
	return mSideNormalBool;
}
bool CUserInterface::getVerticesNormalBool() {
	return mVerticesNormalBool;
}
void CUserInterface::setSideNormalBool(bool b) {
	mSideNormalBool = b;
}
void CUserInterface::setVerticesNormalBool(bool b){
	mVerticesNormalBool = b;
}

float CUserInterface::getShininess() {
	return shininess;
}

bool CUserInterface::getBFCulling() {
	return bfCulling;
}

bool CUserInterface::getZBuffer() {
	return zBuffer;
}

PROJECTION_TYPE CUserInterface::getProjectionBool() {
	return projectionBool;
}

void CUserInterface::setShadingType(SHADING_TYPE shading) {
	this->shading = shading;
}

void CUserInterface::swapToLightMode() {
	TwDefine("'Despliegue de objetos 3D'/'Deploy type' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Projection type' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Shading type' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Backface culling' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Bounding box' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Z-buffer' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Deploy Style' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Side' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Vertices' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Scaling' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Rotation' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Display type color' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Properties color' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'sep2' visible=false ");
	TwDefine("'Despliegue de objetos 3D'/'Load' visible=false "); 

	TwDefine("'Despliegue de objetos 3D'/'Current File' label='Light number' ");
	TwDefine("'Despliegue de objetos 3D'/Translation opened=true ");
	TwDefine("'Despliegue de objetos 3D'/'Illumination color' opened=true ");

	TwDefine("'Despliegue de objetos 3D' size = '250 300'");
	TwDefine("'Despliegue de objetos 3D' color = '0 0 100'");

	TwDefine("'Despliegue de objetos 3D'/'Light' visible=true");

}

void CUserInterface::swapToRegularMode() {
	TwDefine("'Despliegue de objetos 3D'/'Current File' label='Model name' ");
	TwDefine("'Despliegue de objetos 3D'/'Deploy type' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Projection type' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Shading type' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Backface culling' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Bounding box' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Z-buffer' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Deploy Style' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Side' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Vertices' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Scaling' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Rotation' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Display type color' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Properties color' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'sep2' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/'Load' visible=true ");
	TwDefine("'Despliegue de objetos 3D'/Translation opened=false ");
	TwDefine("'Despliegue de objetos 3D'/'Illumination color' opened=false ");
	TwDefine("'Despliegue de objetos 3D'/'Light' visible=false");

	TwDefine("'Despliegue de objetos 3D' size = '250 500'");
	TwDefine("'Despliegue de objetos 3D' color = '0 0 0'");
}

void CUserInterface::setLightStatus(bool b) {
	lightBool = b;
}

bool CUserInterface::getLightStatus() {
	return lightBool;
}

