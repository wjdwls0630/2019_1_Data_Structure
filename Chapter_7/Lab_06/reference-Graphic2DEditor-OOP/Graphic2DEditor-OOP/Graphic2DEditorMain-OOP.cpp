#include "Graphic2DEditor-OOP.h"
/*==========================================================================================
OpenGL ���� �Լ� 
OpenGL Callback �Լ� 

========================================================================================*/


int winWidth=800;//������ ��
int winHeight=600;//������ ��

// global  ���� ���� 

BaseNode* newNode;
List     GObjList;
Attribute curAttrib;
DrawingStatus drawing;  // ���� �׸��� ���¸� ��Ÿ���� ����ü

// �Լ� ���� 
void init(); // ���α׷� �ʱ�ȭ �Լ� 

// Callback related to window size change
void changeSize(int w,int h);//������ ������ �����

// �׷��� ������ ���õǴ� callback �Լ� 
void mouse(int button,int state,int x,int y);//���콺 �ݹ�: ��ư�� ���� �� �߻� 
void move(int x,int y);//���콺 move���� �ݹ� : ��ư�� ������ �ʰ� ������ �� �߻� 
void drag(int x,int y);//���콺 drag���� �ݹ� : ������ ��ư�� ���� ���¿��� ������ �� �߻� 
void display();//���÷��� �ݹ�: ������ graphic object�� ȭ�鿡 ��µ�



//�޴� �ݹ� �Լ���
void mainMenu(int id);
void lineWidthMenu(int id);
void colorMenu(int id);
void createMenu(); // Menu ����


//�����Լ�
void main()
{
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(0,0);
	glutCreateWindow(" << Simple Painter Based On OOP >> ");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(changeSize);
	glutPassiveMotionFunc(move);
	glutMotionFunc(drag);
	init();

	// �׷��� �ý��� �ʱ�ȭ ���� 
	// drawing ��ü�� �ʱ�ȭ 
	drawing.abnormalEnd(); 
	drawing.setShape(NOSHAPE); drawing.abnormalEnd();
	// ������ attribute�� ���� �ִ� curAttrib ��ü�� �ʱ�ȭ 
	curAttrib.setColor(COLOR[WHITE]); curAttrib.setLineWidth(1.0);
	curAttrib.setPointSize(1.0); curAttrib.setFill(NOTFILL);
	curAttrib.setColor(COLOR[BLACK]);
	/// �׷��� �ý��� ��Űȭ END

	createMenu();
	glutMainLoop();

}

void init()
{
	glClearColor(1.0f,1.0f,1.0f,0.0f);  //  ����� ������� �ʱ�ȭ 
	glViewport(0,0,winWidth,winHeight); // ȭ�鿡�� ������ ũ��� ��ġ�� ���� 
	glMatrixMode(GL_PROJECTION);		// 2���� �׷��� ������ ���� ȯ�� ���� 
	glLoadIdentity();
	glOrtho(0.0f,(float)winWidth,0.0f,(float)winHeight,-50.0f,50.0f);
	glMatrixMode(GL_MODELVIEW);
}



//////////////////////////////////////////////////////////////
// ������ ������ ������� �ݹ��Լ��� ���ڴ� ������ ���� ����
void changeSize(int w,int h)
{
	//���ο� ������ ����� ������ ����
	winWidth=w;
	winHeight=h;

	//����Ʈ�� ������带 ���ο� ������ ����� �°� ������
	glViewport(0,0,winWidth,winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,(float)winWidth,0.0f,(float)winHeight,-50.0f,50.0f);
	glMatrixMode(GL_MODELVIEW);
}


