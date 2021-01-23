#ifndef GLIB_DEF_HPP
#define GLIB_DEF_HPP

// --==<alias>==--
#if (GLIB_GAPI & GLIB_GAPI_OGL)
typedef void GLvoid;
typedef char GLchar;
typedef signed char GLbyte;
typedef unsigned char GLubyte;
typedef unsigned char GLboolean;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLuint;
typedef unsigned int GLbitfield;
typedef unsigned short GLushort;
typedef unsigned long GLulong;
typedef unsigned int GLenum;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
#endif // GLIB_GAPI
// --==</alias>==--

#if (GLIB_GAPI & GLIB_GAPI_OGL)
// --==<data_types_ogl>==--
#define GL_BOOL								0x8B56
#define GL_BYTE								0x1400
#define GL_UNSIGNED_BYTE					0x1401
#define GL_SHORT							0x1402
#define GL_UNSIGNED_SHORT					0x1403
#define GL_INT								0x1404
#define GL_UNSIGNED_INT						0x1405
#define GL_FLOAT							0x1406
#define GL_DOUBLE							0x140A
#define GL_SAMPLER_1D 0x8B5D
// --==</data_types_ogl>==--

// --==<types_of_data_nw>==--
#define GLIB_ZERO 0
#define GLIB_ONE 1
#define GLIB_BOOL			GL_BOOL
#define GLIB_INT16		GL_SHORT
#define GLIB_UINT16		GL_UNSIGNED_SHORT
#define GLIB_INT8			GL_BYTE
#define GLIB_UINT8		GL_UNSIGNED_BYTE
#define GLIB_INT32		GL_INT
#define GLIB_UINT32		GL_UNSIGNED_INT
#define GLIB_FLOAT32		GL_FLOAT
#define GLIB_FLOAT64		GL_DOUBLE
#define GLIB_FLOAT32_VEC2	(GLIB_FLOAT32 + 0x0020)
#define GLIB_FLOAT32_VEC3	(GLIB_FLOAT32 + 0x0030)
#define GLIB_FLOAT32_VEC4	(GLIB_FLOAT32 + 0x0040)
#define GLIB_FLOAT32_MAT2	(GLIB_FLOAT32 + 0x0100)
#define GLIB_FLOAT32_MAT3	(GLIB_FLOAT32 + 0x0200)
#define GLIB_FLOAT32_MAT4	(GLIB_FLOAT32 + 0x0300)
#define GLIB_SAMPLER_1D	GL_SAMPLER_1D
// --==</types_of_data_nw>==--

// --==<draw_modes_ogl>==--
#define GL_POINT 0x1B00
#define GL_LINE 0x1B01
#define GL_FILL 0x1B02
// --primitives
#define GL_POINTS 0x0000
#define GL_LINES 0x0001
#define GL_LINE_STRIP 0x0003
#define GL_LINE_LOOP 0x0002
#define GL_LINE_BIT 0x00000004
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_FAN 0x0006
#define GL_QUADS 0x0007
#define GL_QUAD_STRIP 0x0008
#define GL_POLYGON 0x0009
// --==</draw_modes_ogl>==--

// --==<draw_modes_nw>==--
#define GLIB_POINT 0x1B00
#define GLIB_LINE 0x1B01
#define GLIB_FILL 0x1B02
// --primitives
#define GLIB_POINTS 0x0000
#define GLIB_LINES 0x0001
#define GLIB_LINE_STRIP 0x0003
#define GLIB_LINE_LOOP 0x0002
#define GLIB_LINE_BIT 0x00000004
#define GLIB_TRIANGLES 0x0004
#define GLIB_TRIANGLE_STRIP 0x0005
#define GLIB_TRIANGLE_FAN 0x0006
#define GLIB_QUADS 0x0007
#define GLIB_QUAD_STRIP 0x0008
#define GLIB_POLYGON 0x0009
// --==</draw_modes_NW>==--

// --==<planes_ogl>==--
#define GL_FRONT 0x0404
#define GL_BACK 0x0405
#define GL_LEFT 0x0406
#define GL_RIGHT 0x0407
#define GL_FRONT_AND_BACK 0x0408
// --==</planes_ogl>==--
// --==<planes_nw>==--
#define GLIB_FRONT GL_FRONT
#define GLIB_BACK GL_BACK
#define GLIB_LEFT GL_LEFT
#define GLIB_RIGHT GL_RIGHT
#define GLIB_FRONT_AND_BACK GL_FRONT_AND_BACK
// --==</planes_nw>==--

