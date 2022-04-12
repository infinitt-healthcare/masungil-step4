#include <afxwin.h>
//RTTI
//factory design pattern 
class A : public CObject {
	//DECLARE_DYNAMIC(A); //CObject::IsKindOf()
	//DECLARE_DYNCREATE(A); //CObject::IsKindOf(), ��ü ������ �Ϲ�ȭ ���� : CRuntimeClass::CreateObject() 
	DECLARE_SERIAL(A); //CObject::IsKindOf(), ��ü ������ �Ϲ�ȭ ���� : CRuntimeClass::CreateObject(), CObject::Serialize() : (����ҿ� �����ϰ� �б� ��� ���� ) ȣ���� �� �ִ� 
private:
	int a;
	int b;
public:
	A() : a(100), b(100) { 
		TRACE("A() ������ ȣ��\n"); 
	}
	~A() {
		TRACE("~A() �Ҹ��� ȣ��\n");
	}
	int add(int a, int b) {
		TRACE("A::add() ȣ�� = %d\n", (this->a + this->b + a + b));
		return this->a + this->b + a + b;
	}

};

class B : public CObject {
	DECLARE_SERIAL(B);
private:
	int b;
public:
	B() : b(200) {
		TRACE("B() ������ ȣ��\n");
	}
	~B() {
		TRACE("B() �Ҹ��� ȣ��\n");
	}
	int add(int a, int b) {
		return a + b;
	}
	int sub(int a, int b) {
		TRACE("B::sub() ȣ�� = %d\n", (this->b + (a - b)));
		return this->b + (a - b);
	}
};

//IMPLEMENT_DYNAMIC(A, CObject); //�θ��ڽİ����� ����� ����� 
//IMPLEMENT_DYNAMIC(B, CObject);
//IMPLEMENT_DYNCREATE(A, CObject); //�θ��ڽİ����� ����� �����, ��ü ������ �Ϲ�ȭ�� ���� �Լ� ����
//IMPLEMENT_DYNCREATE(B, CObject);
IMPLEMENT_SERIAL(A, CObject, 1); //�θ��ڽİ����� ����� �����, ��ü ������ �Ϲ�ȭ�� ���� �Լ� ����, �б� ���⿡ ���� ����� ���� �� ����� �� �ִ� 
IMPLEMENT_SERIAL(B, CObject, 1);

class CMainFrame : public CFrameWnd {
};

class CMyApp : public CWinApp {
public:
	BOOL InitInstance() {
		CMainFrame* pMainFrame = new CMainFrame();
		pMainFrame->Create(NULL, NULL);
		//pMainFrame->LoadFrame(IDR_MAIN_FRAME);
		pMainFrame->ShowWindow(SW_SHOW);
		m_pMainWnd = pMainFrame;

		CRuntimeClass* pClass = RUNTIME_CLASS(A);

		CObject* pObj = nullptr;
		//pObj = new A;
		pObj = pClass->CreateObject();
		
		pClass = RUNTIME_CLASS(B);
		pObj = pClass->CreateObject();


		if (pObj->IsKindOf(RUNTIME_CLASS(A))) {
			((A*)pObj)->add(10, 20);
		} 
		else if (pObj->IsKindOf(RUNTIME_CLASS(B))) {
			((B*)pObj)->sub(10, 20);
		} else {
			TRACE("@@@@@@@@@@@@@\n");
		}
		delete pObj;

		pObj = new B;
		if (pObj->IsKindOf(RUNTIME_CLASS(A))) {
			((A*)pObj)->add(10, 20);
		}
		else if (pObj->IsKindOf(RUNTIME_CLASS(B))) {
			((B*)pObj)->sub(10, 20);
		}
		else {
			TRACE("@@@@@@@@@@@@@\n");
		}
		delete pObj;


		/*
		��ü ���� ��� 
		1. A obj;
		   A obj();
		   A obj{}

		2. A* pObj = new A();
		   A* pObj = new A;
		   A* pObj = new A{};

		RTTI -> Runtime type information 
		
		CObject ()


int AAA();//�Լ� ���� 
A obj(); //�Լ����� �Լ��� (obj) return type -> A 

		*/

		return TRUE;
	}
	int ExitInstance() {
		return 0;
	}
};

CMyApp theApp;
