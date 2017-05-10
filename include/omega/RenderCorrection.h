/******************************************************************************
 * THE OMEGA LIB PROJECT
 *-----------------------------------------------------------------------------
 * Copyright 2010-2015		Electronic Visualization Laboratory,
 *							University of Illinois at Chicago
 * Authors:
 *  Alessandro Febretti		febret@gmail.com
 *-----------------------------------------------------------------------------
 * Copyright (c) 2010-2015, Electronic Visualization Laboratory,
 * University of Illinois at Chicago
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer. Redistributions in binary
 * form must reproduce the above copyright notice, this list of conditions and
 * the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *-----------------------------------------------------------------------------
 * What's in this file
 *	A class to store pixels and modify pixels
 ******************************************************************************/
#ifndef __RENDER_CORRECTION_H__
#define __RENDER_CORRECTION_H__

#include "osystem.h"
#include "omega/ApplicationBase.h"
#include "omega/GpuResource.h"
#include "omega/RenderTarget.h"
#include "omega/Texture.h"
#include "omega/WarpMesh.h"
#include "omega/AsyncTask.h"
#include "omega/ImageUtils.h"

namespace omega {
	class Renderer;
	struct DrawContext;

    ////////////////////////////////////////////////////////////////////////////////
    class OMEGA_API WarpCorrection : public ReferenceType
    {
    public:
        WarpCorrection();

        virtual void prepare(Renderer* client, const DrawContext& context);
        virtual void render(Renderer* client, const DrawContext& context);
        virtual void setTileRect(const Rect& tr);
        virtual bool isValid() const;

    private:
        Ref<WarpMeshGeometry> geometry;
    };

    ////////////////////////////////////////////////////////////////////////////////
    class OMEGA_API EdgeBlendCorrection : public ReferenceType
    {
    public:
        EdgeBlendCorrection();

        virtual void prepare(Renderer* client, const DrawContext& context);
        virtual void render(Renderer* client, const DrawContext& context);
        virtual void setTileRect(const Rect& tr);
        virtual bool isValid() const;

    private:
        Ref<ImageUtils::LoadImageAsyncTask> task;

    };

    ///////////////////////////////////////////////////////////////////////////
	class OMEGA_API RenderCorrection : public ReferenceType
	{
    public:

        RenderCorrection();

		void enable();
		void disable();
		bool isEnabled();

		virtual void resize(int width, int height);
        virtual void initialize(Renderer* client, const DrawContext& context);
        virtual void prepare(Renderer* client, const DrawContext& context);
        virtual void bind(Renderer* client, const DrawContext& context);
        virtual void unbind(Renderer* client, const DrawContext& context);
        virtual void render(Renderer* client, const DrawContext& context);
        virtual void setTileRect(const Rect& tr);
        virtual void clear(Renderer* client, const DrawContext& context);

  private:
 	    bool enabled;
		Ref<RenderTarget> readbackTarget;
		Ref<Texture> readbackColorTexture;
		Ref<Texture> readbackDepthTexture;
		Ref<WarpCorrection> warpCorrection;
		Ref<EdgeBlendCorrection> edgeBlendCorrection;
		Rect tileRect;
    };

    ///////////////////////////////////////////////////////////////////////////

}

#endif // __RENDER_CORRECTION_H__
