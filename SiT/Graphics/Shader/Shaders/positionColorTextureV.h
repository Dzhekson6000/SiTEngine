"														\n\
attribute vec4 a_position;								\n\
attribute vec4 a_color;									\n\
attribute vec2 a_texCoord;								\n\
uniform	vec4 u_color;									\n\
														\n\
#ifdef GL_ES											\n\
	varying mediump vec2 v_texCoord;					\n\
	varying lowp vec4 v_fragmentColor;					\n\
#else													\n\
	varying vec2 v_texCoord;							\n\
	varying vec4 v_fragmentColor;						\n\
#endif													\n\
														\n\
void main()												\n\
{														\n\
	gl_Position = MVPMatrix * a_position;				\n\
	v_texCoord = a_texCoord;							\n\
	v_fragmentColor = u_color;							\n\
}														\n\
";