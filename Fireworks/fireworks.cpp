#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <random>


olc::vf2d gravity;

int range_randomInt(int low, int high){
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(low, high);
	return distribution(generator);
}

struct Particle{

	olc::vf2d pos, vel, acc;
	bool firework;
	int lifespan = 255;
		int hu;

	Particle(){
		pos.x = 0.0f;
		pos.y = 0.0f;
		vel.x = 0.0f;
		vel.y = 0.0f;
		acc.x = 0.0f;
		acc.y = 0.0f;
		firework = false;
	}

	Particle(float x, float y, bool fire, int h){
		firework = fire;
		hu = h;

		if(firework){
			vel.x = (float)range_randomInt(-10, 10);
			vel.y = (float)range_randomInt(-25, -8);
		} else{
			vel.x = (float)range_randomInt(0, 360);
			vel.y = (float)range_randomInt(0, 360);
		}

		acc.x = 0.0f;
		acc.y = 0.0f;
	}

	void ApplyForce(olc::vf2d force){ acc += force; }

	void Update(){
		vel += acc;
		if(!firework){
			vel *= 0.95f;
			lifespan -= 4;
		}
		pos += vel;
		acc *= 0.0f;
	}
	
	void SetVelocity(olc::vf2d velocity){ vel = velocity; }

	bool isDone(){ return lifespan < 0;	}

};

struct Firework{

	Particle firework;
	bool exploded;
	std::vector<Particle> parts;
	int hu;

	Firework(){
		hu = std::rand() % 255;
		firework = new Particle()
	}
};

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine{
public:
	Example(){
		// Name you application
		sAppName = "Fireworks";
	}

public:
	bool OnUserCreate() override{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override{
		// called once per frame, draws random coloured pixels
		for(int x = 0; x < ScreenWidth(); x++)
			for(int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}
};

int main(){
	Example demo;
	if(demo.Construct(400, 300, 1, 1))
		demo.Start();
	return 0;
}