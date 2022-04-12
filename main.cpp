#include <afxwin.h>
//RTTI
class A : public CObject {
	DECLARE_DYNAMIC(A);
private:
	int a;
	int b;
public:
	A() : a(100), b(100) { 
		TRACE("A() 생성자 호출\n"); 
	}
	~A() {
		TRACE("~A() 소멸자 호출\n");
	}

	int add(int a, int b) {
		TRACE("A::add() 호출 = %d\n", (this->a + this->b + a + b));
		return this->a + this->b + a + b;
	}
};

class B : public CObject {
	DECLARE_DYNAMIC(B);
private:
	int b;
public:
	B() : b(200) {
		TRACE("B() 생성자 호출\n");
	}
	~B() {
		TRACE("B() 소멸자 호출\n");
	}
	int add(int a, int b) {
		return a + b;
	}
	int sub(int a, int b) {
		TRACE("B::sub() 호출 = %d\n", (this->b + (a - b)));
		return this->b + (a - b);
	}
};

IMPLEMENT_DYNAMIC(A, CObject);
IMPLEMENT_DYNAMIC(B, CObject);

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

		CObject* pObj = nullptr;
		//CObject* pObj = NULL;
		pObj = new A;
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
		객체 생성 방법 
		1. A obj;
		   A obj();
		   A obj{}

		2. A* pObj = new A();
		   A* pObj = new A;
		   A* pObj = new A{};

		RTTI -> Runtime type information 
		
		CObject ()


int AAA();//함수 선언 
A obj(); //함수선언 함수명 (obj) return type -> A 

		*/

		return TRUE;
	}
	int ExitInstance() {
		return 0;
	}
};

CMyApp theApp;
