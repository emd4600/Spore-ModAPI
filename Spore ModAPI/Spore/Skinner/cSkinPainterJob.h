#pragma once

#include <Spore\Graphics\ILayer.h>
#include <Spore\Object.h>

#define cSkinPainterJobPtr eastl::intrusive_ptr<Skinner::cSkinPainterJob>

namespace Skinner
{
	/// Base class for tasks executed in the process of generating a skinpaint texture.
	/// Since the graphics renderer is needed, the process is broken down into small tasks that get executed
	/// at the end of each frame.
	/// The only method subclasses have to change is SkinPainterTask::Execute().
	/// The process continues if Execute() returns true; if it returns false, it will repeat executing until it returns true.
	class cSkinPainterJob
		: public Graphics::ILayer
		, public RefCountTemplateAtomic
	{
	public:
		cSkinPainterJob();
		virtual int AddRef() override;
		virtual int Release() override;

		virtual void DrawLayer(int flags, int layerIndex, App::cViewer** viewers, Graphics::RenderStatistics& statistics) override;

		/// If `mHasFinished` is false, it adds this task as a post-render job (with budget 10) in the Renderer
		/* 10h */	virtual void Initialize();

		/// Executes the main function of this task. Returns true if the task finished and the process must continue;
		/// false if the task didn't finish, and has to be executed again.
		/* 14h */	virtual bool Execute();

	public:
		/* 0Ch */	bool mHasFinished;
	};
	ASSERT_SIZE(cSkinPainterJob, 0x10);

	namespace Addresses(cSkinPainterJob)
	{
		DeclareAddress(DrawLayer);  // 0x5172C0 TODO
		DeclareAddress(Initialize);  // 0x517420 TODO
	}
}