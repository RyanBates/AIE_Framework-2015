#include "GameLoop.h"
#include <CustomVML.h>

//library vectors
Vec2 <double> A, B, C, H, I, J; 
Vec3 <double> D, E, F, G, K, L;


///////////////////////////////////////////////////////////////////////////
Vec4 <unsigned int> HC;
///////////////////////////////////////////////////////////////////////////


//cirlce a
System::Point2D<int>pos{ 0,450 };
System::Size2D<int>siz{ 100,50 };
System::Color<int>col{ 255,255,150,255 };

//circle b
System::Point2D<int>po{ 1600,450 };
System::Size2D<int>si{ 350,48 };
System::Color<int>co{ 0,255,138,255 };

System::Point2D<float>dp{ pos.X,pos.Y };
System::Point2D<float>d{ po.X,po.Y };
System::Color<float>cl{ col.Red,col.Blue,col.Green,col.Alpha };
System::Color<float>c{ co.Red,co.Blue,co.Green,co.Alpha };

//player 1 
System::Point2D<float>r{ 10,475 };
System::Size2D<float>rs{ 10,75 };
System::Color<float>rc{ 0,10,250,200 };

//player 2 
System::Point2D<float>ta{ 1575,475 };
System::Size2D<float>ts{ 10,75 };
System::Color<float>tc{ 170,5,170,200 };

//ball 
System::Point2D<int>bs{ 800,500 };
System::Color<int>ba{ 138,138,150,255 };

int ballmid = bs.X / 2;

Vec2 <int> ball = { 800,500 };
Vec2 <int> ballspeed = { 10,0 };

//boundaries
System::Point2D<float>tp{ 0,0 };
System::Point2D<float>bo{ 0,890 };

//deltatime movement
float currenttime = 0;
float previoustime = 0;
float deltatime = 0;

int score = 0;
int scorep1 = score;
int scorep2 = score;

bool w = false;
bool s = false;
bool UP = false;
bool DOWN = false;

bool mo = false;
bool bal = false;
bool rectTOcircle = false;
bool ballmove = false;

//graph input
System::Point2D<float>b{ 50,800 };
System::Point2D<float>bl{ 1000,800 };

System::Point2D<float>t{ 50,800 };
System::Point2D<float>tl{ 50,50 };

void GameLoop::Loop()
{
	SDL_Event sdlEvent; // Will hold the next event to be parsed

	while (m_bRunning)
	{
		// Events get called one at a time, so if multiple things happen in one frame, they get parsed individually through 'SDL_PollEvent'
		// The next event to parse gets stored into 'sdlEvent', and then passed to the 'EventHandler' class which will call it's appropriate function here
		// 'SDL_PollEvent' returns 0 when there are no more events to parse
		while (SDL_PollEvent(&sdlEvent))
		{
			// Calls the redefined event function for the EventHandler class
			// Refer to its header file and cpp for more information on what each inherited function is capable of
			// and its syntax
			OnEvent(sdlEvent);
		}		

		float div = 1000;
		float ct = clock();

		currenttime = (float) ct / div;
		previoustime = currenttime;

		Update();

		LateUpdate();

		Draw();

		//scoring
		if (bs.X == 1600)
		{
			scorep1++;
			cout << "player 1 scored. the score is now: " << scorep1 << ":" << scorep2;
			cout << endl;
		}

		if (bs.X == 0)
		{
			scorep2++;
			cout << "player 2 scored. the score is now: " << scorep1 << ":" << scorep2;
			cout << endl;
		}

		if (bs.X == 0)
		{
			bs.X = 800;
			bs.Y = 500;
		}

		if (bs.X == 1600)
		{
			bs.X = 800;
			bs.Y = 500;
		}

		if (scorep1 == 7)
		{
			cout << "player 1 wins. the games over" << endl;
			cout << endl;
			break;	
		}

		if (scorep2 == 7)
		{
			cout << "player 2 wins. the games over" << endl;
			cout << endl;
			break;
		}

		Graphics::Flip(); // Required to update the window with all the newly drawn content
	}
}

