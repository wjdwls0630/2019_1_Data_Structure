#include <iostream>
#include <fstream>
#include <math.h>

#pragma comment (lib, "lib/glu32.lib")
#pragma comment (lib, "lib/glut32.lib")
#include "include/glut.h"

#define FILL 1
#define NOTFILL 0

enum Boolean {FALSE,TRUE};
enum mouseEvent{MOVE,DRAG,LBUTTON_DOWN,LBUTTON_UP};
enum colID{NOCOLOR,RED,GREEN,BLUE,CYAN,MAGENTA,YELLOW,WHITE,BLACK};
enum shapeID{QUIT,RECTANGLE,CIRCLE,CIRCLE_PASSIVE,POLYGON,FILLSEL,NOSHAPE};


typedef GLfloat ColorType[3]; // color 자료형을 정의 
// 자주 사용하는 color를 정의 
static ColorType COLOR[30]={	{1.0f,1.0f,1.0f,}, // not color
					{1.0f,0.0f,0.0f},  //RED
				    {0.0f,1.0f,0.0f},     //GREEN
					{0.0f,0.0f,1.0f},  //BLUE
					{0.0f,1.0f,1.0f},  //CYAN
					{1.0f,0.0f,1.0f},  //MAGENTA
					{1.0f,1.0f,0.0f},  //YELLOW
					{1.0f,1.0f,1.0f},  //WHITE
					{0.0f,0.0f,0.0f}};  //BLACK

class Attribute;
class DrawingStatus;
class BaseNode;
class CircleNode;
class RectangleNode;
class PolygonNode;
class List;
class ListIterator;

//=====================  Object Instanciation(인스턴스 생성) =============================================


struct Point
{
	GLfloat x;
	GLfloat y;

	void Init(int c, int e) { x = c; y=e;}; // 노드 초기화
	Point operator=(Point& b) { x=b.x; y=b.y; return *this;};
};


/*===================================================================================
 왜 필요하가?
   그래픽스 시스템에서 객체를 그릴 때 현재 세팅되어 있는 속성(색, 라인 두께 등)을 
   이용하여 그리게 된다. 따라서 객체를 생성할 때 현재의 속성을 저장할 필요가 있다.
   Attribute class는 각 객체에 저장할 객체와 시스템에서 현재 속성상태를 유지하기 위한 
   global 변수 curAttrib를 정의하는 데 사용된다. 
 멤버함수 
   setColor() : 입력된 값을 color 변수에 assign하고 현재 컬러를 세팅
   setPointSize(): 입력된 값을 pointSize 변수에 assign하고 현재 점크기를 세팅
   setLineWidth(): 입력된 값을 lineWidth 변수에 assign하고 현재 선두께를 세팅
   setFill(): 도형 체우기 여부를 나타내는 fill 변수를 TRUE로 세팅 
   setAllReg(): 현재 저장된 속성으로 현재의 OpenGl 속성을 세팅 
   getFill(): 도형 체우기 여부를 return 
   copyAll(a): a에 저장된 속성을 this에 복사 
=====================================================================================*/

class Attribute {  // attribute class
public:
	friend class BaseNode;
	Attribute(){};
	// openGL register를 세팅하고 내부 변수도 세팅 
	void  setColor(ColorType inCol){color[0]=inCol[0]; color[1]=inCol[1];color[2]=inCol[2];
								glColor3fv(color);};
	void  setLineWidth(float width){lineWidth=width; glLineWidth(lineWidth);};
	void  setPointSize(float size){ pointSize=size;};

	int   getFill(){return fill;};
	void  setFill(int a){ fill=a;};
	
	// setAllReg() // this의 내용으로 OpenGL register를 세팅 
	void  setAllReg(){glColor3fv(color); glLineWidth(lineWidth);
			glPointSize(pointSize);};
	// getAll(a) : a를 this에 복사 
	void  copyAll(Attribute& a){color[0]=a.color[0];color[1]=a.color[1];color[2]=a.color[2];
				fill=a.fill; pointSize=a.pointSize;	lineWidth=a.lineWidth;};

private:
	ColorType color;
	int fill;
	float pointSize;
	float lineWidth;

};


/*============================================================================
왜 필요한가 
    - 그림 그리기 중 유지해야 할 정보를 체계적으로 관리하기 위해서
    - 그리기를 마쳤을 때, 도형을 리스트에 추가하고 초기화하기 위해서 
기능 : 
	- drawing 중인 도형의 그리기 상태를 나타낸다.
		* 도형의 종료,  * 그리기 시작 여부 
		* 관련 함수 : setStart(), isStarted()
	- 현재 수행중인 도형 또는 명령의 ID를 등록하고 알려준다. 
		* 관련 함수 : setShape(), getShape()
	- 초기화 함수
		* normalEnd: 도형의 그리가가 끝나면 list에 추가하고 초기화 한다. 
		* abnormalEnd: 비정상적으로 종료되었을 때, 초기화 
 ===========================================================================*/
