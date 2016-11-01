#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
    gl_FragColor = vec4(0, 0, 0.8, 1.0) * texture2D(CC_Texture0, v_texCoord);
}