void GameLoop::Update()
{
	deltatime = currenttime - previoustime;
	ba.Alpha, ba.Blue, ba.Green, ba.Red = bs.X;

	//player  boundaries / movemenet
	if (w == true)
	{
		if (r.Y >= 10)
		{
			r.Y = r.Y - 10;
		}
	}
	if (s == true)
	{
		if (r.Y <= 810)
		{
			r.Y = r.Y + 10;
		}
	}

	if (UP == true)
	{
		if (ta.Y >= 10)
		{
			ta.Y = ta.Y - 10;
		}
	}
	if (DOWN == true)
	{
		if (ta.Y <= 810)
		{
			ta.Y = ta.Y + 10;
		}
	}

	//ball movement / boundraies	
	if (ballmove == false)
	{
		ballspeed.x = (bs.X += 4) * deltatime;
	}

	else
	{
		ballspeed.x = (bs.X -= 4) * deltatime;
	}

	if (ballmove == true)
	{
		if (bs.Y + 5 == tp.Y - 5)
		{
			ballspeed.y = bs.Y = (bs.Y += 4) * deltatime;
		}

		if (bs.Y + 5 == bo.Y - 5)
		{
			ballspeed.y = bs.Y = (bs.Y -= 4) * deltatime;
		}
	}

	// ball movement
	if (ballmove == false)
	{
		ball = ball - ballspeed;
	}
	if (ballmove == true)
	{
		ball = ball + ballspeed;
	}

	//ball off player 1
	if (ball.x - ballmid <= 10 && ball.x - ballmid >= 0 && ball.y >= r.Y && ball.y <= r.Y + 125)
	{
		ballmove = false;
		{
			if (ballspeed.y == 0)
			{
				ballspeed = { ballspeed.x + 1, ballspeed.y - 1 };
			}
			else if (ballspeed.y > 0)
			{
				ballspeed = { ballspeed.x + 1, -(ballspeed.y) - 1 };
			}
			else if (ballspeed.y < 0)
			{
				ballspeed = { ballspeed.x + 1, -(ballspeed.y) + 1 };
			}
		}
	}

	//ball off player 2
	if (ball.x + ballmid <= 1575 && ball.x + ballmid >= 1585 && ball.y >= t.Y && ball.y <= t.Y + 125)
	{
		ballmove = true;
		{
			if (ballspeed.y == 0)
			{
				ballspeed = { ballspeed.x + 1, ballspeed.y + 1 };
			}
			else if (ballspeed.y > 0)
			{
				ballspeed = { ballspeed.x + 1, (ballspeed.y) - 1 };
			}
			else if (ballspeed.y < 0)
			{
				ballspeed = {ballspeed.x + 1, (ballspeed.y) + 1};
			}
		}
	}
		
	// top and bottom	
	if (ball.y + ballmid >= 875)
	{
		ballspeed = { ballspeed.x, -(ballspeed.y) };
	}
	if (ball.y + ballmid >= 10)
	{
		ballspeed = { ballspeed.x, +(ballspeed.y) };
	}
	
	//circle stuff.
	col.Alpha, col.Blue, col.Green, col.Red = pos.X;
	co.Alpha, co.Blue, co.Green, co.Red = po.X;

	//circle a and b bounce off.
	if (pos.X + 45 == po.X - 45)
	{
		mo = true;
	}
	if (pos.Y + 45 == po.Y - 45)
	{
		mo = true;
	}
	if (pos.X + 45 == 0)
	{
		mo == true;
	}
	if (po.X + 45 == 1600 - 45)
	{
		mo == true;
	}

	//circle a
	if (mo == true)
	{
		(pos.X -= 5)*deltatime;
	}
	else
	{
		(pos.X += 5)*deltatime;
	}

	//self changing color for a
	if (pos.X == 250)
	{
		col.Alpha = 255;
	}
	if (pos.X == 250)
	{
		col.Blue = 50;
	}
	if (pos.X == 250)
	{
		col.Green = 35;
	}
	if (pos.X == 250)
	{
		col.Red = 250;
	}

	//circle b
	if (mo == true)
	{
		(po.X += 5)*deltatime;
	}

	else
	{
		(po.X -= 5)*deltatime;
	}

	//self changing color for b
	if (po.X == 250)
	{
		co.Alpha = 255;
	}
	if (po.X == 250)
	{
		co.Blue = 240;
	}
	if (po.X == 250)
	{
		co.Green = 159;
	}
	if (po.X == 250)
	{
		co.Red = 255;
	}
}

