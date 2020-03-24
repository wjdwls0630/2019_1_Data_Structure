/*==========================================================================================
		
		  <<  class���� ����Լ��� ���� ��  >> 

==========================================================================================*/
#include "Graphic2DEditor-OOP.h"

extern BaseNode* newNode;
extern List     GObjList;
extern Attribute curAttrib;
extern DrawingStatus drawing;  // ���� �׸��� ���¸� ��Ÿ���� ����ü



////////////////////////////////////////////////////////////////////////////////////
// DrawingStatusNode�� member function  ���� 
///////////////////////////////////////////////////////////////////////////////////

// ��������: ���� �ۼ��� ��ģ ������ ����Ʈ�� �����ϰ� �ʱ�ȭ
void DrawingStatus:: normalEnd()  
{
	if (newNode!=0) GObjList.Attach(newNode);
	newNode=0;
	start = FALSE; //�ʱ����
}
/* ///////////////////////////////////////////////////////////////////////////////
    ����������: 
	- ������ �߻��߰ų� ���콺�� �ٸ� ������ �Űܼ� ���� �ۼ����� ������ ����
	- ���� ��ü�� ����
=================================================================================*/
void DrawingStatus::abnormalEnd()
{
	if (newNode!=0) delete newNode;
	newNode=0;
	start = FALSE; //�ʱ����
}



////////////////////////////////////////////////////////////////////////////////////
// BaseNode�� member function  ���� 
///////////////////////////////////////////////////////////////////////////////////
BaseNode::BaseNode()
{
	rlink = 0;
	llink = 0;
}


////////////////////////////////////////////////////////////////////////////////////
// List member function  ���� 
////////////////////////////////////////////////////////////////////////////////////
List::List()
{   
	first = new RectangleNode();
	first->rlink=first->llink=first;//�ڽ��� ����Ű�� doubly linked�� ����
}


// List�� ����� ��� ����� �޸𸮸� ������Ų��. 
List::~List()
{ 
	DeleteAllNode();
	delete first;
}



// List�� ����� ��� ����� �޸𸮸� ������Ų��. 
void List::DeleteAllNode()
{   
	BaseNode *tmp, *p;
	for(p=first->rlink; p != first; )  	{	
		tmp=p;
		p = p->rlink;
		delete tmp;
	}
	first->llink=first->rlink=first; // empty list�� ���� 
}



// list �ڿ� newNode�� �߰� 
void List::Attach(BaseNode *newNode)
{
	BaseNode *lastNode = first->llink;  // lastNode


	newNode->llink = lastNode;
	newNode->rlink = first;
	lastNode->rlink = newNode;
	first->llink = newNode;
}

void List::displayAll() // ��� primitive�� draw �Ѵ�. 
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
		iter.current->display(0); // ���� ��带 ���. Virtual �Լ� 
		iter.Next();  // �����͸� ������ �̵� 
	}
	if (drawing.isStarted())
		newNode->display(1);
}



///////////////////////////////////////////////////////////////////////////////////////
//=================ListIterator Member �Լ� ���� ========================
///////////////////////////////////////////////////////////////////////////////////////

// list�� ���� ���Ұ� Header�� �ƴ��� �˻�
Boolean ListIterator::NotHeader()
{
	if (current!=list.first)  //header�� �ƴ��� Ȯ�� 
		return TRUE;
	else
		return FALSE;
}


