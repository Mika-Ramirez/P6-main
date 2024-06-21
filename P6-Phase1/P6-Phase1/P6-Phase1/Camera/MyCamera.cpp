#include "MyCamera.h"

MyCamera::MyCamera() {
	this->cameraPos = glm::vec3(0.f, 0.f, 3.f);
}

/* Camera Position */
void MyCamera::createCameraPos() {
	this->cameraPositionMatrix = glm::translate(glm::mat4(1.0f), this->cameraPos * -1.f);
	this->WorldUp = glm::vec3(0, 1.f, 0);
	this->Center = glm::vec3(0.f, 0.f, 0.f);
	this->F = glm::vec3(this->Center - this->cameraPos);
	this->F = glm::normalize(this->F);
	this->R = glm::normalize(glm::cross(this->F, WorldUp));
	this->U = glm::normalize(glm::cross(this->R, this->F));
}

/* Camera Orientation */
void MyCamera::createCameraOrientation() {
	this->cameraOrientation = glm::mat4(1.f);

	this->cameraOrientation[0][0] = R.x;
	this->cameraOrientation[1][0] = R.y;
	this->cameraOrientation[2][0] = R.z;

	this->cameraOrientation[0][1] = U.x;
	this->cameraOrientation[1][1] = U.y;
	this->cameraOrientation[2][1] = U.z;

	this->cameraOrientation[0][2] = -F.x;
	this->cameraOrientation[1][2] = -F.y;
	this->cameraOrientation[2][2] = -F.z;
}

/* Camera View */
void MyCamera::createCameraView() {
	this->viewMatrix = cameraOrientation * cameraPositionMatrix;
}

/* Create Camera Proper */
void MyCamera::createCamera() {
	this->createProjection();
	this->createCameraPos();
	this->createCameraOrientation();
	this->createCameraView();
}

/* Camera Renderer */
void MyCamera::render(GLuint shaderProg) {
	unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");

	glUniformMatrix4fv(projectionLoc,
		1,
		GL_FALSE,
		glm::value_ptr(this->projectionMatrix));

	unsigned int viewLoc = glGetUniformLocation(shaderProg, "view");

	glUniformMatrix4fv(viewLoc,
		1,
		GL_FALSE,
		glm::value_ptr(this->viewMatrix));
}

void MyCamera::perform(GLuint shaderProg) {
	this->render(shaderProg);
}

glm::vec3 MyCamera::getCameraPos() {
	return this->cameraPos;
}

glm::mat4 MyCamera::getViewMatrix() {
	return this->viewMatrix;
}

glm::mat4 MyCamera::getProjectionMatrix() {
	return this->projectionMatrix;
}
void MyCamera::setCameraPosition(glm::vec3 modelPos) {
	this->cameraPos = modelPos;
}