// --==<Shaders_ogl>==--
#define GL_SHADER 0x82E1
#define GL_PROGRAM 0x82E2
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_GEOMETRY_SHADER 0x8DD9
#define GL_VERTEX_SHADER 0x8B31

#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_ATTACHED_SHADERS 0x8B85
// --==<shaders_ogl>==--

// --==<shaders_nw>==--
#define GLIB_SHADER				GL_PROGRAM
#define GLIB_SHADER_VERTEX		GL_VERTEX_SHADER
#define GLIB_SHADER_GEOMETRY		GL_GEOMETRY_SHADER
#define GLIB_SHADER_PIXEL			GL_FRAGMENT_SHADER

#define GLIB_COMPILE_STATUS		GL_COMPILE_STATUS
#define GLIB_LINK_STATUS			GL_LINK_STATUS
// --==</Shaders_NW>==--

// --==<configurations_ogl>==--
#define GL_SRC_COLOR 0x0300
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_DST_ALPHA 0x0304
#define GL_ONE_MINUS_DST_ALPHA 0x0305
#define GL_DST_COLOR 0x0306
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_SRC_ALPHA_SATURATE 0x0308
#define GL_POINT_SIZE 0x0B11
#define GL_LINE_SMOOTH 0x0B20
#define GL_LINE_WIDTH 0x0B21

#define GL_CULL_FACE 0x0B44
#define GL_CULL_FACE_MODE 0x0B45
#define GL_FRONT_FACE 0x0B46
#define GL_CW 0x0900
#define GL_CCW 0x0901

#define GL_DEPTH_TEST 0x0B71
#define GL_DEPTH_FUNC 0x0B74

#define GL_STENCIL_TEST 0x0B90
#define GL_STENCIL_FUNC 0x0B92

#define GL_BLEND_DST 0x0BE0
#define GL_BLEND_SRC 0x0BE1
#define GL_BLEND 0x0BE2

#define GL_KEEP				0x1E00
#define GL_REPLACE			0x1E01
#define GL_INCR				0x1E02
#define GL_DECR				0x1E03
// --==</configurations_ogl>==--

// --==<configurations_nw>==--
#define GLIB_SRC_COLOR GL_SRC_COLOR
#define GLIB_ONE_MINUS_SRC_COLOR GL_ONE_MINUS_SRC_COLOR
#define GLIB_SRC_ALPHA GL_SRC_ALPHA
#define GLIB_ONE_MINUS_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
#define GLIB_DST_ALPHA GL_DST_ALPHA
#define GLIB_ONE_MINUS_DST_ALPHA GL_ONE_MINUS_DST_ALPHA
#define GLIB_DST_COLOR GL_DST_COLOR
#define GLIB_ONE_MINUS_DST_COLOR GL_ONE_MINUS_DST_COLOR
#define GLIB_SRC_ALPHA_SATURATE GL_SRC_ALPHA_SATURATE
#define GLIB_POINT_SIZE GL_POINT_SIZE
#define GLIB_LINE_SMOOTH GL_LINE_SMOOTH
#define GLIB_LINE_WIDTH GL_LINE_WIDTH

#define GLIB_CULL_FACE		GL_CULL_FACE
#define GLIB_CULL_FACE_MODE	GL_CULL_FACE_MODE
#define GLIB_FRONT_FACE		GL_FRONT_FACE
#define GLIB_CW				GL_CW
#define GLIB_CCW				GL_CCW

#define GLIB_DEPTH_TEST		GL_DEPTH_TEST
#define GLIB_DEPTH_FUNC		GL_DEPTH_FUNC

#define GLIB_STENCIL_TEST		GL_STENCIL_TEST
#define GLIB_STENCIL_FUNC		GL_STENCIL_FUNC

#define GLIB_BLEND_DST		GL_BLEND_DST
#define GLIB_BLEND_SRC		GL_BLEND_SRC
#define GLIB_BLEND			GL_BLEND

