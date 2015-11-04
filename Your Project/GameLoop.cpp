#include "GameLoop.h"
#include "CustomVML.h"
Vec2 <double> A, B, C; //Vec2 objects of data type float
Vec3 <double> D, E, F; //Vec3 objects of data type float
//cirlce a
System::Point2D<int>pos{ 350,80 };
System::Size2D<int>siz{ 100,50 };
System::Color<int>col{ 300,450,150,1600 };

//circle b
System::Point2D<int>po{ 800,500 };
System::Size2D<int>si{ 350,480 };
System::Color<int>c{ 0,255,138,255 };

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
		Update();

		LateUpdate();

		Draw();

		Graphics::Flip(); // Required to update the window with all the newly drawn content
	}
}

void GameLoop::Update()
{

}
void GameLoop::LateUpdate()
{

}

void GameLoop::Draw()
{
	// Objects are drawn in a painter's layer fashion meaning the first object drawn is on the bottom, and the last one drawn is on the top
	// just like a painter would paint onto a canvas
	
	// Ben's
	//Graphics::DrawRect({ 400, 400 }, { 450, 400 }, { 160, 65, 255, 255 });
	//Graphics::DrawRect({ 250, 500 }, { 1000, 200 }, { 0, 255, 0, 255 });

	//Graphics::DrawLine({ 10, 10 }, { 100, 100 }, { 255, 255, 255, 255 });
	//Graphics::DrawPoint({ 5, 5 }, { 255, 255, 255, 255 });

	//Graphics::DrawRing({ 140, 140 }, 50, 25, { 50, 0, 200, 255 });
	//Graphics::DrawCircle({ 800, 450 }, 200, 50, { 0, 255, 255, 150 });
	
	// mine
	//Graphics::DrawRect({ 350,80 }, { 260, 250 }, { 0,80,34,1500 });

	Graphics::DrawCircle({ pos.X,pos.Y },  siz.H, siz.W, {col.Red,col.Blue,col.Green,col.Alpha});
	Graphics::DrawCircle({ pos.X,pos.Y }, 15, 100, { 250,0,0,255 });
	//Graphics::DrawLine({ 15,15 }, { 60,60 }, { 20,68,150,83 });
	//Graphics::DrawPoint({ 20,20 }, { 60,150,800,350 });

	Graphics::DrawCircle({ po.X,po.Y }, si.H, si.W, { c.Red,c.Blue,c.Green,c.Alpha });
	Graphics::DrawCircle({ po.X,po.Y }, 15, 100, { 0,250,0,255 });
}

