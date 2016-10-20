#include "L3_Rectangle.h"

bool L3_Rectangle::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	this->_scale = true;

	auto size = Director::getInstance()->getWinSize();

	/*
	_vertercies[0] = 0;
	_vertercies[1] = 0;
	_vertercies[2] = size.width;
	_vertercies[3] = 0;
	_vertercies[4] = size.width;
	_vertercies[5] = size.height;
	_vertercies[6] = 0;
	_vertercies[7] = size.height;

	_color[0] = 1;
	_color[1] = 0;
	_color[2] = 0;
	_color[3] = 1;

	_color[4] = 0;
	_color[5] = 1;
	_color[6] = 0;
	_color[7] = 1;

	_color[8] = 0;
	_color[9] = 0;
	_color[10] = 1;
	_color[11] = 1;

	_color[12] = 0;
	_color[13] = 0;
	_color[14] = 1;
	_color[15] = 1;
	*/

	_data[0].position[0] = 0;
	_data[0].position[1] = 0;
	_data[0].color[0] = 1;
	_data[0].color[1] = 0;
	_data[0].color[2] = 0;
	_data[0].color[3] = 1;

	_data[1].position[0] = size.width;
	_data[1].position[1] = 0;
	_data[1].color[0] = 0;
	_data[1].color[1] = 1;
	_data[1].color[2] = 0;
	_data[1].color[3] = 1;

	_data[2].position[0] = size.width;
	_data[2].position[1] = size.height;
	_data[2].color[0] = 0;
	_data[2].color[1] = 0;
	_data[2].color[2] = 1;
	_data[2].color[3] = 1;

	_data[3].position[0] = 0;
	_data[3].position[1] = size.height;
	_data[3].color[0] = 0;
	_data[3].color[1] = 0;
	_data[3].color[2] = 1;
	_data[3].color[3] = 1;

	GLubyte indices[] = {0, 1, 2,  2, 3, 0};

	this->scheduleUpdate();

	/*
	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
	auto program = getGLProgram();
	*/

	auto program = new GLProgram();
	//program->initWithFilenames("L2_Triangle/vertex.shader", "L2_Triangle/fragment.shader");
	program->initWithFilenames("L3_Rectangle/vertex.shader", "L3_Rectangle/fragment.shader");
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
	//glBufferData(GL_ARRAY_BUFFER, sizeof(this->_vertercies), this->_vertercies, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->_data), this->_data, GL_STATIC_DRAW);

	GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
	glEnableVertexAttribArray(positionLocation);
	//glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

	/*
	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->_color), this->_color, GL_STATIC_DRAW);
	*/

	GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
	glEnableVertexAttribArray(colorLocation);
	//glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));


	uint32_t indexVBO;
	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	CHECK_GL_ERROR_DEBUG();
    return true;
}


void L3_Rectangle::visit(Renderer* render, const Mat4& parentTransform, uint32_t parentFlags){
	Layer::visit(render, parentTransform, parentFlags);

	_command.init(_globalZOrder);
	_command.func = CC_CALLBACK_0(L3_Rectangle::onDraw, this);

	Director::getInstance()->getRenderer()->addCommand(&_command);
}

void L3_Rectangle::onDraw(){
	auto program = getGLProgram();
	program->use();
	program->setUniformsForBuiltins();

	glBindVertexArray(this->_vao);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glBindVertexArray(0);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 6);

	CHECK_GL_ERROR_DEBUG();
}

void L3_Rectangle::update(float delta){

	auto size = Director::getInstance()->getWinSize();

	if (this->_scale)
	{
		this->_data[0].position[0]++;
		this->_data[0].position[1]++;

		this->_data[1].position[0]--;
		this->_data[1].position[1]++;

		this->_data[2].position[0]--;
		this->_data[2].position[1]--;

		this->_data[3].position[0]++;
		this->_data[3].position[1]--;
	}else
	{
		this->_data[0].position[0]--;
		this->_data[0].position[1]--;

		this->_data[1].position[0]++;
		this->_data[1].position[1]--;

		this->_data[2].position[0]++;
		this->_data[2].position[1]++;

		this->_data[3].position[0]--;
		this->_data[3].position[1]++;
	}

	if (this->_data[0].position[0] >= 100)
	{
		this->_scale = false;
	}else if (this->_data[0].position[0] <= 0)
	{
		this->_scale = true;
	}


	glBindVertexArray(this->_vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(this->_vertercies), this->_vertercies, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->_data), this->_data, GL_STATIC_DRAW);

	GLuint positionLocation = glGetAttribLocation(getGLProgram()->getProgram(), "a_position");
	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}