/*==========================================================================================
		
		  <<  class들의 멤버함수를 정의 함  >> 

==========================================================================================*/
#include "Graphic2DEditor-OOP.h"

extern BaseNode* newNode;
extern List     GObjList;
extern Attribute curAttrib;
extern DrawingStatus drawing;  // 현재 그리기 상태를 나타내는 구조체



////////////////////////////////////////////////////////////////////////////////////
// DrawingStatusNode의 member function  정의 
///////////////////////////////////////////////////////////////////////////////////

// 정상종료: 현재 작성을 마친 도형을 리스트에 연결하고 초기화
void DrawingStatus:: normalEnd()  
{
	if (newNode!=0) GObjList.Attach(newNode);
	newNode=0;
	start = FALSE; //초기상태
}
/* ///////////////////////////////////////////////////////////////////////////////
    비정상종료: 
	- 에러가 발생했거나 마우스를 다른 곳으로 옮겨서 현재 작성중인 도형을 버림
	- 현재 객체를 해제
=================================================================================*/
void DrawingStatus::abnormalEnd()
{
	if (newNode!=0) delete newNode;
	newNode=0;
	start = FALSE; //초기상태
}



////////////////////////////////////////////////////////////////////////////////////
// BaseNode의 member function  정의 
///////////////////////////////////////////////////////////////////////////////////
BaseNode::BaseNode()
{
	rlink = 0;
	llink = 0;
}


////////////////////////////////////////////////////////////////////////////////////
// List member function  정의 
////////////////////////////////////////////////////////////////////////////////////
List::List()
{   
	first = new RectangleNode();
	first->rlink=first->llink=first;//자신을 가리키는 doubly linked로 만듬
}


// List에 연결되 모든 노드의 메모리를 해제시킨다. 
List::~List()
{ 
	DeleteAllNode();
	delete first;
}



// List에 연결되 모든 노드의 메모리를 해제시킨다. 
void List::DeleteAllNode()
{   
	BaseNode *tmp, *p;
	for(p=first->rlink; p != first; )  	{	
		tmp=p;
		p = p->rlink;
		delete tmp;
	}
	first->llink=first->rlink=first; // empty list로 만듬 
}



// list 뒤에 newNode를 추가 
void List::Attach(BaseNode *newNode)
{
	BaseNode *lastNode = first->llink;  // lastNode


	newNode->llink = lastNode;
	newNode->rlink = first;
	lastNode->rlink = newNode;
	first->llink = newNode;
}

void List::displayAll() // 모든 primitive를 draw 한다. 
{
	if (!NotEmpty() )
	{
		if (!drawing.isStarted()) return;
		else { newNode->display(1); return;}
	}
	glClear(GL_COLOR_BUFFER_BIT);
	ListIterator iter(*this);
    while (iter.NotHeader())
	{
		iter.current->display(0); // 현재 노드를 출력. Virtual 함수 
		iter.Next();  // 포인터를 다음로 이동 
	}
	if (drawing.isStarted())
		newNode->display(1);
}



///////////////////////////////////////////////////////////////////////////////////////
//=================ListIterator Member 함수 정의 ========================
///////////////////////////////////////////////////////////////////////////////////////

// list의 현재 원소가 Header가 아닌지 검사
Boolean ListIterator::NotHeader()
{
	if (current!=list.first)  //header가 아닌지 확인 
		return TRUE;
	else
		return FALSE;
}


// current 자료를 리턴하고 current 포인터를 오른쪽으로 이동  
BaseNode* ListIterator:: Next()
{
		current = current->rlink;
		return current->llink;
}




//ccccccccccccccccccccccccccccccccccccc   CircleNode class function cccccccccccccccccccccccccccccccccccc
//ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc


void CircleNode:: draw(mouseEvent event,GLfloat x, GLfloat y)
{
	if (drawing.getShape()==CIRCLE)
	{
		switch(event)
		{
			case LBUTTON_DOWN:
				if (!drawing.isStarted())  // 첫번째 점 
				{
					drawing.setStart();
					attribute.copyAll(curAttrib); // Attribute을 복사해 온다.
					addPoint(x,y);
					addPointCurPos(x,y); // 두번째 포인트도 같은 것으로 초기화  
				}
				break;
			case LBUTTON_UP:
				if (drawing.isStarted()) //두번째 점
				{
					addPointCurPos(x,y);
					drawing.normalEnd();
				}
				break;
			case DRAG:
				if (drawing.isStarted()) //두번째 점
					addPointCurPos(x,y);
				break;
		}

	}
	else //CIRCLEPASSIVE
	{
		switch(event)
		{
			case LBUTTON_DOWN:
				if (!drawing.isStarted()) // 첫번째 vertex  
				{// 첫번째 점 정의 
					drawing.setStart();
					attribute.copyAll(curAttrib); // Attribute을 복사해온다. 
					addPoint(x,y);
					addPointCurPos(x,y); // 두번째 포인트도 같은 것으로 초기화  
				}
				else // 두번째 점으로 경계점. 세팅후 종료
				{		
					addPointCurPos(x,y);
					drawing.normalEnd();
				}
				break;
			case MOVE:
				if (drawing.isStarted()) // 두번째 점
					addPointCurPos(x,y);
				break;
		}
	}
}



