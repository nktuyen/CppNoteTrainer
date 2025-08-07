#pragma once
#include "afxwin.h"
#include <mmeapi.h>

class CMidiInputThread : public CWinThread
{
public:
	CMidiInputThread(HMIDIIN hInputDevice, HMIDIOUT hOutputDevice = NULL);
	virtual ~CMidiInputThread(void);
	void Stop();
	BOOL IsRunning();
protected:
	BOOL InitInstance() override;
	int Run() override;
private:
	void SetRunning(BOOL bRun);
private:
	BOOL m_bRunning;
	CMutex m_Mutex;
	HMIDIIN m_hMidiInputDevice;
	HMIDIOUT m_hMidiOutputDevice;
};