#define GLIB_KEEP				 GL_KEEP		
#define GLIB_REPLACE			 GL_REPLACE	
#define GLIB_INCR				 GL_INCR		
#define GLIB_DECR				 GL_DECR		
// --==</configurations_nw>==--

// --==<expressions_ogl>==--
// --constants
#define GL_NONE 0
#define GL_FALSE 0
#define GL_TRUE 1
#define GL_ZERO 0
#define GL_ONE 1
// --conditions
#define GL_NEVER 0x0200
#define GL_LESS 0x0201
#define GL_EQUAL 0x0202
#define GL_LEQUAL 0x0203
#define GL_GREATER 0x0204
#define GL_NOTEQUAL 0x0205
#define GL_GEQUAL 0x0206
#define GL_ALWAYS 0x0207
// --logic
#define GL_AND 0x1501
#define GL_AND_REVERSE 0x1502
#define GL_COPY 0x1503
#define GL_AND_INVERTED 0x1504
#define GL_NOOP 0x1505
#define GL_XOR 0x1506
#define GL_OR 0x1507
#define GL_NOR 0x1508
#define GL_EQUIV 0x1509
#define GL_INVERT 0x150A
#define GL_OR_REVERSE 0x150B
#define GL_COPY_INVERTED 0x150C
#define GL_OR_INVERTED 0x150D
#define GL_NAND 0x150E
// --==</expressions_ogl>==--

// --==<expressions_nw>==--
// --constants
#define GLIB_NONE 0
#define GLIB_FALSE 0
#define GLIB_TRUE 1
// --conditions
#define GLIB_NEVER 0x0200
#define GLIB_LESS 0x0201
#define GLIB_EQUAL 0x0202
#define GLIB_LEQUAL 0x0203
#define GLIB_GREATER 0x0204
#define GLIB_NOTEQUAL 0x0205
#define GLIB_GEQUAL 0x0206
#define GLIB_ALWAYS 0x0207
// --logic
#define GLIB_AND 0x1501
#define GLIB_AND_REVERSE 0x1502
#define GLIB_COPY 0x1503
#define GLIB_AND_INVERTED 0x1504
#define GLIB_NOOP 0x1505
#define GLIB_XOR 0x1506
#define GLIB_OR 0x1507
#define GLIB_NOR 0x1508
#define GLIB_EQUIV 0x1509
#define GLIB_INVERT 0x150A
#define GLIB_OR_REVERSE 0x150B
#define GLIB_COPY_INVERTED 0x150C
#define GLIB_OR_INVERTED 0x150D
#define GLIB_NAND 0x150E
// --==</expressions_nw>==--

// --==<colors_ogl>==--
#define GL_COLOR 0x1800
#define GL_RED 0x1903
#define GL_GREEN 0x1904
#define GL_BLUE 0x1905
#define GL_ALPHA 0x1906
#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_RGBA8 0x8058
// --==</colors_ogl>==--

// --==<colors_nw>==--
#define GLIB_COLOR		GL_COLOR
#define GLIB_RED			GL_RED
#define GLIB_GREEN		GL_GREEN
#define GLIB_BLUE			GL_BLUE
#define GLIB_ALPHA		GL_ALPHA
#define GLIB_RGB			GL_RGB
#define GLIB_RGBA			GL_RGBA
#define GLIB_RGBA8		GL_RGBA8
// --==</colors_nw>==--

// --==<textures_ogl>==--
// --types
#define GL_TEXTURE_1D 0x0DE0
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_3D 0x0DE2
// --filters
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601
// --wrappers
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_CLAMP 0x2900
#define GL_REPEAT 0x2901
// --==</textures_ogl>==--

// --==<textures_nw>==--
// --types
#define GLIB_TEXTURE_1D	GL_TEXTURE_1D
#define GLIB_TEXTURE_2D	GL_TEXTURE_2D
#define GLIB_TEXTURE_3D	GL_TEXTURE_3D
// --filters
#define GLIB_TEXTURE_MAG_FILTER			GL_TEXTURE_MAG_FILTER
#define GLIB_TEXTURE_MIN_FILTER			GL_TEXTURE_MIN_FILTER
#define GLIB_TEXTURE_FILTER_NEAREST		GL_NEAREST
#define GLIB_TEXTURE_FILTER_LINEAR		GL_LINEAR
// --wrappers
#define GLIB_TEXTURE_WRAP_S			GL_TEXTURE_WRAP_S
#define GLIB_TEXTURE_WRAP_T			GL_TEXTURE_WRAP_T
#define GLIB_TEXTURE_WRAP_R			GL_TEXTURE_WRAP_R
#define GLIB_TEXTURE_WRAP_CLAMP		GL_CLAMP
#define GLIB_TEXTURE_WRAP_REPEAT		GL_REPEAT
// --==</textures_nw>==--

