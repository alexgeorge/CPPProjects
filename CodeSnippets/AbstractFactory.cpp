#include <iostream>
//#define LINUX

using namespace std;

/**
 * Abstract base product. It should define an interface
 * which will be common to all products. Clients will
 * work with products through this interface, so it
 * should be sufficient to use all products.
 */
class Decoder {
public:
	Decoder () {cout<<"Decoder ctor \n";}
	virtual void decode() = 0;
	virtual ~Decoder(){cout<<"Decoder dtor\n";}
};

/**
 * Concrete product family 1.
 */
class AudioDecoder : public Decoder {
public:
	AudioDecoder(){cout<<"AudioDecoder ctor\n";}
	virtual void decode() { cout << "Audio dec\n"; }
	virtual ~AudioDecoder(){ cout<<"AudioDecoder dtor\n";}
};

class AC3Decoder : public AudioDecoder {
public:
	AC3Decoder(){cout<<"AC3Decoder ctor\n";}
	AC3Decoder(const AC3Decoder&){
		cout<<"Copy ctor in AC3Decoder \n";
	}
	virtual void decode() { cout << "AC3 dec\n"; }
	virtual ~AC3Decoder(){ cout<<"AC3Decoder dtor\n";}
};

/**
 * Concrete product family 2.
 */
class VideoDecoder : public Decoder {
public:
	VideoDecoder(){cout<<"VideoDecoder ctor\n";}
	virtual void decode() { cout << "Video dec\n"; }
	virtual ~VideoDecoder(){ cout<<"VideoDecoder dtor\n";}

};

class MPEG2Decoder : public VideoDecoder {
 public:
	MPEG2Decoder(){cout<<"MPEG2Decoder ctor\n";}
	MPEG2Decoder(const MPEG2Decoder&){
		cout<<"Copy ctor in MPEG2Decoder \n";
	}
	virtual void decode() { cout << "MPEG2Decoder dec\n"; }
	virtual ~MPEG2Decoder(){ cout<<"MPEG2Decoder dtor\n";}

};

/**
 * Abstract factory defines methods to create all
 * related products.
 */
class Factory {
 public:
  virtual Decoder *create_decoder() = 0;
  virtual ~Factory(){
	cout<<"Without virtual destructor no other derived destructors will be called \n";
  }
};

/**
 * Each concrete factory corresponds to one product
 * family. It creates all possible products of
 * one kind.
 */
class AC3Factory : public Factory {
private:
	Decoder* pDec;
public:
	AC3Factory(){
		pDec=0;	
	}
	Decoder *create_decoder() {	
		pDec = new AC3Decoder;
		return pDec;
	}
	~AC3Factory(){
		delete pDec;
	}

};

/**
 * Concrete factory creates concrete products, but
 * returns them as abstract.
 */
class MPEG2Factory : public Factory {
private:
	Decoder* pDec;
public:
	MPEG2Factory(){
		pDec=0;	
	}
	Decoder *create_decoder() {	
		pDec = new MPEG2Decoder;
		return pDec;
	}
	~MPEG2Factory(){
		delete pDec;
	}

};

/**
 * Client receives a factory object from its creator.
 *
 * All clients work with factories through abstract
 * interface. They don't know concrete classes of
 * factories. Because of this, you can interchange
 * concrete factories without breaking clients.
 *
 * Clients don't know the concrete classes of created
 * products either, since abstract factory methods
 * returns abstract products.
 */
class Client {
private:
  Factory *factory;

public:
	Client(){
		factory=0;
	}	
	Client(Factory *f) {
		factory = f;
	}

	void decode() {
		Decoder *w = factory->create_decoder();
		w->decode();
	}
	~Client(){
		cout<<"Deleting client \n";		
	}
};

/**
 * Now the nasty switch statement is needed only once to
 * pick and create a proper factory. Usually that's
 * happening somewhere in program initialization code.
 */

void checkDecodeFeature()
{
  Factory *factory;
#ifdef AC3
  factory = new AC3Factory;
#else // MPEG2
  factory = new MPEG2Factory;
#endif

  Client *c = new Client(factory);
  c->decode();
  delete c;
  delete factory; //since this function is responsible for this object
}

void CheckCPPVersion() {
	if (__cplusplus == 201703L) std::cout << "C++17\n";
	else if (__cplusplus == 201402L) std::cout << "C++14\n";
	else if (__cplusplus == 201103L) std::cout << "C++11\n";
	else if (__cplusplus == 199711L) std::cout << "C++98\n";
	else std::cout << "pre-standard C++\n";
}


int AbsFactmain(){
	CheckCPPVersion();
	int a = 3;
	cout << (a++) << std::endl;
	cout << (a) << std::endl;
	cout << (++a) << std::endl;
	cout << (a) << std::endl;

	checkDecodeFeature();
	return 0;
}