/////////////////////////////////////////////////////////
// �޴��� ����
//////////////////////////////////////////////////////////
void createMenu()
{
	int colorID,lineWidthID;// �޴� �ڵ��

	//Į�� �޴� ����
	colorID=glutCreateMenu(colorMenu);
	glutAddMenuEntry("RED",RED);
	glutAddMenuEntry("GREEN",GREEN);
	glutAddMenuEntry("BLUE",BLUE);
	glutAddMenuEntry("CYAN",CYAN);
	glutAddMenuEntry("MAGENTA",MAGENTA);
	glutAddMenuEntry("YELLOW",YELLOW);
	glutAddMenuEntry("WHITE",WHITE);
	glutAddMenuEntry("BLACK",BLACK);

	//�� ���� �޴� ����
	lineWidthID=glutCreateMenu(lineWidthMenu);
	glutAddMenuEntry("SIZE:1",1);
	glutAddMenuEntry("SIZE:2",2);
	glutAddMenuEntry("SIZE:3",3);
	glutAddMenuEntry("SIZE:4",4);
	glutAddMenuEntry("SIZE:5",5);
	glutAddMenuEntry("SIZE:6",6);
	glutAddMenuEntry("SIZE:7",7);
	glutAddMenuEntry("SIZE:8",8);
	glutAddMenuEntry("SIZE:9",9);
	glutAddMenuEntry("SIZE:10",10);

	//���θ޴� ����
	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Rectangle",RECTANGLE);
	glutAddMenuEntry("Circle", CIRCLE);
	glutAddMenuEntry("Circle_Passive",CIRCLE_PASSIVE);
	glutAddMenuEntry("Polygon",POLYGON);
	if (curAttrib.getFill()==FILL) // fill is enabled
		glutAddMenuEntry(" Fill", FILLSEL);
	else // fill is disabled
		glutAddMenuEntry("NotFill", FILLSEL);

	glutAddSubMenu("������",colorID);
	glutAddSubMenu("�����⺯��",lineWidthID);
	glutAddMenuEntry("������",QUIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//////////////////////////////////////////////////////
// ���θ޴� �ݹ� �Լ�
////////////////////////////////////////////////////////
void mainMenu(int id)
{
	switch(id)
	{
	case RECTANGLE://�簢�� 
		drawing.setShape(RECTANGLE);
		break;
	case CIRCLE://���׸��� 
		drawing.setShape(CIRCLE);
		break;
	case CIRCLE_PASSIVE://��(passive) �׸��� 
		drawing.setShape(CIRCLE_PASSIVE);
		break;
	case POLYGON://polygon �׸��� 
		drawing.setShape(POLYGON);
		break;
	case FILLSEL: // ä��� enalble/disable
		if (curAttrib.getFill()==FILL) curAttrib.setFill(NOTFILL);
		else		 curAttrib.setFill(FILL);
		createMenu();
		break;
	case QUIT: // ������ 
		exit(1);
		break;
	}


}

////////////////////////////////////////////////////////////////////////
// ������ ��ư�� ������ ���� ������ ������ ���� ��ü(Node) ���� 
///////////////////////////////////////////////////////////////////////
BaseNode* getNewNode()
{
	BaseNode *tmp;
	drawing.abnormalEnd(); // clear drawing status and newNode
	switch(drawing.getShape())
	{
	case RECTANGLE://�簢�� 
		tmp = new RectangleNode();
		break;
	case CIRCLE://���׸��� 
		tmp = new CircleNode();
		break;
	case CIRCLE_PASSIVE://��(passive) �׸��� 
		tmp = new CircleNode();
		break;
	case POLYGON://polygon �׸��� 
		tmp = new PolygonNode();
		break;
	default:
		tmp = 0;
	}
	return tmp;
}


///////////////////////////////////////////////////////
// ���󺯰� �޴��� �ݹ� �Լ��� ���� ����...............
void colorMenu(int id)
{
	curAttrib.setColor(COLOR[id]);
}


///////////////////////////////////////////////////////
// �� ���� ���� �޴��� �ݹ��Լ��� ���� ���⸦ ��������
void lineWidthMenu(int id)
{
	curAttrib.setLineWidth((float)id);
}

/*//////////////////////////////////////////////////////////
// ���콺 ��ư�� ������������ �ݹ� �Լ��� ������ ���� Ư¡�� �ִ�.
//  - ��ư�� ����,���콺 ��ǥ�� ������ ȣ��
//  - newNode�� �⺻ class�� BaseNode�� �����ͷ� global�����̴�.
//  - newNode�� �Ļ� class�� ������ü�� ����Ű�� �ִ�.
//  - draw()�Լ��� virtual �Լ��μ� newNode�� ����Ű�� ��ü���� ���ǵǤӤ�
//    �Լ��� ȣ��ȴ�.
////////////////////////////////////////////////////////////////*/
void mouse(int button,int state,int ix,int y)
{
	GLfloat x=(float)ix;
	GLfloat realY=winHeight-y;//���콺 ��ǥ�踦 open gl��ǥ��� ��ȯ
	//��ư �������� �� 
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		if (newNode ==0) newNode=getNewNode();

		if (newNode !=0) newNode->draw(LBUTTON_DOWN, x, realY);
	}
	//�巡�׸� ��ġ�� ��ư�� ��������
	else if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP)
	{
		if (newNode !=0) 
			newNode->draw(LBUTTON_UP, x, realY);
	}
	glutPostRedisplay();
}

