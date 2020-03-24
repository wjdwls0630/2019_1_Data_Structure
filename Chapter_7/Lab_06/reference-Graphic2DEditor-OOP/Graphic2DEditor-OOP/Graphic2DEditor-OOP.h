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


typedef GLfloat ColorType[3]; // color �ڷ����� ���� 
// ���� ����ϴ� color�� ���� 
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

//=====================  Object Instanciation(�ν��Ͻ� ����) =============================================


struct Point
{
	GLfloat x;
	GLfloat y;

	void Init(int c, int e) { x = c; y=e;}; // ��� �ʱ�ȭ
	Point operator=(Point& b) { x=b.x; y=b.y; return *this;};
};


/*===================================================================================
 �� �ʿ��ϰ�?
   �׷��Ƚ� �ý��ۿ��� ��ü�� �׸� �� ���� ���õǾ� �ִ� �Ӽ�(��, ���� �β� ��)�� 
   �̿��Ͽ� �׸��� �ȴ�. ���� ��ü�� ������ �� ������ �Ӽ��� ������ �ʿ䰡 �ִ�.
   Attribute class�� �� ��ü�� ������ ��ü�� �ý��ۿ��� ���� �Ӽ����¸� �����ϱ� ���� 
   global ���� curAttrib�� �����ϴ� �� ���ȴ�. 
 ����Լ� 
   setColor() : �Էµ� ���� color ������ assign�ϰ� ���� �÷��� ����
   setPointSize(): �Էµ� ���� pointSize ������ assign�ϰ� ���� ��ũ�⸦ ����
   setLineWidth(): �Էµ� ���� lineWidth ������ assign�ϰ� ���� ���β��� ����
   setFill(): ���� ü��� ���θ� ��Ÿ���� fill ������ TRUE�� ���� 
   setAllReg(): ���� ����� �Ӽ����� ������ OpenGl �Ӽ��� ���� 
   getFill(): ���� ü��� ���θ� return 
   copyAll(a): a�� ����� �Ӽ��� this�� ���� 
=====================================================================================*/

class Attribute {  // attribute class
public:
	friend class BaseNode;
	Attribute(){};
	// openGL register�� �����ϰ� ���� ������ ���� 
	void  setColor(ColorType inCol){color[0]=inCol[0]; color[1]=inCol[1];color[2]=inCol[2];
								glColor3fv(color);};
	void  setLineWidth(float width){lineWidth=width; glLineWidth(lineWidth);};
	void  setPointSize(float size){ pointSize=size;};

	int   getFill(){return fill;};
	void  setFill(int a){ fill=a;};
	
	// setAllReg() // this�� �������� OpenGL register�� ���� 
	void  setAllReg(){glColor3fv(color); glLineWidth(lineWidth);
			glPointSize(pointSize);};
	// getAll(a) : a�� this�� ���� 
	void  copyAll(Attribute& a){color[0]=a.color[0];color[1]=a.color[1];color[2]=a.color[2];
				fill=a.fill; pointSize=a.pointSize;	lineWidth=a.lineWidth;};

private:
	ColorType color;
	int fill;
	float pointSize;
	float lineWidth;

};


/*============================================================================
�� �ʿ��Ѱ� 
    - �׸� �׸��� �� �����ؾ� �� ������ ü�������� �����ϱ� ���ؼ�
    - �׸��⸦ ������ ��, ������ ����Ʈ�� �߰��ϰ� �ʱ�ȭ�ϱ� ���ؼ� 
��� : 
	- drawing ���� ������ �׸��� ���¸� ��Ÿ����.
		* ������ ����,  * �׸��� ���� ���� 
		* ���� �Լ� : setStart(), isStarted()
	- ���� �������� ���� �Ǵ� ����� ID�� ����ϰ� �˷��ش�. 
		* ���� �Լ� : setShape(), getShape()
	- �ʱ�ȭ �Լ�
		* normalEnd: ������ �׸����� ������ list�� �߰��ϰ� �ʱ�ȭ �Ѵ�. 
		* abnormalEnd: ������������ ����Ǿ��� ��, �ʱ�ȭ 
 ===========================================================================*/
