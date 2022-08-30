#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <condition_variable>

static const std::string DEOCDER_TYPE;

//Abstract base class
class CDecoderBase {
public: 
    CDecoderBase(std::string name) {
        strName = name;
    }
    virtual ~CDecoderBase(){}
    virtual void Start() = 0;
	virtual void Stop() = 0;
protected:     
    std::string getName() {
        return strName;
    }

private:
    std::string strName;
}; 

class CVideoDecoder : public virtual CDecoderBase{
public:
	CVideoDecoder(std::string name) : CDecoderBase(name) { m_videoFrameNum = 0; }
    virtual ~CVideoDecoder() {}

    virtual void Start(){
        std::cout << " Decoding [" << CDecoderBase::getName() << "] video" <<std::endl;
		std::lock_guard<std::mutex> guard(m_decMutex);
		m_bFrameReady = false;
		m_bStopDecode = false;
		m_bStopRender = false;
		m_decThrd = std::thread([this] {decodeVideo(); });
		m_renderThrd = std::thread([this] {renderVideo(); });
    }
	virtual void Stop() {
		std::cout << "Stopping video decoder!" << std::endl;
		std::lock_guard<std::mutex> guard(m_decMutex);
		m_bFrameReady = false;
		m_bStopDecode = true;
		m_bStopRender = true;
		if (m_decThrd.joinable()) {
			m_decThrd.join();
		}	
	}

private:
	//decode and fill  the buffer. Producer thread. Each decoded
	//frame will be rendered just after the decode. This toggle 
	//operation is happening using the condition variable
	void decodeVideo() {
		while (!m_bStopDecode) {

			std::unique_lock<std::mutex> lk(m_syncMutex);
			//this cv will be unblocked only when the frame is consumed
			//ie when m_bFrameReady is false
			m_decCV.wait(lk, [this] { return !m_bFrameReady; });
			
			m_bFrameReady = true;
			m_framePool.push_back(m_videoFrameNum);
			std::cout << "Decoded [" << ++m_videoFrameNum << "] framepool size [" << m_framePool.size() << "]" << std::endl;
			lk.unlock();
			m_decCV.notify_one();
		}
	}

	//consumer thread. Consume the filled in buffer. Should be synced using mutex
	void renderVideo() {
		while (!m_bStopRender) {

			//simulate frame time. Render the frame to the screen
			//for 33 ms so that we are simulating a 30 fps playout
			auto duration = std::chrono::milliseconds(33);
			std::this_thread::sleep_for(duration);

			std::unique_lock<std::mutex> lk(m_syncMutex);

			//Same condition variable is blocked waiting the 
			//decode to complete and fill the frame pool. Render
			//and decode are synced this way. Each with frame time
			m_decCV.wait(lk, [this] { return m_bFrameReady; });
			m_bFrameReady = false;	
			m_framePool.pop_back();
			std::cout << "Rendered [" << m_videoFrameNum << "]" << std::endl;
			lk.unlock();
			m_decCV.notify_one();
		}
	}

private:
	uint64_t m_videoFrameNum;

	//control the decode and render cv
	bool m_bFrameReady;
	
	//stop the threads 
	bool m_bStopRender;
	bool m_bStopDecode;
	
	std::thread m_decThrd;
	std::thread m_renderThrd;

	//use this to access the common buffer
	std::condition_variable m_decCV;
	std::mutex m_syncMutex;
	std::mutex m_decMutex;
	std::vector<uint64_t> m_framePool;
};

class CAudioDecoder : public virtual CDecoderBase {
public:
	CAudioDecoder(std::string name) : CDecoderBase(name) { m_audioFrameNum = 0; };
	virtual ~CAudioDecoder() {}

	virtual void Start() {
		std::cout << " Decoding [" << CDecoderBase::getName() << "] Audio" << std::endl;
		std::lock_guard<std::mutex> guard(m_decMutex);
		m_bStop = false;
		m_audioDecThrd = std::thread([this] {decodeAudio(); });
	}

	virtual void Stop() {
		std::cout << "Stopping audio decoder!" << std::endl;
		std::lock_guard<std::mutex> guard(m_decMutex);
		m_bStop = true;
		if (m_audioDecThrd.joinable()) {
			m_audioDecThrd.join();
		}
	}
	
	//only for audio decoder. 
	virtual void SetBitrate(int bitRate){
		std::cout << "Setting bitrate for audio!" << std::endl;
		m_bitrate = bitRate;
	}

private:
	void decodeAudio() {
		uint64_t frameNumber = 0;
		while (!m_bStop) {
			std::cout << "[Audio] [" << frameNumber++ << "]" << CDecoderBase::getName() << std::endl;
			auto duration = std::chrono::milliseconds(200);
			std::this_thread::sleep_for(duration);
		}
	}

private:
	int m_audioFrameNum;
	int m_bitrate;
	
	std::thread m_audioDecThrd;
	//use this to access the common buffer
	std::mutex m_decMutex;
	bool m_bStop;
};

class CDecFactory {
public:
    CDecFactory() {}
    virtual ~CDecFactory() {}
    std::shared_ptr<CDecoderBase> GetDecoder(std::string type) {
        std::string strDec = "basedec";
        if (type == "Audio"){
            m_dec = std::make_shared<CAudioDecoder>("AAC");        
        }else if (type == "Video"){
            m_dec = std::make_shared<CVideoDecoder>("MPEG4");
        }
        return m_dec;
    };
    
    void Start(){
        m_dec->Start();
    };

	void Stop() {
		m_dec->Stop();
	}

private:
    std::shared_ptr<CDecoderBase> m_dec = NULL ;
};

int Codecmain()
{

    std::cout<<"Simulate a multithreaded media player!" << std::endl;
	std::shared_ptr<CDecFactory> pFac = std::make_shared<CDecFactory>();

	auto pADec = pFac->GetDecoder("Audio");
	auto pVideoDec = pFac->GetDecoder("Video");

	//say if we want to ivoke the audioDeocoder setbitrate we have
	//to dynamic cast it as audio and check if we succeed. For that
	//We have to get the full ptr from shared ptr  pAudioDec.
	auto pAudioDec = dynamic_cast<CAudioDecoder*>(pADec.get());
	if (pAudioDec){
		pAudioDec->Start();
		pAudioDec->SetBitrate(10);
	}

	//Video decoder doesnt need a dynamic casting
	pVideoDec->Start();

	auto wait = std::chrono::seconds(10);	
	std::this_thread::sleep_for(wait);

	pAudioDec->Stop();
	pVideoDec->Stop();

	std::cout << "Finished operations!" << std::endl;
	return 0;
};