void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{

	switch (ac_sdlSym)
	{
	case SDLK_ESCAPE: m_bRunning = false; break; // End the loop

	default: printf("%s\n", SDL_GetKeyName(ac_sdlSym)); break;
	}
	//movement circle a
	if (ac_sdlSym == SDLK_w)
	{
		pos.Y = pos.Y - 5;
	}

	if (ac_sdlSym == SDLK_a)
	{
		pos.X = pos.X - 5;
	}

	if (ac_sdlSym == SDLK_s)
	{
		pos.Y = pos.Y + 5;
	}

	if (ac_sdlSym == SDLK_d)
	{
		pos.X = pos.X + 5;
	}	

	//movement circle b
	if (ac_sdlSym == SDLK_KP_8)
	{
		po.Y = po.Y - 5;
	}

	if (ac_sdlSym == SDLK_KP_4)
	{
		po.X = po.X - 5;
	}

	if (ac_sdlSym == SDLK_KP_2)
	{
		po.Y = po.Y + 5;
	}

	if (ac_sdlSym == SDLK_KP_6)
	{
		po.X = po.X + 5;
	}

	//size circle a
	if (ac_sdlSym == SDLK_e)
	{
		siz.H = siz.H + 10;
	}
	if (ac_sdlSym == SDLK_z)
	{
		siz.W = siz.W - 10;
	}
	if (ac_sdlSym == SDLK_c)
	{
		siz.H = siz.H - 10;
	}
	if (ac_sdlSym == SDLK_q)
	{
		siz.W = siz.W + 10;
	}

	//size circle b
	if (ac_sdlSym == SDLK_KP_9)
	{
		si.H = si.H + 10;
	}
	if (ac_sdlSym == SDLK_KP_1)
	{
		si.W = si.W - 10;
	}
	if (ac_sdlSym == SDLK_KP_7)
	{
		si.H = si.H - 10;
	}
	if (ac_sdlSym == SDLK_KP_3)
	{
		si.W = si.W + 10;
	}

	//color circle a
	if (ac_sdlSym == SDLK_p)
	{
		col.Alpha = col.Alpha + 50;
	}
	if (ac_sdlSym == SDLK_l)
	{
		col.Alpha = col.Alpha - 50;
	}
	if (ac_sdlSym == SDLK_o)
	{
		col.Blue = col.Blue + 50;
	}
	if (ac_sdlSym == SDLK_k)
	{
		col.Blue = col.Blue - 50;
	}
	if (ac_sdlSym == SDLK_i)
	{
		col.Green = col.Green + 50;
	}
	if (ac_sdlSym == SDLK_j)
	{
		col.Green = col.Green - 50;
	}
	if (ac_sdlSym == SDLK_u)
	{
		col.Red = col.Red + 50;
	}
	if (ac_sdlSym == SDLK_h)
	{
		col.Red = col.Red - 50;
	}

	//color circle a
	if (ac_sdlSym == SDLK_0)
	{
		c.Alpha = c.Alpha + 50;
	}
	if (ac_sdlSym == SDLK_9)
	{
		c.Alpha = c.Alpha - 50;
	}
	if (ac_sdlSym == SDLK_8)
	{
		c.Blue = c.Blue + 50;
	}
	if (ac_sdlSym == SDLK_7)
	{
		c.Blue = c.Blue - 50;
	}
	if (ac_sdlSym == SDLK_6)
	{
		c.Green = c.Green + 50;
	}
	if (ac_sdlSym == SDLK_5)
	{
		c.Green = c.Green - 50;
	}
	if (ac_sdlSym == SDLK_4)
	{
		c.Red = c.Red + 50;
	}
	if (ac_sdlSym == SDLK_4)
	{
		c.Red = c.Red - 50;
	}

	if (ac_sdlSym == SDLK_1)
	{
		

		cout << "2D vector A and B:" << endl; //info
		A.x = 5, A.y = 4; //A = (5,4)
		B.x = -2, B.y = 5; //B = (-2,5)
		A.print2(); //print test
		B.print2(); //print test
		cout << endl; //new line

		cout << "2D vector addition:" << endl; //info
		C = A + B; //C will equal ((A.x + B.x)(A.y + B.y))
		C.print2(); //print C add value
		cout << endl; //new line
		cout << "2D vector subtraction:" << endl; //info

		C = A - B; //C will equal ((A.x - B.x)(A.y - B.y))
		C.print2(); //print C sub value
		cout << endl; //new line
		cout << "2D vector magnitude:" << endl; //info
		cout << "Magnitude of A is: " << A.mag2() << endl; //info and prints out magnitude of vector A
		cout << "Magnitude of B is: " << B.mag2() << endl; //info and prints out magnitude of vector B
		cout << endl; //new line

		cout << "2D vector normalise:" << endl; //info
		cout << "Normalise vector A is: " << A.nor2X() << " " << A.nor2Y() << endl; //info and prints out normalise x and y of vector A
		cout << "Normalise vector B is: " << B.nor2X() << " " << B.nor2Y() << endl; //info and prints out normalise x and y of vector B
		cout << endl; //new line
		cout << "2D vector dot product:" << endl; //info

		C = A * B; //C will equal ((A.x * B.x)(A.y * B.y)) 
		C.dot2(); //This will print out the dot product of C
		cout << endl; //new line

		
		cout << "3D vector D and E:" << endl; //info
		D.x = -7, D.y = 9, D.z = 2; //D = (-7,9,2)
		E.x = 3, E.y = 14, E.z = -3; //E = (3,14,-3)
		D.print3(); //print test
		E.print3(); //print test
		cout << endl; //new line
		cout << "3D vector addition:" << endl; //info

		F = D + E; //F will equal ((D.x + E.x)(D.y + E.y)(D.z + E.z))
		F.print3(); //print F add value
		cout << endl; //new line
		cout << "3D vector subtraction:" << endl; //info

		F = D - E; //F will equal ((D.x - E.x)(D.y - E.y)(D.z - E.z))
		F.print3(); //print F sub value
		cout << endl; //new line
		cout << "3D vector magnitude:" << endl; //info
		cout << "Magnitude of D is: " << D.mag3() << endl; //info and prints out magnitude of vector D
		cout << "Magnitude of E is: " << E.mag3() << endl; //info and prints out magnitude of vector E
		cout << endl; //new line
		cout << "3D vector normalise:" << endl; //info
		cout << "Normalise vector D is: " << D.nor3X() << " " << D.nor3Y() << " " << D.nor3Z() << endl; //info and prints out normalise x, y and z of vector D
		cout << "Normalise vector E is: " << E.nor3X() << " " << E.nor3Y() << " " << E.nor3Z() << endl; //info and prints out normalise x, y and z of vector E
		cout << endl; //new line
		cout << "3D vector dot product:" << endl; //info

		F = D * E; //F will equal ((D.x * E.x)(D.y * E.y)(D.z * E.z)) 
		F.dot3(); //This will print out the dot product of F
		cout << endl; //new line

		cout << "3D vector cross product: " << endl;
		F = D / E;
		F.print3();
		cout << endl;

		system("pause");
	}
}
void GameLoop::OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{
	switch (ac_sdlSym)
	{
	default: break;
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
