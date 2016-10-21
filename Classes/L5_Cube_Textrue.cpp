#include "L5_Cube_Textrue.h"

bool L5_Cube_Textrue::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Vertex3D_Tex data[] =
	{
		// Front	Red		coordX = positionX  coordY = -positionY
		{ {1, -1, 1}, {1, 0, 0, 1}, {1, 1}},
		{ {1, 1, 1}, {1, 0, 0, 1}, {1, 0}},
		{ {-1, 1, 1}, {1, 0, 0, 1}, {0, 0}},
		{ {-1, -1, 1}, {1, 0, 0, 1}, {0, 1}},
		// Back		Green		coordX = positionX  coordY = positionY
		{ {1, 1, -1}, {0, 1, 0, 1}, {1, 1}},
		{ {-1, -1, -1}, {0, 1, 0, 1}, {0, 0}},
		{ {1, -1, -1}, {0, 1, 0, 1}, {1, 0}},
		{ {-1, 1, -1}, {0, 1, 0, 1}, {0, 1}},
		// Left		Blue		coordX = positionZ  coordY = -positionY
		{ {-1, -1, 1}, {0, 0, 1, 1}, {1, 1}},
		{ {-1, 1, 1}, {0, 0, 1, 1}, {1, 0}},
		{ {-1, 1, -1}, {0, 0, 1, 1}, {0, 0}},
		{ {-1, -1, -1}, {0, 0, 1, 1}, {0, 1}},
		// Right	Yellow		coordX = -positionZ  coordY = -positionY
		{ {1, -1, -1}, {1, 1, 0, 1}, {1, 1}},
		{ {1, 1, -1}, {1, 1, 0, 1}, {1, 0}},
		{ {1, 1, 1}, {1, 1, 0, 1}, {0, 0}},
		{ {1, -1, 1}, {1, 1, 0, 1}, {0, 1}},
		// Top		Pink		coordX = positionX  coordY = positionZ
		{ {1, 1, 1}, {1, 0, 1, 1}, {1, 1}},
		{ {1, 1, -1}, {1, 0, 1, 1}, {1, 0}},
		{ {-1, 1, -1}, {1, 0, 1, 1}, {0, 0}},
		{ {-1, 1, 1}, {1, 0, 1, 1}, {0, 1}},
		// Bottom	White		coordX = positionX  coordY = -positionZ
		{ {1, -1, -1}, {1, 1, 1, 1}, {1, 1}},
		{ {1, -1, 1}, {1, 1, 1, 1}, {1, 0}},
		{ {-1, -1, 1}, {1, 1, 1, 1}, {0, 0}},
		{ {-1, -1, -1}, {1, 1, 1, 1}, {0, 1}}
	};

	GLubyte indices[] = {
		// Front
		0, 1, 2,
		2, 3, 0,
		// Back
		4, 5, 6,
		4, 5, 7,
		// Left
		8, 9, 10,
		10, 11, 8,
		// Right
		12, 13, 14,
		14, 15, 12,
		// Top
		16, 17, 18,
		18, 19, 16,
		// Bottom
		20, 21, 22,
		22, 23, 20
	};

	auto program = new GLProgram();
	program->initWithFilenames("L5_CubeTexture/vertex.shader", "L5_CubeTexture/fragment.shader");
	program->link();
	program->updateUniforms();
	program->autorelease();

	this->setGLProgram(program);


	GLuint uColorLocation = glGetUniformLocation(program->getProgram(), "u_color");
	float uColor[] = {1.0, 1.0, 1.0, 1.0};

	glUniform4fv(uColorLocation, 1, uColor);

	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	glGenBuffers(1, &this->_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation,	3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D_Tex), (GLvoid*)offsetof(Vertex3D_Tex, position));


	GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D_Tex), (GLvoid*)offsetof(Vertex3D_Tex, color));

	GLuint coordLocation = glGetAttribLocation(program->getProgram(), "a_coord");
	glEnableVertexAttribArray(coordLocation);
	glVertexAttribPointer(coordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D_Tex), (GLvoid*)offsetof(Vertex3D_Tex, texCoord));

	uint32_t indexVBO;
	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	/*
	glGenTextures(1, &_textureId);
	GL::bindTexture2D(_textureId);
	Image* img = new Image();
	img->initWithImageFile(FileUtils::getInstance()->fullPathForFilename("HelloWorld.png"));

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	unsigned char *imageData = img->getData();
	int width = img->getWidth();
	int height = img->getHeight();
	glTexImage2D(GL_TEXTURE_2D,	0, GL_RGB,	width, height,	0, GL_RGB,	GL_UNSIGNED_BYTE,	imageData);
	CC_SAFE_DELETE(img);
	*/

	_textureId = Sprite::create("HelloWorld.png")->getTexture()->getName();


	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	CHECK_GL_ERROR_DEBUG();
	return true;
}


void L5_Cube_Textrue::visit(Renderer* render, const Mat4& parentTransform, uint32_t parentFlags){
	Layer::visit(render, parentTransform, parentFlags);

	_command.init(_globalZOrder);
	_command.func = CC_CALLBACK_0(L5_Cube_Textrue::onDraw, this);

	Director::getInstance()->getRenderer()->addCommand(&_command);
}

void L5_Cube_Textrue::onDraw(){

	glEnable(GL_DEPTH_TEST);
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);


	Mat4 projectionMatrix;
	Mat4::createPerspective(60, 480/320, 1.0, 42, &projectionMatrix);
	Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, projectionMatrix);

	Mat4 modelViewMatrix;
	Mat4::createLookAt(Vec3(0,0,1), Vec3(0,0,0), Vec3(0,1,0), &modelViewMatrix);
	modelViewMatrix.translate(0, 0, -5);

	static float rotation = 0;
	modelViewMatrix.rotate(Vec3(1,1,1),CC_DEGREES_TO_RADIANS(rotation));
	rotation++;
	if (rotation > 360) {
		rotation = 0;
	}
	Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, modelViewMatrix);




	auto program = getGLProgram();
	program->use();
	program->setUniformsForBuiltins();

	glBindVertexArray(this->_vao);
	GL::bindTexture2D(_textureId);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glBindVertexArray(0);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 36);

	CHECK_GL_ERROR_DEBUG();

	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	glDisable(GL_DEPTH_TEST);
}