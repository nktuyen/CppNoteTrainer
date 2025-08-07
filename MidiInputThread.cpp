#include "stdafx.h"
#include "MidiInputThread.h"


CMidiInputThread::CMidiInputThread(HMIDIIN hInputDevice, HMIDIOUT hOutputDevice)
	: CWinThread()
	, m_hMidiInputDevice(hInputDevice)
	, m_hMidiOutputDevice(hOutputDevice)
	, m_bRunning(FALSE)
{
	m_bAutoDelete = FALSE;
}


CMidiInputThread::~CMidiInputThread(void)
{
}

BOOL CMidiInputThread::InitInstance()
{
	CWinThread::InitInstance();

	return TRUE;
}

void CMidiInputThread::SetRunning(BOOL bRun)
{
	CSingleLock locker(&m_Mutex);
	m_bRunning = bRun;
}

BOOL CMidiInputThread::IsRunning()
{
	CSingleLock locker(&m_Mutex);
	BOOL res = m_bRunning;
	return res;
}

void CMidiInputThread::Stop()
{
	CSingleLock locker(&m_Mutex);
	m_bRunning = FALSE;
}

int CMidiInputThread::Run()
{
	SetRunning(TRUE);
	MMRESULT res = MMSYSERR_NOERROR;
	MIDIHDR midiHeader = {0};
	CHAR szData[1024] = {0};
	if(m_hMidiInputDevice != NULL)
	{
		ZeroMemory(&midiHeader, sizeof(MIDIHDR));
		midiHeader.lpData = szData;
		midiHeader.dwBufferLength = 1024;
		res = midiInPrepareHeader(m_hMidiInputDevice, &midiHeader, sizeof(midiHeader));
		if(res == MMSYSERR_NOERROR)
		{
			res = midiInAddBuffer(m_hMidiInputDevice, &midiHeader, sizeof(midiHeader));
		}
		
	}
	SetRunning(FALSE);
	return 0;
}