void CircleNode::display(int currentNode)
{	
	float angle;
	float dx,dy,size,x,y;

	if(currentNode && !drawing.isStarted()) return;
	attribute.setAllReg(); // set current attribute with attribute in this node
	float moveX=vertex[0].x;
	//이동 변환후 원점으로 x;
	float moveY=vertex[0].y;
		
	dx = vertex[1].x-vertex[0].x;
	dy = vertex[1].y - vertex[0].y;
	size = sqrt( dx*dx + dy*dy);
	
	glTranslatef(moveX,moveY,0.0f);// 원의 중점으로 이동변환 수행
	
	//Fill인자의 값으로 그리기 모드 선택
	if(attribute.getFill()==NOTFILL) //현재 그리고 있거나 fill이 아닌 경우 
		glBegin(GL_LINE_LOOP);
	else 
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0f,0.0f);//삼각형으로 이루어진 부채꼴의 중점
	}
	
	//원점을 중심으로 size의 반지름으로 32등분한 원을 생성
	for(angle=0.0f;angle<=2.0f*3.14159f;angle+=3.14159f/32.0f)
	{
		x=size*sin(angle);
		y=size*cos(angle);
		glVertex2f(x,y);
	}
	glEnd();
	
	glTranslatef(-moveX,-moveY,0.0f);//원래의 좌표로 이동변환
};






//ccccccccccccccccccccccccccccccccccccc   RectangleNode class function cccccccccccccccccccccccccccccccccccc
//ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

RectangleNode::RectangleNode()
{
	curNum=0;
}

/*=========================================================================================
 - 첫번째 점은 LB가 down되면서 시작하고, 
 - LB를 누른 상태에서 dragging하면 두번째 점이 update되면서 사각형이 커진다,
 - LB가 떼어지면 확정되어 List에 추가되고 초기화 된다. 
===========================================================================================*/
void RectangleNode:: draw(mouseEvent event,GLfloat x, GLfloat y)
{
	switch (event)
	{
	case LBUTTON_DOWN:
		if (!drawing.isStarted())
		{
			drawing.setStart();
			attribute.copyAll(curAttrib); // Attribute을 복사한다. 
			// vertex를 같은 점으로 초기화한다.
			addPoint(x,y);  addPointCurPos(x,y);
		}
		break;
	case LBUTTON_UP:
		if (drawing.isStarted())
		{
			addPointCurPos(x,y);
			drawing.normalEnd();
		}
		break;
	case DRAG:
		if (drawing.isStarted())
			addPointCurPos(x,y);
		break;
	}	
}


void RectangleNode::display(int currentNode)
{

	if(currentNode && !drawing.isStarted()) return;

	attribute.setAllReg(); // set current attribute with attribute in this node
	if(attribute.getFill()==NOTFILL) // last node 이거나 fill이 아닌경우 
	{
		glBegin(GL_LINE_LOOP);
			glVertex2f(vertex[0].x,vertex[0].y);
			glVertex2f(vertex[1].x,vertex[0].y);
			glVertex2f(vertex[1].x,vertex[1].y);
			glVertex2f(vertex[0].x,vertex[1].y);
		glEnd();
	}
	else
	{
		glRectf(vertex[0].x,vertex[0].y,vertex[1].x,vertex[1].y);//채우기 설정시에 ..
	}
	
}




//ccccccccccccccccccccccccccccccccccccc   PolygonNode class function cccccccccccccccccccccccccccccccccccc
//ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc


void PolygonNode:: draw(mouseEvent event,GLfloat x, GLfloat y)
{
	switch (event)
	{
	case LBUTTON_DOWN:
		if (!drawing.isStarted()) // 첫번째 vertex  
		{// 새로운 polygone
			drawing.setStart();
			attribute.copyAll(curAttrib); // Attribute을 복사한다. 
			// vertex를 같은 점으로 초기화한다. 만약 array full 종료한다.
			addPoint(x,y);
			addPointCurPos(x,y);
		}
		else // 그리기가 시작되어 새로운 점이 입력된다.
		{
			if (isEndPoint(x,y)) // 입력된 점이 마지막점과 일치하면 종료
			{
				addPointCurPos(x,y);
				drawing.normalEnd();
				return;
			}
			if (!addPoint(x,y)) 
			{
				drawing.abnormalEnd();
				return;
			}
			else addPointCurPos(x,y);
		}
		break;
	case MOVE: // passive move. 마지막 점을 임시점으로 등록하고 출력. dragging 효과를 준단 
		if (drawing.isStarted()) // 시작점일 때는 pass
			addPointCurPos(x,y);
		break;
	}	
	
}





void PolygonNode::display(int currentNode)
{
	if(currentNode && !drawing.isStarted()) return;
	if (!currentNode)
	{
		attribute.setAllReg(); // set current attribute with attribute in this node
		if (attribute.getFill()==FILL)		
			glBegin(GL_POLYGON);
		else				glBegin(GL_LINE_LOOP);
		for (int i=0; i<=curNum; i++)
			glVertex2f(vertex[i].x,vertex[i].y);
		glEnd();
	}
	else
	{
		attribute.setAllReg(); // set current attribute with attribute in this node
		glBegin(GL_LINE_STRIP);
		for (int i=0; i<=curNum; i++)
			glVertex2f(vertex[i].x,vertex[i].y);
		glEnd();
	}
}























