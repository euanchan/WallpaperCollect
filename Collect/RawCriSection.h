#if !defined(_CRAWCRISECTION_H)
#define _CRAWCRISECTION_H

class ZMDLL_EXPORT CRawCriSection
{
public:
	CRawCriSection();
	virtual ~CRawCriSection();
	bool Create();
	void Wait();
	void Signal();
	void Close();

private:
	CRITICAL_SECTION* iCriSession;
};

#endif  //_CRAWCRISECTION_H
