#include "System.h"

System::System()
{
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
			fprintf(stderr, "Unable to init SDL: %s\n",
					SDL_GetError());
			exit(1);
	}
}

System::~System()
{
	SDL_Quit();
}

int System::Init()
{
	nFPS=0;
	return true;
}
void System::Run()
{
	if(!_private_FrameFunc) {
		Log("System::Run: No frame function defined");
		return;
	}

	bActive=true;
	float fTime=0.0f;
	float t0fps, cfps;
	float t0=t0fps=SDL_GetTicks();
	float dt=cfps=0;
	float fDeltaTime;
	float nFixedDelta;
	int nLastTime=SDL_GetTicks();

	// MAIN LOOP

	for(;;)
	{

		// If HGE window is focused or we have the "don't suspend" state - process the main loop
		if(bActive)
		{
			// Ensure we have at least 1ms time step
			// to not confuse user's code with 0

			do { dt=SDL_GetTicks() - t0; } while(dt < 1);

			// If we reached the time for the next frame
			// or we just run in unlimited FPS mode, then
			// do the stuff

			frameTime = (float)(SDL_GetTicks() - nLastTime)/1000.0f;
			nLastTime = SDL_GetTicks();

			if(dt >= nFixedDelta)
			{
				// fDeltaTime = time step in seconds returned by Timer_GetDelta

				fDeltaTime=dt/1000.0f;

				// Cap too large time steps usually caused by lost focus to avoid jerks
				if(fDeltaTime > 0.2f)
				{
					fDeltaTime = nFixedDelta ? nFixedDelta/1000.0f : 0.01f;
				}

				// Update time counter returned Timer_GetTime

				fTime += fDeltaTime;

				// Store current time for the next frame
				// and count FPS

				t0=SDL_GetTicks();
				if(t0-t0fps <= 1000.0f) cfps++;
				else
				{
					nFPS=(int)cfps; cfps=0; t0fps=t0;
					Log("FPS: %i", nFPS);
				}

				// Do user's stuff

				if(!_private_FrameFunc->_FrameFunc()) break;

				// If we use VSYNC - we could afford a little
				// sleep to lower CPU usage

				// if(!bWindowed && nHGEFPS==HGEFPS_VSYNC) Sleep(1);
			}

			// If we have a fixed frame rate and the time
			// for the next frame isn't too close, sleep a bit

			else
			{
				if(nFixedDelta && dt+3 < nFixedDelta) Sleep(1);
			}
		}

		// If main loop is suspended - just sleep a bit
		// (though not too much to allow instant window
		// redraw if requested by OS)

		else Sleep(1);
	}
	bActive=false;
	return;
}
int System::FPS()
{
	return nFPS;
}
float System::getFrameTime()
{
	return frameTime;
}
void System::End()
{

}
void System::SetFrameFunc(SysCallBack* frameFunc)
{
	_private_FrameFunc = frameFunc;
}
void System::Sleep(int count)
{
	SDL_Delay(count);
}
void System::Log(char* format,...)
{
	char _strbuf[256];
	///create va_list and load all arguments
	va_list ap;
	va_start(ap, format);
	vsprintf(_strbuf,format, ap); /// Call vprintf
	va_end(ap); /// Cleanup the va_list
	fprintf(stdout,"%s\n",_strbuf);
	fflush(stdout);
}