// current �ڷḦ �����ϰ� current �����͸� ���������� �̵�  
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
				if (!drawing.isStarted())  // ù��° �� 
				{
					drawing.setStart();
					attribute.copyAll(curAttrib); // Attribute�� ������ �´�.
					addPoint(x,y);
					addPointCurPos(x,y); // �ι�° ����Ʈ�� ���� ������ �ʱ�ȭ  
				}
				break;
			case LBUTTON_UP:
				if (drawing.isStarted()) //�ι�° ��
				{
					addPointCurPos(x,y);
					drawing.normalEnd();
				}
				break;
			case DRAG:
				if (drawing.isStarted()) //�ι�° ��
					addPointCurPos(x,y);
				break;
		}

	}
	else //CIRCLEPASSIVE
	{
		switch(event)
		{
			case LBUTTON_DOWN:
				if (!drawing.isStarted()) // ù��° vertex  
				{// ù��° �� ���� 
					drawing.setStart();
					attribute.copyAll(curAttrib); // Attribute�� �����ؿ´�. 
					addPoint(x,y);
					addPointCurPos(x,y); // �ι�° ����Ʈ�� ���� ������ �ʱ�ȭ  
				}
				else // �ι�° ������ �����. ������ ����
				{		
					addPointCurPos(x,y);
					drawing.normalEnd();
				}
				break;
			case MOVE:
				if (drawing.isStarted()) // �ι�° ��
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
	//�̵� ��ȯ�� �������� x;
	float moveY=vertex[0].y;
		
	dx = vertex[1].x-vertex[0].x;
	dy = vertex[1].y - vertex[0].y;
	size = sqrt( dx*dx + dy*dy);
	
	glTranslatef(moveX,moveY,0.0f);// ���� �������� �̵���ȯ ����
	
	//Fill������ ������ �׸��� ��� ����
	if(attribute.getFill()==NOTFILL) //���� �׸��� �ְų� fill�� �ƴ� ��� 
		glBegin(GL_LINE_LOOP);
	else 
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0f,0.0f);//�ﰢ������ �̷���� ��ä���� ����
	}
	
	//������ �߽����� size�� ���������� 32����� ���� ����
	for(angle=0.0f;angle<=2.0f*3.14159f;angle+=3.14159f/32.0f)
	{
		x=size*sin(angle);
		y=size*cos(angle);
		glVertex2f(x,y);
	}
	glEnd();
	
	glTranslatef(-moveX,-moveY,0.0f);//������ ��ǥ�� �̵���ȯ
};






//ccccccccccccccccccccccccccccccccccccc   RectangleNode class function cccccccccccccccccccccccccccccccccccc
//ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

RectangleNode::RectangleNode()
{
	curNum=0;
}

/*=========================================================================================
 - ù��° ���� LB�� down�Ǹ鼭 �����ϰ�, 
 - LB�� ���� ���¿��� dragging�ϸ� �ι�° ���� update�Ǹ鼭 �簢���� Ŀ����,
 - LB�� �������� Ȯ���Ǿ� List�� �߰��ǰ� �ʱ�ȭ �ȴ�. 
===========================================================================================*/
void RectangleNode:: draw(mouseEvent event,GLfloat x, GLfloat y)
{
	switch (event)
	{
	case LBUTTON_DOWN:
		if (!drawing.isStarted())
		{
			drawing.setStart();
			attribute.copyAll(curAttrib); // Attribute�� �����Ѵ�. 
			// vertex�� ���� ������ �ʱ�ȭ�Ѵ�.
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
	if(attribute.getFill()==NOTFILL) // last node �̰ų� fill�� �ƴѰ�� 
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
		glRectf(vertex[0].x,vertex[0].y,vertex[1].x,vertex[1].y);//ä��� �����ÿ� ..
	}
	
}




//ccccccccccccccccccccccccccccccccccccc   PolygonNode class function cccccccccccccccccccccccccccccccccccc
//ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc


void PolygonNode:: draw(mouseEvent event,GLfloat x, GLfloat y)
{
	switch (event)
	{
	case LBUTTON_DOWN:
		if (!drawing.isStarted()) // ù��° vertex  
		{// ���ο� polygone
			drawing.setStart();
			attribute.copyAll(curAttrib); // Attribute�� �����Ѵ�. 
			// vertex�� ���� ������ �ʱ�ȭ�Ѵ�. ���� array full �����Ѵ�.
			addPoint(x,y);
			addPointCurPos(x,y);
		}
		else // �׸��Ⱑ ���۵Ǿ� ���ο� ���� �Էµȴ�.
		{
			if (isEndPoint(x,y)) // �Էµ� ���� ���������� ��ġ�ϸ� ����
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
	case MOVE: // passive move. ������ ���� �ӽ������� ����ϰ� ���. dragging ȿ���� �ش� 
		if (drawing.isStarted()) // �������� ���� pass
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