/*//////////////////////////////////////////////////////////
// ���콺�� ������ �̵��� �� ȣ��Ǵ� �ݹ��Լ� 
//  *** mouse�� ���� 
//	- ��ư�� ����,���콺 ��ǥ�� ������ ȣ��
//	- newNode�� �⺻ class�� BaseNode�� �����ͷ� global�����̴�.
//  - newNode�� �Ļ� class�� ������ü�� ����Ű�� �ִ�.
//  - draw()�Լ��� virtual �Լ��μ� newNode�� ����Ű�� ��ü���� ���ǵǤӤ�
//    �Լ��� ȣ��ȴ�.
////////////////////////////////////////////////////////////////*/
void drag(int ix,int y)
{
	GLfloat x=(float)ix;
	GLfloat realY=winHeight-y;//���콺 ��ǥ�踦 open gl��ǥ��� ��ȯ

	if (newNode !=0 && drawing.isStarted()) // �׸��Ⱑ ���õǰ�, �̹� ���۵Ǿ��ٸ� 
		newNode->draw(DRAG,x,realY);
	glutPostRedisplay();
}


/*//////////////////////////////////////////////////////////
// ���콺�� ���� �̵��� �� ȣ��Ǵ� �ݹ��Լ� 
//  *** mouse�� ���� 
//	- ��ư�� ����,���콺 ��ǥ�� ������ ȣ��
//	- newNode�� �⺻ class�� BaseNode�� �����ͷ� global�����̴�.
//  - newNode�� �Ļ� class�� ������ü�� ����Ű�� �ִ�.
//  - draw()�Լ��� virtual �Լ��μ� newNode�� ����Ű�� ��ü���� ���ǵǤӤ�
//    �Լ��� ȣ��ȴ�.
////////////////////////////////////////////////////////////////*/
void move(int ix,int y)
{
	GLfloat realY=winHeight-y;//���콺 ��ǥ�踦 open gl��ǥ��� ��ȯ
	GLfloat x=(float)ix;

	if (newNode !=0 && drawing.isStarted()) // �׸��Ⱑ ���õǰ�, �̹� ���۵Ǿ��ٸ� 
		newNode->draw(MOVE,x,realY);
	glutPostRedisplay();
}


/*////////////////////////////////////////////////////////////////////////////////////
// ȭ���� �����ϰ��� �� �� glutPostRedisplay(), glFlush()���� ����� �� ȣ��Ǵ� �ݹ�
//   - GObjList�� ������ü�� ��� �ִ� doubly linked list
//   - GObjList.display�� ����Լ��� ����� �� ��ü�� display�Լ��� ȣ�� 
//////////////////////////////////////////////////////////////////////////////////////*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	GObjList.displayAll();

	glPopAttrib();
	glFlush();
	glutSwapBuffers();
}


