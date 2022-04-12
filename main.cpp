#include <afxwin.h>
//RTTI
//factory design pattern 
class A : public CObject {
	//DECLARE_DYNAMIC(A); //CObject::IsKindOf()
	//DECLARE_DYNCREATE(A); //CObject::IsKindOf(), 객체 생성의 일반화 제공 : CRuntimeClass::CreateObject() 
	DECLARE_SERIAL(A); //CObject::IsKindOf(), 객체 생성의 일반화 제공 : CRuntimeClass::CreateObject(), CObject::Serialize() : (저장소에 저장하고 읽기 기능 제공 ) 호출할 수 있다 
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
	DECLARE_SERIAL(B);
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

//IMPLEMENT_DYNAMIC(A, CObject); //부모자식관계의 연결고리 만들기 
//IMPLEMENT_DYNAMIC(B, CObject);
//IMPLEMENT_DYNCREATE(A, CObject); //부모자식관계의 연결고리 만들기, 객체 생성의 일반화에 대한 함수 제공
//IMPLEMENT_DYNCREATE(B, CObject);
IMPLEMENT_SERIAL(A, CObject, 1); //부모자식관계의 연결고리 만들기, 객체 생성의 일반화에 대한 함수 제공, 읽기 쓰기에 대한 기능을 제공 및 사용할 수 있다 
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
