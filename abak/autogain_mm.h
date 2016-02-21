#ifndef _INCLUDE_METAMOD_SOURCE_PLUGIN_H_
#define _INCLUDE_METAMOD_SOURCE_PLUGIN_H_

#include <ISmmPlugin.h>

#ifndef ARRAYSIZE
#define ARRAYSIZE(x)	((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#endif

#ifdef _WIN32
typedef __int64		int64;
#else
typedef long long	int64;
#endif

#define MAX_PLAYERS		65
#define MAX_SCALE		12.0f	// Ignore sample when being scaled over this amount.
#define IDEAL_GAIN		4000.0f	// 10 ^ (72 dB / 20)
#define SAMPLESPERSEC	11025

class IClient;
class Voice_Silk;
class Voice_Speex;
class CDetour;

class AutoGain : public ISmmPlugin
{
public:
	AutoGain();

public: // ISmmPlugin
	virtual bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	virtual bool Unload(char *error, size_t maxlen);

	virtual const char *GetAuthor()			{ return "GoD-Tony"; }
	virtual const char *GetName()			{ return "AutoGain"; }
	virtual const char *GetDescription()	{ return "Automatic gain control for voice input"; }
	virtual const char *GetURL()			{ return "https://forums.alliedmods.net/showthread.php?t=189527"; }
	virtual const char *GetLicense()		{ return "GPL"; }
	virtual const char *GetVersion()		{ return "2.0.2"; }
	virtual const char *GetDate()			{ return __DATE__; }
	virtual const char *GetLogTag()			{ return "AUTOGAIN"; }

public:
	void OnBroadcastVoiceData(IClient *pClient, int nBytes, char *data);
	void NormalizeClientVoice(int client, char *pVoiceData, int nSamples);

private:
	CDetour *m_VoiceDetour;
	Voice_Silk *m_Silk[MAX_PLAYERS];
	Voice_Speex *m_Speex[MAX_PLAYERS];
};

extern AutoGain g_AutoGain;

PLUGIN_GLOBALVARS();

#endif //_INCLUDE_METAMOD_SOURCE_PLUGIN_H_
