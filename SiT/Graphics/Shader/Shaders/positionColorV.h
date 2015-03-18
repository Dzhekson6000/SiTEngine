"													\n\
attribute vec4 a_position;							\n\
uniform	vec4 u_color;								\n\							\n\
													\n\
#ifdef GL_ES										\n\
	varying lowp vec4 v_fragmentColor;				\n\
#else												\n\
	varying vec4 v_fragmentColor;					\n\
#endif												\n\
													\n\
void main()											\n\
{													\n\
	gl_Position = MVPMatrix * a_position;			\n\
	v_fragmentColor = u_color;						\n\
}													\n\
";