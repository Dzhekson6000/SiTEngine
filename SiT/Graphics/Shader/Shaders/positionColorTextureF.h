"																						\n\
#ifdef GL_ES																			\n\
	precision lowp float;																\n\
#endif																					\n\
																						\n\
varying vec2 v_texCoord;																\n\
uniform sampler2D u_Texture0;															\n\
varying vec4 v_fragmentColor;															\n\
																						\n\
void main()																				\n\
{																						\n\
	gl_FragColor=vec4(1, 1, 1, texture2D(u_Texture0, v_texCoord).a)*v_fragmentColor;	\n\
}																						\n\
";