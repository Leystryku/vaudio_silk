#ifndef VOICE_H
#define VOICE_H

#define BYTES_PER_SAMPLE		2
#define MAX_FRAMEBUFFER_SAMPLES	2048

class Voice
{
public:
	Voice();
	virtual ~Voice() {}

	virtual bool Init(int quality = 4) { return true; }
	virtual void Release() { delete this; }

	virtual int Compress(const char *pUncompressedBytes, int nSamples, char *pCompressed, int maxCompressedBytes, bool bFinal = true);
	virtual int Decompress(const char *pCompressed, int compressedBytes, char *pUncompressed, int maxUncompressedBytes);

	virtual bool ResetState() = 0;
protected:
	virtual void DecodeFrame(const char *pCompressed, char *pDecompressedBytes) = 0;
	virtual void EncodeFrame(const char *pUncompressedBytes, char *pCompressed) = 0;
	

protected:
	int m_Quality;
	void *m_EncoderState;
	void *m_DecoderState;

	short m_EncodeBuffer[MAX_FRAMEBUFFER_SAMPLES];
	int m_nEncodeBufferSamples;
	int m_nRawBytes;
	int m_nRawSamples;
	int m_nEncodedBytes;
};



class VoiceCodec
{
public:
	virtual ~VoiceCodec() {}

	// Initialize the object. The uncompressed format is always 8-bit signed mono.
	virtual bool	Init(int quality);

	// Use this to delete the object.
	virtual void	Release();


	// Compress the voice data.
	// pUncompressed		-	16-bit signed mono voice data.
	// maxCompressedBytes	-	The length of the pCompressed buffer. Don't exceed this.
	// bFinal        		-	Set to true on the last call to Compress (the user stopped talking).
	//							Some codecs like big block sizes and will hang onto data you give them in Compress calls.
	//							When you call with bFinal, the codec will give you compressed data no matter what.
	// Return the number of bytes you filled into pCompressed.
	virtual int		Compress(const char *pUncompressed, int nSamples, char *pCompressed, int maxCompressedBytes, bool bFinal);

	// Decompress voice data. pUncompressed is 16-bit signed mono.
	virtual int		Decompress(const char *pCompressed, int compressedBytes, char *pUncompressed, int maxUncompressedBytes);

	// Some codecs maintain state between Compress and Decompress calls. This should clear that state.
	virtual bool	ResetState();
private:
	Voice *silk;

};

#endif // VOICE_H
