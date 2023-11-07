@page SourceCode-Simulator Source Code: Simulator
@brief Some reconstructed Spore source code for the Simulator namespace

@tableofcontents

@section SourceCode-Simulator-cSolarSystem Simulator::cSolarSystem

@subsection SourceCode-Simulator-cSolarSystem-GenerateCelestialBodiesEffects cSolarSystem::GenerateCelestialBodiesEffects()

Code for Simulator::cSolarSystem::GenerateCelestialBodiesEffects()

```cpp
void cSolarSystem::GenerateCelestialBodiesEffects(bool create, float scale)
{
	if (create)
	{
		IEffectWorldPtr effectWorld = SpaceGfx.field_9C;
		if (GetCurrentContext() == SpaceContext::SolarSystem) 
		{
			effectWorld = SpaceGfx.field_94;
			for (auto& obj : mCelestialBodies)
			{
				if (!obj->mpEffect && obj->mType == cCelestialBodyType::Comet)
				{
					obj->mpEffect = nullptr;
					if (effectWorld->CreateEffect(0x3D6F8D8, 0, obj->mpEffect)) {
						obj->mpEffect->Start(0);
					}
				}
			}
		}
		if (mpOwnerStar->IsBinaryStar()) 
		{
			CreateStarEffect(mpStar1->mpEffect, effectWorld.get(), mpOwnerStar->mPrimaryType);
			Transform transform = mpStar1->mpEffect->GetTransform();
			transform.SetScale(scale);
			mpStar1->mpEffect->SetTransform(transform);

			CreateStarEffect(mpStar2->mpEffect, effectWorld.get(), mpOwnerStar->mSecondaryType);
			transform = mpStar2->mpEffect->GetTransform();
			transform.SetScale(scale);
			mpStar1->mpEffect->SetTransform(transform);
		}
		else
		{
			CreateStarEffect(mpStar1->mpEffect, effectWorld.get(), mpOwnerStar->GetStarType());
			Transform transform = mpStar1->mpEffect->GetTransform();
			transform.SetScale(scale);
			mpStar1->mpEffect->SetTransform(transform);
		}
	}
	else
	{
		for (auto& obj : mCelestialBodies) 
		{
			if (obj->mpEffect) 
			{
				obj->mpEffect->Stop();
				obj->mpEffect = nullptr;
			}
		}
	}
}
```

@subsection SourceCode-Simulator-cSolarSystem-Load cSolarSystem::Load()

Code for Simulator::cSolarSystem::Load()

```cpp
void Simulator::cSolarSystem::Load(cStar* pStar)
{
	mpOwnerStar = pStar;
	if (pStar->IsBinaryStar())
	{
		LoadBinaryStar();
	}
	else
	{
		mpStar1 = new cCelestialBody(cCelestialBodyType::Star);
		mCelestialBodies.push_back(mpStar1);
		mpStar1->mOrbit.mbNullOrbit = 1;
		mpStar1->mPosition = Vector3::ZERO;
		mpStar1->mfRotationRate = GetSolarStarRotationRate(pStar->GetStarType());
		mpStar1->mName = pStar->GetName();
		mpStar1->mfHitSphereSize = GetSolarStarRadius(pStar->GetStarType());
	}

	if (pStar->IsStarOrBinaryStar())
	{
		LoadAsteroids();
	}

	auto starType = pStar->GetStarType();
	auto radiusCache = GetPrecalculatedSolarStarRadius();
	if (radiusCache[(int)starType] == 0.0f)
	{
		radiusCache[(int)starType] = pStar->IsBinaryStar() ? 
			GetBinarySystemBaseRadius(starType) : 
			GetSolarStarRadius(starType);
	}
	float temperature = GetSolarStarTemperature(starType);
	float orbitRadius1 = radiusCache[(int)starType] + temperature * 85.0f;
	float orbitRadius2 = radiusCache[(int)starType] + temperature * 195.0f;

	for (auto& planetRecord : pStar->mpStarRecord->GetPlanetRecords())
	{
		cPlanetPtr planet;
		StarManager.RecordToPlanet(planetRecord.get(), planet);
		if (planet)
		{
			mPlanets.push_back(planet);
			float perihelion = cPlanetRecord::GetPerihelion(planetRecord.get(), MoonPerihelionType::Parent);
			if (perihelion < orbitRadius1) {
				planet->mFlags |= kPlanetFlagRedOrbit;
			}
			if (perihelion > orbitRadius2) {
				planet->mFlags |= kPlanetFlagBlueOrbit;
			}
		}
	}
}
```