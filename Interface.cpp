// Interface.cpp: implementation of the Interface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Interface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Interface::Interface()
{
	for(int i=0;i<256;i++)
	{
		m_keys[i]=false;
	}
	m_nMenus=0;
}

Interface::~Interface()
{

}


//////////////////////////////////////////////////////////////////////////
//函数：Proc()
//参数：消息体及相关参数
//功能：消息响应
//////////////////////////////////////////////////////////////////////////
void Interface::Proc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;
	switch(uMsg)
	{
	case WM_KEYDOWN:
		{
			m_keys[wParam] = TRUE;	
			return;

		}
	case WM_KEYUP:
		{
			m_keys[wParam]=false;
			return;
		}

	case WM_MOUSEMOVE:
		{
			CVector2 cursorPos;
			cursorPos.Init(LOWORD(lParam),HIWORD(lParam));
			for(i=0;i<m_nMenus;i++)
			{
				if (m_menus[i].CheckZoom(cursorPos.x,cursorPos.y))
				{
					m_menus[i].m_scale=1.2*m_menus[i].m_scale2;
				}
				else
					m_menus[i].m_scale=m_menus[i].m_scale2;
			}
			return;
		}

	case WM_LBUTTONUP:
		{
			double xPos = LOWORD(lParam); 
			double yPos = HIWORD(lParam);
			//MakeFile(xPos,yPos);
			for(i=0;i<m_nMenus;i++)
			{
				if (m_menus[i].CheckClicked(xPos,yPos))
				{
					m_menus[i].m_bZoomByClick=true;
					m_menus[i].AnimateMenu();
					return;
				}
				
			}
			
			return;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//函数：RenderInterface()
//参数：无
//功能：绘制交互界面（我们采用的3d界面接口，所以自行绘制）
//////////////////////////////////////////////////////////////////////////
void Interface::RenderInterface()
{

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	
	glOrtho(-320,320,-240,240,-10,500);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth BufferGL_COLOR_BUFFER_BIT | 
	glLoadIdentity();// Reset The View
	
	glPushMatrix();
	m_menus[3].RenderMenu();
	glPopMatrix();
	glPushMatrix();
	m_menus[4].RenderMenu();
	glPopMatrix();
	glPushMatrix();
	m_menus[6].RenderMenu();
	glPopMatrix();
	glPushMatrix();
	m_menus[34].RenderMenu();
	glPopMatrix();
	glPushMatrix();
	m_menus[35].RenderMenu();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[0].RenderMenu());

		//OnMenuDAOHANG();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[1].RenderMenu());
		//OnMenuYUYIN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[2].RenderMenu());
		//OnMenuGONGNENG();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[33].RenderMenu());
		//OnMenuFENLEI();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[5].RenderMenu());
		//OnMenuEXIT();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[9].RenderMenu());
		//OnMenuZUIJIALUXIAN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[12].RenderMenu());
		//OnMenuHANGJI();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[7].RenderMenu());
		//OnMenuFANGDA();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[8].RenderMenu());
		//OnMenuSUOXIAO();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[15].RenderMenu());
		//OnMenuEmail();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[16].RenderMenu());
		//OnMenuGengxin();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[10].RenderMenu());
		//OnMenuCHAXUN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[17].RenderMenu());
		//OnMenuBIANJIAN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[36].RenderMenu());
		//OnMenuSANWEINIAOKAN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[38].RenderMenu());
		//OnMenuTurnOffMusic();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[37].RenderMenu());
		//OnMenuTurnOnMusic();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[18].RenderMenu());
		//OnMenuKTV();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[19].RenderMenu());
		//OnMenuBINGUAN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[20].RenderMenu());
		//OnMenuCANYIN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[21].RenderMenu());
		//OnMenuCHAGUAN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[22].RenderMenu());
		//OnMenuGOUWU();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[23].RenderMenu());
		//OnMenuJIAOYU();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[24].RenderMenu());
		//OnMenuJINRONGSHANGWU();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[25].RenderMenu());
		//OnMenuJIUBA();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[26].RenderMenu());
		//OnMenuCAFEI();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[27].RenderMenu());
		//OnMenuLOUPAN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[28].RenderMenu());
		//OnMenuLUYOU();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[29].RenderMenu());
		//OnMenuQICHE();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[30].RenderMenu());
		//OnMenuXIEZILOU();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[31].RenderMenu());
		//OnMenuYIYUAN();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[32].RenderMenu());
		//OnMenuYULE();
	glPopMatrix();
	glPushMatrix();
	if(m_menus[14].RenderMenu());
		//OnMenuBANGZHU();
	glPopMatrix();
	glPushMatrix();
	m_menus[39].RenderMenu();
	glPopMatrix();
	glPushMatrix();
	m_menus[40].RenderMenu();
	glPopMatrix();
	glPushMatrix();
	m_menus[41].RenderMenu();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,0.0f,0.0f);

	glBegin(GL_POLYGON);//填充凸多边形
	glVertex3f(0.0f,0.0f ,0.0f);//a点
	glVertex3f(0.0f,10.0f, 0.0f);//b点
	glVertex3f(10.0f,10.0f,0.0f);//c点
	glVertex3f(10.0f,0.0f,0.0f);//d点
    glEnd();
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

//////////////////////////////////////////////////////////////////////////
//函数：Load()
//参数：无
//功能：加载3d模型（按钮）,并初始化
//////////////////////////////////////////////////////////////////////////
void Interface::Load()
{
	
	//0 导航按钮
	AddMenu("Models/daohang.3DS",257.000000f,174.000000f,-30.000000f,70.000000f,0,0,0.904032f,1,0.163514f,0.106757f,1);
	m_menus[0].Show();
	//1 语音按钮
	AddMenu("Models/yuyin.3DS",257.000000f,141.000000f,-30.000000f,70.000000f,0,0,0.904032f,1.0f,0.233784f,0.177027f,1);
	m_menus[1].Show();
	//2 功能按钮
	AddMenu("Models/gongneng.3DS",257.000000f,108.000000f,-30.000000f,70.000000f,0,0,0.904839f,1.0f,0.301351f,0.243243f,1);
	m_menus[2].Show();
	//3 速度表盘
	AddMenu("Models/biaopan.3DS",-242.000000f,-182.000000f,-20.000000f,6.000000f,0,0,0,0,0,0,1);
	m_menus[3].Show();
	//4 速度指针
	AddMenu("Models/zhizhen.3DS",-242.000000f,-183.000000f,-6.000000f,39.000000f,0,0,0,0,0,0,5);
	m_menus[4].Show();
	//5 退出按钮
	AddMenu("Models/exit.3DS",293.000000f,67.000000f,-6.000000f,14.000000f,180,0,0.919355f,1.0f,0.385135f,0.331081f,4);
	m_menus[5].Show();
	//6 控制导航仪显示与否
	AddMenu("Models/bashou.3DS",107.000000f,-239.000000f,-6.000000f,15.799997f,0,0,0,0,0,0,3);
	m_menus[6].Show();
	//7 放大地图按钮
	AddMenu("Models/+.3DS",26.000000f,-113.000000f,6.000000f,1.000000f,0,0,0.527419f,0.551613f,0.748649f,0.716216f,2);
	m_menus[7].Show();
	//8 缩小地图按钮
	AddMenu("Models/-.3DS",26.000000f,-179.000000f,6.000000f,1.000000f,0,0,0.528226f,0.551613f,0.886486f,0.855405f,2);
	m_menus[8].Show();
	//9 最佳路径
	AddMenu("Models/最佳路线.3DS",256.000000f,-103.000000f,-6.000000f,1.799920f,0,0,0.875000f,0.926613f,0.741892f,0.682432f,4);
	m_menus[9].Show();
	//10 查询
	AddMenu("Models/查询.3DS",265.000000f,-92.000000f,-6.000000f,1.199920f,0,0,0.895161f,0.932258f,0.712162f,0.668919f,4);
	m_menus[10].Show();
	//11	测距
	AddMenu("Models/测距.3DS",303.000000f,-163.000000f,-6.000000f,1.199920f,0,0,0.900000f,1.0f,0.675676f,0.621622f,4);
	m_menus[11].Show();
	//12	航迹
	AddMenu("Models/航迹.3DS",257.000000f,-176.000000f,-6.000000f,1.599920f,0,0,0.876613f,0.925000f,0.893243f,0.836486f,4);
	m_menus[12].Show();
	//13	返回
	AddMenu("Models/返回.3DS",303.000000f,-222.000000f,-6.000000f,-0.400080f,0,0,0.900000f,1.0f,0.675676f,0.621622f,4);
	m_menus[13].Show();
	//14	帮助
	AddMenu("Models/帮助.3DS",233.000000f,-195.000000f,-6.000000f,1.199920f,0,0,0.846774f,0.880645f,0.925676f,0.881081f,4);
	m_menus[14].Show();
	//15	邮件
	AddMenu("Models/email.3DS",265.000000f,-195.000000f,-6.000000f,1.199920f,0,0,0.897581f,0.930645f,0.925676f,0.881081f,4);
	m_menus[15].Show();
	//16	标记
	AddMenu("Models/标记.3DS",233.000000f,-92.000000f,-6.000000f,1.199920f,0,0,0.845968f,0.880645f,0.712162f,0.668919f,4);
	m_menus[16].Show();
	//17	便笺
	AddMenu("Models/便笺.3DS",233.000000f,-141.000000f,-6.000000f,1.199920f,0,0,0.845968f,0.881452f,0.817568f,0.768919f,4);
	m_menus[17].Show();
	//18	KTV	
	AddMenu("Models/KTV.3DS",-260.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.069355f,0.116935f,0.074324f,0.008108f,4);
	m_menus[18].Show();
	//19	宾馆
	AddMenu("Models/宾馆.3DS",-220.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.133871f,0.176613f,0.072973f,0.009459f,4);
	m_menus[19].Show();
	//20	餐饮
	AddMenu("Models/餐饮.3DS",-180.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.194355f,0.240323f,0.072973f,0.010811f,4);
	m_menus[20].Show();
	//21	茶馆
	AddMenu("Models/茶馆.3DS",-140.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.255645f,0.302419f,0.074324f,0.009459f,4);
	m_menus[21].Show();
	//22	购物
	AddMenu("Models/购物.3DS",-100.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.319355f,0.367742f,0.077027f,0.009459f,4);
	m_menus[22].Show();
	//23	教育
	AddMenu("Models/教育.3DS",-60.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.383871f,0.425806f,0.070270f,0.009459f,4);
	m_menus[23].Show();
	//24	金融商务
	AddMenu("Models/金融商务.3DS",-20.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.445161f,0.491935f,0.074324f,0.008108f,4);
	m_menus[24].Show();
	//25	酒吧
	AddMenu("Models/酒吧.3DS",20.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.510484f,0.552419f,0.070270f,0.008108f,4);
	m_menus[25].Show();
	//26	咖啡
	AddMenu("Models/咖啡.3DS",60.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.570161f,0.614516f,0.072973f,0.009459f,4);
	m_menus[26].Show();
	//27	楼盘
	AddMenu("Models/楼盘1.3DS",100.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.634677f,0.677419f,0.070270f,0.009459f,4);
	m_menus[27].Show();
	//28	旅游
	AddMenu("Models/旅游.3DS",140.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.697581f,0.738710f,0.075676f,0.009459f,4);
	m_menus[28].Show();
	//29	汽车
	AddMenu("Models/汽车.3DS",180.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.759677f,0.804032f,0.070270f,0.009459f,4);
	m_menus[29].Show();
	//30	写字楼
	AddMenu("Models/写字楼.3DS",220.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.820968f,0.864516f,0.074324f,0.009459f,4);
	m_menus[30].Show();
	//31	医院
	AddMenu("Models/医院.3DS",260.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.881452f,0.927419f,0.070270f,0.008108f,4);
	m_menus[31].Show();
	//32	娱乐
	AddMenu("Models/娱乐.3DS",300.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.944355f,0.992742f,0.071622f,0.009459f,4);
	m_menus[32].Show();
	//33	控制分类图标显示与否按钮
	AddMenu("Models/弹缩.3DS",-300.000000f,219.000000f,-6.000000f,1.799920f,0,0,0.008065f,0.053226f,0.075676f,0.006757f,4);
	m_menus[33].Show();
	//34	方向盘
	AddMenu("Models/方向盘.3DS",-79.000000f,-160.000000f,-65.000000f,7.399918f,0,0,0,0,0,0,6);
	m_menus[34].Show();
	//35	导航仪边框
	AddMenu("Models/电子狗.3DS",159.000000f,-146.000000f,-65.000000f,2.999921f,0,0,0,0,0,0,6);
	m_menus[35].Show();
	//36	三维鸟瞰
	AddMenu("Models/三维鸟瞰.3DS",265.000000f,-142.000000f,-6.000000f,1.199920f,0,0,0.896774f,0.929839f,0.818919f,0.771622f,4);
	m_menus[36].Show();
	//37	声音开
	AddMenu("Models/kai.3DS",252.000000f,-110.000000f,-6.000000f,75.199921f,0,0,0.870968f,0.915323f,0.755405f,0.698649f,4);
	m_menus[37].Show();
	//38	声音关
	AddMenu("Models/guan.3DS",252.000000f,-174.000000f,-6.000000f,75.199921f,0,0,0.871774f,0.914516f,0.891892f,0.831081f,4);
	m_menus[38].Show();
	//39	地球
	AddMenu("Models/qiu.3DS",272.000000f,174.000000f,-13.000000f,5.399920f,0,0,0,0,0,0,7);
	m_menus[39].Show();
	//40	地球
	AddMenu("Models/语音.3DS",272.000000f,141.000000f,-13.000000f,1.799921f,0,0,0,0,0,0,7);
	m_menus[40].Show();
	//41	地球
	AddMenu("Models/功能.3DS",272.000000f,108.000000f,-13.000000f,0.899900f,0,0,0,0,0,0,7);
	m_menus[41].Show();
	
}


//////////////////////////////////////////////////////////////////////////
//函数：AddMenu(...)
//参数：...
//功能：添加按钮
//////////////////////////////////////////////////////////////////////////
void Interface::AddMenu(char *filename,float xPos, float yPos, float zPos,
							   float scale,int yrot,int zrot,
							   float perX1,float perX2,float perY1,float perY2,int flag)
{
	
	long witdh=GetSystemMetrics(SM_CXSCREEN);//view.m_scrRect.right-view.m_scrRect.left;
	long height=GetSystemMetrics(SM_CYSCREEN);//view.m_scrRect.bottom-view.m_scrRect.top;
	m_menus[m_nMenus].Load(filename);
	m_menus[m_nMenus].Init(xPos,yPos,zPos,scale,yrot,zrot
		,int(witdh*perX1),int(witdh*perX2),int(height*perY1),int(height*perY2),flag);
	//m_menus[m_nMenus].Init(m_pPlayer);
	//m_menus[m_nMenus].m_pAudioManager=m_pAudioManager;
	m_nMenus++;
}