class DrawingStatus {
public:
	DrawingStatus(){start=FALSE;};
	void setShape(shapeID a) {shape=a;};
	shapeID  getShape(){return shape;};
	void setStart(){start=TRUE;};	// �׸��Ⱑ ���۵Ǿ������� Ȯ��
	Boolean isStarted(){return start;};
	void normalEnd();  // ��������: �ۼ��� ������ ����Ʈ�� ����, �ʱ�ȭ
	void abnormalEnd(); // ������ ������ �ʱ�ȭ 
private:
	shapeID shape;  // ���õ� ������ ��Ÿ��.
	Boolean start;  // ���� �׸��Ⱑ ���۵Ǿ����� Ÿ����
};




//================================ BaseNode class ���� ===============================
class BaseNode {
	friend class List;
	friend class ListIterator;
	friend class DrawingStatus;

public:
	BaseNode();
	void setAttribute(){ };
	virtual void draw(mouseEvent ev, GLfloat x, GLfloat y)=0;  // ���� �����Լ� 
	virtual void display(int currentNode)=0;
protected:
	class Attribute attribute;
	BaseNode *rlink;  //������(��) ��带 ����Ű�� ������
	BaseNode *llink;  //����(��) ��带 ����Ű�� ������

};





//================================ Derived Node class ���� ===============================
class CircleNode : public BaseNode{
public:
	CircleNode(){curNum=0;};
	void draw(mouseEvent ev,GLfloat x, GLfloat y); // circle�� �����Ѵ�.
	void display(int currentNode);  // ȭ�鿡 ���
	void addPoint(GLfloat x, GLfloat y){vertex[curNum].x=x; vertex[curNum].y=y; curNum++;};
	void addPointCurPos(GLfloat x, GLfloat y){vertex[curNum].x=x; vertex[curNum].y=y; };
	
private:
	int curNum;
	Point vertex[2];
};



class RectangleNode : public BaseNode {
public:
	RectangleNode();
	void display(int currentNode); // rectangle�� ȭ�鿡 ���
	void draw(mouseEvent ev,GLfloat x, GLfloat y);    // ���� 
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

	Boolean addPoint(GLfloat x, GLfloat y) // ���ο� ����Ʈ�� �߰� 
	{ if (curNum<MAXPOLYPOINTS-1)
		{vertex[curNum].x=x; vertex[curNum].y=y; curNum++; return TRUE;}
	  else return FALSE;
	}

	void    addPointCurPos(GLfloat x, GLfloat y) // ���� ��ġ�� �߰�(drawing�� ���)
	{	vertex[curNum].x=x, vertex[curNum].y = y;};

	Boolean isEndPoint(GLfloat x, GLfloat y) // ���� ���� ������ �������� �˻� 
	{
		if ( (x-2)<= vertex[curNum-1].x && (x+2)>= vertex[curNum-1].x
				&& (y-2)<=vertex[curNum-1].y && (y+2)>=vertex[curNum-1].y)
							return TRUE;
		else return FALSE;
				
	}; // ó������ �������� �Ǻ� 
	
	void display(int currentNode); // ȭ�鿡 ���
	void draw(mouseEvent ev,GLfloat x, GLfloat y); // ���� 
private:
	int curNum;
	Point vertex[MAXPOLYPOINTS];
};



//================================== List class ����  ================================= 
class List {
	friend class ListIterator;
	friend class drawingStatus;
public:
	List();
	~List();
	void Attach(BaseNode* a); // ��带 ������ ��, �ǵڿ� �߰� 
	void displayAll(); // ��� primitive�� draw �Ѵ�. 
	void DeleteAllNode(); // Header�� ������ ����Ʈ�� ����� ��� ��� ���� 
	Boolean NotEmpty(){if (first==first->rlink) return FALSE; else return TRUE;};
private:
	BaseNode *first;  // linked List�� ���� 
};


//==================================== Iterator class�� ����  =========================
class ListIterator
{
public:
	ListIterator(const List &l): list(l),current(l.first->rlink){};
	Boolean NotHeader(); // list�� ���� ���Ұ� ������ ���������� �˻� 
	BaseNode* Next();		// current node�� data�� ��ȯ�ϰ� current ���� ������ �̵�  
private:
	const List &list;
	BaseNode *current;
	friend class List;
};




