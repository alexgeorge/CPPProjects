#include <iostream>
#include <string>

class CDecoder
{
public:
	CDecoder(std::string name) { strName = name+"-"; }
	virtual ~CDecoder() {}
	void Show()
	{
		std::cout << "Name:-" << strName << std::endl;
	}

	//pure abstract method. Need overloading
	virtual void SetName(std::string name) = 0;

protected:
	std::string strName;

};

class CVideoDecoder : public virtual CDecoder
{
public:
	CVideoDecoder() : CDecoder("Video") {}
	virtual ~CVideoDecoder() {}
	void Show()
	{
		CDecoder::Show();
	}
	virtual void SetName(std::string name) override
	{
		strName += name;
	}
};

class CAudioDecoder : public virtual CDecoder
{
public:
	CAudioDecoder() : CDecoder("Audio") {}
	virtual ~CAudioDecoder() {}
	void Show()
	{
		CDecoder::Show();
	}
	virtual void SetName(std::string name) override
	{
		strName += name;
	}
};


void Decodermain()
{
	CDecoder* pDecoder = NULL;
	pDecoder = new CVideoDecoder();
	pDecoder->SetName("MPEG2");
	pDecoder->Show();
	delete pDecoder;
	pDecoder = new CAudioDecoder();
	pDecoder->SetName("AAC");
	pDecoder->Show();
	delete pDecoder;
}