void GameLoop::LateUpdate()
{
	
}

void GameLoop::Draw()
{
	// Objects are drawn in a painter's layer fashion meaning the first object drawn is on the bottom, and the last one drawn is on the top
	// just like a painter would paint onto a canvas

	Graphics::DrawRect({ 0,0 }, { 800, 900 }, { 0,255,0,100 });
	Graphics::DrawRect({ 800,0 }, { 800,900 }, { 255,0,0,100 });

	////circle a
	Graphics::DrawCircle( pos,  siz.H, siz.W, {col.Red,col.Blue,col.Green,col.Alpha});
	Graphics::DrawCircle( pos, 15, 100, { 250,0,0,255 });

	//Graphics::DrawLine({ 15,15 }, { 60,60 }, { 20,68,150,83 });
	//Graphics::DrawPoint({ 20,20 }, { 60,150,255,255 });

	//circle b
	Graphics::DrawCircle( po, si.H, si.W, { co.Red,co.Green,co.Blue,co.Alpha });
	Graphics::DrawCircle( po, 15, 100, { 0,0,250,255 });

	//graph
	Graphics::DrawLine({ b.X,b.Y }, { bl.X,bl.Y }, { 255,38,90,255 });
	Graphics::DrawLine({ t.X,t.Y }, { tl.X,tl.Y }, { 255,38,90,255 });

	//pong
	//player 1
	Graphics::DrawRect( r, rs, rc);

	//player 2
	Graphics::DrawRect( ta, ts, tc);

	//ball
	Graphics::DrawCircle(bs, 10,360, ba);

	//boundaries
	Graphics::DrawRect(bo, { 1600,10 }, { 170,150,255,250 });
	Graphics::DrawRect(tp, { 1600,10 }, { 170,150,255,250 });

	//graph
	float ci = 50;
	float cir = 800;
	for (float c = 0; c < 15; c++)
	{
		Graphics::DrawRect({ ci,cir }, { 6,6 }, { 0, 0, 0, 255 });
		Graphics::DrawLine({ ci, cir }, { 1000,80 }, { 0, 0, 0, 255 });
		ci += 50;
		cir -= 50;
	}

	float x = 50;
	for (float i = 0; i < 20; i++)
	{
		Graphics::DrawLine({ x,790 }, { x,800 }, { 0, 255, 0, 255 });
		x += 50;
	}	

	float y = 800;
	for (float j = 0; j < 16; j++)
	{
		Graphics::DrawLine({ 50,y }, { 60,y }, { 0, 255, 0, 255 });
		y -= 50;
	}
}

