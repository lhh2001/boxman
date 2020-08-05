#include "GameLib/Framework.h"
#include "Sequence/Parent.h"
#include "Boxman.h"

using namespace GameLib;

Sequence::Parent* rootSequence = nullptr;
int cnt = 0;

namespace GameLib
{
	void Framework::update()
	{
        if (!rootSequence)
        {
            rootSequence = new Sequence::Parent();
        }

        if (cnt >= 60)
        {
            cnt = 0;
            cout << " FrameRate:" << frameRate() << endl;
        }
        cnt++;
        rootSequence->update();
        if (isKeyOn('q'))
        {
            requestEnd();
        }
        if (isEndRequested())
        {
            SAFE_DELETE(rootSequence);
        }
	}
}
