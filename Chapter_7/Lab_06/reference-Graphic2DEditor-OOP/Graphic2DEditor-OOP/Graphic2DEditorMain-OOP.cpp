#include "Graphic2DEditor-OOP.h"
/*==========================================================================================
OpenGL 관련 함수 
OpenGL Callback 함수 

========================================================================================*/


int winWidth=800;//윈도우 폭
int winHeight=600;//윈도우 높

// global  변수 선언 

BaseNode* newNode;
List     GObjList;
Attribute curAttrib;
DrawingStatus drawing;  // 현재 그리기 상태를 나타내는 구조체

// 함수 선언 
void init(); // 프로그램 초기화 함수 

// Callback related to window size change
void changeSize(int w,int h);//윈도우 사이즈 변경시

// 그래픽 생성과 관련되는 callback 함수 
void mouse(int button,int state,int x,int y);//마우스 콜백: 버튼을 누를 때 발생 
void move(int x,int y);//마우스 move시의 콜백 : 버튼을 누르지 않고 움직일 때 발생 
void drag(int x,int y);//마우스 drag시의 콜백 : 오른쪽 버튼을 누른 상태에서 움직일 때 발생 
void display();//디스플레이 콜백: 생성된 graphic object가 화면에 출력됨



//메뉴 콜백 함수들
void mainMenu(int id);
void lineWidthMenu(int id);
void colorMenu(int id);
void createMenu(); // Menu 생성


//메인함수
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

	// 그래픽 시스템 초기화 시작 
	// drawing 객체를 초기화 
	drawing.abnormalEnd(); 
	drawing.setShape(NOSHAPE); drawing.abnormalEnd();
	// 현재의 attribute를 갖고 있는 curAttrib 객체를 초기화 
	curAttrib.setColor(COLOR[WHITE]); curAttrib.setLineWidth(1.0);
	curAttrib.setPointSize(1.0); curAttrib.setFill(NOTFILL);
	curAttrib.setColor(COLOR[BLACK]);
	/// 그래픽 시스템 초키화 END

	createMenu();
	glutMainLoop();

}

void init()
{
	glClearColor(1.0f,1.0f,1.0f,0.0f);  //  배경을 흰색으로 초기화 
	glViewport(0,0,winWidth,winHeight); // 화면에서 윈도의 크기와 위치를 결정 
	glMatrixMode(GL_PROJECTION);		// 2차원 그래픽 생성을 위한 환경 세팅 
	glLoadIdentity();
	glOrtho(0.0f,(float)winWidth,0.0f,(float)winHeight,-50.0f,50.0f);
	glMatrixMode(GL_MODELVIEW);
}



//////////////////////////////////////////////////////////////
// 윈도우 사이즈 변경시의 콜백함수로 인자는 윈도우 폭과 높이
void changeSize(int w,int h)
{
	//새로운 윈도우 사이즈를 변수에 저장
	winWidth=w;
	winHeight=h;

	//뷰포트와 관측모드를 새로운 윈도우 사이즈에 맞게 재지정
	glViewport(0,0,winWidth,winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,(float)winWidth,0.0f,(float)winHeight,-50.0f,50.0f);
	glMatrixMode(GL_MODELVIEW);
}