class DrawingStatus {
public:
	DrawingStatus(){start=FALSE;};
	void setShape(shapeID a) {shape=a;};
	shapeID  getShape(){return shape;};
	void setStart(){start=TRUE;};	// 그리기가 시작되었는지를 확인
	Boolean isStarted(){return start;};
	void normalEnd();  // 정상종료: 작성된 도형을 리스트에 연결, 초기화
	void abnormalEnd(); // 도형은 버리고 초기화 
private:
	shapeID shape;  // 선택된 도형을 나타냄.
	Boolean start;  // 도형 그리기가 시작되없음을 타나냄
};




//================================ BaseNode class 정의 ===============================
class BaseNode {
	friend class List;
	friend class ListIterator;
	friend class DrawingStatus;

public:
	BaseNode();
	void setAttribute(){ };
	virtual void draw(mouseEvent ev, GLfloat x, GLfloat y)=0;  // 순수 가상함수 
	virtual void display(int currentNode)=0;
protected:
	class Attribute attribute;
	BaseNode *rlink;  //오른쪽(뒤) 노드를 가리키는 포인터
	BaseNode *llink;  //왼쪽(앞) 노드를 가리키는 포인터

};





//================================ Derived Node class 정의 ===============================
class CircleNode : public BaseNode{
public:
	CircleNode(){curNum=0;};
	void draw(mouseEvent ev,GLfloat x, GLfloat y); // circle을 생성한다.
	void display(int currentNode);  // 화면에 출력
	void addPoint(GLfloat x, GLfloat y){vertex[curNum].x=x; vertex[curNum].y=y; curNum++;};
	void addPointCurPos(GLfloat x, GLfloat y){vertex[curNum].x=x; vertex[curNum].y=y; };
	
private:
	int curNum;
	Point vertex[2];
};



class RectangleNode : public BaseNode {
public:
	RectangleNode();
	void display(int currentNode); // rectangle을 화면에 출력
	void draw(mouseEvent ev,GLfloat x, GLfloat y);    // 생성 
	void addPoint(GLfloat x, GLfloat y){vertex[curNum].x=x; vertex[curNum].y=y; curNum++;};
	void addPointCurPos(GLfloat x, GLfloat y){vertex[curNum].x=x; vertex[curNum].y=y; };
private:
	int curNum;
	Point vertex[2];
};



#define MAXPOLYPOINTS 500
class PolygonNode : public BaseNode {
public:
	PolygonNode(){curNum=0;};

	Boolean addPoint(GLfloat x, GLfloat y) // 새로운 포인트를 추가 
	{ if (curNum<MAXPOLYPOINTS-1)
		{vertex[curNum].x=x; vertex[curNum].y=y; curNum++; return TRUE;}
	  else return FALSE;
	}

	void    addPointCurPos(GLfloat x, GLfloat y) // 현재 위치에 추가(drawing시 사용)
	{	vertex[curNum].x=x, vertex[curNum].y = y;};

	Boolean isEndPoint(GLfloat x, GLfloat y) // 현재 점이 마지막 점인지를 검사 
	{
		if ( (x-2)<= vertex[curNum-1].x && (x+2)>= vertex[curNum-1].x
				&& (y-2)<=vertex[curNum-1].y && (y+2)>=vertex[curNum-1].y)
							return TRUE;
		else return FALSE;
				
	}; // 처음점과 같은지를 판별 
	
	void display(int currentNode); // 화면에 출력
	void draw(mouseEvent ev,GLfloat x, GLfloat y); // 생성 
private:
	int curNum;
	Point vertex[MAXPOLYPOINTS];
};



//================================== List class 정의  ================================= 
class List {
	friend class ListIterator;
	friend class drawingStatus;
public:
	List();
	~List();
	void Attach(BaseNode* a); // 노드를 생성한 후, 맨뒤에 추가 
	void displayAll(); // 모든 primitive를 draw 한다. 
	void DeleteAllNode(); // Header를 제외한 리스트에 연결된 모든 노들 제거 
	Boolean NotEmpty(){if (first==first->rlink) return FALSE; else return TRUE;};
private:
	BaseNode *first;  // linked List의 시작 
};


//==================================== Iterator class의 정의  =========================
class ListIterator
{
public:
	ListIterator(const List &l): list(l),current(l.first->rlink){};
	Boolean NotHeader(); // list의 현재 원소가 마지막 원소인지를 검사 
	BaseNode* Next();		// current node의 data를 반환하고 current 오른 쪽으로 이동  
private:
	const List &list;
	BaseNode *current;
	friend class List;
};




