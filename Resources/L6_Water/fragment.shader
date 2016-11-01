#ifdef GL_ES
precision highp float;
#endif

#ifdef GL_ES
varying highp vec4 v_fragmentColor;
varying highp vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

uniform sampler2D u_normalMap;
//浪花1
uniform sampler2D u_WaveFlowerMask1;
//浪花2
uniform sampler2D u_WaveFlowerMask2;

///////////////////////////////////////
varying vec2 v_norCood;
varying vec2 v_norCood1;


///////////////////////////////////////
//平铺率
float flat_rate_1               = 3.2;
//平铺率
float flat_rate_2               = 7.3;
//浪尖颜色
vec4 wave_flower_color          = vec4(1.0);
//浪花1平铺系数
float wave_flower1_rate         = 2.0;
//浪花2平铺系数
float wave_flower2_rate         = 3.0;

//高光范围系数
float spec_range_rate_min       = 0.965;
float spec_range_rate_max       = 1.0;


float blendOverlayf(float base,float blend) {
    return base < 0.5 ? (2.0 * base * blend) : (1.0 - 2.0 * (1.0 - base) * (1.0 - blend));
}

vec3 BlendOverlay(vec3 base,vec3 blend) {
    float r         = blendOverlayf(base.r, blend.r);
    float g         = blendOverlayf(base.g, blend.g);
    float b         = blendOverlayf(base.b, blend.b);

    return vec3(r, g, b);
}


// 浪花
vec4 handleWaveFlower(vec4 baseColor) {
    vec2 wave1Coord             = fract(v_norCood * wave_flower1_rate);
    vec2 wave2Coord             = fract(v_norCood1 * wave_flower2_rate);
    vec4 wave1Normal            = texture2D(u_WaveFlowerMask1, wave1Coord);
    vec4 wave2Normal            = texture2D(u_WaveFlowerMask2, wave2Coord);

    vec4 waveOverlay            = vec4(BlendOverlay(wave1Normal.rgb , wave2Normal.rgb),1.0);

    return baseColor + wave_flower_color * waveOverlay; 
}


void main()
{
    vec2 normal1Coord               = fract(v_norCood * flat_rate_1);
    vec4 normal1                    = texture2D(u_normalMap, normal1Coord);

    vec2 normal2Coord               = fract(v_norCood1 * flat_rate_2);
    vec4 normal2                    = texture2D(u_normalMap, normal2Coord);

    vec3 normcOlor                  = BlendOverlay(normal1.xyz,normal2.xyz); 

    normcOlor                       = normcOlor * 2.0 - 1.0;
    //基础纹理坐标
    vec2 basecoord                  = v_texCoord + vec2(normcOlor.x,normcOlor.y);
    //基础纹理
    vec4 baseColor                  = texture2D(CC_Texture0, basecoord); 


    // 添加浪花
    baseColor       = handleWaveFlower(baseColor);

    gl_FragColor    = baseColor * v_fragmentColor;

}
