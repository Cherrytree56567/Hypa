/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/gles1.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif








static void glad_gl_load_GL_VERSION_ES_CM_1_0(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_ES_CM_1_0) return;
    context->ActiveTexture = (PFNGLACTIVETEXTUREPROC) load(userptr, "glActiveTexture");
    context->AlphaFunc = (PFNGLALPHAFUNCPROC) load(userptr, "glAlphaFunc");
    context->AlphaFuncx = (PFNGLALPHAFUNCXPROC) load(userptr, "glAlphaFuncx");
    context->BindBuffer = (PFNGLBINDBUFFERPROC) load(userptr, "glBindBuffer");
    context->BindTexture = (PFNGLBINDTEXTUREPROC) load(userptr, "glBindTexture");
    context->BlendFunc = (PFNGLBLENDFUNCPROC) load(userptr, "glBlendFunc");
    context->BufferData = (PFNGLBUFFERDATAPROC) load(userptr, "glBufferData");
    context->BufferSubData = (PFNGLBUFFERSUBDATAPROC) load(userptr, "glBufferSubData");
    context->Clear = (PFNGLCLEARPROC) load(userptr, "glClear");
    context->ClearColor = (PFNGLCLEARCOLORPROC) load(userptr, "glClearColor");
    context->ClearColorx = (PFNGLCLEARCOLORXPROC) load(userptr, "glClearColorx");
    context->ClearDepthf = (PFNGLCLEARDEPTHFPROC) load(userptr, "glClearDepthf");
    context->ClearDepthx = (PFNGLCLEARDEPTHXPROC) load(userptr, "glClearDepthx");
    context->ClearStencil = (PFNGLCLEARSTENCILPROC) load(userptr, "glClearStencil");
    context->ClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC) load(userptr, "glClientActiveTexture");
    context->ClipPlanef = (PFNGLCLIPPLANEFPROC) load(userptr, "glClipPlanef");
    context->ClipPlanex = (PFNGLCLIPPLANEXPROC) load(userptr, "glClipPlanex");
    context->Color4f = (PFNGLCOLOR4FPROC) load(userptr, "glColor4f");
    context->Color4ub = (PFNGLCOLOR4UBPROC) load(userptr, "glColor4ub");
    context->Color4x = (PFNGLCOLOR4XPROC) load(userptr, "glColor4x");
    context->ColorMask = (PFNGLCOLORMASKPROC) load(userptr, "glColorMask");
    context->ColorPointer = (PFNGLCOLORPOINTERPROC) load(userptr, "glColorPointer");
    context->CompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) load(userptr, "glCompressedTexImage2D");
    context->CompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) load(userptr, "glCompressedTexSubImage2D");
    context->CopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) load(userptr, "glCopyTexImage2D");
    context->CopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) load(userptr, "glCopyTexSubImage2D");
    context->CullFace = (PFNGLCULLFACEPROC) load(userptr, "glCullFace");
    context->DeleteBuffers = (PFNGLDELETEBUFFERSPROC) load(userptr, "glDeleteBuffers");
    context->DeleteTextures = (PFNGLDELETETEXTURESPROC) load(userptr, "glDeleteTextures");
    context->DepthFunc = (PFNGLDEPTHFUNCPROC) load(userptr, "glDepthFunc");
    context->DepthMask = (PFNGLDEPTHMASKPROC) load(userptr, "glDepthMask");
    context->DepthRangef = (PFNGLDEPTHRANGEFPROC) load(userptr, "glDepthRangef");
    context->DepthRangex = (PFNGLDEPTHRANGEXPROC) load(userptr, "glDepthRangex");
    context->Disable = (PFNGLDISABLEPROC) load(userptr, "glDisable");
    context->DisableClientState = (PFNGLDISABLECLIENTSTATEPROC) load(userptr, "glDisableClientState");
    context->DrawArrays = (PFNGLDRAWARRAYSPROC) load(userptr, "glDrawArrays");
    context->DrawElements = (PFNGLDRAWELEMENTSPROC) load(userptr, "glDrawElements");
    context->Enable = (PFNGLENABLEPROC) load(userptr, "glEnable");
    context->EnableClientState = (PFNGLENABLECLIENTSTATEPROC) load(userptr, "glEnableClientState");
    context->Finish = (PFNGLFINISHPROC) load(userptr, "glFinish");
    context->Flush = (PFNGLFLUSHPROC) load(userptr, "glFlush");
    context->Fogf = (PFNGLFOGFPROC) load(userptr, "glFogf");
    context->Fogfv = (PFNGLFOGFVPROC) load(userptr, "glFogfv");
    context->Fogx = (PFNGLFOGXPROC) load(userptr, "glFogx");
    context->Fogxv = (PFNGLFOGXVPROC) load(userptr, "glFogxv");
    context->FrontFace = (PFNGLFRONTFACEPROC) load(userptr, "glFrontFace");
    context->Frustumf = (PFNGLFRUSTUMFPROC) load(userptr, "glFrustumf");
    context->Frustumx = (PFNGLFRUSTUMXPROC) load(userptr, "glFrustumx");
    context->GenBuffers = (PFNGLGENBUFFERSPROC) load(userptr, "glGenBuffers");
    context->GenTextures = (PFNGLGENTEXTURESPROC) load(userptr, "glGenTextures");
    context->GetBooleanv = (PFNGLGETBOOLEANVPROC) load(userptr, "glGetBooleanv");
    context->GetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) load(userptr, "glGetBufferParameteriv");
    context->GetClipPlanef = (PFNGLGETCLIPPLANEFPROC) load(userptr, "glGetClipPlanef");
    context->GetClipPlanex = (PFNGLGETCLIPPLANEXPROC) load(userptr, "glGetClipPlanex");
    context->GetError = (PFNGLGETERRORPROC) load(userptr, "glGetError");
    context->GetFixedv = (PFNGLGETFIXEDVPROC) load(userptr, "glGetFixedv");
    context->GetFloatv = (PFNGLGETFLOATVPROC) load(userptr, "glGetFloatv");
    context->GetIntegerv = (PFNGLGETINTEGERVPROC) load(userptr, "glGetIntegerv");
    context->GetLightfv = (PFNGLGETLIGHTFVPROC) load(userptr, "glGetLightfv");
    context->GetLightxv = (PFNGLGETLIGHTXVPROC) load(userptr, "glGetLightxv");
    context->GetMaterialfv = (PFNGLGETMATERIALFVPROC) load(userptr, "glGetMaterialfv");
    context->GetMaterialxv = (PFNGLGETMATERIALXVPROC) load(userptr, "glGetMaterialxv");
    context->GetPointerv = (PFNGLGETPOINTERVPROC) load(userptr, "glGetPointerv");
    context->GetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    context->GetTexEnvfv = (PFNGLGETTEXENVFVPROC) load(userptr, "glGetTexEnvfv");
    context->GetTexEnviv = (PFNGLGETTEXENVIVPROC) load(userptr, "glGetTexEnviv");
    context->GetTexEnvxv = (PFNGLGETTEXENVXVPROC) load(userptr, "glGetTexEnvxv");
    context->GetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) load(userptr, "glGetTexParameterfv");
    context->GetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) load(userptr, "glGetTexParameteriv");
    context->GetTexParameterxv = (PFNGLGETTEXPARAMETERXVPROC) load(userptr, "glGetTexParameterxv");
    context->Hint = (PFNGLHINTPROC) load(userptr, "glHint");
    context->IsBuffer = (PFNGLISBUFFERPROC) load(userptr, "glIsBuffer");
    context->IsEnabled = (PFNGLISENABLEDPROC) load(userptr, "glIsEnabled");
    context->IsTexture = (PFNGLISTEXTUREPROC) load(userptr, "glIsTexture");
    context->LightModelf = (PFNGLLIGHTMODELFPROC) load(userptr, "glLightModelf");
    context->LightModelfv = (PFNGLLIGHTMODELFVPROC) load(userptr, "glLightModelfv");
    context->LightModelx = (PFNGLLIGHTMODELXPROC) load(userptr, "glLightModelx");
    context->LightModelxv = (PFNGLLIGHTMODELXVPROC) load(userptr, "glLightModelxv");
    context->Lightf = (PFNGLLIGHTFPROC) load(userptr, "glLightf");
    context->Lightfv = (PFNGLLIGHTFVPROC) load(userptr, "glLightfv");
    context->Lightx = (PFNGLLIGHTXPROC) load(userptr, "glLightx");
    context->Lightxv = (PFNGLLIGHTXVPROC) load(userptr, "glLightxv");
    context->LineWidth = (PFNGLLINEWIDTHPROC) load(userptr, "glLineWidth");
    context->LineWidthx = (PFNGLLINEWIDTHXPROC) load(userptr, "glLineWidthx");
    context->LoadIdentity = (PFNGLLOADIDENTITYPROC) load(userptr, "glLoadIdentity");
    context->LoadMatrixf = (PFNGLLOADMATRIXFPROC) load(userptr, "glLoadMatrixf");
    context->LoadMatrixx = (PFNGLLOADMATRIXXPROC) load(userptr, "glLoadMatrixx");
    context->LogicOp = (PFNGLLOGICOPPROC) load(userptr, "glLogicOp");
    context->Materialf = (PFNGLMATERIALFPROC) load(userptr, "glMaterialf");
    context->Materialfv = (PFNGLMATERIALFVPROC) load(userptr, "glMaterialfv");
    context->Materialx = (PFNGLMATERIALXPROC) load(userptr, "glMaterialx");
    context->Materialxv = (PFNGLMATERIALXVPROC) load(userptr, "glMaterialxv");
    context->MatrixMode = (PFNGLMATRIXMODEPROC) load(userptr, "glMatrixMode");
    context->MultMatrixf = (PFNGLMULTMATRIXFPROC) load(userptr, "glMultMatrixf");
    context->MultMatrixx = (PFNGLMULTMATRIXXPROC) load(userptr, "glMultMatrixx");
    context->MultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC) load(userptr, "glMultiTexCoord4f");
    context->MultiTexCoord4x = (PFNGLMULTITEXCOORD4XPROC) load(userptr, "glMultiTexCoord4x");
    context->Normal3f = (PFNGLNORMAL3FPROC) load(userptr, "glNormal3f");
    context->Normal3x = (PFNGLNORMAL3XPROC) load(userptr, "glNormal3x");
    context->NormalPointer = (PFNGLNORMALPOINTERPROC) load(userptr, "glNormalPointer");
    context->Orthof = (PFNGLORTHOFPROC) load(userptr, "glOrthof");
    context->Orthox = (PFNGLORTHOXPROC) load(userptr, "glOrthox");
    context->PixelStorei = (PFNGLPIXELSTOREIPROC) load(userptr, "glPixelStorei");
    context->PointParameterf = (PFNGLPOINTPARAMETERFPROC) load(userptr, "glPointParameterf");
    context->PointParameterfv = (PFNGLPOINTPARAMETERFVPROC) load(userptr, "glPointParameterfv");
    context->PointParameterx = (PFNGLPOINTPARAMETERXPROC) load(userptr, "glPointParameterx");
    context->PointParameterxv = (PFNGLPOINTPARAMETERXVPROC) load(userptr, "glPointParameterxv");
    context->PointSize = (PFNGLPOINTSIZEPROC) load(userptr, "glPointSize");
    context->PointSizex = (PFNGLPOINTSIZEXPROC) load(userptr, "glPointSizex");
    context->PolygonOffset = (PFNGLPOLYGONOFFSETPROC) load(userptr, "glPolygonOffset");
    context->PolygonOffsetx = (PFNGLPOLYGONOFFSETXPROC) load(userptr, "glPolygonOffsetx");
    context->PopMatrix = (PFNGLPOPMATRIXPROC) load(userptr, "glPopMatrix");
    context->PushMatrix = (PFNGLPUSHMATRIXPROC) load(userptr, "glPushMatrix");
    context->ReadPixels = (PFNGLREADPIXELSPROC) load(userptr, "glReadPixels");
    context->Rotatef = (PFNGLROTATEFPROC) load(userptr, "glRotatef");
    context->Rotatex = (PFNGLROTATEXPROC) load(userptr, "glRotatex");
    context->SampleCoverage = (PFNGLSAMPLECOVERAGEPROC) load(userptr, "glSampleCoverage");
    context->SampleCoveragex = (PFNGLSAMPLECOVERAGEXPROC) load(userptr, "glSampleCoveragex");
    context->Scalef = (PFNGLSCALEFPROC) load(userptr, "glScalef");
    context->Scalex = (PFNGLSCALEXPROC) load(userptr, "glScalex");
    context->Scissor = (PFNGLSCISSORPROC) load(userptr, "glScissor");
    context->ShadeModel = (PFNGLSHADEMODELPROC) load(userptr, "glShadeModel");
    context->StencilFunc = (PFNGLSTENCILFUNCPROC) load(userptr, "glStencilFunc");
    context->StencilMask = (PFNGLSTENCILMASKPROC) load(userptr, "glStencilMask");
    context->StencilOp = (PFNGLSTENCILOPPROC) load(userptr, "glStencilOp");
    context->TexCoordPointer = (PFNGLTEXCOORDPOINTERPROC) load(userptr, "glTexCoordPointer");
    context->TexEnvf = (PFNGLTEXENVFPROC) load(userptr, "glTexEnvf");
    context->TexEnvfv = (PFNGLTEXENVFVPROC) load(userptr, "glTexEnvfv");
    context->TexEnvi = (PFNGLTEXENVIPROC) load(userptr, "glTexEnvi");
    context->TexEnviv = (PFNGLTEXENVIVPROC) load(userptr, "glTexEnviv");
    context->TexEnvx = (PFNGLTEXENVXPROC) load(userptr, "glTexEnvx");
    context->TexEnvxv = (PFNGLTEXENVXVPROC) load(userptr, "glTexEnvxv");
    context->TexImage2D = (PFNGLTEXIMAGE2DPROC) load(userptr, "glTexImage2D");
    context->TexParameterf = (PFNGLTEXPARAMETERFPROC) load(userptr, "glTexParameterf");
    context->TexParameterfv = (PFNGLTEXPARAMETERFVPROC) load(userptr, "glTexParameterfv");
    context->TexParameteri = (PFNGLTEXPARAMETERIPROC) load(userptr, "glTexParameteri");
    context->TexParameteriv = (PFNGLTEXPARAMETERIVPROC) load(userptr, "glTexParameteriv");
    context->TexParameterx = (PFNGLTEXPARAMETERXPROC) load(userptr, "glTexParameterx");
    context->TexParameterxv = (PFNGLTEXPARAMETERXVPROC) load(userptr, "glTexParameterxv");
    context->TexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) load(userptr, "glTexSubImage2D");
    context->Translatef = (PFNGLTRANSLATEFPROC) load(userptr, "glTranslatef");
    context->Translatex = (PFNGLTRANSLATEXPROC) load(userptr, "glTranslatex");
    context->VertexPointer = (PFNGLVERTEXPOINTERPROC) load(userptr, "glVertexPointer");
    context->Viewport = (PFNGLVIEWPORTPROC) load(userptr, "glViewport");
}
static void glad_gl_load_GL_APPLE_copy_texture_levels(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_copy_texture_levels) return;
    context->CopyTextureLevelsAPPLE = (PFNGLCOPYTEXTURELEVELSAPPLEPROC) load(userptr, "glCopyTextureLevelsAPPLE");
}
static void glad_gl_load_GL_APPLE_framebuffer_multisample(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_framebuffer_multisample) return;
    context->RenderbufferStorageMultisampleAPPLE = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) load(userptr, "glRenderbufferStorageMultisampleAPPLE");
    context->ResolveMultisampleFramebufferAPPLE = (PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) load(userptr, "glResolveMultisampleFramebufferAPPLE");
}
static void glad_gl_load_GL_APPLE_sync(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_sync) return;
    context->ClientWaitSyncAPPLE = (PFNGLCLIENTWAITSYNCAPPLEPROC) load(userptr, "glClientWaitSyncAPPLE");
    context->DeleteSyncAPPLE = (PFNGLDELETESYNCAPPLEPROC) load(userptr, "glDeleteSyncAPPLE");
    context->FenceSyncAPPLE = (PFNGLFENCESYNCAPPLEPROC) load(userptr, "glFenceSyncAPPLE");
    context->GetInteger64vAPPLE = (PFNGLGETINTEGER64VAPPLEPROC) load(userptr, "glGetInteger64vAPPLE");
    context->GetSyncivAPPLE = (PFNGLGETSYNCIVAPPLEPROC) load(userptr, "glGetSyncivAPPLE");
    context->IsSyncAPPLE = (PFNGLISSYNCAPPLEPROC) load(userptr, "glIsSyncAPPLE");
    context->WaitSyncAPPLE = (PFNGLWAITSYNCAPPLEPROC) load(userptr, "glWaitSyncAPPLE");
}
static void glad_gl_load_GL_EXT_debug_marker(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_debug_marker) return;
    context->InsertEventMarkerEXT = (PFNGLINSERTEVENTMARKEREXTPROC) load(userptr, "glInsertEventMarkerEXT");
    context->PopGroupMarkerEXT = (PFNGLPOPGROUPMARKEREXTPROC) load(userptr, "glPopGroupMarkerEXT");
    context->PushGroupMarkerEXT = (PFNGLPUSHGROUPMARKEREXTPROC) load(userptr, "glPushGroupMarkerEXT");
}
static void glad_gl_load_GL_EXT_discard_framebuffer(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_discard_framebuffer) return;
    context->DiscardFramebufferEXT = (PFNGLDISCARDFRAMEBUFFEREXTPROC) load(userptr, "glDiscardFramebufferEXT");
}
static void glad_gl_load_GL_EXT_map_buffer_range(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_map_buffer_range) return;
    context->FlushMappedBufferRangeEXT = (PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) load(userptr, "glFlushMappedBufferRangeEXT");
    context->MapBufferRangeEXT = (PFNGLMAPBUFFERRANGEEXTPROC) load(userptr, "glMapBufferRangeEXT");
}
static void glad_gl_load_GL_EXT_multi_draw_arrays(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_multi_draw_arrays) return;
    context->MultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC) load(userptr, "glMultiDrawArraysEXT");
    context->MultiDrawElementsEXT = (PFNGLMULTIDRAWELEMENTSEXTPROC) load(userptr, "glMultiDrawElementsEXT");
}
static void glad_gl_load_GL_EXT_multisampled_render_to_texture(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_multisampled_render_to_texture) return;
    context->FramebufferTexture2DMultisampleEXT = (PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) load(userptr, "glFramebufferTexture2DMultisampleEXT");
    context->RenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) load(userptr, "glRenderbufferStorageMultisampleEXT");
}
static void glad_gl_load_GL_EXT_robustness(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_robustness) return;
    context->GetGraphicsResetStatusEXT = (PFNGLGETGRAPHICSRESETSTATUSEXTPROC) load(userptr, "glGetGraphicsResetStatusEXT");
    context->GetnUniformfvEXT = (PFNGLGETNUNIFORMFVEXTPROC) load(userptr, "glGetnUniformfvEXT");
    context->GetnUniformivEXT = (PFNGLGETNUNIFORMIVEXTPROC) load(userptr, "glGetnUniformivEXT");
    context->ReadnPixelsEXT = (PFNGLREADNPIXELSEXTPROC) load(userptr, "glReadnPixelsEXT");
}
static void glad_gl_load_GL_EXT_texture_storage(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_storage) return;
    context->TexStorage1DEXT = (PFNGLTEXSTORAGE1DEXTPROC) load(userptr, "glTexStorage1DEXT");
    context->TexStorage2DEXT = (PFNGLTEXSTORAGE2DEXTPROC) load(userptr, "glTexStorage2DEXT");
    context->TexStorage3DEXT = (PFNGLTEXSTORAGE3DEXTPROC) load(userptr, "glTexStorage3DEXT");
    context->TextureStorage1DEXT = (PFNGLTEXTURESTORAGE1DEXTPROC) load(userptr, "glTextureStorage1DEXT");
    context->TextureStorage2DEXT = (PFNGLTEXTURESTORAGE2DEXTPROC) load(userptr, "glTextureStorage2DEXT");
    context->TextureStorage3DEXT = (PFNGLTEXTURESTORAGE3DEXTPROC) load(userptr, "glTextureStorage3DEXT");
}
static void glad_gl_load_GL_IMG_multisampled_render_to_texture(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->IMG_multisampled_render_to_texture) return;
    context->FramebufferTexture2DMultisampleIMG = (PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) load(userptr, "glFramebufferTexture2DMultisampleIMG");
    context->RenderbufferStorageMultisampleIMG = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) load(userptr, "glRenderbufferStorageMultisampleIMG");
}
static void glad_gl_load_GL_IMG_user_clip_plane(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->IMG_user_clip_plane) return;
    context->ClipPlanefIMG = (PFNGLCLIPPLANEFIMGPROC) load(userptr, "glClipPlanefIMG");
    context->ClipPlanexIMG = (PFNGLCLIPPLANEXIMGPROC) load(userptr, "glClipPlanexIMG");
}
static void glad_gl_load_GL_NV_fence(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_fence) return;
    context->DeleteFencesNV = (PFNGLDELETEFENCESNVPROC) load(userptr, "glDeleteFencesNV");
    context->FinishFenceNV = (PFNGLFINISHFENCENVPROC) load(userptr, "glFinishFenceNV");
    context->GenFencesNV = (PFNGLGENFENCESNVPROC) load(userptr, "glGenFencesNV");
    context->GetFenceivNV = (PFNGLGETFENCEIVNVPROC) load(userptr, "glGetFenceivNV");
    context->IsFenceNV = (PFNGLISFENCENVPROC) load(userptr, "glIsFenceNV");
    context->SetFenceNV = (PFNGLSETFENCENVPROC) load(userptr, "glSetFenceNV");
    context->TestFenceNV = (PFNGLTESTFENCENVPROC) load(userptr, "glTestFenceNV");
}
static void glad_gl_load_GL_OES_EGL_image(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_EGL_image) return;
    context->EGLImageTargetRenderbufferStorageOES = (PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) load(userptr, "glEGLImageTargetRenderbufferStorageOES");
    context->EGLImageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) load(userptr, "glEGLImageTargetTexture2DOES");
}
static void glad_gl_load_GL_OES_blend_equation_separate(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_blend_equation_separate) return;
    context->BlendEquationSeparateOES = (PFNGLBLENDEQUATIONSEPARATEOESPROC) load(userptr, "glBlendEquationSeparateOES");
}
static void glad_gl_load_GL_OES_blend_func_separate(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_blend_func_separate) return;
    context->BlendFuncSeparateOES = (PFNGLBLENDFUNCSEPARATEOESPROC) load(userptr, "glBlendFuncSeparateOES");
}
static void glad_gl_load_GL_OES_blend_subtract(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_blend_subtract) return;
    context->BlendEquationOES = (PFNGLBLENDEQUATIONOESPROC) load(userptr, "glBlendEquationOES");
}
static void glad_gl_load_GL_OES_draw_texture(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_draw_texture) return;
    context->DrawTexfOES = (PFNGLDRAWTEXFOESPROC) load(userptr, "glDrawTexfOES");
    context->DrawTexfvOES = (PFNGLDRAWTEXFVOESPROC) load(userptr, "glDrawTexfvOES");
    context->DrawTexiOES = (PFNGLDRAWTEXIOESPROC) load(userptr, "glDrawTexiOES");
    context->DrawTexivOES = (PFNGLDRAWTEXIVOESPROC) load(userptr, "glDrawTexivOES");
    context->DrawTexsOES = (PFNGLDRAWTEXSOESPROC) load(userptr, "glDrawTexsOES");
    context->DrawTexsvOES = (PFNGLDRAWTEXSVOESPROC) load(userptr, "glDrawTexsvOES");
    context->DrawTexxOES = (PFNGLDRAWTEXXOESPROC) load(userptr, "glDrawTexxOES");
    context->DrawTexxvOES = (PFNGLDRAWTEXXVOESPROC) load(userptr, "glDrawTexxvOES");
}
static void glad_gl_load_GL_OES_fixed_point(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_fixed_point) return;
    context->AlphaFuncxOES = (PFNGLALPHAFUNCXOESPROC) load(userptr, "glAlphaFuncxOES");
    context->ClearColorxOES = (PFNGLCLEARCOLORXOESPROC) load(userptr, "glClearColorxOES");
    context->ClearDepthxOES = (PFNGLCLEARDEPTHXOESPROC) load(userptr, "glClearDepthxOES");
    context->ClipPlanexOES = (PFNGLCLIPPLANEXOESPROC) load(userptr, "glClipPlanexOES");
    context->Color4xOES = (PFNGLCOLOR4XOESPROC) load(userptr, "glColor4xOES");
    context->DepthRangexOES = (PFNGLDEPTHRANGEXOESPROC) load(userptr, "glDepthRangexOES");
    context->FogxOES = (PFNGLFOGXOESPROC) load(userptr, "glFogxOES");
    context->FogxvOES = (PFNGLFOGXVOESPROC) load(userptr, "glFogxvOES");
    context->FrustumxOES = (PFNGLFRUSTUMXOESPROC) load(userptr, "glFrustumxOES");
    context->GetClipPlanexOES = (PFNGLGETCLIPPLANEXOESPROC) load(userptr, "glGetClipPlanexOES");
    context->GetFixedvOES = (PFNGLGETFIXEDVOESPROC) load(userptr, "glGetFixedvOES");
    context->GetLightxvOES = (PFNGLGETLIGHTXVOESPROC) load(userptr, "glGetLightxvOES");
    context->GetMaterialxvOES = (PFNGLGETMATERIALXVOESPROC) load(userptr, "glGetMaterialxvOES");
    context->GetTexEnvxvOES = (PFNGLGETTEXENVXVOESPROC) load(userptr, "glGetTexEnvxvOES");
    context->GetTexParameterxvOES = (PFNGLGETTEXPARAMETERXVOESPROC) load(userptr, "glGetTexParameterxvOES");
    context->LightModelxOES = (PFNGLLIGHTMODELXOESPROC) load(userptr, "glLightModelxOES");
    context->LightModelxvOES = (PFNGLLIGHTMODELXVOESPROC) load(userptr, "glLightModelxvOES");
    context->LightxOES = (PFNGLLIGHTXOESPROC) load(userptr, "glLightxOES");
    context->LightxvOES = (PFNGLLIGHTXVOESPROC) load(userptr, "glLightxvOES");
    context->LineWidthxOES = (PFNGLLINEWIDTHXOESPROC) load(userptr, "glLineWidthxOES");
    context->LoadMatrixxOES = (PFNGLLOADMATRIXXOESPROC) load(userptr, "glLoadMatrixxOES");
    context->MaterialxOES = (PFNGLMATERIALXOESPROC) load(userptr, "glMaterialxOES");
    context->MaterialxvOES = (PFNGLMATERIALXVOESPROC) load(userptr, "glMaterialxvOES");
    context->MultMatrixxOES = (PFNGLMULTMATRIXXOESPROC) load(userptr, "glMultMatrixxOES");
    context->MultiTexCoord4xOES = (PFNGLMULTITEXCOORD4XOESPROC) load(userptr, "glMultiTexCoord4xOES");
    context->Normal3xOES = (PFNGLNORMAL3XOESPROC) load(userptr, "glNormal3xOES");
    context->OrthoxOES = (PFNGLORTHOXOESPROC) load(userptr, "glOrthoxOES");
    context->PointParameterxOES = (PFNGLPOINTPARAMETERXOESPROC) load(userptr, "glPointParameterxOES");
    context->PointParameterxvOES = (PFNGLPOINTPARAMETERXVOESPROC) load(userptr, "glPointParameterxvOES");
    context->PointSizexOES = (PFNGLPOINTSIZEXOESPROC) load(userptr, "glPointSizexOES");
    context->PolygonOffsetxOES = (PFNGLPOLYGONOFFSETXOESPROC) load(userptr, "glPolygonOffsetxOES");
    context->RotatexOES = (PFNGLROTATEXOESPROC) load(userptr, "glRotatexOES");
    context->SampleCoveragexOES = (PFNGLSAMPLECOVERAGEXOESPROC) load(userptr, "glSampleCoveragexOES");
    context->ScalexOES = (PFNGLSCALEXOESPROC) load(userptr, "glScalexOES");
    context->TexEnvxOES = (PFNGLTEXENVXOESPROC) load(userptr, "glTexEnvxOES");
    context->TexEnvxvOES = (PFNGLTEXENVXVOESPROC) load(userptr, "glTexEnvxvOES");
    context->TexParameterxOES = (PFNGLTEXPARAMETERXOESPROC) load(userptr, "glTexParameterxOES");
    context->TexParameterxvOES = (PFNGLTEXPARAMETERXVOESPROC) load(userptr, "glTexParameterxvOES");
    context->TranslatexOES = (PFNGLTRANSLATEXOESPROC) load(userptr, "glTranslatexOES");
}
static void glad_gl_load_GL_OES_framebuffer_object(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_framebuffer_object) return;
    context->BindFramebufferOES = (PFNGLBINDFRAMEBUFFEROESPROC) load(userptr, "glBindFramebufferOES");
    context->BindRenderbufferOES = (PFNGLBINDRENDERBUFFEROESPROC) load(userptr, "glBindRenderbufferOES");
    context->CheckFramebufferStatusOES = (PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) load(userptr, "glCheckFramebufferStatusOES");
    context->DeleteFramebuffersOES = (PFNGLDELETEFRAMEBUFFERSOESPROC) load(userptr, "glDeleteFramebuffersOES");
    context->DeleteRenderbuffersOES = (PFNGLDELETERENDERBUFFERSOESPROC) load(userptr, "glDeleteRenderbuffersOES");
    context->FramebufferRenderbufferOES = (PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) load(userptr, "glFramebufferRenderbufferOES");
    context->FramebufferTexture2DOES = (PFNGLFRAMEBUFFERTEXTURE2DOESPROC) load(userptr, "glFramebufferTexture2DOES");
    context->GenFramebuffersOES = (PFNGLGENFRAMEBUFFERSOESPROC) load(userptr, "glGenFramebuffersOES");
    context->GenRenderbuffersOES = (PFNGLGENRENDERBUFFERSOESPROC) load(userptr, "glGenRenderbuffersOES");
    context->GenerateMipmapOES = (PFNGLGENERATEMIPMAPOESPROC) load(userptr, "glGenerateMipmapOES");
    context->GetFramebufferAttachmentParameterivOES = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) load(userptr, "glGetFramebufferAttachmentParameterivOES");
    context->GetRenderbufferParameterivOES = (PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) load(userptr, "glGetRenderbufferParameterivOES");
    context->IsFramebufferOES = (PFNGLISFRAMEBUFFEROESPROC) load(userptr, "glIsFramebufferOES");
    context->IsRenderbufferOES = (PFNGLISRENDERBUFFEROESPROC) load(userptr, "glIsRenderbufferOES");
    context->RenderbufferStorageOES = (PFNGLRENDERBUFFERSTORAGEOESPROC) load(userptr, "glRenderbufferStorageOES");
}
static void glad_gl_load_GL_OES_mapbuffer(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_mapbuffer) return;
    context->GetBufferPointervOES = (PFNGLGETBUFFERPOINTERVOESPROC) load(userptr, "glGetBufferPointervOES");
    context->MapBufferOES = (PFNGLMAPBUFFEROESPROC) load(userptr, "glMapBufferOES");
    context->UnmapBufferOES = (PFNGLUNMAPBUFFEROESPROC) load(userptr, "glUnmapBufferOES");
}
static void glad_gl_load_GL_OES_matrix_palette(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_matrix_palette) return;
    context->CurrentPaletteMatrixOES = (PFNGLCURRENTPALETTEMATRIXOESPROC) load(userptr, "glCurrentPaletteMatrixOES");
    context->LoadPaletteFromModelViewMatrixOES = (PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) load(userptr, "glLoadPaletteFromModelViewMatrixOES");
    context->MatrixIndexPointerOES = (PFNGLMATRIXINDEXPOINTEROESPROC) load(userptr, "glMatrixIndexPointerOES");
    context->WeightPointerOES = (PFNGLWEIGHTPOINTEROESPROC) load(userptr, "glWeightPointerOES");
}
static void glad_gl_load_GL_OES_point_size_array(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_point_size_array) return;
    context->PointSizePointerOES = (PFNGLPOINTSIZEPOINTEROESPROC) load(userptr, "glPointSizePointerOES");
}
static void glad_gl_load_GL_OES_query_matrix(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_query_matrix) return;
    context->QueryMatrixxOES = (PFNGLQUERYMATRIXXOESPROC) load(userptr, "glQueryMatrixxOES");
}
static void glad_gl_load_GL_OES_single_precision(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_single_precision) return;
    context->ClearDepthfOES = (PFNGLCLEARDEPTHFOESPROC) load(userptr, "glClearDepthfOES");
    context->ClipPlanefOES = (PFNGLCLIPPLANEFOESPROC) load(userptr, "glClipPlanefOES");
    context->DepthRangefOES = (PFNGLDEPTHRANGEFOESPROC) load(userptr, "glDepthRangefOES");
    context->FrustumfOES = (PFNGLFRUSTUMFOESPROC) load(userptr, "glFrustumfOES");
    context->GetClipPlanefOES = (PFNGLGETCLIPPLANEFOESPROC) load(userptr, "glGetClipPlanefOES");
    context->OrthofOES = (PFNGLORTHOFOESPROC) load(userptr, "glOrthofOES");
}
static void glad_gl_load_GL_OES_texture_cube_map(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_texture_cube_map) return;
    context->GetTexGenfvOES = (PFNGLGETTEXGENFVOESPROC) load(userptr, "glGetTexGenfvOES");
    context->GetTexGenivOES = (PFNGLGETTEXGENIVOESPROC) load(userptr, "glGetTexGenivOES");
    context->GetTexGenxvOES = (PFNGLGETTEXGENXVOESPROC) load(userptr, "glGetTexGenxvOES");
    context->TexGenfOES = (PFNGLTEXGENFOESPROC) load(userptr, "glTexGenfOES");
    context->TexGenfvOES = (PFNGLTEXGENFVOESPROC) load(userptr, "glTexGenfvOES");
    context->TexGeniOES = (PFNGLTEXGENIOESPROC) load(userptr, "glTexGeniOES");
    context->TexGenivOES = (PFNGLTEXGENIVOESPROC) load(userptr, "glTexGenivOES");
    context->TexGenxOES = (PFNGLTEXGENXOESPROC) load(userptr, "glTexGenxOES");
    context->TexGenxvOES = (PFNGLTEXGENXVOESPROC) load(userptr, "glTexGenxvOES");
}
static void glad_gl_load_GL_OES_vertex_array_object(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_vertex_array_object) return;
    context->BindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC) load(userptr, "glBindVertexArrayOES");
    context->DeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC) load(userptr, "glDeleteVertexArraysOES");
    context->GenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC) load(userptr, "glGenVertexArraysOES");
    context->IsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC) load(userptr, "glIsVertexArrayOES");
}
static void glad_gl_load_GL_QCOM_driver_control(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_driver_control) return;
    context->DisableDriverControlQCOM = (PFNGLDISABLEDRIVERCONTROLQCOMPROC) load(userptr, "glDisableDriverControlQCOM");
    context->EnableDriverControlQCOM = (PFNGLENABLEDRIVERCONTROLQCOMPROC) load(userptr, "glEnableDriverControlQCOM");
    context->GetDriverControlStringQCOM = (PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) load(userptr, "glGetDriverControlStringQCOM");
    context->GetDriverControlsQCOM = (PFNGLGETDRIVERCONTROLSQCOMPROC) load(userptr, "glGetDriverControlsQCOM");
}
static void glad_gl_load_GL_QCOM_extended_get(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_extended_get) return;
    context->ExtGetBufferPointervQCOM = (PFNGLEXTGETBUFFERPOINTERVQCOMPROC) load(userptr, "glExtGetBufferPointervQCOM");
    context->ExtGetBuffersQCOM = (PFNGLEXTGETBUFFERSQCOMPROC) load(userptr, "glExtGetBuffersQCOM");
    context->ExtGetFramebuffersQCOM = (PFNGLEXTGETFRAMEBUFFERSQCOMPROC) load(userptr, "glExtGetFramebuffersQCOM");
    context->ExtGetRenderbuffersQCOM = (PFNGLEXTGETRENDERBUFFERSQCOMPROC) load(userptr, "glExtGetRenderbuffersQCOM");
    context->ExtGetTexLevelParameterivQCOM = (PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) load(userptr, "glExtGetTexLevelParameterivQCOM");
    context->ExtGetTexSubImageQCOM = (PFNGLEXTGETTEXSUBIMAGEQCOMPROC) load(userptr, "glExtGetTexSubImageQCOM");
    context->ExtGetTexturesQCOM = (PFNGLEXTGETTEXTURESQCOMPROC) load(userptr, "glExtGetTexturesQCOM");
    context->ExtTexObjectStateOverrideiQCOM = (PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) load(userptr, "glExtTexObjectStateOverrideiQCOM");
}
static void glad_gl_load_GL_QCOM_extended_get2(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_extended_get2) return;
    context->ExtGetProgramBinarySourceQCOM = (PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) load(userptr, "glExtGetProgramBinarySourceQCOM");
    context->ExtGetProgramsQCOM = (PFNGLEXTGETPROGRAMSQCOMPROC) load(userptr, "glExtGetProgramsQCOM");
    context->ExtGetShadersQCOM = (PFNGLEXTGETSHADERSQCOMPROC) load(userptr, "glExtGetShadersQCOM");
    context->ExtIsProgramBinaryQCOM = (PFNGLEXTISPROGRAMBINARYQCOMPROC) load(userptr, "glExtIsProgramBinaryQCOM");
}
static void glad_gl_load_GL_QCOM_tiled_rendering(GladGLES1Context *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_tiled_rendering) return;
    context->EndTilingQCOM = (PFNGLENDTILINGQCOMPROC) load(userptr, "glEndTilingQCOM");
    context->StartTilingQCOM = (PFNGLSTARTTILINGQCOMPROC) load(userptr, "glStartTilingQCOM");
}