// --==<gbuffers_ogl>==--
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_UNIFORM_BUFFER 0x8A11
// --==</gbuffers_ogl>==--

// --==<buffers_ogl>==--
#define GL_COLOR_BUFFER_BIT					0x00004000
#define GL_DEPTH_BUFFER_BIT					0x00000100
#define GL_ACCUM_BUFFER_BIT					0x00000200
#define GL_STENCIL_BUFFER_BIT				0x00000400
// --==</buffers_ogl>==--


// --==<gbuffers_nw>==--
#define GLIB_GBUFFER_VERTEX GL_ARRAY_BUFFER
#define GLIB_GBUFFER_INDEX GL_ELEMENT_ARRAY_BUFFER
#define GLIB_GBUFFER_SHADER GL_UNIFORM_BUFFER
// --==</gbuffers_nw>==--

// --==<framebuffers_nw>==--
#define GLIB_BUFFER_COLOR_BIT					GL_COLOR_BUFFER_BIT
#define GLIB_BUFFER_DEPTH_BIT					GL_DEPTH_BUFFER_BIT
#define GLIB_BUFFER_STENCIL_BIT				GL_STENCIL_BUFFER_BIT
// --==</framebuffers_nw>==--

// --==<data_load_types_ogl>==--
#define GL_STATIC_DRAW 0x88E4
#define GL_STREAM_DRAW 0x88E0
#define GL_DYNAMIC_DRAW 0x88E8
// --==</data_load_types_ogl>==--

// --==<data_load_types_nw>==--
#define GLIB_STATIC_DRAW		GL_STATIC_DRAW 
#define GLIB_STREAM_DRAW		GL_STREAM_DRAW 
#define GLIB_DYNAMIC_DRAW		GL_DYNAMIC_DRAW
// --==</data_load_types_nw>==--

// --==<error_codes_ogl>==--
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_OUT_OF_MEMORY                  0x0505
// --==</error_codes_ogl>==--

// --==<error_codes_nw>==--
#define GLIB_OK							GL_NO_ERROR         
#define GLIB_INVALID_ENUM					GL_INVALID_ENUM     
#define GLIB_INVALID_VALUE				GL_INVALID_VALUE    
#define GLIB_INVALID_OPERATION			GL_INVALID_OPERATION
#define GLIB_STACK_OVERFLOW				GL_STACK_OVERFLOW   
#define GLIB_STACK_UNDERFLOW				GL_STACK_UNDERFLOW  
#define GLIB_OUT_OF_MEMORY				GL_OUT_OF_MEMORY  

#define GLIB_ERR_DATA_LOSS				0b1110'0000'0000

#define GLIB_ERR_NO_SUPPORT				0b1110'0000'0001
#define GLIB_ERR_NO_DATA					0b1110'0000'0001
#define GLIB_ERR_NO_INIT					0b1110'0000'0010
#define GLIB_ERR_NO_QUIT					0b1110'0000'0011
#define GLIB_ERR_NO_STATE					0b1110'0000'0100

#define GLIB_ERR_UNKNOWN_ID				0b1111'0000'0000

#define GLIB_ERR_SHADER_INVALID_FORMAT	0b0011'0000'0000
#define GLIB_ERR_SHADER_LOAD_PATH			0b1000'0000'0000
#define GLIB_ERR_SHADER_LOAD_FAIL			0b1001'0000'0000
#define GLIB_ERR_SHADER_LINK				0b1011'0000'0000
#define GLIB_ERR_SHADER_COMPILE			0b1100'0000'0000
// --==</error_codes_nw>==--

// --==<info_ogl>==--
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03
// --==</info_ogl>==--
// Nothing for now... 08.11.20
#endif // GLIB_GAPI

#endif	// GLIB_DEF_HPP