========================================================================
    WIN32 APPLICATION : GS2 Project Overview
========================================================================
CODE GRAVEYARD

int dubtrack;
float seekstart = 0.f, seekend = 6.8f;
float theseekstart = 0.f, theseekend = 6.8f;
int soundstage = 0;
SceneNode* tp5;

	//SceneNode* tp1 = SceneGraph().AddChild("terrainpart");
	//pMODEL m1 = ContentManager().LoadXModel("models/background.X", true, false);  //TODO: Should be true
	//tp1->SetModel(m1);

	/*SceneNode* tp2 = SceneGraph().AddChild("terrainpart");
	pMODEL m2 = ContentManager().LoadXModel("models/tree layer 2.X", false, false);  //TODO: Should be true
	ContentManager().LoadDiffuse(m2, 0, "models/trees.tga");
	tp2->SetModel(m2);

	SceneNode* tp3 = SceneGraph().AddChild("terrainpart");
	pMODEL m3 = ContentManager().LoadXModel("models/tree layer 1.X", false, false);  //TODO: Should be true
	ContentManager().LoadDiffuse(m3, 0, "models/trees.tga");
	tp3->SetModel(m3);*/

	//SceneNode* tp4 = SceneGraph().AddChild("terrainpart");
	//pMODEL m4 = ContentManager().LoadXModel("models/road markings.X", false, false); //TODO: Should be true
	//ContentManager().LoadDiffuse(m4, 0, "models/road markings.tga");
	//tp4->SetModel(m4);

	/*tp5 = SceneGraph().AddChild("blimp");
	pMODEL m5 = ContentManager().LoadXModel("models/blimp.X", false, false); //TODO: Should be true
	ContentManager().LoadDiffuse(m5, 0, "models/blimpmap.jpg");
	ContentManager().LoadNormal(m5, 0, "models/blimpmap_normal.jpg");
	tp5->SetModel(m5);*/


	/*tp1->Translate(0, -100, 0);
	tp1->SetScale(0.1, 0.1, 0.1);

	tp2->Translate(0, -100, 0);
	tp2->SetScale(0.1, 0.1, 0.1);

	tp3->Translate(0, -100, 0);
	tp3->SetScale(0.1, 0.1, 0.1);*/

	//tp4->Translate(0, -100, 0);
	//tp4->SetScale(0.1, 0.1, 0.1);

	//tp5->Translate(0, -100, 0);
	//tp5->SetScale(0.1, 0.1, 0.1);

		//Create Skybox
	//RenderSystem().InitSkybox("models/skybox2.X");
	//ContentManager().SetTexture(RenderSystem().GetSkybox(), 0, CreateCellular2CTexture(RenderSystem().GetDevice(), Rule2C(109), 1, 512, qRandFloat(0.f, 1.f), qRandFloat(0.f, 1.f), qRandFloat(-0.4f, 0.4f)));
	//ContentManager().SetTexture(RenderSystem().GetSkybox(), 1, CreateCellular3CTextureNoise(RenderSystem().GetDevice(), Rule3C(qRand(0, 2187)), 3, 32, qRandFloat(0.000f, 1.000f), qRandFloat(0.000f, 1.000f), qRandFloat(-0.400f, 0.400f), qRandFloat(0.000f, 0.500f)));

	//Add a prop entity
	//PropEntity* m_prop = new PropEntity;
	//m_prop->Init("box", "models/cube.X", Vector3(5, -10, 10), 1.0f);
	//m_entities.push_back(m_prop);


		//what cars are avalible
	/*std::vector<std::string> m_vehs;
	m_vehiclecontroller->GetAvalibleVehicles(&m_vehs);

	for(std::vector<std::string>::iterator iter = m_vehs.begin(); iter != m_vehs.end(); ++iter)
	{
		MessageBox(0, iter->c_str(), "", MB_OK | MB_TOPMOST);
	}*/

	//Load Sound
	//dubtrack = SoundSystem().LoadPCM("data/sounds/track.pcm");
	//SoundSystem().SetLooping(dubtrack, true);
	//SoundSystem().PlaySound(dubtrack);


		//TEST Sound Sequencer
	/*if(soundstage == 2)
	{
		if(m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetSpeedKPH() < 350.f)
		{
			seekstart = 0.f;
			seekend = 6.8f;
			soundstage = 0;
		}
		else
		{
			if(m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetSpeedKPH() < 580.f)
			{
				seekstart = 6.8f;
				seekend = 20.57f;
				soundstage = 1;
			}
		}
	}

	if(soundstage == 1)
	{
		if(m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetSpeedKPH() < 350.f)
		{
			seekstart = 0.f;
			seekend = 6.8f;
			soundstage = 0;
		}

		if(m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetSpeedKPH() >= 580.f)
		{
			seekstart = 20.57f;
			seekend = 34.28f;
			soundstage = 2;
		}
	}

	if(soundstage == 0)
	{
		if(m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetSpeedKPH() >= 580.f)
		{
			seekstart = 20.57f;
			seekend = 34.28f;
			soundstage = 2;
		}
		else
		{
			if(m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetSpeedKPH() >= 350.f)
			{
				seekstart = 6.8f;
				seekend = 20.57f;
				soundstage = 1;
			}
		}
	}

	if(SoundSystem().GetSeekSeconds(dubtrack) >= theseekend)
	{
		theseekstart = seekstart;
		theseekend = seekend;
		SoundSystem().SetSeekSeconds(dubtrack, theseekstart);
	}*/

		
		
	//Code Speed Testing
	/*if(GetAsyncKeyState(VK_END)&1)
	{
		CStopWatch sw;
		sw.startTimer();

		for(int i = 0; i < 30000; i++)
		{
			float x = math::fsqrt(qRand(10, 20));
		}

		sw.stopTimer();
			
		char lol[256];
		sprintf(lol, "%f", sw.getElapsedTime());
		MessageBox(0, lol, "", 0);
	}*/