static void glad_gl_free_extensions(char **exts_i) {
    if (exts_i != NULL) {
        unsigned int index;
        for(index = 0; exts_i[index]; index++) {
            free((void *) (exts_i[index]));
        }
        free((void *)exts_i);
        exts_i = NULL;
    }
}
static int glad_gl_get_extensions(GladGLES1Context *context, const char **out_exts, char ***out_exts_i) {
#if defined(GL_ES_VERSION_3_0) || defined(GL_VERSION_3_0)
    if (context->GetStringi != NULL && context->GetIntegerv != NULL) {
        unsigned int index = 0;
        unsigned int num_exts_i = 0;
        char **exts_i = NULL;
        context->GetIntegerv(GL_NUM_EXTENSIONS, (int*) &num_exts_i);
        exts_i = (char **) malloc((num_exts_i + 1) * (sizeof *exts_i));
        if (exts_i == NULL) {
            return 0;
        }
        for(index = 0; index < num_exts_i; index++) {
            const char *gl_str_tmp = (const char*) context->GetStringi(GL_EXTENSIONS, index);
            size_t len = strlen(gl_str_tmp) + 1;

            char *local_str = (char*) malloc(len * sizeof(char));
            if(local_str == NULL) {
                exts_i[index] = NULL;
                glad_gl_free_extensions(exts_i);
                return 0;
            }

            memcpy(local_str, gl_str_tmp, len * sizeof(char));
            exts_i[index] = local_str;
        }
        exts_i[index] = NULL;

        *out_exts_i = exts_i;

        return 1;
    }
#else
    GLAD_UNUSED(out_exts_i);
#endif
    if (context->GetString == NULL) {
        return 0;
    }
    *out_exts = (const char *)context->GetString(GL_EXTENSIONS);
    return 1;
}
static int glad_gl_has_extension(const char *exts, char **exts_i, const char *ext) {
    if(exts_i) {
        unsigned int index;
        for(index = 0; exts_i[index]; index++) {
            const char *e = exts_i[index];
            if(strcmp(e, ext) == 0) {
                return 1;
            }
        }
    } else {
        const char *extensions;
        const char *loc;
        const char *terminator;
        extensions = exts;
        if(extensions == NULL || ext == NULL) {
            return 0;
        }
        while(1) {
            loc = strstr(extensions, ext);
            if(loc == NULL) {
                return 0;
            }
            terminator = loc + strlen(ext);
            if((loc == extensions || *(loc - 1) == ' ') &&
                (*terminator == ' ' || *terminator == '\0')) {
                return 1;
            }
            extensions = terminator;
        }
    }
    return 0;
}

