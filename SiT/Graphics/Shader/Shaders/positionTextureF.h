"																	\n\
#ifdef GL_ES														\n\
	precision lowp float;											\n\
#endif																\n\
																	\n\
varying vec2 v_texCoord;											\n\
uniform sampler2D u_Texture0;										\n\
varying vec4 v_fragmentColor;										\n\
																	\n\
void main()															\n\
{																	\n\
	gl_FragColor=texture2D(u_Texture0, v_texCoord)*v_fragmentColor; \n\
}																	\n\
";