#include "oglWidget.hpp"

void OGLWidget::changeImage(const std::vector<std::array<uint8_t, 4>>& img, 
							const int w, const int h) {
	imageWidth = w;
	imageHeight = h;
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data());
}


void OGLWidget::initializeGL() {
	std::cout << "Hello OpenGL!" << std::endl;
	initializeOpenGLFunctions();
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glEnable( GL_TEXTURE_2D );

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	const std::vector<std::array<uint8_t, 4>> img{256*256, {255,0,255,255}};
	changeImage(img, 128, 128);
}

void OGLWidget::resizeGL(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, +1);
	glMatrixMode( GL_MODELVIEW ); 
	glLoadIdentity();
}

void OGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_QUADS); 
		glTexCoord2f(0.f, 0.f); glVertex2f(0, 0);
		glTexCoord2f(1.f, 0.f); glVertex2f(imageWidth, 0);
		glTexCoord2f(1.f, 1.f); glVertex2f(imageWidth, imageHeight);
		glTexCoord2f(0.f, 1.f); glVertex2f(0, imageHeight);
	glEnd();
}