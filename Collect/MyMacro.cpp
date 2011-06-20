#include "stdafx.h"
#include "MyMacro.h"

struct PtrNode
{
	char name[32];
	void* ptr;
	PtrNode* next;
	PtrNode( const char* aName ) : ptr(NULL), next(NULL)
	{
		strcpy( name, aName );
	}
};

void*& GetPtrByName( const char* aName )
{
	static PtrNode* s_PtrNode = NULL;
	PtrNode* pNode = s_PtrNode;
	while( pNode )
	{
		if( aName )
		{
			if( strcmp( pNode->name, aName ) == 0 )
			{
				return pNode->ptr;
			}
			else if( pNode->next == NULL )
			{
				PtrNode* pTmp = new PtrNode( aName );
				pNode->next = pTmp;
				return pTmp->ptr;
			}
			pNode = pNode->next;
		}
		else
		{
			s_PtrNode = pNode->next;
			delete pNode;
			pNode = s_PtrNode;
		}
	};
	if( aName )
	{
		s_PtrNode = new PtrNode( aName );
		return s_PtrNode->ptr;
	}
	return (void*&)s_PtrNode;
}
