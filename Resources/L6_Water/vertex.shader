#ifdef GL_ES
precision highp float;
#endif
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

uniform vec2  u_contentSize;

//暂停海水扰动,1:暂停
uniform int u_pause;



#ifdef GL_ES
varying highp vec4 v_fragmentColor;
varying highp vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

varying vec3 v_centerpoint;
varying vec2 v_contentSize;

varying vec2 v_norCood;
varying vec2 v_norCood1;
 

float lastTime = 0.0;
float angle = 15.0 * 3.1415/180.0;
 

void main()
{
    //gl_Position = CC_PMatrix * a_position;

    float time = u_pause == 1 ? lastTime : CC_Time.y;

    gl_Position   = CC_PMatrix * a_position; 


    v_fragmentColor = a_color;
    v_texCoord    = a_texCoord;

    
    

    v_centerpoint     = vec3(u_contentSize.x/2.0,u_contentSize.y/2.0,0.0);
    v_contentSize   = u_contentSize;


    //滚动纹理坐标
    v_norCood         = vec2(v_texCoord.x - time * 0.03,v_texCoord.y - time * 0.03);  
    v_norCood1        = vec2(v_texCoord.x - time * 0.02,v_texCoord.y - time * 0.02);     

    lastTime        = time;
  }