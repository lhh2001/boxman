#include "Sequence/Parent.h"
#include "Boxman.h"
#include "StringRenderer.h"
#include "GameLib/Framework.h"
#include <sstream>

using namespace GameLib;

Sequence::Parent* rootSequence = nullptr;

namespace GameLib
{
	void Framework::update()
	{
        if (!rootSequence)
        {
            rootSequence = new Sequence::Parent();
            StringRenderer::create("fonts/font.dds");
        }
        rootSequence->update();
        StringRenderer::getInstance()->draw(33, 0, ("FPS:" + std::to_string(frameRate())).c_str());
        if (isKeyOn('q'))
        {
            requestEnd();
        }
        if (isEndRequested())
        {
            SAFE_DELETE(rootSequence);
            StringRenderer::destroy();
        }
	}
}