static GLADapiproc glad_gl_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_gl_find_extensions_gles1(GladGLES1Context *context) {
    const char *exts = NULL;
    char **exts_i = NULL;
    if (!glad_gl_get_extensions(context, &exts, &exts_i)) return 0;

    context->AMD_compressed_3DC_texture = glad_gl_has_extension(exts, exts_i, "GL_AMD_compressed_3DC_texture");
    context->AMD_compressed_ATC_texture = glad_gl_has_extension(exts, exts_i, "GL_AMD_compressed_ATC_texture");
    context->APPLE_copy_texture_levels = glad_gl_has_extension(exts, exts_i, "GL_APPLE_copy_texture_levels");
    context->APPLE_framebuffer_multisample = glad_gl_has_extension(exts, exts_i, "GL_APPLE_framebuffer_multisample");
    context->APPLE_sync = glad_gl_has_extension(exts, exts_i, "GL_APPLE_sync");
    context->APPLE_texture_2D_limited_npot = glad_gl_has_extension(exts, exts_i, "GL_APPLE_texture_2D_limited_npot");
    context->APPLE_texture_format_BGRA8888 = glad_gl_has_extension(exts, exts_i, "GL_APPLE_texture_format_BGRA8888");
    context->APPLE_texture_max_level = glad_gl_has_extension(exts, exts_i, "GL_APPLE_texture_max_level");
    context->ARM_rgba8 = glad_gl_has_extension(exts, exts_i, "GL_ARM_rgba8");
    context->EXT_blend_minmax = glad_gl_has_extension(exts, exts_i, "GL_EXT_blend_minmax");
    context->EXT_debug_marker = glad_gl_has_extension(exts, exts_i, "GL_EXT_debug_marker");
    context->EXT_discard_framebuffer = glad_gl_has_extension(exts, exts_i, "GL_EXT_discard_framebuffer");
    context->EXT_map_buffer_range = glad_gl_has_extension(exts, exts_i, "GL_EXT_map_buffer_range");
    context->EXT_multi_draw_arrays = glad_gl_has_extension(exts, exts_i, "GL_EXT_multi_draw_arrays");
    context->EXT_multisampled_render_to_texture = glad_gl_has_extension(exts, exts_i, "GL_EXT_multisampled_render_to_texture");
    context->EXT_read_format_bgra = glad_gl_has_extension(exts, exts_i, "GL_EXT_read_format_bgra");
    context->EXT_robustness = glad_gl_has_extension(exts, exts_i, "GL_EXT_robustness");
    context->EXT_sRGB = glad_gl_has_extension(exts, exts_i, "GL_EXT_sRGB");
    context->EXT_texture_compression_dxt1 = glad_gl_has_extension(exts, exts_i, "GL_EXT_texture_compression_dxt1");
    context->EXT_texture_filter_anisotropic = glad_gl_has_extension(exts, exts_i, "GL_EXT_texture_filter_anisotropic");
    context->EXT_texture_format_BGRA8888 = glad_gl_has_extension(exts, exts_i, "GL_EXT_texture_format_BGRA8888");
    context->EXT_texture_lod_bias = glad_gl_has_extension(exts, exts_i, "GL_EXT_texture_lod_bias");
    context->EXT_texture_storage = glad_gl_has_extension(exts, exts_i, "GL_EXT_texture_storage");
    context->IMG_multisampled_render_to_texture = glad_gl_has_extension(exts, exts_i, "GL_IMG_multisampled_render_to_texture");
    context->IMG_read_format = glad_gl_has_extension(exts, exts_i, "GL_IMG_read_format");
    context->IMG_texture_compression_pvrtc = glad_gl_has_extension(exts, exts_i, "GL_IMG_texture_compression_pvrtc");
    context->IMG_texture_env_enhanced_fixed_function = glad_gl_has_extension(exts, exts_i, "GL_IMG_texture_env_enhanced_fixed_function");
    context->IMG_user_clip_plane = glad_gl_has_extension(exts, exts_i, "GL_IMG_user_clip_plane");
    context->KHR_debug = glad_gl_has_extension(exts, exts_i, "GL_KHR_debug");
    context->NV_fence = glad_gl_has_extension(exts, exts_i, "GL_NV_fence");
    context->OES_EGL_image = glad_gl_has_extension(exts, exts_i, "GL_OES_EGL_image");
    context->OES_EGL_image_external = glad_gl_has_extension(exts, exts_i, "GL_OES_EGL_image_external");
    context->OES_blend_equation_separate = glad_gl_has_extension(exts, exts_i, "GL_OES_blend_equation_separate");
    context->OES_blend_func_separate = glad_gl_has_extension(exts, exts_i, "GL_OES_blend_func_separate");
    context->OES_blend_subtract = glad_gl_has_extension(exts, exts_i, "GL_OES_blend_subtract");
    context->OES_byte_coordinates = glad_gl_has_extension(exts, exts_i, "GL_OES_byte_coordinates");
    context->OES_compressed_ETC1_RGB8_sub_texture = glad_gl_has_extension(exts, exts_i, "GL_OES_compressed_ETC1_RGB8_sub_texture");
    context->OES_compressed_ETC1_RGB8_texture = glad_gl_has_extension(exts, exts_i, "GL_OES_compressed_ETC1_RGB8_texture");
    context->OES_compressed_paletted_texture = glad_gl_has_extension(exts, exts_i, "GL_OES_compressed_paletted_texture");
    context->OES_depth24 = glad_gl_has_extension(exts, exts_i, "GL_OES_depth24");
    context->OES_depth32 = glad_gl_has_extension(exts, exts_i, "GL_OES_depth32");
    context->OES_draw_texture = glad_gl_has_extension(exts, exts_i, "GL_OES_draw_texture");
    context->OES_element_index_uint = glad_gl_has_extension(exts, exts_i, "GL_OES_element_index_uint");
    context->OES_extended_matrix_palette = glad_gl_has_extension(exts, exts_i, "GL_OES_extended_matrix_palette");
    context->OES_fbo_render_mipmap = glad_gl_has_extension(exts, exts_i, "GL_OES_fbo_render_mipmap");
    context->OES_fixed_point = glad_gl_has_extension(exts, exts_i, "GL_OES_fixed_point");
    context->OES_framebuffer_object = glad_gl_has_extension(exts, exts_i, "GL_OES_framebuffer_object");
    context->OES_mapbuffer = glad_gl_has_extension(exts, exts_i, "GL_OES_mapbuffer");
    context->OES_matrix_get = glad_gl_has_extension(exts, exts_i, "GL_OES_matrix_get");
    context->OES_matrix_palette = glad_gl_has_extension(exts, exts_i, "GL_OES_matrix_palette");
    context->OES_packed_depth_stencil = glad_gl_has_extension(exts, exts_i, "GL_OES_packed_depth_stencil");
    context->OES_point_size_array = glad_gl_has_extension(exts, exts_i, "GL_OES_point_size_array");
    context->OES_point_sprite = glad_gl_has_extension(exts, exts_i, "GL_OES_point_sprite");
    context->OES_query_matrix = glad_gl_has_extension(exts, exts_i, "GL_OES_query_matrix");
    context->OES_read_format = glad_gl_has_extension(exts, exts_i, "GL_OES_read_format");
    context->OES_required_internalformat = glad_gl_has_extension(exts, exts_i, "GL_OES_required_internalformat");
    context->OES_rgb8_rgba8 = glad_gl_has_extension(exts, exts_i, "GL_OES_rgb8_rgba8");
    context->OES_single_precision = glad_gl_has_extension(exts, exts_i, "GL_OES_single_precision");
    context->OES_stencil1 = glad_gl_has_extension(exts, exts_i, "GL_OES_stencil1");
    context->OES_stencil4 = glad_gl_has_extension(exts, exts_i, "GL_OES_stencil4");
    context->OES_stencil8 = glad_gl_has_extension(exts, exts_i, "GL_OES_stencil8");
    context->OES_stencil_wrap = glad_gl_has_extension(exts, exts_i, "GL_OES_stencil_wrap");
    context->OES_surfaceless_context = glad_gl_has_extension(exts, exts_i, "GL_OES_surfaceless_context");
    context->OES_texture_cube_map = glad_gl_has_extension(exts, exts_i, "GL_OES_texture_cube_map");
    context->OES_texture_env_crossbar = glad_gl_has_extension(exts, exts_i, "GL_OES_texture_env_crossbar");
    context->OES_texture_mirrored_repeat = glad_gl_has_extension(exts, exts_i, "GL_OES_texture_mirrored_repeat");
    context->OES_texture_npot = glad_gl_has_extension(exts, exts_i, "GL_OES_texture_npot");
    context->OES_vertex_array_object = glad_gl_has_extension(exts, exts_i, "GL_OES_vertex_array_object");
    context->QCOM_driver_control = glad_gl_has_extension(exts, exts_i, "GL_QCOM_driver_control");
    context->QCOM_extended_get = glad_gl_has_extension(exts, exts_i, "GL_QCOM_extended_get");
    context->QCOM_extended_get2 = glad_gl_has_extension(exts, exts_i, "GL_QCOM_extended_get2");
    context->QCOM_perfmon_global_mode = glad_gl_has_extension(exts, exts_i, "GL_QCOM_perfmon_global_mode");
    context->QCOM_tiled_rendering = glad_gl_has_extension(exts, exts_i, "GL_QCOM_tiled_rendering");
    context->QCOM_writeonly_rendering = glad_gl_has_extension(exts, exts_i, "GL_QCOM_writeonly_rendering");

    glad_gl_free_extensions(exts_i);

    return 1;
}

