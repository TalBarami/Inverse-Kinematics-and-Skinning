#include "IK.h"
#include <iostream>

using namespace std;
using namespace glm;


void printArr(vector<int> arr)
{

	std::cout << "array" << std::endl;
	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << i << "  ";
	}
	std::cout << std::endl;
	for (int p : arr)
	{

		std::cout << p << "  ";
	}
	cout << std::endl;
}
	
IK::IK(void)
{
	cameraMode = false;
	isIKactive = false;
	delta = 1e-1;
	distPosition = vec3(1, 0, 0);
	tipPosition = vec3(0, 0, 2 * linksNum*scaleFactor);
	maxDistance = linksNum * 2.0f*scaleFactor;
}

IK::IK(vec3 position, float angle, float hwRelation, float near, float far) : Scene(position, angle, hwRelation, near, far)
{
	cameraMode = false;
	isIKactive = false;
	delta = 1e-1;
	distPosition = vec3(1, 0, 0);
	tipPosition = vec3(0, 0, 2 * linksNum*scaleFactor);
	maxDistance = linksNum * 2.0f*scaleFactor;
}

IK::~IK(void)
{
}

void IK::init(Vertex *vertices, unsigned int *indices, int verticesSize, int indicesSize)
{
	myRotate(-90.0f, vec3(1, 0, 0), -1);
	//addShape(vertices, verticesSize, indices, indicesSize,"./res/textures/plane.png",-1);
	addShape(0, 2, "./res/textures/plane.png", -1);
	pickedShape = 0;
	shapeTransformation(zScale, scaleFactor);

	for (int i = 1; i < linksNum - 1; i++)
	{
		pickedShape = i;
		addShape(1, 1, "./res/textures/plane.png", -1);
		shapeTransformation(zScale, scaleFactor);

		shapeTransformation(zGlobalTranslate, 1.0);
		setParent(i, i - 1);
	}

	pickedShape = linksNum - 1;
	addShape(0, 3, "./res/textures/plane.png", -1);
	shapeTransformation(zScale, scaleFactor);

	shapeTransformation(zGlobalTranslate, 1.0);
	setParent(linksNum - 1, linksNum - 2);

	pickedShape = 0;
	// distination point
	pickedShape = linksNum;

	//addShape(0,"./res/textures/box0.bmp",-1);
	addShape(vertices, verticesSize, indices, indicesSize, "./res/textures/box0.bmp", -1);
	shapeTransformation(xScale, 0.5);
	shapeTransformation(yScale, 0.5);
	shapeTransformation(zScale, 0.5);
	shapeTransformation(xGlobalTranslate, -8.0);
	shapeTransformation(yGlobalTranslate, 4.0);
	shapeTransformation(zGlobalTranslate, 4.0);
	pickedShape = 0;

	distPosition = getDistination(linksNum);
	tipPosition = getTipPosition(linksNum - 1);


}

void IK::addShape(int CylParts, int linkPosition, int parent)
{

	__super::addShape(CylParts, linkPosition, parent);
}

void IK::addShape(int CylParts, int linkPosition, const std::string& fileName, int parent)
{
	__super::addShape(CylParts, linkPosition, fileName, parent);
}

void IK::addShape(int type, int parent)
{

	__super::addShape(type, parent);
}

void IK::addShape(const std::string& fileName, int parent)
{

	__super::addShape(fileName, parent);
}

void IK::addShape(const std::string& fileName, const std::string& textureFileName, int parent)
{

	__super::addShape(fileName, textureFileName, parent);
}

void IK::addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, int parent)
{

	__super::addShape(vertices, numVertices, indices, numIndices, parent);
}
	
void IK::addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const std::string &textureFlieName, int parent)
{

	__super::addShape(vertices, numVertices, indices, numIndices, textureFlieName, parent);
}
	
void IK::calculateStep(bool EulerVersion)
{


}

void IK::pick_next(int offset)
{

	pickedShape = (pickedShape + offset);
	while (pickedShape < 0 || pickedShape >= linksNum)
	{
		if (pickedShape < 0)
		{
			pickedShape += linksNum;
		}
		else
		{
			pickedShape -= linksNum;
		}

	}
}

void IK::pick_box()
{
	pickedShape = pickedShape == linksNum ? 0 : linksNum;
}

void IK::transformation(int type, float amt)
{
	auto picked_backup = pickedShape;
	if (cameraMode)
	{
		pickedShape = -1;
	}
	shapeTransformation(type, amt);
	pickedShape = picked_backup;
}

void IK::makeChange()
{
	isIKactive = true;
}

	