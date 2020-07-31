#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <random>


olc::vf2d gravity;

int range_randomInt(int high){
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, high);
	return distribution(generator);
}

int range_randomInt(int low, int high){
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(low, high);
	return distribution(generator);
}

//struct Particle{
//
//	olc::vf2d pos, vel, acc;
//	bool firework;
//	int lifespan = 255;
//	int hu;
//
//	Particle(){
//		pos.x = 0.0f;
//		pos.y = 0.0f;
//		vel.x = 0.0f;
//		vel.y = 0.0f;
//		acc.x = 0.0f;
//		acc.y = 0.0f;
//		firework = false;
//	}
//
//	Particle(float x_, float y_, bool fire, int h){
//		firework = fire;
//		hu = h;
//		pos.x = x_;
//		pos.y = y_;
//
//		if(firework){
//			vel.x = (float)range_randomInt(-10, 10);
//			vel.y = (float)range_randomInt(-25, -8);
//		} else{
//			vel.x = (float)range_randomInt(0, 360);
//			vel.y = (float)range_randomInt(0, 360);
//		}
//
//		acc.x = 0.0f;
//		acc.y = 0.0f;
//	}
//
//	Particle(olc::vf2d position , bool fire, int h){
//		firework = fire;
//		hu = h;
//		pos = position;
//
//		if(firework){
//			vel.x = (float)range_randomInt(-10, 10);
//			vel.y = (float)range_randomInt(-25, -8);
//		} else{
//			vel.x = (float)range_randomInt(0, 360);
//			vel.y = (float)range_randomInt(0, 360);
//		}
//
//		acc.x = 0.0f;
//		acc.y = 0.0f;
//	}
//
//	void ApplyForce(olc::vf2d force){ acc += force; }
//
//	void Update(){
//		vel += acc;
//		if(!firework){
//			vel *= 0.95f;
//			lifespan -= 4;
//		}
//		pos += vel;
//		acc *= 0.0f;
//	}
//	
//	void SetVelocity(olc::vf2d velocity){ vel = velocity; }
//
//	bool isDone(){ return lifespan < 0;	}
//
//};
//
//struct Firework{
//
//	Particle *firework;
//	bool exploded;
//	std::vector<Particle *> parts;
//	int hu;
//	int width, height;
//	olc::PixelGameEngine * gfx;
//	int deadCount = 0;
//
//	Firework(){
//		width = 256;
//		height = 240;
//		gfx = nullptr;
//		hu = std::rand() % 255;
//		firework = new Particle((float)range_randomInt(width), height, true, hu);
//		exploded = false;
//		parts.reserve(100);
//	}
//
//	Firework(int screenWidth, int screenHeight, olc::PixelGameEngine* engine){
//		width = screenHeight;
//		height = screenWidth;
//		gfx = engine;
//		hu = std::rand() % 255;
//		firework = new Particle((float)range_randomInt(width), height, true, hu);
//		exploded = false;
//		parts.reserve(100);
//	}
//
//	~Firework(){
//		for(unsigned int i = 0; i < parts.size(); i++){
//			delete parts[i];
//		}
//		delete firework;
//	}
//
//	void operator = (const Firework& rhs){
//		width = rhs.width;
//		height = rhs.height;
//		gfx = rhs.gfx;
//		hu = rhs.hu;
//		firework = rhs.firework;
//		exploded = rhs.exploded;
//		parts = rhs.parts;
//	}
//
//
//
//	void Explode(){
//		for(unsigned int i = 0; i < parts.size(); i++)
//			parts.push_back(new Particle(firework->pos, false, hu));
//	}
//
//	void Update(){
//		if(!exploded){
//			firework->ApplyForce(gravity);
//			firework->Update();
//			
//			if(firework->vel.y >= 0){
//				exploded = true;
//				Explode();
//			}
//		}
//
//		for(unsigned int i = 0; i < parts.size(); i++){
//			if(parts[i] != nullptr){
//				parts[i]->ApplyForce(gravity);
//				parts[i]->Update();
//				if(parts[i]->isDone())
//					deadCount++;
//			}
//		}
//	}
//
//	void Show(){
//		if(!exploded){
//			gfx->FillCircle(firework->pos, 2);
//		}
//
//		for(unsigned int i = 0; i < parts.size(); i++){
//			if(parts[i] != nullptr && !parts[i]->isDone()){
//				gfx->FillCircle(parts[i]->pos, 1);
//			}
//		}
//	}
//
//	bool isDone(){
//		return(exploded && (deadCount == parts.size()));
//	}
//
//
//};

struct Particle{
	olc::vi2d pos, vel, acc;
};

// Override base class with your custom functionality
class Fireworks : public olc::PixelGameEngine{
public:
	Particle firework;
	olc::vi2d gravity = {0, 20};
	float targetFrameTime = 1.00f / 60.0f;
	float accumulatedTime = 0.00f;

public:
	Fireworks(){
		// Name you application
		sAppName = "Fireworks";
	}

public:
	bool OnUserCreate() override{
		// Called once at the start, so create things here
		firework.pos.x = ScreenWidth() / 2;
		firework.pos.y = ScreenHeight();
		firework.vel.y = -500;
		return true;
	}

	void DrawParticle(Particle& part){
		FillCircle(part.pos, 10, olc::RED);
	}

	void UpdateParticle(Particle& part, float fElapsedTime){
		part.acc += gravity;
		part.vel += part.acc * fElapsedTime;
		part.pos += part.vel * fElapsedTime;

		part.acc *= 0;
	}

	bool OnUserUpdate(float fElapsedTime) override{
		//Clear(olc::Pixel(0, 0, 0, 25));
		Clear(olc::BLACK);
		UpdateParticle(firework, fElapsedTime);
		DrawParticle(firework);



		return true;
	}
};

int main(){
	Fireworks demo;
	if(demo.Construct(400, 300, 2, 2, false, true))
		demo.Start();
	return 0;
}