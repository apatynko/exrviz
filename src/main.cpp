#include <iostream>
#include <vector>
#include <array>
#include <cstdint>

#include <ImfRgbaFile.h>
#include <ImfRgba.h>

#include <QtWidgets>

#include "oglWidget.hpp"

void read_exr(	const char* fileName,
				std::vector<Imf::Rgba>& image,
				int& width, int& height) {
	Imf::RgbaInputFile file(fileName);
	Imath::Box2i dw = file.dataWindow();
	width  = dw.max.x - dw.min.x + 1;
	height = dw.max.y - dw.min.y + 1;
	image.resize(height * width);
	file.setFrameBuffer(image.data() - dw.min.x - dw.min.y * width, 1, width);
	file.readPixels(dw.min.y, dw.max.y);
}


int main(int argc, char** argv) {
	QApplication app(argc, argv);
	QWidget window;
	window.resize(500, 500);
	window.setWindowTitle("exrviz");

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->setContentsMargins(0,0,0,0);

	QWidget* bottomBarLayoutContainer = new QWidget;	// This is used to give a fixed height to the layout
	bottomBarLayoutContainer->setFixedHeight(30);
	QHBoxLayout* bottomBarLayout = new QHBoxLayout;
	QLabel* pixelInfoLabel = new QLabel("Cursor not on image");
	bottomBarLayout->addWidget(pixelInfoLabel);
	bottomBarLayoutContainer->setLayout(bottomBarLayout);

	OGLWidget* oglWidget = new OGLWidget(*pixelInfoLabel);
	oglWidget->setMouseTracking(true);

	mainLayout->addWidget(oglWidget);
	mainLayout->addWidget(bottomBarLayoutContainer);
	window.setLayout(mainLayout);
	window.show();

	int img_w, img_h;
	std::vector<Imf::Rgba> img{0};
	read_exr(argv[1], img, img_w, img_h);
	oglWidget->changeImage(img, img_w, img_h);

	return app.exec();
}

