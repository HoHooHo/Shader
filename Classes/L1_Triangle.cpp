#include "L1_Triangle.h"

bool L1_Triangle::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto size = Director::getInstance()->getWinSize();


	_vertercies[0] = 0;
	_vertercies[1] = 0;
	_vertercies[2] = size.width;
	_vertercies[3] = 0;
	_vertercies[4] = size.width/2;
	_vertercies[5] = size.height;

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

	this->scheduleUpdate();

	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    
    return true;
}


void L1_Triangle::visit(Renderer* render, const Mat4& parentTransform, uint32_t parentFlags){
	Layer::visit(render, parentTransform, parentFlags);

	_command.init(_globalZOrder);
	_command.func = CC_CALLBACK_0(L1_Triangle::onDraw, this);

	Director::getInstance()->getRenderer()->addCommand(&_command);
}

void L1_Triangle::onDraw(){
	auto glProgram = getGLProgram();
	glProgram->use();
	glProgram->setUniformsForBuiltins();

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, this->_vertercies);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, this->_color);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);

	CHECK_GL_ERROR_DEBUG();
}

void L1_Triangle::update(float delta){

	auto size = Director::getInstance()->getWinSize();

	for (int i = 0; i < 3; i++)
	{
		float x = this->_vertercies[i * 2];
		float y = this->_vertercies[i * 2 + 1];

		if (y == 0 && x < size.width)
		{
			this->_vertercies[i * 2] += 2;
		}else if (y == size.height && x > 0)
		{
			this->_vertercies[i * 2] -= 2;
		}else if(x == size.width && y < size.height)
		{
			this->_vertercies[i * 2 + 1] += 2;
		}else if(x == 0 && y > 0){
			this->_vertercies[i * 2 + 1] -= 2;
		}
	}
	
}