void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{

	switch (ac_sdlSym)
	{
	case SDLK_ESCAPE: m_bRunning = false; break; // End the loop

	default: printf("%s\n", SDL_GetKeyName(ac_sdlSym)); break;
	}

	switch (ac_sdlSym)
	{
		//player 1 movement
	case SDLK_w:
		{
			w = true;
			break;
		}
	case SDLK_s:
		{
			s = true;
			break;
		}

		//player 2 movement
	case SDLK_UP:
		{
			UP = true;
			break;
		}
	case SDLK_DOWN:
		{
			DOWN = true;
			break;
		}
	}

	//math library
	switch (ac_sdlSym)
	{
	case SDLK_1:
		cout << "2D vector A and B:" << endl;
		A.x = 5, A.y = 4;
		B.x = -2, B.y = 5; 
		A.print2(); 
		B.print2(); 
		cout << endl; 

		cout << "2D vector addition:" << endl; 
		C = A + B; 
		C.print2(); 
		cout << endl; 

		break;

	case SDLK_2:
		cout << "2D vector subtraction:" << endl;
		C = A - B; 
		C.print2(); 
		cout << endl;
		cout << "2D vector magnitude:" << endl; 
		cout << "Magnitude of A is: " << A.mag2() << endl; 
		cout << "Magnitude of B is: " << B.mag2() << endl; 
		cout << endl; 
		break;

	case SDLK_3:
		cout << "2D vector normalise:" << endl; 
		cout << "Normalise vector A is: " << A.nor2X() << " " << A.nor2Y() << endl; 
		cout << "Normalise vector B is: " << B.nor2X() << " " << B.nor2Y() << endl; 
		cout << endl;
		break;

	case SDLK_4:
		C = A * B; 
		C.dot2(); 
		cout << endl;
		break;

	case SDLK_5:
		cout << "2D linear product: " << endl;
		H.x = 1, H.y = 6;
		I.x = 3, I.y = 5;
		H.print2();
		I.print2();
		J = H % I;
		cout << "answer: " << endl;
		J.print2();
		cout << endl;
		break;

	case SDLK_6:
		cout << "3D vector D and E:" << endl; 
		D.x = 68, D.y = -54, D.z = 32; 
		E.x = 233, E.y = -124, E.z = 43; 
		D.print3(); 
		E.print3(); 
		cout << endl; 
		
		cout << "3D vector addition:" << endl; 
		F = D + E; 
		F.print3(); 
		cout << endl;
		break;

	case SDLK_7:
		cout << "3D vector subtraction:" << endl;
		F = D - E; 
		F.print3(); 
		cout << endl; 

		cout << "3D vector magnitude:" << endl; 
		cout << "Magnitude of D is: " << D.mag3() << endl; 
		cout << "Magnitude of E is: " << E.mag3() << endl; 
		cout << endl; 

		cout << "3D vector normalise:" << endl; 
		cout << "Normalise vector D is: " << D.nor3X() << " " << D.nor3Y() << " " << D.nor3Z() << endl; 
		cout << "Normalise vector E is: " << E.nor3X() << " " << E.nor3Y() << " " << E.nor3Z() << endl; 
		cout << endl;
		
		break;

	case SDLK_8:
		cout << "3D vector dot product:" << endl;
		F = D * E; 
		F.dot3(); 
		cout << endl; 
		break;

	case SDLK_9:
		cout << "3D vector cross product: " << endl;
		F = D / E;
		F.print3();
		cout << endl;
		break;

	case SDLK_0:
		cout << "3D Linear product: " << endl;
		G.x = 1, G.y = 15, G.z = 61;
		K.x = 6, K.y = 21, K.z = 8;
		G.print3();
		K.print3();
		L = G % K;
		cout << endl;
		cout << "answer:" << endl;
		L.print3();
		cout << endl;
		break;

		// Hex
	case SDLK_m:
		HC.R = 0x45C24D23;
		HC.G = 0x035F4A15;
		HC.B = 0x11EB68D3;
		HC.A = 0x777F9CC6;
		cout << HC.r4H() << "," << HC.g4H() << "," << HC.b4H() << "," << HC.a4H() << endl;
		cout << endl;
		break;

		system("pause");
	}
	
}
void GameLoop::OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{
	switch (ac_sdlSym)
	{

	default: break;
	}
	switch (ac_sdlSym)
	{
	//player 1 movement
	case SDLK_w:
	{
		w = false;
		break;
	}
	case SDLK_s:
	{
		s = false;
		break;
	}

	//player 2 movement
	case SDLK_UP:
	{
		UP = false;
		break;
	}
	case SDLK_DOWN:
	{
		DOWN = false;
		break;
	}
	}
}
void GameLoop::OnExit()
{
	m_bRunning = false; // End the loop
}

GameLoop::GameLoop()
{
	m_bRunning = true;
}
GameLoop::~GameLoop()
{

}
