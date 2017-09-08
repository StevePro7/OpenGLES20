#ifndef ESUTIL_H
#define ESUTIL_H

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#ifdef __cplusplus
extern "C"
{
#endif


	#define ESUTIL_API  __cdecl
	#define ESCALLBACK  __cdecl


	/// esCreateWindow flag - RGB color buffer
	#define ES_WINDOW_RGB           0
		/// esCreateWindow flag - ALPHA color buffer
	#define ES_WINDOW_ALPHA         1 
		/// esCreateWindow flag - depth buffer
	#define ES_WINDOW_DEPTH         2 
		/// esCreateWindow flag - stencil buffer
	#define ES_WINDOW_STENCIL       4
		/// esCreateWindow flat - multi-sample buffer
	#define ES_WINDOW_MULTISAMPLE   8


	typedef struct
	{
		GLfloat   m[4][4];
	} ESMatrix;


	typedef struct
	{
		/// Put your user data here...
		void*       userData;

		/// Window width
		GLint       width;

		/// Window height
		GLint       height;

		/// Window handle
		EGLNativeWindowType  hWnd;

		/// EGL display
		EGLDisplay  eglDisplay;

		/// EGL context
		EGLContext  eglContext;

		/// EGL surface
		EGLSurface  eglSurface;

		/// Callbacks
		void (ESCALLBACK *drawFunc) (void*);
		void (ESCALLBACK *keyFunc) (void*, unsigned char, int, int);
		void (ESCALLBACK *updateFunc) (void*, float deltaTime);
	} ESContext;


	void ESUTIL_API esInitContext(ESContext *esContext);

	GLboolean ESUTIL_API esCreateWindow(ESContext *esContext, const char *title, GLint width, GLint height, GLuint flags);

	void ESUTIL_API esMainLoop(ESContext *esContext);

	void ESUTIL_API esRegisterDrawFunc(ESContext *esContext, void (ESCALLBACK *drawFunc) (void*));
	void ESUTIL_API esRegisterUpdateFunc(ESContext *esContext, void (ESCALLBACK *updateFunc) (void*, float));
	void ESUTIL_API esRegisterKeyFunc(ESContext *esContext, void (ESCALLBACK *drawFunc) (void*, unsigned char, int, int));

	void ESUTIL_API esLogMessage(const char *formatStr, ...);

	GLuint ESUTIL_API esLoadShader(GLenum type, const char *shaderSrc);
	GLuint ESUTIL_API esLoadProgram(const char *vertShaderSrc, const char *fragShaderSrc);

	int ESUTIL_API esGenSphere(int numSlices, float radius, GLfloat **vertices, GLfloat **normals, GLfloat **texCoords, GLuint **indices);
	int ESUTIL_API esGenCube(float scale, GLfloat **vertices, GLfloat **normals, GLfloat **texCoords, GLuint **indices);

	char* ESUTIL_API esLoadTGA(char *fileName, int *width, int *height);

	void ESUTIL_API esScale(ESMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz);
	void ESUTIL_API esTranslate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
	void ESUTIL_API esRotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void ESUTIL_API esFrustum(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
	void ESUTIL_API esPerspective(ESMatrix *result, float fovy, float aspect, float nearZ, float farZ);
	void ESUTIL_API esOrtho(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
	void ESUTIL_API esMatrixMultiply(ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB);
	void ESUTIL_API esMatrixLoadIdentity(ESMatrix *result);

#ifdef __cplusplus
}
#endif

#endif // ESUTIL_H