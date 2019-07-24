/* Shared Use License: This file is owned by Derivative Inc. (Derivative) and
 * can only be used, and/or modified for use, in conjunction with 
 * Derivative's TouchDesigner software, and only if you are a licensee who has
 * accepted Derivative's TouchDesigner license or assignment agreement (which
 * also govern the use of this file).  You may share a modified version of this
 * file with another authorized licensee of Derivative's TouchDesigner software.
 * Otherwise, no redistribution or sharing of this file, with or without
 * modification, is permitted.
 *
 * TouchPlugIn
 *
 * Copyright © 2018 Derivative. All rights reserved.
 *
 */

#ifndef TEGraphicsContext_h
#define TEGraphicsContext_h

#include "TEBase.h"
#include "TETypes.h"
#include "TED3DTexture.h"
#include "TEDXGITexture.h"
#include "TEOpenGLTexture.h"
#ifdef __APPLE__
	#include <OpenGL/OpenGL.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

TE_ASSUME_NONNULL_BEGIN

typedef TEObject TEGraphicsContext;
typedef TEGraphicsContext TEOpenGLContext;
typedef TEGraphicsContext TED3DContext;

#ifdef _WIN32
struct ID3D11Device;
typedef struct HGLRC__ *HGLRC;
typedef struct HDC__ *HDC;
#endif

#ifdef _WIN32

/*
 Creates a graphics context for use with Direct3D.
 
 'device' is the Direct3D device to be used for texture creation.
 'context' will be set to a TED3DContext on return, or NULL if a context could not be created.
	The caller is responsible for releasing the returned TED3DContext using TERelease()
 Returns TEResultSucccess or an error
 */
TE_EXPORT TEResult TED3DContextCreate(ID3D11Device * TE_NULLABLE device,
										TED3DContext * TE_NULLABLE * TE_NONNULL context);

/*
Returns the ID3D11Device associated with a Direct3D context, or NULL.
*/
TE_EXPORT ID3D11Device *TED3DContextGetDevice(TED3DContext *context);

/*
 Work may be done in the graphics context by this call.
 The caller is responsible for releasing the returned TETexture using TERelease() -
	work may be done in the graphics context by the final call to TERelease()
	for the returned texture.
 */
TE_EXPORT TEResult TED3DContextCreateTexture(TED3DContext *context, TEDXGITexture *source, TED3DTexture * TE_NULLABLE * TE_NONNULL texture);

/*
 Creates a graphics context for use with OpenGL.
 
 'dc' is a valid device context to be used for OpenGL commands
	This value can be changed later using TEOpenGLContextSetDC()
 'rc' is a valid OpenGL render context to be used for OpenGL commands
 'context' will be set to a TEOpenGLContext on return, or NULL if a context could not be created.
	The caller is responsible for releasing the returned TEOpenGLContext using TERelease()
 Returns TEResultSucccess or an error
 */
TE_EXPORT TEResult TEOpenGLContextCreate(HDC dc,
									  		HGLRC rc,
											TEOpenGLContext * TE_NULLABLE * TE_NONNULL context);

/*
 Returns the device context associated with an OpenGL context, or NULL.
 */
TE_EXPORT HDC TEOpenGLContextGetDC(TEOpenGLContext *context);

/*
 Returns the OpenGL render context associated with an OpenGL context, or NULL.
 */
TE_EXPORT HGLRC TEOpenGLContextGetRC(TEOpenGLContext *context);

/*
 Change the device context used by an OpenGL context.
 Returns TEResultSuccess on success, or an error.
 */
TE_EXPORT TEResult TEOpenGLContextSetDC(TEOpenGLContext *context, HDC dc);

/*
 Work may be done in the graphics context by this call.
 The current OpenGL texture binding may be changed during this call.
 The caller is responsible for releasing the returned TETexture using TERelease() -
	work may be done in the graphics context associated with the instance by the final
	call to TERelease() for the returned texture.
 */
TE_EXPORT TEResult TEOpenGLContextCreateTexture(TED3DContext *context, TEDXGITexture *source, TEOpenGLTexture * TE_NULLABLE * TE_NONNULL texture);

#endif

#ifdef __APPLE__

TE_EXPORT TEResult TEOpenGLContextCreate(CGLContextObj cgl, TEOpenGLContext * TE_NULLABLE * TE_NONNULL context);

TE_EXPORT CGLContextObj TEOpenGLContextGetCGLContext(TEOpenGLContext *context);

// TODO: tex instantiation function

#endif

TE_ASSUME_NONNULL_END

#ifdef __cplusplus
}
#endif

#endif