/////////////////////////////////////////////////////////
// 메뉴를 생성
//////////////////////////////////////////////////////////
void createMenu()
{
	int colorID,lineWidthID;// 메뉴 핸들들

	//칼라 메뉴 생성
	colorID=glutCreateMenu(colorMenu);
	glutAddMenuEntry("RED",RED);
	glutAddMenuEntry("GREEN",GREEN);
	glutAddMenuEntry("BLUE",BLUE);
	glutAddMenuEntry("CYAN",CYAN);
	glutAddMenuEntry("MAGENTA",MAGENTA);
	glutAddMenuEntry("YELLOW",YELLOW);
	glutAddMenuEntry("WHITE",WHITE);
	glutAddMenuEntry("BLACK",BLACK);

	//선 굵기 메뉴 생성
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

	//메인메뉴 생성
	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Rectangle",RECTANGLE);
	glutAddMenuEntry("Circle", CIRCLE);
	glutAddMenuEntry("Circle_Passive",CIRCLE_PASSIVE);
	glutAddMenuEntry("Polygon",POLYGON);
	if (curAttrib.getFill()==FILL) // fill is enabled
		glutAddMenuEntry(" Fill", FILLSEL);
	else // fill is disabled
		glutAddMenuEntry("NotFill", FILLSEL);

	glutAddSubMenu("색지정",colorID);
	glutAddSubMenu("선굵기변경",lineWidthID);
	glutAddMenuEntry("나가기",QUIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//////////////////////////////////////////////////////
// 메인메뉴 콜백 함수
////////////////////////////////////////////////////////
void mainMenu(int id)
{
	switch(id)
	{
	case RECTANGLE://사각형 
		drawing.setShape(RECTANGLE);
		break;
	case CIRCLE://원그리기 
		drawing.setShape(CIRCLE);
		break;
	case CIRCLE_PASSIVE://원(passive) 그리기 
		drawing.setShape(CIRCLE_PASSIVE);
		break;
	case POLYGON://polygon 그리기 
		drawing.setShape(POLYGON);
		break;
	case FILLSEL: // 채우기 enalble/disable
		if (curAttrib.getFill()==FILL) curAttrib.setFill(NOTFILL);
		else		 curAttrib.setFill(FILL);
		createMenu();
		break;
	case QUIT: // 나가기 
		exit(1);
		break;
	}


}

////////////////////////////////////////////////////////////////////////
// 오른쪽 버튼이 눌리면 새로 생성될 도형을 위한 객체(Node) 생성 
///////////////////////////////////////////////////////////////////////
BaseNode* getNewNode()
{
	BaseNode *tmp;
	drawing.abnormalEnd(); // clear drawing status and newNode
	switch(drawing.getShape())
	{
	case RECTANGLE://사각형 
		tmp = new RectangleNode();
		break;
	case CIRCLE://원그리기 
		tmp = new CircleNode();
		break;
	case CIRCLE_PASSIVE://원(passive) 그리기 
		tmp = new CircleNode();
		break;
	case POLYGON://polygon 그리기 
		tmp = new PolygonNode();
		break;
	default:
		tmp = 0;
	}
	return tmp;
}


///////////////////////////////////////////////////////
// 색상변경 메뉴의 콜백 함수로 색상 변경...............
void colorMenu(int id)
{
	curAttrib.setColor(COLOR[id]);
}


///////////////////////////////////////////////////////
// 선 굵기 변경 메뉴의 콜백함수로 선의 굵기를 변경해줌
void lineWidthMenu(int id)
{
	curAttrib.setLineWidth((float)id);
}

/*//////////////////////////////////////////////////////////
// 마우스 버튼이 눌려졌을때의 콜백 함수로 다음과 같은 특징이 있다.
//  - 버튼의 상태,마우스 좌표를 가지고 호출
//  - newNode는 기본 class인 BaseNode의 포인터로 global변수이다.
//  - newNode는 파생 class인 도형객체를 가리키고 있다.
//  - draw()함수는 virtual 함수로서 newNode가 가리키는 객체에서 정의되ㅣㄴ
//    함수가 호출된다.
////////////////////////////////////////////////////////////////*/
void mouse(int button,int state,int ix,int y)
{
	GLfloat x=(float)ix;
	GLfloat realY=winHeight-y;//마우스 좌표계를 open gl좌표계로 변환
	//버튼 눌려졌을 때 
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		if (newNode ==0) newNode=getNewNode();

		if (newNode !=0) newNode->draw(LBUTTON_DOWN, x, realY);
	}
	//드래그를 마치고 버튼을 떼었을때
	else if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP)
	{
		if (newNode !=0) 
			newNode->draw(LBUTTON_UP, x, realY);
	}
	glutPostRedisplay();
}

/*//////////////////////////////////////////////////////////
// 마우스를 누르고 이동할 때 호출되는 콜백함수 
//  *** mouse와 동일 
//	- 버튼의 상태,마우스 좌표를 가지고 호출
//	- newNode는 기본 class인 BaseNode의 포인터로 global변수이다.
//  - newNode는 파생 class인 도형객체를 가리키고 있다.
//  - draw()함수는 virtual 함수로서 newNode가 가리키는 객체에서 정의되ㅣㄴ
//    함수가 호출된다.
////////////////////////////////////////////////////////////////*/
void drag(int ix,int y)
{
	GLfloat x=(float)ix;
	GLfloat realY=winHeight-y;//마우스 좌표계를 open gl좌표계로 변환

	if (newNode !=0 && drawing.isStarted()) // 그리기가 선택되고, 이미 시작되었다면 
		newNode->draw(DRAG,x,realY);
	glutPostRedisplay();
}


/*//////////////////////////////////////////////////////////
// 마우스를 떼고 이동할 때 호출되는 콜백함수 
//  *** mouse와 동일 
//	- 버튼의 상태,마우스 좌표를 가지고 호출
//	- newNode는 기본 class인 BaseNode의 포인터로 global변수이다.
//  - newNode는 파생 class인 도형객체를 가리키고 있다.
//  - draw()함수는 virtual 함수로서 newNode가 가리키는 객체에서 정의되ㅣㄴ
//    함수가 호출된다.
////////////////////////////////////////////////////////////////*/
void move(int ix,int y)
{
	GLfloat realY=winHeight-y;//마우스 좌표계를 open gl좌표계로 변환
	GLfloat x=(float)ix;

	if (newNode !=0 && drawing.isStarted()) // 그리기가 선택되고, 이미 시작되었다면 
		newNode->draw(MOVE,x,realY);
	glutPostRedisplay();
}


/*////////////////////////////////////////////////////////////////////////////////////
// 화면을 수정하고자 할 때 glutPostRedisplay(), glFlush()등이 수행될 땔 호출되는 콜백
//   - GObjList는 도형객체를 담고 있는 doubly linked list
//   - GObjList.display는 멤버함수로 연결된 각 객체의 display함수를 호출 
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