static int glad_gl_find_core_gles1(GladGLES1Context *context) {
    int i;
    const char* version;
    const char* prefixes[] = {
        "OpenGL ES-CM ",
        "OpenGL ES-CL ",
        "OpenGL ES ",
        "OpenGL SC ",
        NULL
    };
    int major = 0;
    int minor = 0;
    version = (const char*) context->GetString(GL_VERSION);
    if (!version) return 0;
    for (i = 0;  prefixes[i];  i++) {
        const size_t length = strlen(prefixes[i]);
        if (strncmp(version, prefixes[i], length) == 0) {
            version += length;
            break;
        }
    }

    GLAD_IMPL_UTIL_SSCANF(version, "%d.%d", &major, &minor);

    context->VERSION_ES_CM_1_0 = (major == 1 && minor >= 0) || major > 1;

    return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadGLES1ContextUserPtr(GladGLES1Context *context, GLADuserptrloadfunc load, void *userptr) {
    int version;

    context->GetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    if(context->GetString == NULL) return 0;
    version = glad_gl_find_core_gles1(context);

    glad_gl_load_GL_VERSION_ES_CM_1_0(context, load, userptr);

    if (!glad_gl_find_extensions_gles1(context)) return 0;
    glad_gl_load_GL_APPLE_copy_texture_levels(context, load, userptr);
    glad_gl_load_GL_APPLE_framebuffer_multisample(context, load, userptr);
    glad_gl_load_GL_APPLE_sync(context, load, userptr);
    glad_gl_load_GL_EXT_debug_marker(context, load, userptr);
    glad_gl_load_GL_EXT_discard_framebuffer(context, load, userptr);
    glad_gl_load_GL_EXT_map_buffer_range(context, load, userptr);
    glad_gl_load_GL_EXT_multi_draw_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_multisampled_render_to_texture(context, load, userptr);
    glad_gl_load_GL_EXT_robustness(context, load, userptr);
    glad_gl_load_GL_EXT_texture_storage(context, load, userptr);
    glad_gl_load_GL_IMG_multisampled_render_to_texture(context, load, userptr);
    glad_gl_load_GL_IMG_user_clip_plane(context, load, userptr);
    glad_gl_load_GL_NV_fence(context, load, userptr);
    glad_gl_load_GL_OES_EGL_image(context, load, userptr);
    glad_gl_load_GL_OES_blend_equation_separate(context, load, userptr);
    glad_gl_load_GL_OES_blend_func_separate(context, load, userptr);
    glad_gl_load_GL_OES_blend_subtract(context, load, userptr);
    glad_gl_load_GL_OES_draw_texture(context, load, userptr);
    glad_gl_load_GL_OES_fixed_point(context, load, userptr);
    glad_gl_load_GL_OES_framebuffer_object(context, load, userptr);
    glad_gl_load_GL_OES_mapbuffer(context, load, userptr);
    glad_gl_load_GL_OES_matrix_palette(context, load, userptr);
    glad_gl_load_GL_OES_point_size_array(context, load, userptr);
    glad_gl_load_GL_OES_query_matrix(context, load, userptr);
    glad_gl_load_GL_OES_single_precision(context, load, userptr);
    glad_gl_load_GL_OES_texture_cube_map(context, load, userptr);
    glad_gl_load_GL_OES_vertex_array_object(context, load, userptr);
    glad_gl_load_GL_QCOM_driver_control(context, load, userptr);
    glad_gl_load_GL_QCOM_extended_get(context, load, userptr);
    glad_gl_load_GL_QCOM_extended_get2(context, load, userptr);
    glad_gl_load_GL_QCOM_tiled_rendering(context, load, userptr);



    return version;
}


int gladLoadGLES1Context(GladGLES1Context *context, GLADloadfunc load) {
    return gladLoadGLES1ContextUserPtr(context, glad_gl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}



 


#ifdef __cplusplus
}
#endif
